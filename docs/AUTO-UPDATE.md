# Auto-updates: the release formats and the signing key (issue #100)

The updater is built in steps. **Steps 1–4 are built and tested**: both packages state
which files they own, the release manifest is generated from the two archives, the owner
has an offline signing tool, the game has the whole engine — check, download, verify,
stage, apply, roll back, recover and relaunch — and the title screen now offers an update
and installs it. The release key list is still empty (the owner supplies the public key),
so a package build refuses to compile until it is filled in.

| Piece | Where | State |
|---|---|---|
| `package-manifest.txt` in each package | `tools/package_manifest.py`, called by both packaging scripts | built, tested |
| `update-manifest.txt` for a release | `tools/make_update_manifest.py` | built, tested |
| `update-manifest.txt.sig` | `tools/release_sign/` (`build/linux/release_sign`) | built, tested against RFC 8032 |
| CI artifact for the release | `.github/workflows/build.yml`, job `update-manifest` | green on `feat/auto-updater` (run 41558670935): both archives, both `.sha256` files and the manifest |
| HTTPS GET (redirects, timeouts, cancel) | `src/platform/http.h`, `http_curl.cpp`, `http_winhttp.cpp` | built; Linux tested against a local fixture and the real 0.2.1 asset; Windows compiled only by CI (no toolchain here) |
| Version, path rules, both parsers, archive readers, SHA-256/Ed25519 | `src/update/` | built, tested |
| Check, download, verify, stage, apply, roll back, recover, relaunch | `src/update/updater.{h,cpp}`, `apply_posix.cpp` / `apply_win32.cpp` | built, tested on Linux; the Windows cases run in `update_selftest.exe` |
| Trusted release keys | `src/update/release_keys.h` | **empty until the owner supplies the public key**; a `DAYBREAK_RELEASE_BUILD` refuses to compile without one |
| Title notice, update screen, Options row, `--no-update-check` | `src/frontend/update_notice.*`, `screen_update.*`, `src/app/main.cpp` | built; device-free notice/failure tests and captures, Windows relaunch not run |

## Why a package manifest

Players extract a release package **into their game folder**, next to the copyrighted data
(`daybreakXX.dat`, `data/`, `movie/`, `custom-textures/`, `hd-textures/`). The updater must
therefore only ever touch files the package itself owns, and `package-manifest.txt` is the
list that says which files those are.

The rule the runtime will follow, and the reason the formats are versioned:

* replace every file the **new** manifest lists;
* delete a file only if the **old** (installed) manifest lists it and the new one does not;
* leave everything else alone, including files in neither manifest;
* refuse a `format` newer than the running updater understands and tell the player to
  download that release by hand.

That also makes a package-layout change an ordinary update: renamed or moved files arrive
with the new manifest, and the old paths go away through the old one.

## `package-manifest.txt`

At the **package root**: inside the Linux archive's top-level directory
(`daybreak-<ver>-linux-x86_64/`), at the zip root on Windows.

```
format = 1
version = 0.2.1
target = linux-x86_64
launch = daybreak
[files]
<sha256 lowercase hex>  <size in bytes>  <mode>  <relative/path>
```

* Exactly the five header lines above, in that order, then one line per file with **two
  spaces** between the four fields. LF line endings, a final newline, no blank lines.
* `target` is `linux-x86_64` or `windows-x86_64`; `version` is the package's `VERSION`.
* `launch` is the entry point (`daybreak` on Linux, `DaybreakRemake.exe` on Windows) and
  must name a file in the list; on Linux that file's mode must be `x`.
* `mode` is `x` for a file that must be executable and `-` otherwise. On Linux it comes from
  the staged file's exec bit; on Windows every file is `-`.
* Paths are relative to the package root, use `/`, are sorted bytewise, and never contain
  `..`, a leading `/`, a drive letter, `\`, a control character, or one of `< > : " | ? *`.
  The rules are the intersection of both platforms, because the same manifest drives an
  update on Windows and on Linux and a layout change may move files between them: no
  component may end in `.` or a space, no component may be a Windows device name (`CON`,
  `PRN`, `AUX`, `NUL`, `COM1`–`COM9`, `LPT1`–`LPT9`, any case, with or without an
  extension), two entries may not differ only in case, and a file path may not be a
  directory of another entry (`a` beside `a/b`).
* Only regular files are listed. A symlink, device, fifo or socket fails the packaging
  rather than being skipped. Directories are implied by the files in them.
