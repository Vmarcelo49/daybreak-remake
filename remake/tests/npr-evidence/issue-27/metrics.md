# NPR evidence, issue #27 - measured

Generated 2026-10-06 19:29:24 by `remake/foundation/tests/npr_evidence.py`. Every number below is a measurement of a committed-demo capture; the recipes are in `metrics.json` (`commands`) and beside each capture under `logs/`.

Scene: **Rena 0 (favourite cleaver)** (Rena 0 = 竜宮レナ + 愛用の鉈), bind pose, no stage, `--camera=bounds`.
Thresholds (a port-side evidence rule, not a renderer constant): READS at 10% visible or dE 3.0; OBVIOUS at 15% / dE 4.0.

Renderer determinism (the control frame captured twice at 1920x1080): sha256 90eda20f5af68e00, identical.

## Techniques (close-up, 1920x1080 unless stated)

### B - B bands - soft 0.06 (the curve alone, neutral tint)

OFF `(no flag)`  ON `--npr=bands:soft,shadow:none`

verdict: **no-op (byte-identical frames)**

| region | px | visible | dL | dE | L off | L on |
|---|---|---|---|---|---|---|
| whole | 100972 | 0.0% | +0.00 | 0.00 | 99.98 | 99.98 |
| rim | 17642 | 0.0% | +0.00 | 0.00 | 98.36 | 98.36 |
| interior | 83330 | 0.0% | +0.00 | 0.00 | 100.33 | 100.33 |
| face | 16271 | 0.0% | +0.00 | 0.00 | 102.45 | 102.45 |
| hair | 11825 | 0.0% | +0.00 | 0.00 | 130.35 | 130.35 |
| torso | 21070 | 0.0% | +0.00 | 0.00 | 161.76 | 161.76 |
| background | 1972628 | 0.0% | +0.00 | 0.00 | 42.44 | 42.44 |

1920x1080: figure 100972 px, visible 0.0%, dL +0.00, dE 0.00 (byte-identical)

640x360: figure 11221 px, visible 0.0%, dL +0.00, dE 0.00 (byte-identical)

960x540: figure 25242 px, visible 0.0%, dL +0.00, dE 0.00 (byte-identical)

### C - C coloured shadow (the default violet-grey tint)

OFF `--npr=bands:soft,shadow:none`  ON `--npr=bands:soft,shadow`

verdict: **reads**

| region | px | visible | dL | dE | L off | L on |
|---|---|---|---|---|---|---|
| whole | 100972 | 11.1% | -1.48 | 2.54 | 99.98 | 98.50 |
| rim | 17642 | 4.6% | -0.63 | 1.04 | 98.36 | 97.73 |
| interior | 83330 | 12.5% | -1.66 | 2.85 | 100.33 | 98.67 |
| face | 16271 | 14.8% | -2.20 | 3.49 | 102.45 | 100.25 |
| hair | 11825 | 16.2% | -2.50 | 3.89 | 130.35 | 127.85 |
| torso | 21070 | 14.4% | -2.03 | 3.20 | 161.76 | 159.74 |
| affected | 30368 | 36.9% | -4.93 | 8.43 | 102.78 | 97.86 |
| background | 1972628 | 0.0% | +0.00 | 0.00 | 42.44 | 42.44 |

1920x1080: figure 100972 px, visible 11.1%, dL -1.48, dE 2.54

640x360: figure 11221 px, visible 11.2%, dL -1.49, dE 2.55

960x540: figure 25242 px, visible 11.1%, dL -1.49, dE 2.54

### D - D character key light (camera-relative)

OFF `--npr=bands:soft,shadow`  ON `--npr=bands:soft,shadow,key:cam`

verdict: **below the bar**

