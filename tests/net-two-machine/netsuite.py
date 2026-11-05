#!/usr/bin/env python3
"""Two-machine online checks (issue #106), driven from the machine that holds this checkout.

Both machines are the owner's, on one network. This side runs a peer and drives the other's over
ssh; the other machine needs nothing checked out, only the game files, a peer binary and the two
shared libraries that binary needs, which `prepare` copies into its $HOME. The two run different
distributions, so a binary built here may not run there at all: `prepare` checks that, and names
the library that is missing when it does not.

`netctl` is a headless online peer: real sockets, the real battle, no window and no GPU. It
prints one JSON line per run with the rollback, desync and round-over counters and `"slots"`, the
per-seat verdict `battle.slot_is_cpu` gives (`H` a player drives it, `C` the CPU does). That is
online step 8's own evidence — two machines agreeing — and nothing about the original, which has
no netplay to compare with.

    netsuite.py prepare     --remote USER@HOST   copy netctl and its libraries over, check it runs
    netsuite.py robustness  --remote USER@HOST   two machines in one headless room, ideal and bad
    netsuite.py interactive --remote USER@HOST   the game on both screens, for what only a person
                                                 can see (docs/NET-TWO-MACHINE.md)

`robustness` has to know which machine hosts the room, and a host that cannot be reached is a
failure rather than a mystery, so `--host` is required. This machine's own firewall may drop
inbound UDP, in which case only the other machine can host (docs/NET-TWO-MACHINE.md).

Exit codes: 0 every check passed, 1 a check failed, 2 the setup is not ready, 3 a machine could
not be reached.
"""
import argparse
import json
import os
import re
import socket
import subprocess
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.abspath(os.path.join(HERE, "..", ".."))
OUT = os.path.join(REPO, "build", "net-two-machine")
# The two shared libraries a binary built here is not guaranteed to find on the other machine, and
# the ones a package ships for the same reason (CMakeLists.txt's install rules): wgpu-native comes
# from the fetched release and has no business being installed anywhere, and SDL3 may be absent.
SHIPPED_LIBS = ("libwgpu_native.so", "libSDL3.so.0")
# data/ beside a packaged executable (main.cpp's "beside the package") and a game folder as
# GAME_DIR: together they cover both routes the port reads its game files through.
GAME_DIR_VAR = "GAME_DIR"
DEFAULT_PORT = 37564      # frontend_settings.h's netPort: the port the game binds for a room
PEER_DEADLINE = 240       # netctl's own deadline is ticks/60 + 120 s
# Remote shape: ~/daybreak-net/{bin/, lib/, data/, <the packaged game>, config/}.


def result_of(out):
    """GekkoNet prints notices of its own, so the result is the last JSON line."""
    lines = [line for line in out.splitlines() if line.startswith("{")]
    if not lines:
        raise RuntimeError("no result line in:\n" + out[-600:])
    return json.loads(lines[-1])


class Remote:
    """The other machine, as a shell over ssh."""

    def __init__(self, target):
        self.target = target
        self.home = self.run("echo $HOME").stdout.strip()
        self.dir = self.home + "/daybreak-net"
        self.netctl = self.dir + "/bin/netctl"
        self.lib = self.dir + "/lib"
        # The game files are the owner's installed copy, never packaged: they go in a folder of
        # their own and reach both binaries through GAME_DIR.
        self.data = self.dir + "/data"
        self.config = self.dir + "/config"

    def environment(self):
        """LD_LIBRARY_PATH rather than a patched rpath: the copied libraries sit beside, not in,
        the binary's own directory, and nothing here rewrites a binary we might want to compare."""
        return "env {}={} LD_LIBRARY_PATH={}".format(GAME_DIR_VAR, self.data, self.lib)

    def peer(self, arguments):
        """A command that runs a peer against the copied game files."""
        return "{} {} {}".format(self.environment(), self.netctl, arguments)

    def runs(self, command, timeout=60):
        """True when `command` exits 0 there, with the libraries and the game files in place."""
        return self.run(self.environment() + " " + command, timeout).returncode == 0

    def starts(self, binary, timeout=60):
        """True when `binary` runs there: it prints the product's usage, which it exits 1 for.

        `netctl --help` exits 0, but the game exits 1 for its usage, so its start cannot be told
        by the exit code. A missing library never prints `usage:`, which is what separates the two.
        """
        out = self.run(self.environment() + " " + binary + " --help 2>&1", timeout).stdout
        return "usage: daybreak" in out

    def run(self, command, timeout=PEER_DEADLINE):
        return subprocess.run(["ssh", self.target, command], capture_output=True, text=True,
                              timeout=timeout)

    def spawn(self, command):
        """A peer on the other machine, kept running while its output is read."""
        return subprocess.Popen(["ssh", self.target, command], stdout=subprocess.PIPE,
                                stderr=subprocess.PIPE, text=True)

    def copy(self, name, dest_dir):
        """`tar | ssh tar`: no rsync, no second checkout, nothing version-specific.

        `-h` follows symlinks, because a library copied by its SONAME is a link to the versioned
        file and a link on its own resolves to nothing there.
        """
        self.run("mkdir -p " + dest_dir, timeout=30)
        sent = subprocess.run(
            "tar -C {src} -chf - {name} | ssh {target} 'tar -C {dst} -xf -'".format(
                src=os.path.dirname(name), name=os.path.basename(name), target=self.target,
                dst=dest_dir),
            shell=True, capture_output=True, text=True)
        if sent.returncode != 0:
            fail(3, "copying {}: {}".format(name, sent.stderr.strip()))


