#!/usr/bin/env bash
# Wrapper to run radare2 (and friends) with the right LD_LIBRARY_PATH.
# Usage: ./scripts/r2.sh [r2 args]
#        ./scripts/r2.sh rabin2 -I build/daybreak.exe
TOOLS=/home/z/my-project/tools/r2
export LD_LIBRARY_PATH="${TOOLS}/usr/lib/x86_64-linux-gnu:${LD_LIBRARY_PATH:-}"
# Also export MAGIC so libmagic finds its database
export MAGIC="${TOOLS}/usr/share/file/misc/magic.mgc"
# If first arg is a known r2 tool name, run that binary; otherwise run r2.
tool="${1:-r2}"
case "${tool}" in
    r2|radare2|rabin2|rafind2|rahash2|rasm2|r2pm|r2r|ragg2|rapatch2|rafind2|rarun2|rasign2|rax2|rafs2|r2agent|r2sdb|clang-format-radare2)
        exec "${TOOLS}/usr/bin/${tool}" "${@:2}"
        ;;
    *)
        # Treat as r2 invocation with all args
        exec "${TOOLS}/usr/bin/r2" "$@"
        ;;
esac