| region | px | visible | dL | dE | L off | L on |
|---|---|---|---|---|---|---|
| whole | 100972 | 5.1% | +0.67 | 1.34 | 98.50 | 99.18 |
| rim | 17642 | 19.1% | +2.07 | 4.13 | 97.73 | 99.80 |
| interior | 83330 | 2.1% | +0.38 | 0.75 | 98.67 | 99.04 |
| face | 16271 | 3.2% | +0.45 | 0.94 | 100.25 | 100.69 |
| hair | 11825 | 7.9% | +0.96 | 1.63 | 127.85 | 128.81 |
| torso | 21070 | 5.6% | +0.54 | 1.28 | 159.74 | 160.28 |
| affected | 13863 | 37.1% | +4.90 | 9.78 | 84.35 | 89.26 |
| background | 1972628 | 0.0% | +0.00 | 0.00 | 42.44 | 42.44 |

1920x1080: figure 100972 px, visible 5.1%, dL +0.67, dE 1.34

640x360: figure 11221 px, visible 5.1%, dL +0.67, dE 1.34

960x540: figure 25242 px, visible 5.1%, dL +0.67, dE 1.34

### E - E secondary lighting normals

OFF `(no flag)`  ON `--npr=normals`

verdict: **reads**

| region | px | visible | dL | dE | L off | L on |
|---|---|---|---|---|---|---|
| whole | 100972 | 44.1% | -8.53 | 20.73 | 99.98 | 91.46 |
| rim | 17642 | 33.2% | -7.82 | 17.88 | 98.36 | 90.55 |
| interior | 83330 | 46.4% | -8.68 | 21.34 | 100.33 | 91.65 |
| face | 16271 | 47.2% | -16.91 | 33.48 | 102.45 | 85.54 |
| hair | 11825 | 81.6% | -18.63 | 42.96 | 130.35 | 111.72 |
| torso | 21070 | 33.1% | -6.89 | 18.29 | 161.76 | 154.87 |
| affected | 65126 | 68.4% | -13.22 | 32.15 | 97.26 | 84.03 |
| background | 1972628 | 0.0% | +0.00 | 0.00 | 42.44 | 42.44 |

1920x1080: figure 100972 px, visible 44.1%, dL -8.53, dE 20.73

640x360: figure 11221 px, visible 44.1%, dL -8.52, dE 20.65

960x540: figure 25242 px, visible 44.2%, dL -8.61, dE 20.85

### F - F generated shadow mask (over bands:hard, tinted)

OFF `--npr=bands:hard,shadow,mask:0`  ON `--npr=bands:hard,shadow,mask:1`

verdict: **reads where it lands (6.4% of the figure, dE 19.2) but below the whole-figure bar**

| region | px | visible | dL | dE | L off | L on |
|---|---|---|---|---|---|---|
| whole | 100972 | 5.1% | +0.73 | 1.24 | 97.77 | 98.50 |
| rim | 17642 | 2.9% | +0.40 | 0.66 | 97.33 | 97.73 |
| interior | 83330 | 5.6% | +0.80 | 1.36 | 97.87 | 98.67 |
| face | 16271 | 4.4% | +0.78 | 1.26 | 99.47 | 100.25 |
| hair | 11825 | 11.5% | +1.57 | 2.41 | 126.29 | 127.86 |
| torso | 21070 | 5.9% | +1.20 | 1.88 | 158.54 | 159.74 |
| affected | 6512 | 79.7% | +11.33 | 19.22 | 110.12 | 121.45 |
| background | 1972628 | 0.0% | +0.00 | 0.00 | 42.44 | 42.44 |

1920x1080: figure 100972 px, visible 5.1%, dL +0.73, dE 1.24

640x360: figure 11221 px, visible 5.1%, dL +0.71, dE 1.21

960x540: figure 25242 px, visible 5.1%, dL +0.72, dE 1.22

### G - G stylized hard-threshold specular

OFF `(no flag)`  ON `--npr=spec`

verdict: **reads**