def fail(code, message):
    print(message)
    raise SystemExit(code)


def local_address():
    """This machine's address on the network the other machine is on, without sending traffic."""
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as probe:
        probe.connect(("192.0.2.1", 9))     # TEST-NET-1: picks the route, sends nothing
        return probe.getsockname()[0]


def remote_address(machine):
    """The other machine's address on the network we reach it over, discovered not assumed.

    `hostname -I` lists every address, bridges and containers included, and the first is not
    always the one that reaches us. Asking the kernel which local address it uses to send to the
    ssh target is, and costs a connected UDP socket that sends nothing.
    """
    host = machine.target.rsplit("@", 1)[-1]
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as probe:
        probe.connect((host, 9))
        ours = probe.getsockname()
    line = machine.run("ip -4 route get {} 2>/dev/null | head -1".format(ours[0]), timeout=30).stdout
    found = re.search(r"\bsrc (\d+\.\d+\.\d+\.\d+)", line)
    if not found:
        # No `ip` command there: whatever address answers as the source for our /24 is enough for
        # a peer on the same network, and the host echoes its private address anyway.
        return socket.gethostbyname(host)
    return found.group(1)


def free_port():
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as probe:
        probe.bind(("0.0.0.0", 0))
        return probe.getsockname()[1]


def version():
    with open(os.path.join(REPO, "VERSION")) as handle:
        return handle.read().strip()


def game_tree():
    """The packaged tree of this checkout's VERSION, if one was built: the shape a release ships.

    A tree of any other version is a stale one, and copying it would put a different build on the
    other machine's screen than the one under test.
    """
    candidate = os.path.join(REPO, "build", "package", "daybreak-{}-linux-x86_64".format(version()))
    return candidate if os.path.isdir(candidate) else None


def shipped_libraries(binary):
    """The libraries `binary` loads from SHIPPED_LIBS: name -> path, from its own `ldd`."""
    out = subprocess.run(["ldd", binary], capture_output=True, text=True).stdout
    libraries = {}
    for line in out.splitlines():
        parts = line.split()
        if len(parts) >= 3 and parts[1] == "=>" and parts[0] in SHIPPED_LIBS:
            libraries[parts[0]] = parts[2]
    return libraries


# -- prepare ------------------------------------------------------------------------------