* The manifest does not list itself.

`tools/package_manifest.py` is the only implementation (Python 3 stdlib, run with
`python3 -I`):

```bash
python3 -I tools/package_manifest.py write <stage-dir> \
    --version=<X.Y.Z> --target=<linux-x86_64|windows-x86_64> --launch=<path>
python3 -I tools/package_manifest.py check <stage-dir>
```

`check` verifies the same file set, hashes, sizes and modes the updater will, so a package
that passes it is a package the updater accepts. Both packaging scripts call it.

## `update-manifest.txt`

One file, in the newest stable release, at
`https://github.com/Vmarcelo49/daybreak-remake/releases/latest/download/update-manifest.txt`.
The updater reads it instead of the GitHub API: no request limit, no API version to follow,
nothing to parse but our own format.

```
format = 1
version = 1.0.0
notes = https://github.com/Vmarcelo49/daybreak-remake/releases/tag/v1.0.0
[linux-x86_64]
archive = daybreak-1.0.0-linux-x86_64.tar.gz
size = 19876543
sha256 = <64 lowercase hex characters>
[windows-x86_64]
archive = daybreak-1.0.0-2d33582-windows-x86_64.zip
size = 19876544
sha256 = <64 lowercase hex characters>
```

* `version` is a plain `X.Y.Z` (no suffix, no leading zeros); the download URL is
  `releases/download/v<version>/<archive>`.
* `size` and `sha256` describe the **archive file**; the archive contains the per-file
  manifest, so one signature covers everything the package ships.
* The archive names are the release's own: `daybreak-<version>-linux-x86_64.tar.gz`, whose
  single top-level directory is `daybreak-<version>-linux-x86_64`, and
  `daybreak-<version>-<7 to 40 lowercase hex>-windows-x86_64.zip`. A renamed, stale or
  `-dirty` archive is refused, so the manifest cannot describe something that was not the
  release build.
* The file is byte-for-byte reproducible from the same inputs — LF line endings, no trailing
  whitespace, fixed order — because it is signed.

```bash
python3 -I tools/make_update_manifest.py --version=<X.Y.Z> \
    --linux=daybreak-<ver>-linux-x86_64.tar.gz \
    --windows=daybreak-<ver>-<rev>-windows-x86_64.zip \
    --out=update-manifest.txt
```

Before writing anything, the tool opens both archives and proves each one against the
`package-manifest.txt` inside it: same file set, hashes, sizes and Linux exec bits, and no
symlink, hard link or unsafe path. A mismatch is a failed release, not a warning.

## What the archives may contain

`make_update_manifest.py` refuses anything outside this set, because the game's reader
(`src/update/archive.cpp`, step 2) implements exactly this set: an archive the tool accepted
but the game could not read would be an update nobody can apply. Damaged input is a
one-line `make_update_manifest:` error and exit 1, never a traceback.

**Linux (`daybreak-<version>-linux-x86_64.tar.gz`)**

* one gzip member (no trailing data) holding a POSIX **ustar** archive;
* members are regular files (type `0` or NUL) and directories (type `5`) only: no symlinks,
  hard links, devices, GNU long-name records (`L`/`K`), pax headers (`x`/`g`) or sparse
  files (`S`);
* header magic `ustar\0` and version `00`, octal size fields, a verified header checksum,
  and the archive ends with the zero blocks;
* names are `prefix + "/" + name`, so a path may be up to 255 bytes; `package_linux.sh`
  passes `--format=ustar` and tar fails loudly on a name ustar cannot hold;
* exactly one top-level directory, named `daybreak-<version>-linux-x86_64`.

**Windows (`daybreak-<version>-<7–40 lowercase hex>-windows-x86_64.zip`)**

* one disk, compression method 0 (stored) or 8 (deflate) only, no encryption, no zip64
  (neither the `0x0001` extra field nor the `0xFFFF`/`0xFFFFFFFF` markers);
* names are UTF-8 (general-purpose flag bit 11) or plain ASCII;
* the central directory and each local header must agree on the name, and the CRC32 and
  both sizes are verified.

Both archives are bounded: at most 10,000 entries, 1 GiB uncompressed in total, and a
200:1 compression ratio per entry, so a zip bomb is refused rather than inflated.

