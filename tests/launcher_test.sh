#!/usr/bin/env bash
# tests/launcher_test.sh — the packaged entry point's contract (issue #22).
#
# WHY a shell test: the launcher IS the user-facing behaviour this issue ships — which
# folder it picks, what it remembers, and what it says when it cannot. The binary behind it
# needs a GPU and a display, so this test builds a sandbox "package" whose daybreak-bin
# is a stub that prints its arguments, and drives the real launcher inside it. That covers
# the search order, the persistence file and the failure messages with no device and no
# game data (a fake install is an empty daybreak00.dat marker).
#
#   usage: launcher_test.sh <path to package/daybreak>
#
# The GUI-notice path is exercised too: a zenity stub earlier on PATH records the call
# instead of opening a dialog on the developer's desktop.
set -u

launcher=${1:?usage: launcher_test.sh <package/daybreak>}
[ -f "$launcher" ] || { echo "launcher_test: no launcher at $launcher" >&2; exit 1; }
launcher=$(cd "$(dirname "$launcher")" && pwd)/$(basename "$launcher")

work=$(mktemp -d) || exit 1
trap 'rm -rf "$work"' EXIT

checks=0
failures=0
ok()  { checks=$((checks + 1)); }
bad() { checks=$((checks + 1)); failures=$((failures + 1)); printf 'FAIL: %s\n' "$*"; }
expect() { # expect <description> <haystack> <needle>
    case $2 in
        *"$3"*) ok ;;
        *) bad "$1 (wanted \"$3\" in: $2)" ;;
    esac
}
reject() { # reject <description> <haystack> <needle>
    case $2 in
        *"$3"*) bad "$1 (did not want \"$3\" in: $2)" ;;
        *) ok ;;
    esac
}

# A zenity/kdialog that records instead of opening a window.
mkdir -p "$work/bin"
for tool in zenity kdialog; do
    printf '#!/bin/sh\nprintf "%%s\\n" "$*" >> "%s/gui-notice"\nexit 0\n' "$work" > "$work/bin/$tool"
    chmod +x "$work/bin/$tool"
done

make_package() { # make_package <dir> — the packaged layout the launcher checks for
    mkdir -p "$1/assets/fonts" "$1/lib"
    cp "$launcher" "$1/daybreak"
    chmod +x "$1/daybreak"
    printf '0.1.0\n' > "$1/VERSION"
    : > "$1/assets/fonts/gyrotrope-black.otf"
    : > "$1/assets/fonts/NotoSansCJKjp-Regular.otf"
    : > "$1/lib/libwgpu_native.so"
    : > "$1/lib/libSDL3.so.0"
    cat > "$1/daybreak-bin" <<'STUB'
#!/bin/sh
printf 'STUB %s\n' "$*"
STUB
    chmod +x "$1/daybreak-bin"
}

make_install() { mkdir -p "$1"; : > "$1/daybreak00.dat"; }

run() { # run <pkg> <home> <cfg> <data> <cwd> [args...]
    local pkg=$1 home=$2 cfg=$3 data=$4 cwd=$5
    shift 5
    rm -f "$work/gui-notice"
    ( cd "$cwd" && env -u LD_LIBRARY_PATH -u DAYBREAK_INSTALL \
        PATH="$work/bin:$PATH" HOME="$home" XDG_CONFIG_HOME="$cfg" XDG_DATA_HOME="$data" \
        "$pkg/daybreak" "$@" > "$work/out" 2> "$work/err" )
    status=$?
    out=$(cat "$work/out")
    err=$(cat "$work/err")
}

pkg="$work/package with spaces"
make_package "$pkg"
mkdir -p "$work/home" "$work/config" "$work/data" "$work/cwd"
game="$work/game data/Higurashi-Daybreak"
make_install "$game"

# --- no game folder anywhere --------------------------------------------------------
run "$pkg" "$work/home" "$work/config" "$work/data" "$work/cwd"
[ "$status" = 1 ] || bad "no install: expected exit 1, got $status"
expect "no install: names the game data" "$err" "No Higurashi Daybreak game data found"
expect "no install: names daybreak00.dat" "$err" "daybreak00.dat"
expect "no install: lists where it looked" "$err" "Looked for daybreak00.dat in:"
expect "no install: lists the package folder" "$err" "$pkg"
expect "no install: lists the working directory" "$err" "$work/cwd"
expect "no install: shows the --install fix" "$err" '--install="/path/to/Higurashi-Daybreak"'
expect "no install: mentions DAYBREAK_INSTALL" "$err" "DAYBREAK_INSTALL"
reject "no install: never launches the binary" "$out" "STUB"
expect "no install: a double-click gets a dialog" "$(cat "$work/gui-notice" 2>/dev/null)" "no game folder was found"

