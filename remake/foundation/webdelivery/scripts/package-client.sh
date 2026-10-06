#!/usr/bin/env bash
# Copy the built web client into the Docker build context.
#
#   ./scripts/package-client.sh [build-dir] [dest]
#
# The default build dir is remake/foundation/build/web (what ./build.sh web writes).
# The client is not committed and not part of the repository: it is a build artifact,
# and the only thing the image is allowed to contain besides this server. Keeping the
# copy explicit means the Docker context never includes the tree that holds the game
# install, so an image cannot contain game data even by accident.
set -euo pipefail

here=$(cd "$(dirname "$0")" && pwd)
source_dir=${1:-$here/../build/web}
dest_dir=${2:-$here/client}

if [[ ! -f "$source_dir/foundation_demo.wasm" ]]; then
    echo "package-client: no foundation_demo.wasm in $source_dir" >&2
    echo "  build it first:  (cd $here/.. && ./build.sh web)" >&2
    exit 2
fi

mkdir -p "$dest_dir"
copied=0
for file in "$source_dir"/foundation_demo.{html,js,wasm,data}; do
    [[ -f "$file" ]] || continue
    cp -f "$file" "$dest_dir/"
    copied=$((copied + 1))
done
if [[ $copied -eq 0 ]]; then
    echo "package-client: nothing to copy from $source_dir" >&2
    exit 2
fi
echo "package-client: $copied file(s) -> $dest_dir ($(du -sh "$dest_dir" | cut -f1))"