The game's readers (`src/update/archive.cpp`) implement exactly this set. They inflate
through the **vendored zlib** that the reference core already carries
(`battle_core_zlib`, unpatched — `src/battle/core/PATCHES.md`), not through
`xm::detail::Inflater`: it is faster, it provides `crc32`, and linking it costs nothing
because it is already in the tree. The "one shared Inflater" line in issue #100 is
superseded; `src/assets/xmodel.h` is unchanged.

## `update-manifest.txt.sig`

64 bytes of Ed25519 over the manifest's **exact bytes**, stored as 128 lowercase hex
characters plus a newline so it diffs and pastes cleanly. `tools/release_sign` writes and
checks it; the updater will check it the same way before reading anything else.

```bash
build/linux/release_sign keygen --secret=<path> --public=<path>
build/linux/release_sign sign   --secret=<path> [--expect-public=<hex or path>] update-manifest.txt
build/linux/release_sign verify --public=<hex or path> update-manifest.txt update-manifest.txt.sig
```

Exit codes: `0` success, `1` usage, `2` file or format error, `3` invalid signature.
`verify` accepts the key as 64 hex characters or as a file holding them.

## Trust model

A `.sha256` published beside an archive catches a damaged download. It does not stop anyone
who can upload to the release: a stolen GitHub token or a compromised workflow can replace
the archive **and** its hash together. A signature by a key that never touches GitHub or CI
is what closes that gap.

* **The private key never goes to GitHub.** The owner generates it on their own machine,
  keeps it offline (password manager or USB stick) and runs `release_sign` locally when
  publishing. The cost is one manual step per release; `docs/RELEASE-CHECKLIST.md` §9 lists
  it.
* **The public key ships in the game** (step 3). Builds carry a **list** of trusted keys, so
  the key can be replaced later: a new key is introduced by a release signed with the old
  one, and the game accepts a manifest whose key is in its list. Removing an old key happens
  in a later release, once the new one has been out. The mechanism itself is step 3.
* **Key files.** The secret is the 32-byte Ed25519 seed as 64 hex characters, mode `0600`;
  `release_sign` derives the key pair from it, refuses to use it if group or others can
  access it, and refuses to overwrite an existing one. Storing the seed alone is deliberate:
  a file that carried its own copy of the public half could sign with a half that does not
  belong to the seed, which produces a release nobody can verify (and is the known Ed25519
  misuse). `sign` verifies its own signature before writing anything, and
  `--expect-public=<hex or path>` refuses unless the derived key is the one named; the
  release checklist passes the release's `.pub` there. The public key is 32 bytes as 64 hex
  characters and is not secret. `*.release-secret` is in `.gitignore` so a real key cannot
  be committed by accident.
* **The signature covers the manifest, the manifest covers the archives.** Order of checks
  in the updater (step 3): signature → manifest → archive size → archive hash → each
  extracted file against the new `package-manifest.txt`. Anything failing means nothing is
  applied.

## The HTTP client

`src/platform/http.h` is one blocking GET, safe to call from a worker thread (step 4 runs
the check off the main thread) and cancellable through its progress callback. Two
implementations sit behind it:

* **Linux** (`http_curl.cpp`) loads `libcurl.so.4` (or `libcurl-gnutls.so.4`) with
  `dlopen` and never links it: every desktop has libcurl, no player has its development
  package, and a linked dependency would need a version we ship. Missing libcurl is
  `Unavailable`, whose message tells the player to download the release manually. The
  client compiles against pinned curl headers (8.23.0, sha256-verified by
  `scripts/fetch_deps.sh`), so the option names and types are curl's own.
* **Windows** (`http_winhttp.cpp`) uses WinHTTP from the OS: system certificate store,
  system proxy settings, no shipped bytes. Automatic proxy falls back to the default on
  systems older than Windows 8.1.

The URL policy is shared and enforced on every hop: **https only**, at most five
redirects, and an https → http redirect is `Refused` (the Linux client follows redirects
itself precisely so each hop can be checked; WinHTTP is configured to refuse the downgrade
and bound the chain). The one exception is plain HTTP to `127.0.0.1:<port>` or
`localhost:<port>` while `DAYBREAK_UPDATE_TEST_HTTP=1` is set — that is the CTest fixture,
and a release build has no other way to reach it. Any status other than 200 is `Status`
with the code; a body over `maxBytes` is `TooLarge`; no bytes for the stall timeout is
`Timeout`; cancelling returns `Cancelled`.