def prepare(remote, rebuild):
    """Copy the headless peer and the shared libraries it needs, prove they run there, and compare
    the arithmetic the two machines compute.

    The game tree is optional and only matters for the interactive step: `netctl` reads the game
    files through GAME_DIR and needs nothing beside it, so the robustness run must not depend on a
    release package having been built here (building one reconfigures this build tree).
    """
    netctl = os.path.join(REPO, "build", "linux", "netctl")
    math_fingerprint = os.path.join(REPO, "build", "linux", "math_fingerprint")
    if rebuild or not os.path.exists(netctl) or not os.path.exists(math_fingerprint):
        print("[prepare] building netctl and math_fingerprint", flush=True)
        built = subprocess.run(["cmake", "--build", "build/linux", "--target", "netctl",
                                "math_fingerprint"], cwd=REPO, capture_output=True, text=True)
        if built.returncode != 0:
            fail(2, built.stderr[-1500:])
    machine = Remote(remote)
    if machine.run("echo ok", timeout=30).returncode != 0:
        fail(3, "cannot reach " + remote + " over ssh")

    machine.copy(netctl, machine.dir + "/bin")
    libraries = shipped_libraries(netctl)
    missing = sorted(set(SHIPPED_LIBS) - set(libraries))
    if missing:
        fail(2, "netctl's ldd does not resolve {} — it cannot be copied beside it".format(
            ", ".join(missing)))
    machine.run("mkdir -p " + machine.lib, timeout=30)
    for name, path in sorted(libraries.items()):
        machine.copy(path, machine.lib)
    print("[prepare] shipped netctl + " + ", ".join(sorted(libraries)), flush=True)

    remote_data = [line.split()[-1] for line in
                   machine.run("ls {} 2>/dev/null".format(machine.data), timeout=30).stdout.splitlines()]
    local_data = sorted(name for name in os.listdir(os.path.join(REPO, "Higurashi-Daybreak"))
                        if name.startswith("daybreak") and name.endswith(".dat"))
    if not remote_data:
        print("[prepare] no game files in {}: netctl needs them, so copy them there before a "
              "robustness run".format(machine.data))
    elif sorted(remote_data) != local_data:
        print("[prepare] game files there differ from this machine's: {} vs {}".format(
            " ".join(sorted(remote_data)), " ".join(local_data)))
    else:
        print("[prepare] game files: " + " ".join(local_data), flush=True)

    if not machine.runs(machine.netctl + " --help >/dev/null"):
        check = machine.run(machine.environment() + " ldd " + machine.netctl, timeout=60)
        fail(2, "netctl does not start there. `ldd` says:\n" + check.stdout[-1200:])

    # Two peers must compute the same floats. The C runtime is one way they can differ, and the CPU
    # model is another: SSE's rsqrtss and rcpps return a per-model estimate, which desynced the room
    # on almost every frame at frame 181 before the core stopped using them (issue #107).
    # math_fingerprint prints one digest per kind of math and needs no game files, so it and this
    # comparison are the cheap proof, on the real pair, that the two machines agree.
    machine.copy(math_fingerprint, machine.dir + "/bin")
    here = subprocess.run([math_fingerprint], capture_output=True, text=True, timeout=120)
    there = machine.run(machine.dir + "/bin/math_fingerprint", timeout=120)
    if there.returncode != 0:
        print("[prepare] math_fingerprint does not run on the other machine; the arithmetic the "
              "two peers use has not been compared")
    elif there.stdout == here.stdout:
        print("[prepare] arithmetic: the two machines compute every kind of math identically",
              flush=True)
    else:
        only_here = set(here.stdout.splitlines()) - set(there.stdout.splitlines())
        only_there = set(there.stdout.splitlines()) - set(here.stdout.splitlines())
        print("[prepare] the two machines compute different arithmetic, so a match between them "
              "would desync. This machine only:\n  " + "\n  ".join(sorted(only_here)) +
              "\nthe other machine only:\n  " + "\n  ".join(sorted(only_there)))

    tree = game_tree()
    if tree:
        machine.copy(tree, machine.dir)          # -> ~/daybreak-net/<packaged tree>
        print("[prepare] game tree: " + os.path.basename(tree), flush=True)
        game = os.path.join(machine.dir, os.path.basename(tree), "daybreak-bin")
        if not machine.starts(game):
            check = machine.run(machine.environment() + " ldd " + game, timeout=60)
            print("[prepare] the packaged game does not start there. `ldd` says:\n" +
                  check.stdout[-1200:])
            return 2
        print("[prepare] ready: netctl and the game both run on the other machine")
        return 0
    print("[prepare] ready for the headless run: netctl runs on the other machine.\n"
          "[prepare] the interactive step is not set up: there is no packaged game tree here for "
          "this version (build/package/daybreak-{}-linux-x86_64), and staging one needs a build "
          "tree configured as a release, which this one is not. See docs/NET-TWO-MACHINE.md."
          .format(version()))
    return 0


# -- robustness: two machines, one headless room ------------------------------------------

