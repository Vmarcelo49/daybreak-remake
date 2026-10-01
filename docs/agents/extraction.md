# Agent guide — Ghidra extraction

> For automation agents driving the Ghidra/MCP side. Condensed from
> `docs/archive/AGENT_EXTRACTION_ONBOARDING.md`. Note: extraction phases
> 1–12 are complete and the tunnel is closed — this guide is for
> reproducibility and any future re-extraction, not current work.

## What this role was

Drive Ghidra 11.x via the GhidraMCP bridge: recon, function mapping,
prioritization, mass decompilation, call-graph analysis, Ghidra-side
annotation (tags + plate comments), and thematic deep-dives (scene
table, network, render pipeline, anti-analysis).

## What you do / don't do

- DO: read via MCP (`read_memory`, decompile, xrefs, strings); annotate
  with **tags and plate comments**; record name suggestions in
  `research/symbols/functions.json` with
  `suggested_by: "agent:extraction"`.
- DON'T: `rename_function` in Ghidra (forbidden until `locked`);
  use write/byte-edit tools without operator approval; expose the
  tunnel URL; commit keys or `.env`.

## Session setup (archived procedure)

1. Ghidra 11.x + GhidraMCP open on `DaybreakDX.exe`, bridge on
   `localhost:8081`.
2. Ephemeral Cloudflare tunnel for the session only — tear down after.
3. Confirm scope with the operator before starting; never leave the
   tunnel up unattended (it exposes write-capable tools).

## Most-used tool classes

- **Read**: decompile-by-address, read_memory, list strings/imports/
  xrefs, call-graph queries.
- **Annotate (careful)**: tags, plate comments — no renames.
- **Analyze**: hub/dispatcher ranking, anti-analysis sweeps.
- **Prohibited without approval**: anything that writes bytes,
  renames, or exfiltrates outside the repo.

## Hand-off contract

Every extraction finding lands in one of: a `research/binary_data/`
report (`FASE*.md`), a `research/symbols/` suggestion, or a
`research/extraction_phases/` raw dump. Findings without one of these
three are lost — the Ghidra IDB itself is not the record.
