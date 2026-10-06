# NPR experiments (issue #25) — evidence, cost and a recommendation

> Written 2026-10-05 on `feat/issue-25-npr-experiments`. Issue #25 is an **experiment**
> issue: it asks which modern anime/NPR techniques improve Higurashi Daybreak without
> erasing its identity, and its definition of done is a set of captures plus a
> recommendation. Nothing here is a new art direction, and nothing here changes what the
> game renders by default.
>
> **The recommendation in this file is mine. The decision is the human's.** Every number
> below is measured on the machine that ran the captures and is reproducible with the
> commands printed beside it.

## 1. What was built

One switch family, `--npr=<spec>`, plus `--pose-step=<n>` and `--bench=<n>`. The spec is a
comma-separated list applied left to right, so a composed arm is a longer list rather than
a new flag:

| modifier | experiment | what it does |
|---|---|---|
| `off` | — | every experiment off; the default state |
| `on` | D/E stack | soft bands + a camera-relative key + secondary normals + a restrained rim |
| `bands:hard\|soft\|three`, `soft:<f>` | B | the banding curve: a hard step, a short smoothstep, or a second darker band |
| `shadow:<#rrggbb>\|none` | C | the shadow tint (default `#dbc0c7`, a violet-grey; the `on` preset uses `#e0c7d1`) |
| `key:fixed\|cam\|off`, `keydir:<x,y,z>`, `keystr:<f>` | D | the character key light and its arm |
| `normals\|nonormals`, `mask:<f>` | E/F | light the secondary normals; scale the generated shadow mask |
| `spec\|nospec`, `spectint:`, `specstr:<f>` | G | stylized hard-threshold specular |
| `rim\|norim`, `rimtint:`, `rimstr:<f>` | H | character-only rim light |
| `outline:<f>` | I | the recovered hull width × this (`--toon` required) |

`--pose-step=<n>` quantises the pose clock while the render clock is untouched (J).
`--bench=<n>` renders n frames of the capture scene back to back, waiting for the GPU after
each, and prints the mean frame time.

**What is recovered and what is not.** The toon row (`--toon`) is recovered work from issue
#21 and this issue does not touch it: the outline hull, the shipped ramp, `MaterialColor`,
the eligibility rule and the OFF identity are exactly as landed. Everything under `--npr`
is a **port-side experiment with no RE provenance** — the switches, the curves, the tints
and the generated normals are labelled as such at their definitions
(`src/render/scene_renderer.h`, `src/shaders/model_wgsl.h`, `src/assets/xmodel.h`).

**Web / no-ramp behaviour.** The band, shadow, key, normals, mask, specular and rim
experiments need no shipped asset: they are curve and tint arithmetic, so they work on a
pack that has no `data/directX/toon.cnv`. Only the outline-width experiment (I) needs the
ramp, because the hull is submitted only while the recovered toon row is on and that row
degrades to off without the bitmap. So on a single-directory browser pack, `--npr=on`
still shades but `--npr=outline:<n>` is inert — the same "no game data" path
`ROADMAP-PENDING.md` records for `--toon`, not a silent substitution.

**OFF is byte-identical to the pre-change renderer**, on the two frames this environment
reproduces deterministically:

| frame | no flag | `--npr=off` | recorded pre-#25 value |
|---|---|---|---|
| bind-pose character, 800×600 | `eb191e0f` | `eb191e0f` | `eb191e0f` (`ROADMAP-PENDING.md`) |
| stage01, 400×300 | `a7049fe3` | `a7049fe3` | `a7049fe3` (same) |
| 4-view battle, 960×540 | *not reproducible here* | *not reproducible here* | `bcfd50ca` (same) |

The third row is an environment finding, not a regression: the `--screen=battle
--local-players=4` capture returns a **different hash on every run of the same binary** in
this session (measured `304bad08`, `5e04bdef`, `6f82accc`, `5ceb8c02` back to back), and it
does so at the pre-#25 commit too. Live input held by another process on this machine
reaches the demo's device queues, which moves the match's synthetic pads and therefore the
cameras and the fight; `tests/hud_cell_scale.py`, which uses the same recipe, fails here for
the same reason and also fails at the pre-#25 commit with this work stashed. Neither frame
is used as evidence in this document.