| region | px | visible | dL | dE | L off | L on |
|---|---|---|---|---|---|---|
| whole | 100972 | 16.2% | +3.23 | 7.24 | 99.98 | 103.21 |
| rim | 17642 | 6.9% | +1.27 | 3.17 | 98.36 | 99.63 |
| interior | 83330 | 18.2% | +3.64 | 8.11 | 100.33 | 103.97 |
| face | 16271 | 3.7% | +0.75 | 1.76 | 102.45 | 103.20 |
| hair | 11825 | 19.8% | +6.00 | 9.61 | 130.35 | 136.35 |
| torso | 21070 | 13.0% | +1.77 | 4.86 | 161.76 | 163.54 |
| affected | 18280 | 89.6% | +17.83 | 40.00 | 114.45 | 132.27 |
| background | 1972628 | 0.0% | +0.00 | 0.00 | 42.44 | 42.44 |

1920x1080: figure 100972 px, visible 16.2%, dL +3.23, dE 7.24

640x360: figure 11221 px, visible 16.1%, dL +3.22, dE 7.21

960x540: figure 25242 px, visible 16.3%, dL +3.24, dE 7.26

### H - H character rim light

OFF `(no flag)`  ON `--npr=rim`

verdict: **reads**

| region | px | visible | dL | dE | L off | L on |
|---|---|---|---|---|---|---|
| whole | 100972 | 37.0% | +6.83 | 13.43 | 99.98 | 106.81 |
| rim | 17642 | 64.4% | +12.62 | 24.68 | 98.36 | 110.98 |
| interior | 83330 | 31.1% | +5.60 | 11.05 | 100.33 | 105.93 |
| face | 16271 | 40.9% | +7.47 | 14.53 | 102.45 | 109.92 |
| hair | 11825 | 42.5% | +8.26 | 14.61 | 130.35 | 138.61 |
| torso | 21070 | 36.5% | +7.61 | 14.49 | 161.76 | 169.37 |
| affected | 78017 | 47.8% | +8.83 | 17.38 | 99.40 | 108.23 |
| background | 1972628 | 0.0% | +0.00 | 0.00 | 42.44 | 42.44 |

1920x1080: figure 100972 px, visible 37.0%, dL +6.83, dE 13.43

640x360: figure 11221 px, visible 37.0%, dL +6.83, dE 13.43

960x540: figure 25242 px, visible 36.9%, dL +6.82, dE 13.41

### I - I outline width x2 (over the recovered toon row)

OFF `--toon`  ON `--toon --npr=outline:2`

verdict: **reads**

| region | px | visible | dL | dE | L off | L on |
|---|---|---|---|---|---|---|
| whole | 108791 | 7.2% | -2.12 | 6.69 | 83.32 | 81.20 |
| rim | 17463 | 24.5% | -1.94 | 9.21 | 60.90 | 58.96 |
| interior | 91328 | 3.9% | -2.16 | 6.21 | 87.61 | 85.45 |
| face | 17093 | 10.0% | -4.80 | 12.97 | 95.99 | 91.19 |
| hair | 12584 | 7.7% | -2.38 | 7.99 | 87.40 | 85.03 |
| torso | 22320 | 9.2% | -3.95 | 11.75 | 151.89 | 147.94 |
| affected | 8021 | 97.8% | -28.78 | 90.72 | 70.66 | 41.88 |
| background | 1964809 | 0.0% | +0.00 | 0.00 | 42.44 | 42.44 |

1920x1080: figure 108791 px, visible 7.2%, dL -2.12, dE 6.69

640x360: figure 12088 px, visible 7.4%, dL -2.21, dE 6.91

960x540: figure 27206 px, visible 7.4%, dL -2.23, dE 6.88

### STACK - the recommended stack (--npr=on)

OFF `(no flag)`  ON `--npr=on`

verdict: **reads**

