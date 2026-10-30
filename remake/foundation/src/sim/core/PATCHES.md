# Local changes to the vendored core

One entry per change: file, what changed, why, and the evidence. Empty means the files match
`MANIFEST.sha256`.

| Date | File | Change | Evidence |
|---|---|---|---|
| 2026-10-30 | `legacy_trig.hpp` | An angle past 2^31 after scaling no longer throws; it takes `_ftol2`'s low 32 bits, or 0 past 2^63. `abs(0x80000000)` is kept in range rather than indexing before the table | **Failure:** random input threw "Legacy angle outside defined conversion range" in matches with Ohishi+2 (`simfuzz 8 2 1 1000 9`, tick 797). **Tier 2:** row 463's bullet 19 at `0x4dbed5`-`0x4dbee2` on the pinned binary adds a clamped signed field to `rand()%30` and loads it with a zeroed high word through `FILD QWORD`, so a negative sum really becomes a pitch near 2^32 in the original. `FUN_0065d010` then uses `FUN_0066b668` (`_ftol2`) and `FUN_0066b65c` (`abs`). Not observed on the original runtime |