def run_room(machine, peers, ticks, seed, time_limit=None, proxy_args=None, host_side="local",
             loopback=False):
    """One room of `peers` players: one side on this machine, every other peer on the other.

    `loopback` puts the whole room on this machine instead, which is all a proxied room can be:
    a peer told `--proxy` sends every packet to the proxy and trusts the 6-byte prefix it comes
    back with, so every peer of a room must share one proxy, and `tools/net_proxy.py` binds to
    loopback (measured: a proxied joiner never reaches a direct host). The delay and loss profile
    therefore stays a one-machine rehearsal, and what crosses the network is measured on the ideal
    profile. It is still a real rollback run: the proxy's loss and delay are what make the peers
    predict and roll back (`tests/net_play_check.py` measures the same way).
    """
    out = os.path.join(OUT, "robustness-" + time.strftime("%Y%m%d-%H%M%S"))
    os.makedirs(out, exist_ok=True)
    port = free_port()
    host_here = host_side == "local"
    # The joiners are told the host's address on the network the two share: loopback when the
    # whole room is here, otherwise the host's LAN address, discovered rather than assumed.
    room = "127.0.0.1" if loopback else (remote_address(machine) if not host_here
                                          else local_address())
    common = "--ticks {} --seed {}".format(ticks, seed)
    if time_limit:
        common += " --time-limit {}".format(time_limit)
    local_netctl = os.path.join(REPO, "build", "linux", "netctl")
    local_env = dict(os.environ, GAME_DIR=os.path.join(REPO, "Higurashi-Daybreak"))

    def start(arguments, here):
        """Start a peer here, or on the other machine through ssh.

        `loopback` keeps every peer on this machine but starts the other side's through a shell,
        the way ssh would run it, so a quoting mistake shows up without the network.
        """
        if here:
            return subprocess.Popen([local_netctl] + arguments.split(), stdout=subprocess.PIPE,
                                    stderr=subprocess.PIPE, text=True, env=local_env)
        if loopback:
            return subprocess.Popen(["sh", "-c", local_netctl + " " + arguments],
                                    stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True,
                                    env=local_env)
        return machine.spawn(machine.peer(arguments))

    proxy = None
    proxy_args_all = ""
    if proxy_args:
        proxy_port = free_port()
        proxy = subprocess.Popen([sys.executable, os.path.join(REPO, "tools", "net_proxy.py"),
                                  "--port", str(proxy_port)] + proxy_args.split())
        proxy_args_all = " --proxy 127.0.0.1:{}".format(proxy_port)
        time.sleep(0.5)

    def log_path(here, name):
        """Where a peer writes its `frame hash` log: this run's folder, or the other machine."""
        return os.path.join(out if here or loopback else machine.dir, name + ".log")

    def fetch(here, name):
        """Bring a log the other machine wrote into this run's folder, leaving nothing behind."""
        if here or loopback:
            return
        path = log_path(here, name)
        written = machine.run("cat " + path, timeout=60).stdout
        with open(os.path.join(out, name + ".log"), "w") as handle:
            handle.write(written)
        machine.run("rm -f " + path, timeout=30)

    host = start("--host {} --peers {} {}{} --log {}".format(
        port, peers, common, proxy_args_all, log_path(host_here, "host")), host_here)
    time.sleep(1.0)     # the host binds before anyone knocks
    guests = []
    try:
        for i in range(1, peers):
            # The side that is not the host joins, every joiner the same way.
            here = not host_here or loopback
            guests.append(start("--join {}:{} {}{} --log {}".format(
                room, port, common, proxy_args_all, log_path(here, "guest{}".format(i))), here))
            time.sleep(0.5)
        results = {}
        text, err = communicate(host)
        try:
            results["host"] = result_of(text)
        except RuntimeError:
            # A peer that never reports is a failed check, not a crashed suite: say what to look
            # at and let the caller count it as one.
            print("the host reported nothing ({}). The joiners must reach the host at {}:{}; "
                  "ssh working says nothing about UDP, so check that machine's firewall (allow "
                  "udp/{}) and that both are on the same network.{}".format(
                      err.strip() or "no stderr", room, port, port,
                      "\nThis machine's firewall drops inbound UDP, so it cannot host: --host "
                      "remote." if host_here else ""))
            return {}, out
        for i, guest in enumerate(guests, 1):
            text, err = communicate(guest)
            try:
                results["guest{}".format(i)] = result_of(text)
            except RuntimeError as error:
                print("guest{}: {} {}".format(i, error, err[-300:]))
        for name in results:
            fetch((name == "host") == host_here, name)
    finally:
        for process in [host] + guests:
            if process.poll() is None:
                process.kill()
                process.wait()
        if proxy:
            proxy.kill()
            proxy.wait()
        # An ssh killed mid-run leaves its peer running on the other machine, holding the port and
        # skewing the next profile, so nothing this suite may have started there survives it.
        if not loopback:
            machine.run("pkill -f 'daybreak-net/bin/netctl' >/dev/null 2>&1; true", timeout=30)
    return results, out


