#!/usr/bin/env bash
# wt-setup.sh — create and pre-warm an isolated worktree for one issue.
#
#   tools/wt-setup.sh <slug> <branch> [base-ref]
#
# Creates <worktree-root>/<slug> on <branch> from <base-ref> (default main),
# hardlinks third_party/, symlinks the game install, and configures + builds the
# Linux target with ccache so a worker's first build is a cache hit (~30 s
# instead of a full rebuild).
#
# WHY this layout: one issue = one branch = one worktree = one agent, with the
# coordinator owning main (docs/agents/orchestration.md). Two details make the
# isolation cheap:
#   * third_party/ is hardlinked, not copied — 61 MB of inodes that no build
#     writes to, so the link count is safe.
#   * the game install is symlinked at the worktree ROOT, so the documented
#     `--install=Higurashi-Daybreak` resolves from that root. An absolute path
#     to another copy, or running from a different cwd, fails as
#     `cannot read data/item/001.dat`.
#
# Worktrees go BESIDE the checkout, not inside it, so a worker's `git status`
# never sees another worker's build outputs. Handing anyone the shared install:
# it is one directory, symlinked by every worktree — never rename or hide it to
# simulate a missing install, because that contaminates every other agent.
#
# Overrides: DAYBREAK_INSTALL (install path), DAYBREAK_WORKTREES (worktree root).
set -euo pipefail

slug=${1:?usage: wt-setup.sh <slug> <branch> [base-ref]}
branch=${2:?usage: wt-setup.sh <slug> <branch> [base-ref]}
base=${3:-main}

primary=$(git -C "$(dirname "$0")" rev-parse --show-toplevel)
install=${DAYBREAK_INSTALL:-$primary/Higurashi-Daybreak}
root=${DAYBREAK_WORKTREES:-$(dirname "$primary")/dbd-worktrees}
wt="$root/$slug"

if [ ! -d "$install" ]; then
    echo "no game install at $install (set DAYBREAK_INSTALL, or fetch it)" >&2
    exit 1
fi
[ -e "$wt" ] && { echo "worktree $wt already exists" >&2; exit 1; }
mkdir -p "$root"

git -C "$primary" worktree add -b "$branch" "$wt" "$base"

cp -al "$primary/remake/foundation/third_party" "$wt/remake/foundation/third_party"
ln -s "$install" "$wt/Higurashi-Daybreak"

cmake -S "$wt/remake/foundation" -B "$wt/remake/foundation/build/linux" -GNinja \
    -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER_LAUNCHER=ccache >/dev/null
cmake --build "$wt/remake/foundation/build/linux" >/dev/null

echo "worktree ready: $wt  branch=$branch  base=$base"
