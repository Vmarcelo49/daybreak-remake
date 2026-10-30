# Local changes to the vendored core

One entry per change: file, what changed, why, and the evidence. Empty means the files match
`MANIFEST.sha256`.

| Date | File | Change | Evidence |
|---|---|---|---|
| 2026-10-30 | `legacy_trig.hpp` | An angle past 2^31 after scaling no longer throws; it takes `_ftol2`'s low 32 bits, or 0 past 2^63. `abs(0x80000000)` is kept in range rather than indexing before the table | **Failure:** random input threw "Legacy angle outside defined conversion range" in matches with Ohishi+2 (`simfuzz 8 2 1 1000 9`, tick 797). **Tier 2:** row 463's bullet 19 at `0x4dbed5`-`0x4dbee2` on the pinned binary adds a clamped signed field to `rand()%30` and loads it with a zeroed high word through `FILD QWORD`, so a negative sum really becomes a pitch near 2^32 in the original. `FUN_0065d010` then uses `FUN_0066b668` (`_ftol2`) and `FUN_0066b65c` (`abs`). Not observed on the original runtime |
| 2026-10-30 | `development_animated_combat.hpp` | Rena+0's row 350 copies `attack_flag` to `native_contact_mode`, so the Hyper EX asks for its camera clip | **Failure:** `native_contact_mode` stayed -1 through the whole row; `battle_rena_full_charge.hpp:108` computed the flag and nothing read it. **Tier 2:** `FUN_0043ffc0` case 0x15e writes `param_1[0x1a1]` (+0x684) every update, 0 before and 1 after `+0xe8` arms at frame 0x32. Rena+1's row 350 is a different body and is unchanged. Regression: `sim_core_test` `test_rena_ex_camera` |
| 2026-10-30 | `asset_search_path.hpp` | `index_directory` resolves archive names to loose files under a prepared tree, for the web build, which has no archives | **Failure:** web battles could not start after M5 (`docs/BUILD-web.md`). **Evidence:** tier 5; `tests/web_match_group_check.py`: `simctl` on only the files a browser downloads gives the same hash as the `.dat` files for all 46 combos over 1200 ticks. |