def communicate(process):
    return process.communicate(timeout=PEER_DEADLINE)


def compare_logs(directory, peers):
    """Frame-by-frame agreement over the logs the peers kept, as tests/net_play_check.py does."""
    logs = []
    for i in range(peers):
        path = os.path.join(directory, "host.log" if i == 0 else "guest{}.log".format(i))
        if not os.path.exists(path):
            return None
        with open(path) as handle:
            entries = {}
            for line in handle:
                parts = line.split()
                if len(parts) == 2:
                    entries[int(parts[0])] = parts[1]
            logs.append(entries)
    if any(len(log) < 100 for log in logs):
        return None
    common = set(logs[0])
    for log in logs[1:]:
        common &= set(log)
    disagree = [frame for frame in sorted(common) if len({log[frame] for log in logs}) > 1]
    return len(common), disagree[:5]


def robustness(remote, peers, ticks, time_limit, host_side, rehearsal):
    machine = Remote(remote)
    if not (rehearsal or machine.runs(machine.netctl + " --help >/dev/null")):
        fail(2, "netctl does not run on the other machine: netsuite.py prepare --remote " + remote)
    checks, failures = 0, []
    where = ("this machine" if host_side == "local" else "the other machine")
    print("[robustness] hosting: {}{}".format(
        where, " (rehearsal: every peer runs here, the other side through a shell)" if rehearsal
        else ""))

    def check(condition, what):
        nonlocal checks
        checks += 1
        print(("ok   " if condition else "FAIL ") + what)
        if not condition:
            failures.append(what)

    # The bad network cannot cross machines (see run_room), so it is the loopback room in both
    # runs, and only the ideal profile is asked to prove what two machines do over a real network.
    profiles = [("ideal network", None, False),
                ("10% loss, 80 ms delay, 5 ms jitter", "--delay-ms 80 --jitter-ms 5 --loss 0.10 "
                 "--seed 3", True)]
    for label, proxy, loopback in profiles:
        shown = label if not loopback else label + " (both ends here through the proxy)"
        results, directory = run_room(machine, peers, ticks, 11 + peers, time_limit, proxy,
                                      host_side, loopback or rehearsal)
        print("[robustness] {}: {}".format(shown, ", ".join(
            "{} frames={} rollbacks={} desyncs={} slots={}".format(name, r["frames"], r["rollbacks"],
                                                                  r["desyncs"], r["slots"])
            for name, r in results.items())))
        print("[robustness] logs in " + directory)
        check(len(results) == peers, label + ": every peer reported")
        if len(results) != peers:
            check(False, label + ": the room could not be measured")
            continue
        check(all(r["desyncs"] == 0 for r in results.values()), label + ": no desyncs")
        check(len({r["round_over"] for r in results.values()}) == 1,
              label + ": one round, one end frame on both machines")
        check(all(r["slots"].count("H") == peers for r in results.values()),
              label + ": every seat a peer plays is HUMAN on every machine")
        compared = compare_logs(directory, peers)
        check(compared is not None and not compared[1],
              label + ": the logs agree frame by frame" +
              (" ({} frames, first disagreement at {})".format(compared[0], compared[1][0])
               if compared and compared[1] else ""))
    print("\nnet-two-machine: {}/{} checks passed".format(checks - len(failures), checks))
    return 0 if not failures else 1


# -- interactive --------------------------------------------------------------------------

