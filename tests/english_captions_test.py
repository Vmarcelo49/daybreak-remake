#!/usr/bin/env python3
"""Static guard for built-in bilingual captions in English mode.

Covers literal Words pairs in the port-owned option and online panels. It does
not inspect image text, dynamic values, dialogue or player-provided strings.
"""
import pathlib
import re
import sys

ROOT = pathlib.Path(__file__).resolve().parents[1]
PAIR = re.compile(r'\{\s*"([^"\\]*)"\s*,\s*"([^"\\]*)"\s*\}')
JAPANESE = re.compile(r"[\u3040-\u30ff\u3400-\u9fff\uf900-\ufaff\uff66-\uff9f]")


def main():
    count = 0
    for relative in ("src/frontend/screen_options.cpp", "src/frontend/screen_online.cpp"):
        source = (ROOT / relative).read_text(encoding="utf-8")
        pairs = PAIR.findall(source)
        for japanese, english in pairs:
            if not JAPANESE.search(japanese):
                continue
            assert english and not JAPANESE.search(english), f"{relative}: untranslated English: {english!r}"
            count += 1
        # Detect a missing English literal in the common direct say({"...", ...}) form.
        for expression in re.findall(r'say\(\s*\{\s*"([^"\\]*)"\s*,\s*([^}]*)\}', source):
            japanese, english = expression
            if JAPANESE.search(japanese) and not english.strip().startswith('"'):
                # Online refusal texts come from the shared ASCII refusal_text table.
                assert english.strip().startswith('net::refusal_text('), f"{relative}: unreviewed English expression: {english}"
    assert count >= 50, f"caption pair extraction incomplete: {count}"
    print(f"english_captions_test: {count} bilingual literal pairs checked")
    return 0


if __name__ == "__main__":
    sys.exit(main())