| region | px | visible | dL | dE | L off | L on |
|---|---|---|---|---|---|---|
| whole | 100972 | 66.7% | -1.07 | 29.59 | 99.98 | 98.92 |
| rim | 17642 | 68.3% | +3.71 | 29.27 | 98.36 | 102.07 |
| interior | 83330 | 66.4% | -2.08 | 29.66 | 100.33 | 98.25 |
| face | 16271 | 70.4% | -4.99 | 36.44 | 102.45 | 97.46 |
| hair | 11825 | 85.0% | -18.86 | 42.96 | 130.35 | 111.49 |
| torso | 21070 | 66.2% | +8.04 | 37.65 | 161.76 | 169.80 |
| affected | 96101 | 70.1% | -1.12 | 31.09 | 97.69 | 96.57 |
| background | 1972628 | 0.0% | +0.00 | 0.00 | 42.44 | 42.44 |

1920x1080: figure 100972 px, visible 66.7%, dL -1.07, dE 29.59

640x360: figure 11221 px, visible 66.8%, dL -1.05, dE 29.52

960x540: figure 25242 px, visible 66.8%, dL -1.14, dE 29.62

### STACK_toon - the stack over the recovered toon row

OFF `--toon`  ON `--toon --npr=on`

verdict: **reads**

| region | px | visible | dL | dE | L off | L on |
|---|---|---|---|---|---|---|
| whole | 104861 | 85.8% | +8.77 | 56.12 | 84.85 | 93.62 |
| rim | 17483 | 63.3% | +11.88 | 43.24 | 72.29 | 84.17 |
| interior | 87378 | 90.3% | +8.15 | 58.69 | 87.36 | 95.52 |
| face | 16705 | 82.2% | -5.62 | 48.29 | 97.23 | 91.62 |
| hair | 12217 | 92.0% | +15.85 | 56.72 | 88.75 | 104.61 |
| torso | 21716 | 87.7% | +4.23 | 87.21 | 154.93 | 159.16 |
| affected | 96589 | 93.2% | +9.53 | 60.92 | 88.97 | 98.49 |
| background | 1968739 | 0.0% | +0.00 | 0.00 | 42.44 | 42.44 |

1920x1080: figure 104861 px, visible 85.8%, dL +8.77, dE 56.12

640x360: figure 11648 px, visible 85.9%, dL +8.80, dE 56.14

960x540: figure 26208 px, visible 85.8%, dL +8.74, dE 56.14

## Sanity sweeps (960x540, the arm's own parameter at its extremes)

### B-curve - B - the band curve at the shipped width, tinted and neutral

expected: the three curves must draw different pictures, and the curve must be what draws them - not the tint it multiplies

**CLAIM FAILS - hard, neutral tint, soft 0.06, neutral tint: the curve only selects how much of the shadow TINT is applied: with a neutral tint mix(tint, white, w) is white for every w, so the frame is byte-identical and the 'band' never bands the shading (model_wgsl.h:385); byte-identical to the control: hard, neutral tint, soft 0.06, neutral tint**

| step | args | vs the control | visible | dL | dE |
|---|---|---|---|---|---|
| off (no flag) | `(no flag)` | changed | 0.0% | +0.00 | 0.00 |
| hard, tinted | `--npr=bands:hard,shadow` | changed | 11.4% | -1.49 | 2.54 |
| hard, neutral tint | `--npr=bands:hard,shadow:none` | identical | 0.0% | +0.00 | 0.00 |
| soft 0.06, tinted | `--npr=bands:soft,shadow` | changed | 11.1% | -1.49 | 2.54 |
| soft 0.06, neutral tint | `--npr=bands:soft,shadow:none` | identical | 0.0% | +0.00 | 0.00 |
| three, tinted | `--npr=bands:three,shadow` | obvious | 16.0% | -1.80 | 3.15 |
| three, neutral tint | `--npr=bands:three,shadow:none` | changed | 2.0% | -0.41 | 0.79 |

- hard tinted against hard neutral: differs, visible 11.4%, dL +1.49, dE 2.54
- soft 0.06 tinted against soft 0.06 neutral: differs, visible 11.1%, dL +1.49, dE 2.54
- three tinted against three neutral: differs, visible 10.7%, dL +1.39, dE 2.38
- hard against soft 0.06, both tinted: differs, visible 0.4%, dL +0.00, dE 0.24

