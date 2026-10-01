# Agent guide — local recomposition

> For automation agents doing naming/review work on the decompiled
> corpus. Condensed from `docs/archive/AGENT_LOCAL_ONBOARDING.md`.
> Shared pipeline background lives in `docs/pipeline.md` — read that first.

## Your loop

1. Check `research/progress/coverage.json` — take the top `hot_spots`.
2. For each function: read `research/decompiled/FUN_<addr>.c`, propose a
   name, list `depends_on_unresolved`, note ambiguities.
3. Write to `research/symbols/functions.json` with `status: suggested`.
4. Add ambiguities to `research/symbols/notes.json`.
5. Run `ingest → generate_recomp → coverage_report`, commit per
   `docs/conventions.md` §6.

## What you do / don't do

- DO: suggest names, type hypotheses, ambiguity notes, dependency lists.
- DON'T: edit `research/recomp/` (generated), rename in Ghidra, promote
  past `suggested` (that's architect/operator), invent logic for
  ambiguous code (use `// TODO(decomp): …`).

## Schema (minimal)

```json
{
  "FUN_00401230": {
    "suggested_name": "ParseAnimationHeader",
    "confidence": "low|medium|high",
    "status": "suggested",
    "source_file": "research/decompiled/FUN_00401230.c",
    "signature_hash": "<from ingest.py — never hand-write>",
    "depends_on_unresolved": ["FUN_004025a0"],
    "suggested_by": "agent:<your-name>"
  }
}
```

`signature_hash` comes from `ingest.py` (hash of normalized body).
`depends_on_unresolved` non-empty blocks `locked` later.

## Confidence guide

- `high`: called with a telling string/guid, or behavior is unambiguous
  (e.g. called with `"data/bgm/title.ogg"` → audio loader).
- `medium`: role clear from callers/callees, details fuzzy.
- `low`: large function (500+ lines — decompiler artifacts likely),
  or pure guess. Say so.

## Offline sources (no MCP needed)

- Body: `research/decompiled/*.c`
- Callers/callees: `research/binary_data/callgraph/full_call_graph.txt`
- Strings: `research/binary_data/strings/` (22 filters + full list)
- Types: `research/binary_data/types/`
- Prior suggestions: `research/symbols/functions.json` (check
  `suggested_by: agent:extraction` first — don't duplicate blindly;
  disagreements go in `notes.json`, operator decides)