# --- an explicit --install= ---------------------------------------------------------
run "$pkg" "$work/home" "$work/config" "$work/data" "$work/cwd" --install="$game"
[ "$status" = 0 ] || bad "--install: expected exit 0, got $status"
expect "--install: forwards the folder and the front end" "$out" "STUB --install=$game --screen=title"
expect "--install: reports the source" "$err" "(--install=)"
# Issue #36: the BINARY owns the remembered folder (settings.conf), so the launcher must
# write nothing at all — it forwards the folder and the binary persists what it opens.
[ ! -e "$work/config/daybreak-decomp/install.conf" ] && ok || bad "--install: the launcher creates no install.conf"
[ ! -e "$work/config/daybreak-decomp/settings.conf" ] && ok || bad "--install: the launcher writes no settings.conf either"

# --- the remembered folder comes from settings.conf (written by the binary) ---------
saved_config="$work/config-remembered/daybreak-decomp"
mkdir -p "$saved_config"
cat > "$saved_config/settings.conf" <<EOF
version = 4

[game]
# The game folder this port last opened (issue #36).
install_dir = $game

[display]
fullscreen = false
EOF
run "$pkg" "$work/home" "$work/config-remembered" "$work/data" "$work/cwd"
[ "$status" = 0 ] || bad "remembered: expected exit 0, got $status"
expect "remembered: is used without a flag" "$out" "STUB --install=$game --screen=title"
expect "remembered: is named as the source" "$err" "(the remembered folder)"
[ ! -e "$saved_config/install.conf" ] && ok || bad "remembered: the launcher writes no install.conf here either"

# A settings.conf whose version this launcher does not know is not guessed at: the folder
# is ignored and the search goes on (the binary would reject that whole document too).
future_config="$work/config-future/daybreak-decomp"
mkdir -p "$future_config"
printf 'version = 8\n\n[game]\ninstall_dir = %s\n' "$game" > "$future_config/settings.conf"
run "$pkg" "$work/home" "$work/config-future" "$work/data" "$work/cwd"
[ "$status" = 1 ] || bad "unknown schema: expected the search to continue (exit 1), got $status"
reject "unknown schema: its folder is not used" "$out" "STUB"

env_home="$work/home-env"
mkdir -p "$env_home" "$work/config-env"
( cd "$work/cwd" && env -u LD_LIBRARY_PATH PATH="$work/bin:$PATH" HOME="$env_home" \
    XDG_CONFIG_HOME="$work/config-env" XDG_DATA_HOME="$work/data" DAYBREAK_INSTALL="$game" \
    "$pkg/daybreak" --frames=3 > "$work/out" 2> "$work/err" )
status=$?; out=$(cat "$work/out"); err=$(cat "$work/err")
[ "$status" = 0 ] || bad "DAYBREAK_INSTALL: expected exit 0, got $status"
expect "DAYBREAK_INSTALL: is used" "$out" "STUB --install=$game --screen=title --frames=3"
expect "DAYBREAK_INSTALL: is named as the source" "$err" "(DAYBREAK_INSTALL)"

# --- a wrong --install is reported, not silently replaced ---------------------------
run "$pkg" "$work/home" "$work/config" "$work/data" "$work/cwd" --install="$work/empty folder"
[ "$status" = 1 ] || bad "wrong --install: expected exit 1, got $status"
expect "wrong --install: names the folder" "$err" "No game data in \"$work/empty folder\" (--install=)"
expect "wrong --install: says what a game folder has" "$err" "no daybreakXX.dat files"
reject "wrong --install: never launches the binary" "$out" "STUB"

# An extracted data/ tree is not something the launcher can hand to the binary by name
# (the port reads a tree only from inside it), so it must be reported, not half-accepted.
tree="$work/extracted tree"
mkdir -p "$tree/data/title"
: > "$tree/data/title/back00.cnv"
run "$pkg" "$work/home" "$work/config-tree" "$work/data" "$work/cwd" --install="$tree"
[ "$status" = 1 ] || bad "extracted tree: expected exit 1, got $status"
expect "extracted tree: names the missing bundles" "$err" "no daybreakXX.dat files"
reject "extracted tree: never launches the binary" "$out" "STUB"