`update_selftest --live <url>` is the opt-in live check (never part of CTest): it fetches a
real release asset through the real redirect chain and prints its size and SHA-256. It ran
on Linux against the 0.2.1 asset (21,514,040 bytes, sha256 `8460d5e6…`); the Windows run is
pending a machine with the toolchain.

## Applying an update

The engine is `src/update/updater.{h,cpp}`; the file operations it needs (rename aside,
atomic write, free space, self path, exec/CreateProcess) are `apply_posix.cpp` /
`apply_win32.cpp`. The rules are what make it safe to write into a folder that also holds
the copyrighted game data:

* **The install root must be a package.** It is the directory of the running binary, and it
  must hold a parseable `package-manifest.txt` whose `target` matches this build. A
  development build tree is refused ("this copy wasn't installed from a release package").
* **The workspace is `<root>/.daybreak-update/<version>/`**, on the same volume as the
  install so the renames are atomic.
* **Before the download** the engine checks free space against the archive size plus twice
  a conservative unpack (the exact total lives inside the archive).
* **The download is capped at the manifest's `size`** and hashed as it streams; a wrong
  size or sha256 deletes the archive and applies nothing.
* **The staged tree is proven against the archive's own `package-manifest.txt`**: version,
  target, every size, hash and exec bit, and the file set must match exactly.
* **Never overwrite a file the old package doesn't own.** If a path in the new manifest
  exists in the install, is not in the old manifest, and has different bytes, the apply
  aborts and names the path. With no old manifest (missing or corrupt) the engine only adds
  and replaces, deletes nothing, and the new manifest's paths are trusted to be the
  package's own.
* **A package may not list a game-data path.** `data/`, `movie/`, `custom-textures/`,
  `hd-textures/` and `daybreak[0-9][0-9].dat` are refused by both manifest parsers, in any
  case, so a release can never step on the game's files or a texture pack.
* **Journal.** `<workspace>/journal` is written atomically (temp file, fsync, rename,
  directory fsync) before the first rename, listing every operation. Its states are
  `applying` and `committed`; it also records the new manifest's sha256.
* **Per file:** the existing file is renamed to `<path>.old`, then the staged file is
  renamed into place (parent directories created). Deletions become `.old` too, so a
  rollback can restore them. Windows uses `MoveFileExW` without `REPLACE_EXISTING` and
  retries `ERROR_ACCESS_DENIED`/`ERROR_SHARING_VIOLATION` for up to five seconds, because
  antivirus scanners and the still-exiting old process hold fresh `.exe`/`.dll` files.
* **The commit point is the new `package-manifest.txt`**, replaced by an atomic rename;
  only then is the journal marked `committed`.
* **Any failure before the commit rolls the journal back**, restoring every `.old` and
  removing every added file, so the old version is exactly as it was.
* **Startup recovery** (`update::recoverOnStartup`) runs first thing on native builds. With
  no journal it is one `stat` and does nothing. `applying` rolls back — unless the installed
  manifest already matches the journal's hash, in which case the commit happened and the
  `.old` files are cleaned. `committed` just cleans up. A `.old` that cannot be deleted yet
  on Windows is retried on the next start.
* **Relaunch** starts the new entry point with the original arguments plus
  `--updated-from=<old>`; the game logs that flag and ignores it (migrations hook in later).
  Linux `execv`s the launcher, Windows `CreateProcessW`s it and lets the caller exit.

The trusted keys are a **parameter**: the game passes `release_keys.h`, the tests pass
throwaway keys. Nothing on a player's machine can add one. While the list is empty every
check reports "untrusted"; a build with `DAYBREAK_RELEASE_BUILD` defined fails to compile
with an empty list (a static assertion) and the logic suite also asserts it at run time.

What is verified today: `update_apply_test` (120 checks) runs the whole chain against the
step-2 loopback server with archives built by the real release tools — every outcome, the
collision and game-area refusals, a read-only root, the space hook, cancel at each phase, a
layout change, a missing old manifest, an injected failure at **every** operation with a
complete rollback, a child process that `_exit()`s at every operation followed by recovery,
and the end-to-end stub that applies and relaunches into the new version. The Windows
counterparts (including renaming the running `update_selftest.exe` aside) run in
`update_selftest.exe` on the owner's machine.

## What the player sees (step 4)

The check runs **once per launch, on a worker thread**, started when the title screen
first appears; no frame waits for it. It never runs when:

* `[update] check = off` (the Options screen's UPDATES row), which also cancels a check
  already in flight;
* `--no-update-check` is passed;
* the build is the web build;
* the install root has no `package-manifest.txt` (a development build: one log line);
* the launch is a verification, capture or test run — `--frames`, `--out`, `--headless`,
  `--script`/`--script2`, `--match`, `--versus`, `--hud-test`, `--bench`, `--list`,
  `--audio-test`, `--input-test`, `--plan`, `--pause-overlay`, `--net-stress`,
  `--rollback-stress`, `--hud-probe`, `--debug-keys`, `--text-keys` (one helper,
  `updateCheckSuppressed`, so a new flag is gated once);
* `DAYBREAK_NO_UPDATE_CHECK=1` is set — CTest sets it for every test and
  `tools/fingerprints.sh` sets it too.

The result waits until the player is on the title screen; no other screen offers an
update. The notice sits at the lower left, in the existing panel style:

* **Available** — "Version X.Y.Z is available": **Update**, **Release notes**
  (`SDL_OpenURL`), **Later** (hidden until the next launch) and **Skip this version**
  (writes `skip_version`). Down from the last title item moves into the notice; up or
  cancel moves back, and the title menu keeps its own cursor machine until then.
* **ManualOnly** — "This update must be downloaded manually" + **Open release page**.
* **Unavailable** (no libcurl) — "Updates need libcurl" + **Open release page**, once.
* **Failed**, **UpToDate**, **Skipped**, an untrusted signature — nothing but one log line.
* After a relaunch, **"Updated to Y"** for that launch, from `--updated-from=`.

The update screen runs the apply on its own worker: **Downloading** (MB done / total and a
bar), **Verifying**, **Installing**, then **Restarting…**. Back/Esc cancels during
download and verify and returns to the title with the install untouched; once installing
starts there is no cancel. A failure shows a plain-language reason (no connection, GitHub
didn't answer, the download was damaged, not signed by us, the game folder isn't
writable, a file is in the way, not enough space) with **Back** and **Open release page**;
the old version keeps running. Success saves the settings, shuts audio, video and the net
layer down the way a normal quit does, and only then calls `update::relaunch`, so Windows
never flashes a second window.

`--update-result=available|manual|unavailable|updated|progress` is the test/capture hook
that feeds the title a fake result instead of a check (no environment variable); it also
suppresses the real check.

## What is still missing

* The title-screen notice, the progress screen, the Options rows, the settings keys and
  `--no-update-check`, plus the CTest gate that keeps verification runs off the network.
* The real public key in `src/update/release_keys.h`.
* `package/LICENSES/` already carries Monocypher's notice: the game links it from step 2.

## Reproducing steps 1 and 2

```bash
./scripts/package_linux.sh --no-build          # run twice: same sha256
python3 -I tools/make_update_manifest.py --version="$(cat VERSION)" \
    --linux=build/package/daybreak-"$(cat VERSION)"-linux-x86_64.tar.gz \
    --windows=build/package/daybreak-"$(cat VERSION)"-<rev>-windows-x86_64.zip \
    --out=update-manifest.txt
build/linux/release_sign keygen --secret=/tmp/test.release-secret --public=/tmp/test.pub
build/linux/release_sign sign   --secret=/tmp/test.release-secret \
    --expect-public=/tmp/test.pub update-manifest.txt
build/linux/release_sign verify --public=/tmp/test.pub update-manifest.txt update-manifest.txt.sig
```

The updater's own suites run without game data or the internet:

```bash
ctest -L platform --output-on-failure     # includes the update suites
ctest -L net --output-on-failure          # the HTTP fixture on 127.0.0.1
build/linux/update_selftest               # the same three suites as one binary (Windows)
build/linux/update_selftest --live https://github.com/Vmarcelo49/daybreak-remake/releases/download/v0.2.1/daybreak-0.2.1-linux-x86_64.tar.gz
```

`ctest -L platform` includes `package_manifest_test`, `update_manifest_test`,
`release_sign_test`, `update_logic_test`, `update_crypto_test`, `update_archive_test` and
`update_http_test`; `ctest -L net` includes the HTTP one as well. `release_sign_test` and
`update_crypto_test` cover RFC 8032 §7.1 TEST 1 and TEST 2, so a change that turned either
side into a non-standard Ed25519 variant fails there.