def interactive(remote, host_side):
    """Sets the room up on both screens; what to look at is docs/NET-TWO-MACHINE.md."""
    machine = Remote(remote)
    tree = game_tree()
    if not tree:
        print("[interactive] no packaged game tree here (build/package/daybreak-{}-linux-x86_64): "
              "run the game on each machine yourself, from a build of this checkout.".format(version()))
    else:
        machine.copy(tree, machine.dir)
        print("[interactive] copied {} to the other machine".format(os.path.basename(tree)))
    there = os.path.join(machine.dir, os.path.basename(tree or "daybreak-<version>-linux-x86_64"))
    display = machine.run("echo $WAYLAND_DISPLAY $DISPLAY", timeout=30).stdout.strip()
    if not display:
        fail(2, "the other machine reports no display over ssh, so nothing here can open there. "
                "Start the game from that machine's own session, with the paths printed below.")
    # Settings are ours, not the original's, and the XDG base directory spec lets each side pin its
    # own file, so this suite never touches anyone's real settings.conf. Neither is written here:
    # the game creates it on its first run, and pointing XDG_CONFIG_HOME at a folder that does not
    # exist yet is enough to keep it out of the way.
    here = os.path.expanduser("~/.config/daybreak-decomp")
    there_config = machine.config
    host_here = host_side == "local"
    print("\n[interactive] room: " + ("this machine hosts" if host_here else "the other hosts"))
    print("  here  settings: " + here + "/settings.conf (this suite sets XDG_CONFIG_HOME)")
    print("  there settings: " + there_config + "/settings.conf (same there)")
    print("  port: " + str(DEFAULT_PORT) + " (each side's [network] port)")
    if host_here:
        print("  this machine binds UDP {}; the other joins {}:{}".format(
            DEFAULT_PORT, local_address(), DEFAULT_PORT))
        print("  run here:     daybreak --net-host=" + str(DEFAULT_PORT) + " --no-audio")
        print("  run there:    XDG_CONFIG_HOME={} LD_LIBRARY_PATH={} {}/daybreak --net-join={}:{}"
              .format(there_config, machine.lib, there, local_address(), DEFAULT_PORT))
    else:
        address = remote_address(machine)
        print("  the other machine binds UDP {} at {}; this machine joins".format(DEFAULT_PORT,
                                                                                 address))
        print("  run there:    XDG_CONFIG_HOME={} LD_LIBRARY_PATH={} {}/daybreak --net-host={} "
              "--no-audio".format(there_config, machine.lib, there, DEFAULT_PORT))
        print("  run here:     daybreak --net-join={}:{} --no-audio".format(address, DEFAULT_PORT))
    print("\n  what to look at: docs/NET-TWO-MACHINE.md, `The checks only a person can make`.")
    print("  both players must take a panel on the character select; the stage page waits until\n"
          "  every machine's player has one (screen_select.cpp's online claim).")
    return 0


def main():
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    sub = parser.add_subparsers(dest="command", required=True)
    prepare_cmd = sub.add_parser("prepare")
    prepare_cmd.add_argument("--remote", required=True, help="USER@HOST of the other machine")
    prepare_cmd.add_argument("--rebuild", action="store_true", help="rebuild netctl first")
    robust = sub.add_parser("robustness")
    robust.add_argument("--remote", required=True, help="USER@HOST of the other machine")
    robust.add_argument("--peers", type=int, default=2)
    robust.add_argument("--ticks", type=int, default=3600)
    robust.add_argument("--time-limit", type=int, default=None)
    robust.add_argument("--host", choices=("local", "remote"), required=True,
                        help="which machine hosts the room. Remote is the only option when this "
                             "machine's firewall drops inbound UDP: its rules cannot be changed "
                             "without root, and a reply to an outbound flow is let through")
    robust.add_argument("--rehearse", action="store_true",
                        help="run both profiles with every peer on this machine, so a failure "
                             "can only be the harness; the ideal profile still starts the "
                             "host side through the shell ssh would use")
    board = sub.add_parser("interactive")
    board.add_argument("--remote", required=True, help="USER@HOST of the other machine")
    board.add_argument("--host", choices=("local", "remote"),
                       help="which machine hosts the room (same meaning as robustness --host)")
    args = parser.parse_args()
    try:
        if args.command == "prepare":
            return prepare(args.remote, args.rebuild)
        if args.command == "robustness":
            return robustness(args.remote, args.peers, args.ticks, args.time_limit, args.host,
                              args.rehearse)
        return interactive(args.remote, args.host or "local")
    except subprocess.TimeoutExpired:
        fail(3, "a peer did not answer: one machine could not reach the other's UDP port, or "
                "the other machine's firewall drops it")
    except FileNotFoundError as error:
        fail(2, str(error))


if __name__ == "__main__":
    sys.exit(main())