The identity is pinned by `tests/npr_experiments.py` on the character frame, and it is the
reason the experiments take a second vertex entry point (`vs_npr`) instead of a branch
inside `vs_main`: a branch — or even a `select` — changes how the driver compiles the
unmodified path, and the OFF frame moved by a pixel when that was tried.

## 2. The test scene

| | |
|---|---|
| character | `rena:0` (costume 0), bind pose (`--no-anim`), no stage |
| camera | the demo's automatic bounds framing, identical in every arm (`camera auto at [107 129 -116] looking at [0 70 7] (distance 173)`) |
| size | 800×600 — the original's own canvas, which is what the outline constants are sized for |
| capture | `--headless --frames=3 --out=<file>` |

Command (one arm; every capture below is this line with `$FLAGS` substituted):

```bash
cd remake/foundation/build/linux
I=../../Higurashi-Daybreak
./foundation_demo --headless --install=$I --character=$I/data/rena:0 --no-anim \
  --frames=3 --size=800x600 --out=/tmp/npr/<arm>.ppm $FLAGS
```

A second, gameplay-distance scene was captured for the composed stack only: a scripted
`--versus` at 960×540 with the arena camera (the command is in §6). It confirms the stack
survives at gameplay distance; the numbers in §3–§5 are the close scene, which is where a
1–2 px outline and a band edge are actually measurable.

## 3. The experiments, arm by arm

Captures are committed as PNGs under `remake/tests/npr-evidence/captures/`; the `.log`
beside each one is the demo's own output for that run. `A_baseline` is the reference for
every "changed px" number.

| arm | flags | capture | what changed vs baseline | recommendation |
|---|---|---|---|---|
| A | *(none)* / `--npr=off` | `A_baseline.png`, `A_npr_off.png` | — (byte-identical to each other) | **keep as the default** |
| A' | `--toon` | `A_toon.png` | the recovered technique: outline rim + ramp surface | keep (already landed) |
| B1 | `--npr=bands:hard,shadow` | `B_hard.png` | 20535 px; the shadow side is one flat tinted level | **keep** |
| B2 | `--npr=bands:soft,shadow` | `B_soft.png` | 22518 px; a short transition instead of a step | **keep** |
| B3 | `--npr=bands:three,shadow` | `B_three.png` | 22987 px; a second, darker band under the terminator (10680 px darker than B1) | keep, second choice |
| C1 | `--npr=bands:soft,shadow,mask:0` | `C_shadow_nomask.png` | the band curve with the generated mask pinned neutral | the F control |
| C2 | `--npr=bands:soft,shadow,mask:1` | `C_shadow_mask.png` | as B2 with the mask on (the default) | see §5, F |
| D1 | `--npr=bands:soft,shadow` | `D_key_off.png` | = B2: world light only | the D control |
| D2 | `+key:fixed` | `D_key_fixed.png` | +28969 px brighter, 0 darker | **keep** |
| D3 | `+key:cam` | `D_key_cam.png` | +13234 px brighter, 0 darker; a different picture from D2 | **keep, preferred** |
| E | `--npr=normals` | `E_normals.png` | 40672 px of surface shading changed, silhouette moved by **0** px | **keep** |
| F1 | `--npr=bands:hard,shadow,mask:0` | `F_mask_off.png` | the generated mask pinned neutral | the F control |
| F2 | `--npr=bands:hard,shadow,mask:1` | `F_mask_on.png` | a different frame from F1 | see §5 |
| G | `--npr=spec` | `G_spec.png` | +11262 px brighter, 0 darker | keep, restrained |
| H | `--npr=rim` | `H_rim.png` | +49307 px brighter, 0 darker | keep, restrained |
| I1 | `--toon --npr=outline:1` | `I_outline_1.png` | byte-identical to `--toon` alone | the identity of the experiment |
| I2 | `--toon --npr=outline:2` | `I_outline_2.png` | +1125 rim px, 12 lost | available, not recommended as a default |
| I3 | `--toon --npr=outline:0.4` | `I_outline_half.png` | +1 / −678 px: a thinner rim | available |
| D+E | `--npr=on` | `DE_stack.png` | 68861 px changed (+39737 / −26210) | **the recommended stack** |
| A'+D+E | `--toon --npr=on` | `A_toon_on_stack.png` | the recovered row plus the stack | the composed state to look at |

`CONTACT_baseline_hard_soft_stack.png` is a 2×2 sheet (baseline / hard / soft / stack) for
a first look.