### B-softness - B - the softness parameter soft:<f> (neutral tint)

expected: each width must move the terminator further than the last

**CLAIM FAILS - hard (no softness), soft 0.02, soft 0.06 (default), soft 0.30, soft 1.00: the width has no effect on the picture at all: the smoothstep only shapes the tint weight, which is invisible while the tint is neutral; byte-identical to the control: hard (no softness), soft 0.02, soft 0.06 (default), soft 0.30, soft 1.00**

| step | args | vs the control | visible | dL | dE |
|---|---|---|---|---|---|
| off (no flag) | `(no flag)` | changed | 0.0% | +0.00 | 0.00 |
| hard (no softness) | `--npr=bands:hard,shadow:none` | identical | 0.0% | +0.00 | 0.00 |
| soft 0.02 | `--npr=bands:soft,soft:0.02,shadow:none` | identical | 0.0% | +0.00 | 0.00 |
| soft 0.06 (default) | `--npr=bands:soft,soft:0.06,shadow:none` | identical | 0.0% | +0.00 | 0.00 |
| soft 0.30 | `--npr=bands:soft,soft:0.3,shadow:none` | identical | 0.0% | +0.00 | 0.00 |
| soft 1.00 | `--npr=bands:soft,soft:1.0,shadow:none` | identical | 0.0% | +0.00 | 0.00 |
| soft 1.00, default tint | `--npr=bands:soft,soft:1.0,shadow` | changed | 8.7% | -2.03 | 3.69 |

- soft 0.06 against soft 1.00, both with a neutral tint: byte-identical, visible 0.0%, dL +0.00, dE 0.00
- soft 1.00 neutral against soft 1.00 tinted: differs, visible 8.7%, dL -2.03, dE 3.69

### C-tint - C - the shadow tint shadow:<#rrggbb>

expected: the tinted shadow must move hue, and a saturated tint obviously so

**claim holds: the tint colours the shadowed side, so it changes the picture**

| step | args | vs the control | visible | dL | dE |
|---|---|---|---|---|---|
| none (neutral) | `--npr=bands:soft,shadow:none` | changed | 0.0% | +0.00 | 0.00 |
| default #dbc0c7 | `--npr=bands:soft,shadow` | changed | 11.1% | -1.49 | 2.54 |
| saturated #ff00ff | `--npr=bands:soft,shadow:#ff00ff` | obvious | 23.0% | -4.50 | 6.30 |


### D-arm - D - the key arm key:fixed|cam

expected: the two arms are different lights and both add light

**claim holds: the key adds light, so both arms change the picture**

| step | args | vs the control | visible | dL | dE |
|---|---|---|---|---|---|
| off | `--npr=bands:soft,shadow` | changed | 0.0% | +0.00 | 0.00 |
| fixed | `--npr=bands:soft,shadow,key:fixed` | obvious | 15.0% | +2.02 | 4.17 |
| cam | `--npr=bands:soft,shadow,key:cam` | changed | 5.1% | +0.67 | 1.34 |

- the two key arms against each other: differs, visible 17.5%, dL -1.35, dE 4.86

### D-strength - D - the key strength keystr:<f> (key:cam)

expected: the brightness must follow the strength

**claim holds: the brightness follows the strength, so each step changes the picture**

| step | args | vs the control | visible | dL | dE |
|---|---|---|---|---|---|
| 0 | `--npr=bands:soft,shadow,key:cam,keystr:0` | changed | 0.0% | +0.00 | 0.00 |
| 0.35 (default) | `--npr=bands:soft,shadow,key:cam` | changed | 5.1% | +0.67 | 1.34 |
| 1.5 | `--npr=bands:soft,shadow,key:cam,keystr:1.5` | obvious | 12.0% | +2.64 | 5.16 |


### E-normals - E - the secondary normals normals|nonormals

