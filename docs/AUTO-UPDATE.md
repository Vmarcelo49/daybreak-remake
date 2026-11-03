# Auto-updates: the release formats and the signing key (issue #100)

The updater is built in steps. **Step 1 is built and tested**: both packages state which
files they own, the release manifest is generated from the two archives, and the owner has
an offline signing tool. **The runtime side is not built yet** (steps 2–4): nothing in
`src/` reads these files, no menu offers an update, and no run makes a network request.

| Piece | Where | State |
|---|---|---|
| `package-manifest.txt` in each package | `tools/package_manifest.py`, called by both packaging scripts | built, tested |
| `update-manifest.txt` for a release | `tools/make_update_manifest.py` | built, tested |
| `update-manifest.txt.sig` | `tools/release_sign/` (`build/linux/release_sign`) | built, tested against RFC 8032 |
| CI artifact for the release | `.github/workflows/build.yml`, job `update-manifest` | written, not yet run on CI |
| Check, download, verify, apply, roll back | `src/update/` | **not built** (steps 2–4) |

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
  `..`, a leading `/`, a drive letter, `\` or a control character.
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

## `update-manifest.txt.sig`

64 bytes of Ed25519 over the manifest's **exact bytes**, stored as 128 lowercase hex
characters plus a newline so it diffs and pastes cleanly. `tools/release_sign` writes and
checks it; the updater will check it the same way before reading anything else.

```bash
build/linux/release_sign keygen --secret=<path> --public=<path>
build/linux/release_sign sign   --secret=<path> update-manifest.txt
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
* **Key files.** The secret is Monocypher's 64-byte secret key (seed followed by the public
  half) as 128 hex characters, mode `0600`; `release_sign` refuses to use it if group or
  others can access it, and refuses to overwrite an existing one. The public key is 32 bytes
  as 64 hex characters and is not secret. `*.release-secret` is in `.gitignore` so a real
  key cannot be committed by accident.
* **The signature covers the manifest, the manifest covers the archives.** Order of checks
  in the updater (step 3): signature → manifest → archive size → archive hash → each
  extracted file against the new `package-manifest.txt`. Anything failing means nothing is
  applied.

## What is still missing (steps 2–4)

* `src/platform/http`: HTTPS GET (WinHTTP on Windows, `dlopen`'d libcurl on Linux).
* `src/update/`: version comparison, download, signature check, extraction, staged apply,
  rollback, journal recovery, cleanup, and the title-screen notice and Options rows.
* The public key list compiled into the game, and `--no-update-check` plus the CTest
  environment gate that keeps verification runs off the network.
* `package/LICENSES/` gains Monocypher's notice **when the game links it** (step 2). The
  signing tool does not ship, so step 1 adds nothing there.

## Reproducing step 1

```bash
./scripts/package_linux.sh --no-build          # run twice: same sha256
python3 -I tools/make_update_manifest.py --version="$(cat VERSION)" \
    --linux=build/package/daybreak-"$(cat VERSION)"-linux-x86_64.tar.gz \
    --windows=build/package/daybreak-"$(cat VERSION)"-<rev>-windows-x86_64.zip \
    --out=update-manifest.txt
build/linux/release_sign keygen --secret=/tmp/test.release-secret --public=/tmp/test.pub
build/linux/release_sign sign   --secret=/tmp/test.release-secret update-manifest.txt
build/linux/release_sign verify --public=/tmp/test.pub update-manifest.txt update-manifest.txt.sig
```

`ctest -L platform` includes `package_manifest_test`, `update_manifest_test` and
`release_sign_test`; the last one covers RFC 8032 §7.1 TEST 1 and TEST 2, so a change that
turned the tool into a non-standard Ed25519 variant fails there.