### What each experiment looks like, in words

* **B (bands).** The baseline shades the skin, the white shirt and the skirt as smooth
  gradients. Any band arm replaces the shadowed side of each surface with one flat value,
  which is where the "anime" read comes from — the face and the collar gain a drawn edge
  instead of a gradient. **Hard and soft at the default width (0.06) are nearly the same
  picture**: they differ on 4236 px of 72284, i.e. the terminator is a thin line either
  way. A 0.3-wide transition separates them (21943 px) and reads as a soft, painted edge
  rather than a step. The 3-band arm adds a second, darker region (the Guilty Gear
  "under the chin / under the hair" read); it is the most stylized of the three and the
  one most likely to need per-character tuning.
* **C (colored shadows).** The shadowed side of the white shirt goes violet-grey instead
  of grey. Only the diffuse term is tinted, so the ambient structure and the specular-free
  whites survive; measured against the same curve with a neutral tint, the shadowed set's
  red/green ratio rises and **no pixel gets lighter**.
* **D (character key).** The camera-relative arm lifts the face and the front of the
  silhouette while the world light still carries the frame; the character-relative arm
  does the same in the fighter's own frame. Both are pure additions (+28969/−0 and
  +13234/−0 px). This is the cheapest readability win in the set and the one that survives
  the fighter turning away from the stage's light.