expected: lighting the secondary stream must visibly re-shade the surface

**claim holds: lighting the secondary stream re-shades the surface; byte-identical to the control: nonormals**

| step | args | vs the control | visible | dL | dE |
|---|---|---|---|---|---|
| off | `(no flag)` | changed | 0.0% | +0.00 | 0.00 |
| nonormals | `--npr=nonormals` | identical | 0.0% | +0.00 | 0.00 |
| normals | `--npr=normals` | obvious | 44.2% | -8.61 | 20.85 |


### F-mask - F - the generated mask scale mask:<f>

expected: the scale must move the boundary, and inversion must move it the other way - with a neutral tint as well as with the shipped one

**CLAIM FAILS - mask 1, neutral tint: the mask only moves the edge of the tint weight: with a neutral tint it renders identically, so it cannot hold a band that the shader never draws (model_wgsl.h:383); byte-identical to the control: mask 1, neutral tint**

| step | args | vs the control | visible | dL | dE |
|---|---|---|---|---|---|
| mask 0, neutral tint (the control) | `--npr=bands:hard,shadow:none,mask:0` | changed | 0.0% | +0.00 | 0.00 |
| mask 1, neutral tint | `--npr=bands:hard,shadow:none,mask:1` | identical | 0.0% | +0.00 | 0.00 |
| mask -1, tinted | `--npr=bands:hard,shadow,mask:-1` | obvious | 21.9% | -3.07 | 5.27 |
| mask 0, tinted | `--npr=bands:hard,shadow,mask:0` | obvious | 16.4% | -2.21 | 3.76 |
| mask 1, tinted | `--npr=bands:hard,shadow,mask:1` | changed | 11.4% | -1.49 | 2.54 |
| mask 3, tinted | `--npr=bands:hard,shadow,mask:3` | changed | 0.6% | -0.31 | 0.53 |

- mask 0 against mask 1, both tinted: differs, visible 5.1%, dL +0.72, dE 1.22
- mask 1 against mask 3, both tinted: differs, visible 10.7%, dL +1.18, dE 2.01

### G-spec - G - the specular strength/tint

expected: the highlight must grow with the strength and take the tint

**claim holds: the highlight draws and grows with the strength**

| step | args | vs the control | visible | dL | dE |
|---|---|---|---|---|---|
| off | `(no flag)` | changed | 0.0% | +0.00 | 0.00 |
| 0.35 (default) | `--npr=spec` | obvious | 16.3% | +3.24 | 7.26 |
| tint #ff00ff, str 2 | `--npr=spec,spectint:#ff00ff,specstr:2` | obvious | 17.4% | +2.42 | 14.56 |


### H-rim - H - the rim strength/tint

expected: the rim must grow with the strength and take the tint

**claim holds: the rim draws and grows with the strength**

| step | args | vs the control | visible | dL | dE |
|---|---|---|---|---|---|
| off | `(no flag)` | changed | 0.0% | +0.00 | 0.00 |
| 0.30 (default) | `--npr=rim` | obvious | 36.9% | +6.82 | 13.41 |
| tint #00ff00, str 2 | `--npr=rim,rimtint:#00ff00,rimstr:2` | obvious | 56.1% | +24.87 | 34.77 |


### I-outline - I - the outline width scale (--toon)

expected: a wider hull must widen the rim, a thinner one must thin it, and 1.0 must be --toon alone

**claim holds: 1.0 is the recovered width: byte-identical to --toon alone; byte-identical to the control: outline 1.0**

| step | args | vs the control | visible | dL | dE |
|---|---|---|---|---|---|
| --toon alone (the recovered width) | `--toon` | changed | 0.0% | +0.00 | 0.00 |
| outline 0.25 | `--toon --npr=outline:0.25` | obvious | 5.4% | +1.78 | 5.20 |
| outline 1.0 | `--toon --npr=outline:1` | identical | 0.0% | +0.00 | 0.00 |
| outline 2 | `--toon --npr=outline:2` | obvious | 7.4% | -2.23 | 6.88 |
| outline 3 | `--toon --npr=outline:3` | obvious | 13.3% | -3.82 | 11.97 |

