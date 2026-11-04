#!/usr/bin/env python3
"""Two-machine online checks (issue #106), driven from the machine that holds this checkout.

Both machines are the owner's, on one network. This side runs a peer and drives the other's over
ssh; the other machine needs nothing checked out, only a game tree and a peer binary copied into
its $HOME, which `prepare` does. The two run different distributions, so a binary built here may
not run there: `prepare` checks that, and says how to build on the other machine when it does not.

`netctl` is a headless online peer: real sockets, the real battle, no window and no GPU. It
prints one JSON line per run with the rollback, desync and round-over counters and `"slots"`, the
per-seat verdict `battle.slot_is_cpu` gives (`H` a player drives it, `C` the CPU does). That is
online step 8's own evidence — two machines agreeing — and nothing about the original, which has
no netplay to compare with.

    netsuite.py prepare     --remote USER@HOST   copy the game tree and netctl over, check they run
    netsuite.py robustness  --remote USER@HOST   two machines in one headless room, ideal and bad
    netsuite.py interactive --remote USER@HOST   the game on both screens, for what only a person
                                                 can see (docs/NET-TWO-MACHINE.md)

Exit codes: 0 every check passed, 1 a check failed, 2 the setup is not ready, 3 a machine could
not be reached.
"""
import argparse
import json
import os
import socket
import subprocess
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.abspath(os.path.join(HERE, "..", ".."))
OUT = os.path.join(REPO, "build", "net-two-machine")
GAME_NAME = "daybreak-1.0.0-linux-x86_64"     # the packaged tree, from scripts/package_linux.sh
# data/ beside the executable (main.cpp's "beside the package") and a game folder as GAME_DIR:
# together they cover both routes the port reads its game files through.
GAME_DIR_VAR = "GAME_DIR"
DEFAULT_PORT = 37564      # frontend_settings.h's netPort: the port the game binds for a room
PEER_DEADLINE = 240       # netctl's own deadline is ticks/60 + 120 s
NETCTL = "netctl"         # remote shape: ~/daybreak-net/{bin/netctl, game/...}


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
        self.game = self.dir + "/" + GAME_NAME
        # The game files are the owner's installed copy, never packaged: they go in a folder of
        # their own and reach both binaries through GAME_DIR.
        self.data = self.dir + "/data"

    def peer(self, arguments):
        """A command that runs a peer against the copied game files."""
        return "env {}={} {} {}".format(GAME_DIR_VAR, self.data, self.netctl, arguments)

    def run(self, command, timeout=PEER_DEADLINE):
        return subprocess.run(["ssh", self.target, command], capture_output=True, text=True,
                              timeout=timeout)

    def spawn(self, command):
        return subprocess.Popen(["ssh", self.target, command], stdout=subprocess.PIPE,
                                stderr=subprocess.PIPE, text=True)

    def copy(self, name, dest_dir, source_dir=None):
        """`tar | ssh tar`: no rsync, no second checkout, nothing version-specific."""
        self.run("mkdir -p " + dest_dir, timeout=30)
        sent = subprocess.run(
            "tar -C {src} -cf - {name} | ssh {target} 'tar -C {dst} -xf -'".format(
                src=source_dir or os.path.dirname(name), name=os.path.basename(name),
                target=self.target, dst=dest_dir),
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


def free_port():
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as probe:
        probe.bind(("0.0.0.0", 0))
        return probe.getsockname()[1]


def game_tree():
    package = os.path.join(REPO, "build", "package")
    if not os.path.isdir(package):
        return None
    for name in sorted(os.listdir(package), reverse=True):
        candidate = os.path.join(package, name)
        if os.path.exists(os.path.join(candidate, "daybreak")) and \
                os.path.isdir(os.path.join(candidate, "data")):
            return candidate
    return None


# -- prepare ------------------------------------------------------------------------------

def prepare(remote, rebuild):
    tree = game_tree()
    if not tree:
        fail(2, "no packaged game tree under build/package. Build and package it here first:\n"
                "  ./build.sh linux && scripts/package_linux.sh\n"
                "(the tree is the one a release ships: binary, data/ and assets/ beside it)")
    netctl = os.path.join(REPO, "build", "linux", "netctl")
    if rebuild or not os.path.exists(netctl):
        print("[prepare] building netctl", flush=True)
        built = subprocess.run(["cmake", "--build", "build/linux", "--target", "netctl"], cwd=REPO,
                               capture_output=True, text=True)
        if built.returncode != 0:
            fail(2, built.stderr[-1500:])
    machine = Remote(remote)
    if machine.run("echo ok", timeout=30).returncode != 0:
        fail(3, "cannot reach " + remote + " over ssh")
    print("[prepare] game tree: " + tree, flush=True)
    machine.copy(tree, machine.dir)          # -> ~/daybreak-net/daybreak-1.0.0-linux-x86_64
    machine.copy(os.path.join(REPO, "build", "linux", "netctl"), machine.dir + "/bin")
    check = machine.run(machine.netctl + " --help >/dev/null 2>&1 && " +
                        machine.game + "/daybreak --help >/dev/null 2>&1 && echo both-run", timeout=60)
    if "both-run" not in check.stdout:
        print("[prepare] copied, but a binary does not start there. netctl needs no display; the "
              "game does, so test it on a machine with a session:")
        print(check.stderr.strip()[:600])
        return 2
    print("[prepare] ready: both binaries run on the other machine")
    return 0


# -- robustness: two machines, one headless room ------------------------------------------

def run_room(machine, peers, ticks, seed, time_limit=None, proxy_args=None, same_host=False):
    """This machine hosts `peers` players, the other machine joins, every peer keeps its log."""
    stamp = time.strftime("%Y%m%d-%H%M%S")
    out = os.path.join(OUT, "robustness-" + stamp)
    os.makedirs(out, exist_ok=True)
    port = free_port()
    address = "127.0.0.1" if same_host else local_address()
    common = "--ticks {} --seed {}".format(ticks, seed)
    if time_limit:
        common += " --time-limit {}".format(time_limit)
    proxy = real_args = ""
    if proxy_args:
        proxy_port = free_port()
        proxy = subprocess.Popen([sys.executable, os.path.join(REPO, "tools", "net_proxy.py"),
                                  "--port", str(proxy_port)] + proxy_args.split())
        real_args = " --proxy 127.0.0.1:{}".format(proxy_port)
        time.sleep(0.5)
    host_log = os.path.join(out, "host.log")
    host = subprocess.Popen(
        [os.path.join(REPO, "build", "linux", "netctl"), "--host", str(port), "--peers", str(peers)]
        + common.split() + real_args.split() + ["--log", host_log],
        stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True,
        env=dict(os.environ, GAME_DIR=os.path.join(REPO, "Higurashi-Daybreak")))
    time.sleep(1.0)     # the host binds before anyone knocks
    guests = []
    try:
        for i in range(1, peers):
            guests.append(machine.spawn(machine.peer("--join {}:{} {}{} --log {}/guest{}.log".format(
                address, port, common, real_args, machine.dir, i))))
            time.sleep(0.5)
        host_text, host_err = communicate(host)
        try:
            results = {"host": result_of(host_text)}
        except RuntimeError:
            # A peer that never reports is a failed check, not a crashed suite: say what to look
            # at and let the caller count it as one.
            print("the host reported nothing ({}). The other machine must reach this one at "
                  "{}:{}; ssh working says nothing about UDP, so check this machine's firewall "
                  "(allow udp/{}) and that both machines are on the same network."
                  .format(host_err.strip() or "no stderr", address, port, port))
            return {}, out
        for i, guest in enumerate(guests, 1):
            text, err = communicate(guest)
            try:
                results["guest{}".format(i)] = result_of(text)
            except RuntimeError as error:
                print("guest{}: {} {}".format(i, error, err[-300:]))
        for i in range(1, peers):
            machine.run("cat {}/guest{}.log >> {}/guest{}.log".format(machine.dir, i, out, i), timeout=60)
    finally:
        for process in [host] + guests:
            if process.poll() is None:
                process.kill()
        if proxy:
            proxy.kill()
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


def robustness(remote, peers, ticks, time_limit, same_host=False):
    machine = Remote(remote)
    if machine.run("test -x " + machine.netctl + " && echo yes", timeout=30).stdout.strip() != "yes":
        fail(2, "the other machine has no netctl: netsuite.py prepare --remote " + remote)
    checks, failures = 0, []

    def check(condition, what):
        nonlocal checks
        checks += 1
        print(("ok   " if condition else "FAIL ") + what)
        if not condition:
            failures.append(what)

    for label, proxy in [("ideal network", None),
                         ("10% loss, 80 ms delay, 5 ms jitter",
                          "--delay-ms 80 --jitter-ms 5 --loss 0.10 --seed 3")]:
        results, directory = run_room(machine, peers, ticks, 11 + peers, time_limit, proxy, same_host)
        print("[robustness] {}: {}".format(label, ", ".join(
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

def interactive(remote, host_here):
    """Sets the room up on both screens; what to look at is docs/NET-TWO-MACHINE.md."""
    machine = Remote(remote)
    if machine.run("test -x " + machine.game + "/daybreak && echo yes", timeout=30).stdout.strip() != "yes":
        fail(2, "no game on the other machine: netsuite.py prepare --remote " + remote)
    display = machine.run("echo $WAYLAND_DISPLAY $DISPLAY", timeout=30).stdout.strip()
    if not display:
        fail(2, "the other machine reports no display, so the game cannot open there. Start it "
                "from that machine's own session, then run this again.")
    # Settings are ours, not the original's, and the XDG base directory spec lets each side
    # pin its own file, so this suite never touches anyone's real settings.conf.
    here = os.path.expanduser("~/.config/daybreak-decomp")
    there = machine.dir + "/config"
    print("\n[interactive] room: " + ("this machine hosts" if host_here else "the other hosts"))
    print("  here  settings: " + here + "/settings.conf")
    print("  there settings: " + there + "/settings.conf (written by prepare)")
    print("  port: " + str(DEFAULT_PORT) + " (each side's [network] port)")
    if host_here:
        print("  this machine binds UDP {}; the other joins {}:{}".format(DEFAULT_PORT,
                                                                          local_address(), DEFAULT_PORT))
        print("  run here:     daybreak --net-host=" + str(DEFAULT_PORT) + " --no-audio")
        print("  run there:    XDG_CONFIG_HOME={} {}/daybreak --net-join={}:{}".format(
            there, machine.game, local_address(), DEFAULT_PORT))
    else:
        address = (machine.run("hostname -I", timeout=30).stdout.split() or [""])[0]
        print("  the other machine binds UDP {} at {}; this machine joins".format(DEFAULT_PORT, address))
        print("  run there:    XDG_CONFIG_HOME={} {}/daybreak --net-host={} --no-audio".format(
            there, machine.game, DEFAULT_PORT))
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
    robust.add_argument("--same-host", action="store_true",
                        help="rehearse with both sides on this machine (the second side is told "
                             "127.0.0.1); a real second machine joins this machine's LAN address")
    board = sub.add_parser("interactive")
    board.add_argument("--remote", required=True, help="USER@HOST of the other machine")
    board.add_argument("--host", choices=("local", "remote"), default="local")
    args = parser.parse_args()
    try:
        if args.command == "prepare":
            return prepare(args.remote, args.rebuild)
        if args.command == "robustness":
            return robustness(args.remote, args.peers, args.ticks, args.time_limit, args.same_host)
        return interactive(args.remote, args.host == "local")
    except subprocess.TimeoutExpired:
        fail(3, "a peer did not answer: one machine could not reach the other's UDP port, or "
                "the other machine's firewall drops it")
    except FileNotFoundError as error:
        fail(2, str(error))


if __name__ == "__main__":
    sys.exit(main())