* **E (secondary normals).** 42.6° mean deviation from the geometric normals on rena,
  built once from the bind-pose geometry (16-cell clusters, three neighbour passes, an
  orientation hint taken from the mesh's own normals, a flip guard). The shading becomes
  broader and the noisy small-scale variation on the hair and the skirt calms down, while
  the silhouette is bit-for-bit the same mesh — measured 0 px added or lost.
* **G/H (specular, rim).** The specular is a hard-threshold half-vector lobe (a drawn
  highlight, not a sliding one); the rim is a fresnel edge on the character only. Both are
  additive and both are easy to overdo — at the shipped strengths the rim is visible on
  the silhouette and the specular is a small highlight on the hair.
* **I (outline width).** The recovered 1.1 px rim is what `--toon` already draws; the
  experiment exists to answer "should it be thicker?", and the answer from the captures is
  that **the recovered width is already the right one at this camera distance**. At 2× the
  rim starts to read as a drawn border and eats the fine hair strands; at 0.4× it nearly
  disappears.

## 4. Cost

`--bench=400` on the close scene (mean of 400 frames, GPU waited after each submit,
minimum of three runs of the same command), and `--bench=300` on the 4-view 960×540 battle
scene:

| arm | close scene, min ms/frame | battle scene, min ms/frame |
|---|---|---|
| baseline | 0.0567 | 0.1883 |
| `--toon` | 0.0617 | 0.1992 |
| `--npr=on` (stack) | 0.0602 | 0.1679 |
| hard band | 0.0625 | — |
| soft band | 0.0597 | — |
| 3-band | 0.0562 | — |
| shadow | 0.0605 | — |
| key:cam | 0.0626 | — |
| normals | 0.0587 | — |
| spec | 0.0607 | — |
| rim | 0.0582 | — |
| `--toon --npr=outline:2` | 0.0619 | — |

**Read these numbers honestly.** The run-to-run spread of a single configuration
(0.0567–0.0668 on the baseline) is larger than any difference between arms, and the stack
even measured faster than the baseline on the battle scene. At this scene size the frame
cost is dominated by fixed per-frame work (submission, the queue wait, the uniform fill),
not by the GPU's fragment work, so **these numbers cannot resolve the cost of a fragment
term**. What they do establish is an upper bound: no technique here adds a measurable
millisecond, and none adds a draw call — every experiment is a draw-time state change on
draws that already exist. The one structural cost is the secondary normal stream
(16 bytes/vertex on character and weapon meshes only, built once at upload); the outline
hull's second geometry pass is issue #21's cost, not this issue's.

For a real cost profile the measurement would have to run at a resolution and a scene
complexity where the GPU is the bottleneck; `--bench` is the instrument for that, and it is
committed for whoever needs it.

## 5. What the harness cannot see, and what needs authoring

* **F (shadow-threshold masks) is the weakest experiment here.** The mask is *generated*
  (a per-vertex scalar from how far the smoothed normal faces up), and the captures show
  it moving the band boundary — `mask:0` and `mask:1` are different frames — but the
  generated version cannot know where an artist wants the shadow to fall. A real version
  wants authored data: a per-vertex channel or a small mask texture, neither of which the
  install ships. The harness is the thing to keep; the generated mask is a placeholder.
* **Secondary normals are generated, not authored.** The Guilty Gear reference is explicit
  that the normals are *edited by an artist* per region. The generated version is a
  credible first pass (it produces broad, clean shading), but per-character authored
  normals would be better and are an authoring task, not a renderer one.
* **J (stepped pose presentation) is implemented but not evaluated.** `--pose-step=<n>`
  exists and quantises the pose clock without touching the frame clock; no capture in this
  report uses it, because judging it needs motion, and a still frame cannot show whether
  stepping reads as authored or as dropped frames. **Not run.**
* **K (VFX as unlit stylized geometry) is not run.** The effect cards from issue #17
  already draw unlit through `Pass::Effect`, so the experiment's premise ("some effects
  should not be lit") is already the renderer's behaviour for the cards it has; what is
  missing is the comparison capture and any statement about *which* effects should change.
  **Not run.**
* **L (impact/anime combat presentation) is not run.** Hit-stop, flashes, speed lines,
  trails and afterimages all need the match's event timeline; the `--versus`/`--match`
  captures are the place to do it, and it is a separate issue's worth of work. **Not run.**
* **M (stage-aware colour integration) is not run.** The parameters exist in principle
  (shadow tint, rim colour, key tint, exposure offset are all per-appearance already), but
  a stage-dependent policy needs a decision about where the policy lives (stage data vs
  code) and a per-stage review of all 13 stages. **Not run.**

## 6. What the human should look at

All paths are relative to the repository root. Each capture is the same frame, camera and
pose; open them side by side.

1. **`remake/tests/npr-evidence/contact-baseline-hard-soft-stack.png`** — the four-up
   sheet. This is the fastest read: baseline (top-left), hard band (top-right), soft band
   (bottom-left), the recommended stack (bottom-right).
2. **`remake/tests/npr-evidence/captures/A_baseline.png`** vs
   **`.../DE_stack.png`** — the A/B the issue asks for first. Does the stack improve the
   read at this distance, or does it look like a filter?
3. **`.../B_hard.png`** vs **`.../B_soft.png`** — the band edge. At the default width they
   are nearly the same picture; this is the decision about whether the terminator should
   be a step or a transition.
4. **`.../C_shadow_nomask.png`** vs **`.../C_shadow_mask.png`** — the violet-grey shadow
   and the generated mask. If the mask's placement looks wrong to you, that is the
   expected result: it is generated, not authored (§5).
5. **`.../D_key_off.png`** vs **`.../D_key_cam.png`** — the key light. The readability
   question: does the face hold up better with it?
6. **`.../E_normals.png`** vs **`.../A_baseline.png`** — the broad shading. Look at the
   hair and the skirt: calmer, or flatter?
7. **`.../I_outline_1.png`** vs **`.../I_outline_2.png`** vs
   **`.../I_outline_half.png`** — the outline width, with `--toon` on.
8. **`.../A_toon_on_stack.png`** — the recovered row and the stack together, which is what
   the recommended state would actually look like.
9. **Gameplay distance** — `remake/tests/npr-evidence/captures/GAMEPLAY_vs_off.png` vs
   `.../GAMEPLAY_vs_stack.png`: the same scripted versus frame at 960×540 with the stack
   off and on. This is the read that decides whether the stack is art or a filter, and it
   is the one to judge the recommendation by. (Regenerate with the command below; this
   capture IS deterministic — md5 `b6c2ded7` / `b6f7fea9` — unlike the 4-view battle
   capture the identity table calls out.)

```bash
cd remake/foundation/build/linux
I=../../Higurashi-Daybreak
for s in "--npr=off" "--npr=on"; do
  ./foundation_demo --headless --install=$I --stage=$I/data/stage01 \
    --character=$I/data/rena:0 --enemy=$I/data/mion:0 --versus --camera=arena \
    --frames=300 --size=960x540 --out=/tmp/npr/vs_$(echo $s|tr -d '=').ppm $s
done
```

## 7. Recommendation

> **Superseded by §8 (2026-10-06, issue #27).** Kept as the record of what was recommended
> on the captures this section names; §8 re-measured them at three resolutions, in a fight
> scene and with every parameter probed at its extremes, and it changes the answer for B,
> E and F. Read §8 before acting on this table.

**Keep the harness, keep four techniques, and do not change the default yet.**

| technique | keep? | why |
|---|---|---|
| the `--npr` harness + `--bench` | **yes** | it is the deliverable; every later art decision can be tested with it |
| E — secondary normals | **yes, first** | the largest shading-quality change for no authoring and no silhouette risk; 0 px of silhouette movement |
| D — character key light (camera-relative) | **yes** | the largest readability win, purely additive, and it is the technique that keeps working when the fighter turns away from the stage's light |
| C — colored shadows | **yes** | cheap, additive-only, and it is what makes a band read as art rather than as a threshold |
| B — bands (soft, with the hard step available) | **yes** | the core of the anime read; the default width should stay short (0.06) |
| H — rim light | yes, at a restrained strength | silhouette separation; easy to overdo |
| G — stylized specular | yes, small | reads on hair and metal; the current lobe is deliberately hard-edged |
| I — outline width | **keep as a control, ship the recovered 1.0** | the recovered width is right at gameplay distance; the parameter is useful for future stages/cameras |
| F — generated shadow mask | keep the switch, **drop the generated data** | the placement is an art decision; the generated mask is a placeholder that should be replaced by authored data or removed |
| J, K, L, M | not run | see §5; each is a separate evaluation |

The recommended stack is therefore **E + D(camera) + C + B(soft) + a restrained rim**, which
is what `--npr=on` composes (it also turns the rim on; the specular is deliberately left
out of `on` because a highlight is the easiest thing to over-apply). It does not change the
default: `--npr=on` is opt-in, and the options screen still has exactly the recovered rows
it had before.

**What would change this recommendation:** if the composed stack at gameplay distance
(§6.9) reads as a filter rather than as the game's own art, drop C and the rim first —
they are the two that add colour rather than structure — and keep E and D.

## 8. Issue #27 — the evidence review, and what it changes (2026-10-06)

> Written on `fix/issue-27-npr-evidence` after the human rejected §3–§7's evidence: the A/B
> prints look identical at a glance, only one resolution was tested (800x600 bind pose),
> and "N pixels changed" cannot tell *subtle* from *not running*. **This section supersedes
> §7's recommendation.** §1–§6 stay as the record of what was built and measured then;
> where they disagree with this section, this section is the measurement.
>
> Everything here is reproducible with
> `python3 remake/foundation/tests/npr_evidence.py --demo remake/foundation/build/linux/foundation_demo --install <game dir>`
> (contact sheets, region metrics and the sweeps) and
> `python3 remake/foundation/tests/npr_experiments.py <demo> <game dir>` (the no-op gate).
> Captures: `remake/tests/npr-evidence/issue-27/`. Numbers below are from the machine that
> ran it; sha256 prefixes identify each frame.

### 8.1 The scene, and why it changed

| | |
|---|---|
| combo | **Rena 0** — 竜宮レナ + 愛用の鉈 (`data/rena/00.x` + `data/item/01.x`, id 001). Rule 7: no bare fighter |
| pose | bind pose (`--no-anim`) |
| stage | none: the background is the pass's clear colour (40,42,54), so the character mask is exact |
| camera | `--camera=bounds` |
| sizes | 640x360, 960x540, 1920x1080 — all 16:9, exact multiples, one world camera (the demo prints `camera bounds at [163 147 -202] looking at [0 65 6] (distance 276)` in all three) |
| fight scene | `--versus --camera=arena`, stage01 (schoolyard_day), **Rena 0 vs Mion 0** (Mion 0 = コテ拳銃, `data/item/04.x`), 300 frames, 960x540 |
| 4-view | `--screen=battle --local-players=4`, stage03, 300 frames, 960x540 (front-end roster: Rena 0, Mion 0, Mion 0, Rika 0) |

**`--camera=auto` is not usable for a weaponed fighter at 16:9**: the framing fits the
bounds radius (distance = 2R, fovY 45°), and an attached weapon grows R and drops the
bounds centre, so the top of the hair leaves the frame — 333 px of hair sit on row 0 of the
1080p capture. That is a harness-framing defect, not a technique's, and `bounds` (1.53x the
distance) frames the whole figure at every resolution. §2's captures are all `auto`, and
they had no weapon attached, which is the only reason the framing fitted them.

The regions the metrics read are drawn on every sheet: **rim** = figure pixels within
2/3/6 px of the silhouette (scaled with the frame; the recovered toon hull is ~0.7/1.0/2.0
px there), **face** = 890,250-1045,370 at 1080p, **hair** = 874,174-1063,250, **torso** =
880,350-1050,500, plus `whole`, `interior`, `background` and `affected` (the set the arm
moved, reported with its share of the figure).

### 8.2 The no-op sanity check (item 3): **three arms do not do what they claim**

Every arm's own parameter was swept to an extreme at 960x540, with its control beside it.
A step that renders **byte-identical** to its control is not a subtle technique: the
parameter is not reaching the picture. The probe is now permanent —
`tests/npr_experiments.py` probes 19 arms at an extreme (17 in the close-up, 2 in a fight
frame) and fails on any identity that is not listed in its `KNOWN_INERT` table, which names
issue #27 and fails again if an arm starts drawing, so the list cannot rot.

| arm | parameter at its extreme | measured |
|---|---|---|
| **B bands, hard** | `bands:hard,shadow:none` | **byte-identical to no flag** |
| **B bands, soft 0.06** | `bands:soft,shadow:none` | **byte-identical to no flag** |
| **B softness `soft:<f>`** | 0.02 / 0.06 / 0.30 / 1.00, neutral tint | **all four byte-identical to no flag** |
| B bands, 3-band | `bands:three,shadow:none` | differs: darkens the shadow core (2.0% of the figure, dE 0.79) |
| **F mask `mask:<f>`** | 0 / 1 with a neutral tint | **byte-identical**; with the shipped tint it moves the *tint* boundary (mask -1/0/1/3 = 21.9/16.4/11.4/0.6% visible) |
| C tint | `shadow` vs `shadow:none` | differs (11.1%, dE 2.54) |
| D key | `key:cam`, `key:fixed`, `keystr:0/0.35/1.5` | differs, monotone in the strength |
| **E normals** | `normals` in the **fight scene** | **byte-identical** at frames 150 and 300 |
| G spec | `spec`, `specstr:2` | differs (16.3%, dE 7.26 at the default) |
| H rim | `rim`, `rimstr:2` | differs (36.9%, dE 13.41 at the default) |
| I outline | 0.25 / 1.0 / 2 / 3 over `--toon` | 1.0 is byte-identical to `--toon` alone (the identity the recovered width needs); 0.25/2/3 differ |

**B — the band curve never bands the shading.** `model_wgsl.h:385` is
`diffuse = diffuse * mix(draw.nprBand.rgb, vec3<f32>(1.0), w)`. With the neutral tint of
its own control that mix is white *for every* `w`, so the curve is an algebraic identity:
the hard step, the smoothstep and its width cannot change a pixel. What the curve really
does is select **how much of the C tint** is applied, which is why §3's B rows moved
20 535 px — that was the tint, not the band. Measured on one flat material (the skirt), the
tinted shadow keeps its gradient: the shadowed set's 5-95% luminance spread goes
33.2 -> 28.1 (ratio **0.848**) for hard and 36.0 -> 32.5 (0.900) for soft 0.06, against the
~0.05 a surface replaced by *one flat value* would show. The doc's "one flat value" is not
what is implemented. The **three**-band arm is the exception: `nprBandCore` multiplies the
diffuse below N·L < 0.25, so it really does darken the shadow core — by 45%, and only where
a surface reaches that far into shadow (0 px on screen in the 300-frame fight, 583-1008 px
at frames 30-300 with the fighters lit differently).

**F — the mask has nothing to hold.** `model_wgsl.h:383` feeds the mask into the band
*weight*, so it moves the tint boundary and nothing else. With the tint held neutral,
`mask:0` and `mask:1` are byte-identical. §5 already wanted authored data over the
generated mask; the measurement now says the switch as implemented cannot do its job at
all, so it is a drop, not a "replace the data later".

**E — the normals never reach a fight scene.** `--npr=normals` is byte-identical to
`--npr=off` in `--versus` (frames 150 and 300) and in the 4-view battle, while in the
close-up it is the largest change of any arm (44.1% of the figure, dE 20.73). The cause is
in the renderer, not the shader: `scene_renderer.cpp` caches **one pipeline per pass**
(`WGPURenderPipeline boundPipelines[kPassCount]`), created with the `npr` flag of the
*first* draw of that pass. A fight scene draws the stage first (`toon=false`), so the
non-NPR `vs_main` entry is cached for `Pass::Opaque` and every later character draw reuses
it; only the stage-less close-up, whose first opaque draw *is* a character, ever gets
`vs_npr`. The fragment-side arms (tint, key, rim, spec) are unaffected because they live in
`fs_main`, which is why the defect hid for a whole issue. The reach sheet measures all nine
arms in the fight and only E comes back identical.

### 8.3 What each technique would make a player notice (item 5)

Numbers are the 1920x1080 close-up unless stated. "Reads" uses a declared bar — READS at
10% of the figure visibly moving (>=8/255 in a channel) or dE 3.0; the second clause allows
a technique that only lights part of the figure (the key light) to pass on the set it
lands on, with that set's share printed beside it.

| technique | what a player sees | measured | evidence passes 1-4? | recommendation |
|---|---|---|---|---|
| **B bands** | nothing from the curve; with the shipped tint, a violet shadow whose edge is hard or short. No flat band, no drawn terminator | curve = byte-identical; hard vs soft (both tinted) differ on 0.4% of the figure, dE 0.24 | **no** (item 3) | **drop the band arm as documented** — the claim is false; re-implementing it (make the weight scale the diffuse) is ~3 lines but is a shading decision for a follow-up issue |
| **C colour shadow** | the shadowed side reads cool violet instead of grey: 30% of the figure, -4.9 levels on those pixels, dE 8.4 | 11.1% visible, dE 2.54; face 14.8%, hair 16.2%, torso 14.4% | yes | **keep**, tint strength/colour is authoring; the default #dbc0c7 is deliberately gentle |
| **D key light** | the face and the camera-side of the fighter lift; the *fixed* arm is ~3x the camera arm at the same strength | cam: 5.1% visible, dE 1.34, on 13.7% of the figure at dE 9.8; fixed: 15.0%, dE 4.17 | yes (close-up); at fight distance 0.8% of the P2 box | **keep the switch and drop the "preferred" label on `cam`**: `key:fixed` measurably does more at the same strength, and 0.35 is a floor, not a settled value (1.5 -> 12.0% visible) |
| **E secondary normals** | in the close-up: hair and skirt shade in broad, calm gradients and the figure darkens ~8.5 levels; in a fight: nothing at all | close-up 44.1% visible, dE 20.73, hair 81.6%; fight: byte-identical | **no** (item 3, fight scene) | **fix the reach defect first** (4 lines, §8.5), then re-measure; do not keep it on the close-up evidence alone |
| **F generated mask** | with the tint on, it slides the shadow tint's boundary; with a neutral tint, nothing | mask 0 vs 1 neutral = byte-identical; tinted -1/0/1/3 = 21.9/16.4/11.4/0.6% visible | **no** (item 3) | **drop** (and with it the generated mask data §5 wanted replaced) |
| **G specular** | a hard-edged highlight on the hair and the blade; the pixels it touches are strong | 16.2% visible, dE 7.24; affected 18.1% of the figure at dE 40.0; hair 19.8%, torso 13.0% | yes | **keep**, restrained; it is the arm whose change is a bright shape rather than a gradient |
| **H rim light** | the whole silhouette lights up, not just its edge: at 0.30 it is not "restrained" | 37.0% visible, +6.8 levels, dE 13.43; 77.3% of the figure is touched; rim band 64.4% | yes | **keep the technique, lower the default**: the #25 `on` preset's 0.22 is closer to the doc's own word than the arm default 0.30 |
| **I outline width** | 2x reads as a drawn border around the hair strands; 0.25 nearly disappears | 1.0 is byte-identical to `--toon`; 2 -> +7.4% visible, 0.25 -> 5.4% | yes | **keep the recovered 1.0** (already landed, not part of `--npr`); the scale stays a control |
| **stack `--npr=on`** | everything that reaches: broad shading, a lifted face, a violet shadow edge, a lit silhouette | 66.7% visible, dE 29.59; hair 85.0%, face 70.4% | yes for C, D, G, H — **not** for E (dead in fights) or B/F (inert) | **restate it without B and F, and with E only after the fix** |

### 8.4 "Only one resolution was tested" (items 1-2)

The three resolutions are on every contact sheet at native scale, with 2x crops of the
face, the hair and the torso and a 4x crop of the same face out of the 640x360 frame.
**The measured share of changed pixels is resolution-invariant** — C 11.2/11.1/11.1%, D
5.1/5.1/5.1%, E 44.1/44.2/44.1%, H 37.0/36.9/37.0%, stack 66.8/66.8/66.7% — because every
arm is a per-pixel multiply. What changes with resolution is *legibility*, not the metric:
at 640x360 the figure is 256 px tall and the face 40 px, and the sheets show that the tint
and the rim still read there while the key light and the specular become single pixels.
That is the question the sheets put in front of a human; no count answers it.

Both `dL` (mean luminance change) and `dE` (mean RGB distance) are reported per region
with the before/after mean luminance, because a hue change that keeps luminance (the tint)
would be invisible to `dL` alone: C is -1.48 `dL` but dE 2.54 over the figure and
dE 8.43 over the 30% of it the tint moves, and inside that set the mean colour goes
(111,100,106) -> (108,95,101), i.e. (-3.3, -5.4, -4.9) per channel: red falls least, which
is the violet-grey the tint asks for.

### 8.5 Fight distance and the 4-view frame (item 4)

* `gameplay-<arm>.png` — the fight area at native 960x540 and the P2 box at 4x, one sheet
  per kept arm plus E as the counter-example. The whole frame is a 70 px-tall fighter in a
  stage, so **no arm reaches a whole-frame bar there**; the numbers that matter are the P2
  box (a rectangle, drawn on the sheet) and the human's look at the sheet.
* `reach-versus.png` — the reach table above, with the P2 box magnified for E (identical)
  and H (differs).
* `fourview-2v2.png` — the 2v2 split screen, off/on, each of the four cells magnified 2x.
  The stack changes 11 622 px of the 960x540 frame (2.24% of it, 4 250 px of those by
  >=8/255 - 0.82% of the frame) spread over all four cells (3 427 / 4 142 / 2 407 / 1 646),
  which is what "it reaches every view's draw" looks like at 480x270 per cell.
* **The 4-view capture is deterministic in this environment** — sha256 `0f30fad5…` on two
  runs of `--npr=off` — so §1's "not reproducible here" row is stale: it was measured
  before issue #29 made verification runs ignore physical devices.
* Continuity with §6.9: the `--versus` 960x540 frame with `--npr=off` is still
  **md5 `b6c2ded7…`** and `--npr=on` still `b6f7fea9…`, i.e. the fight frame has not moved
  since the #25 captures.

### 8.6 Recommendation, restated only for what passes

**Keep the harness, keep C, D (with `fixed` re-labelled and a re-tuned strength), G, H (at
a lower default than 0.30) and the recovered outline width. Drop the B band arm as
documented and F's generated mask. Do not recommend E on this evidence: it is the largest
change in the close-up and a no-op in every fight scene.** No default changes: `--npr`
stays opt-in and the Options screen keeps the rows it has.

Two things to do next, in this order:

1. **Fix the reach defect** (`scene_renderer.cpp`: key the pipeline cache on
   `(pass, nprDraw)`, ~4 lines) and re-run
   `npr_evidence.py` — E's fight sheets and the reach table are the acceptance test.
2. **Decide B's fate**: either re-implement the band as a diffuse quantisation (a flat
   level, then the tint on top) — which is a shading decision with a new constant and a
   knock-on re-measure of `three` and F — or delete the band arm and keep C as it is.

### 8.7 Defects this review found, none of them fixed here

Out of scope for an evidence issue; each is small and named with its site.

| # | defect | site | size |
|---|---|---|---|
| 1 | the NPR vertex entry never reaches a fight scene (E dead in `--versus`/`--match`/`--screen=battle`) | `src/render/scene_renderer.cpp`, `boundPipelines[kPassCount]` | ~4 lines |
| 2 | the B curve is only a tint weight, so "bands" never band the shading | `src/shaders/model_wgsl.h:385` | ~3 lines + a shading decision |
| 3 | the F mask has no band to hold: it moves the tint edge only | `src/shaders/model_wgsl.h:383` | follows #2 |
| 4 | `--camera=auto` clips the top of a weaponed fighter at 16:9 (333 px of hair on row 0 at 1080p) | `src/main.cpp` auto framing | framing rule, not a bug in a technique |
| 5 | §3's B and F rows measured the tint, not the technique they name | this file | corrected by this section |