- 0.25 against the recovered width: differs, visible 5.4%, dL +1.78, dE 5.20
- 2 against the recovered width: differs, visible 7.4%, dL -2.23, dE 6.88
- 3 against 2: differs, visible 7.0%, dL -1.67, dE 6.20

## Is the tinted shadow one flat value? (the B band claim)

The set is the pixels the tint moved inside a patch of one flat material (the skirt, (880, 500, 1080, 660) at 1080p), so the spread is the lighting's spread and not the albedo's. A band that replaces the shadowed side with one value collapses it; a tint that multiplies an unbanded gradient keeps it.

| arm | shadow px | spread off | spread on | ratio | levels off -> on |
|---|---|---|---|---|---|
| hard, default tint | 7628 | 33.16 | 28.12 | 0.848 | 46 -> 40 |
| soft 0.06, default tint | 8395 | 36.05 | 32.45 | 0.900 | 50 -> 46 |
| soft 1.00, default tint | 17000 | 52.10 | 49.88 | 0.957 | 62 -> 61 |
| three, default tint | 8593 | 37.07 | 33.93 | 0.915 | 51 -> 42 |

## Gameplay distance (--versus, stage01, arena camera, 960x540)

The `whole` row is the whole FRAME (a stage fills it, so there is no figure mask); the `P2 box` row is the rectangle around Mion, the one fully visible fighter, drawn on each sheet.

- C: below the bar - whole frame visible 0.05%, dL -0.009, dE 0.01; P2 box visible 2.3%, dL -0.35, dE 0.57
- D: below the bar - whole frame visible 0.05%, dL +0.009, dE 0.02; P2 box visible 0.8%, dL +0.09, dE 0.21
- E: no-op (byte-identical frames) - whole frame visible 0.00%, dL +0.000, dE 0.00; P2 box visible 0.0%, dL +0.00, dE 0.00
- G: below the bar - whole frame visible 0.14%, dL +0.031, dE 0.06; P2 box visible 2.3%, dL +0.58, dE 1.24
- H: below the bar - whole frame visible 0.30%, dL +0.057, dE 0.10; P2 box visible 9.4%, dL +1.87, dE 3.39
- STACK: below the bar - whole frame visible 0.28%, dL +0.043, dE 0.09; P2 box visible 8.2%, dL +1.14, dE 2.68

## Does the arm reach a fight scene at all? (--versus, stage01)

The close-up sheets are a stage-less bind pose. These rows are the same arms where the product draws them - a stage first, then the fighters - so an arm that is byte-identical to its control at every probed frame is one the fight never sees.

| arm | on | frame 150 | frame 300 |
|---|---|---||
| E secondary normals | `--npr=normals` | **IDENTICAL** | **IDENTICAL** |
| C shadow tint | `--npr=bands:soft,shadow` | 1344 px changed | 1040 px changed |
| B soft bands, neutral tint | `--npr=bands:soft,shadow:none` | **IDENTICAL** | **IDENTICAL** |
| B three bands, neutral tint | `--npr=bands:three,shadow:none` | 678 px changed | 583 px changed |
| D key:cam | `--npr=bands:soft,shadow,key:cam` | 587 px changed | 549 px changed |
| F mask 1, neutral tint | `--npr=bands:hard,shadow:none,mask:1` | **IDENTICAL** | **IDENTICAL** |
| G specular | `--npr=spec` | 1312 px changed | 829 px changed |
| H rim | `--npr=rim` | 4156 px changed | 3149 px changed |
| I outline x2 | `--toon --npr=outline:2` | 897 px changed | 845 px changed |

## 4-view 2v2

- frame-wide: visible 0.8%, dL +0.13, dE 0.30; byte-identical on a repeat run: yes