# --- the space-separated flag and relative paths ------------------------------------
mkdir -p "$work/rel"
make_install "$work/rel/Daybreak"
run "$pkg" "$work/home" "$work/config" "$work/data" "$work/rel" --install Daybreak
[ "$status" = 0 ] || bad "--install DIR: expected exit 0, got $status"
expect "--install DIR: resolves a relative folder" "$out" "STUB --install=$work/rel/Daybreak --screen=title"

# --- the package folder itself (unpacked inside the game folder) ---------------------
drop="$work/drop in"
make_install "$drop"
make_package "$drop"
run "$drop" "$work/home" "$work/config-fresh" "$work/data" "$work/cwd"
[ "$status" = 0 ] || bad "drop-in: expected exit 0, got $status"
expect "drop-in: uses the package folder" "$err" "(the package folder)"

# --- a remembered folder that is gone falls through to the next candidate -----------
mkdir -p "$work/config-stale/daybreak-decomp" "$work/data-stale/Higurashi-Daybreak"
printf 'version = 4\n\n[game]\ninstall_dir = %s\n' "$work/gone" \
    > "$work/config-stale/daybreak-decomp/settings.conf"
make_install "$work/data-stale/Higurashi-Daybreak"
run "$pkg" "$work/home" "$work/config-stale" "$work/data-stale" "$work/cwd"
[ "$status" = 0 ] || bad "stale remembered folder: expected exit 0, got $status"
expect "stale remembered folder: falls through to XDG data" "$err" "(XDG data)"

# --- the retired install.conf (issue #22) is migrated once, then removed ------------
legacy="$work/config-legacy/daybreak-decomp"
mkdir -p "$legacy"
printf 'version=1\ndirectory=%s\n' "$game" > "$legacy/install.conf"
run "$pkg" "$work/home" "$work/config-legacy" "$work/data" "$work/cwd"
[ "$status" = 0 ] || bad "legacy install.conf: expected exit 0, got $status"
expect "legacy install.conf: its folder is used" "$out" "STUB --install=$game --screen=title"
expect "legacy install.conf: is named as the source" "$err" "(the old install.conf)"
expect "legacy install.conf: the move is reported" "$err" "settings.conf"
[ ! -e "$legacy/install.conf" ] && ok || bad "legacy install.conf: the retired file is removed"

# A legacy file whose folder is gone is not better than any other dead candidate: the
# search continues and the file stays where it is.
stale_legacy="$work/config-legacy-stale/daybreak-decomp"
mkdir -p "$stale_legacy"
printf 'version=1\ndirectory=%s\n' "$work/gone" > "$stale_legacy/install.conf"
run "$pkg" "$work/home" "$work/config-legacy-stale" "$work/data-stale" "$work/cwd"
[ "$status" = 0 ] || bad "stale legacy install.conf: expected exit 0, got $status"
expect "stale legacy install.conf: falls through to XDG data" "$err" "(XDG data)"
[ -e "$stale_legacy/install.conf" ] && ok || bad "stale legacy install.conf: an unused one is left alone"

# --- an incomplete package ----------------------------------------------------------
broken="$work/broken package"
make_package "$broken"
rm "$broken/assets/fonts/NotoSansCJKjp-Regular.otf"
run "$broken" "$work/home" "$work/config" "$work/data" "$work/cwd"
[ "$status" = 1 ] || bad "incomplete package: expected exit 1, got $status"
expect "incomplete package: names the missing font" "$err" "assets/fonts/NotoSansCJKjp-Regular.otf"
expect "incomplete package: says to unpack again" "$err" "Unpack the release archive again"

# --- --help and --version -----------------------------------------------------------
run "$pkg" "$work/home" "$work/config" "$work/data" "$work/cwd" --help
[ "$status" = 0 ] || bad "--help: expected exit 0, got $status"
expect "--help: documents the search order" "$out" "XDG_DATA_HOME/Higurashi-Daybreak"
expect "--help: documents the remembered folder" "$out" "settings.conf"
run "$pkg" "$work/home" "$work/config" "$work/data" "$work/cwd" --version
[ "$status" = 0 ] || bad "--version: expected exit 0, got $status"
expect "--version: prints the packaged version" "$out" "daybreak 0.1.0"

printf 'launcher_test: %d checks, %d failure(s)\n' "$checks" "$failures"
[ "$failures" = 0 ] || exit 1
