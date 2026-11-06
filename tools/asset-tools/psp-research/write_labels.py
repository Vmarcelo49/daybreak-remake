"""Write notes/take_labels.tsv: what each PSP motion take is, with confidence.

    python3 write_labels.py

The numbers (frames, root displacement) come from `measure_takes.py`'s profile of the
posed rig, in model units; the labels come from looking at the contact sheets in
`takes/` (see notes/take_labels.md for the method and for what could not be settled).
`LABELS` below is the whole classification: one entry per rig and take index, with the
confidence and the observation behind it. Anything not in `LABELS` and not empty is an
error, so the table cannot silently lose a take.
"""
import os

HERE = os.path.dirname(os.path.abspath(__file__))
PSP = os.path.normpath(os.path.join(HERE, ".."))
NOTES = os.path.join(PSP, "notes")
FIGHTER = {"chrm17": "17", "chrm18": "18", "chrm19": "19", "chrm02": "02"}
RIGS = ["chrm17", "chrm18", "chrm19", "chrm02"]

# Shared first block: all four rigs carry the same twelve takes in the same order, and the
# pose signature check (notes/take_index_agreement_psp.tsv) finds every measured pair
# agreeing at indices 0-12, so a label there rests on four rigs rather than one.
CORE = {
    0: ("jump (full arc)", "high",
        "airborne ~38 frames, root peaks ~132 units up, arms up at apex; same on all 4 rigs"),
    1: ("bow/bend forward", "medium",
        "bends 60-72 deg forward and returns to the start pose; same shape on all 4 rigs"),
    2: ("crouch", "medium",
        "root drops 20-24 units, knees bend, hands toward the ground, returns to idle"),
    3: ("knockdown+down+getup", "high",
        "90-94 frames: falls, lies, kip-up through 160 deg pitch, stands; all 4 rigs"),
    4: ("duck/dodge", "medium",
        "20-21 frames, crouches with a leg lift, returns to idle"),
    5: ("knockdown (launched, on back)", "high",
        "ends lying (root -66 y), body flips through ~168 deg, travels -21 z; all 4 rigs"),
    6: ("down (stays down, KO candidate)", "medium",
        "ends lying at ~100 deg pitch with no getup inside the take; 55-60 frames"),
    7: ("knockdown (to knees/sit)", "medium",
        "root falls 28-60 units, ends at ~48 deg pitch, still partly upright"),
    8: ("turn 180", "high",
        "11 frames, no travel; the root bone rotates a full 180 deg (measured on chrm17)"),
    9: ("knockdown (face down, slides)", "high",
        "root travels -53..-67 z and -57..-68 y, ends face down at ~104-116 deg"),
    10: ("melee swing", "medium",
        "an arm swings across the body and returns; hands reach 46-59 units forward"),
    11: ("run cycle", "medium",
        "forward lean 27-46 deg, knees high, zero net root travel"),
    12: ("getup", "high",
        "starts on the ground at ~96-155 deg pitch, ends standing; root rises 43-67 units"),
    13: ("idle/stand", "high",
        "the only long take with no root and no foot motion (43-65 frames)"),
    14: ("run cycle", "medium",
        "16-frame cycle, 19-45 deg lean; half the length of 11, so twice the cadence"),
    15: ("walk cycle", "medium",
        "11-33 frame locomotion cycle with less lean than 14"),
}

# 16 and up diverge between rigs: the pose check stops agreeing, and the takes differ in
# length and content, so each rig gets its own reading.
LABELS = {
    "chrm17": {**CORE, **{
        16: ("jump/leap (airborne pose)", "medium", "air 9 frames, body angled with legs trailing"),
        17: ("run cycle", "low", "air 8 frames, crouch start, run stride"),
        18: ("run cycle", "low", "air 8 frames, same family as 17"),
        19: ("stop/brake from run", "medium",
             "10 frames: starts in a running stride at 39 deg lean, ends standing"),
        20: ("run cycle", "low-medium",
             "54 frames, air 34, starts and ends on the same pose, no travel"),
        22: ("air fall/dive", "medium",
             "airborne all 18 frames, body horizontal, drifts +10 z and -17 y"),
        24: ("taunt/gesture", "low",
             "25 frames in place, arms move, legs still, loops"),
        25: ("dash/lunge forward", "low", "travels +11 z, rises 9 y, ends standing"),
        26: ("melee lunge/thrust", "medium",
             "41 frames: deep forward lunge with an arm out, returns to idle"),
        27: ("drift back and rise", "low",
             "starts crouched at 39 deg, rises, travels -32 z"),
        28: ("hit reaction (flail)", "low",
             "fastest hand travel in the whole table (105 units/frame), +31 y, -43 z"),
        29: ("dive/roll and get up", "medium",
             "45 frames: run, dive, lie, get up; pitch reaches 106 deg"),
        30: ("in-place motion, unidentified", "low",
             "35 frames in place, feet planted, loops"),
        31: ("dive/roll and get up", "low",
             "38 frames, air 16, pitch reaches 129 deg"),
        32: ("side step/flip (lateral)", "medium",
             "the only take with large lateral travel (57 units on X) and no net forward travel"),
        33: ("air attack (jump kick)", "medium",
             "airborne all 37 frames, legs kick, starts and ends in the air"),
        34: ("air attack (jump kick)", "low", "airborne all 21 frames, same air start pose"),
        35: ("taunt/gesture", "low", "38 frames in place, arms up then down, loops"),
        36: ("in-place motion, unidentified", "low", "25 frames in place, feet planted"),
        37: ("bow/bend forward", "low", "32 frames, bends to 55 deg, returns"),
        38: ("in-place motion, unidentified", "low", "35 frames in place, loops"),
        41: ("in-place motion, unidentified", "low",
             "71 frames, loops; taunt or intro-like"),
        43: ("in-place motion, unidentified", "low",
             "111 frames, the longest take; intro / victory / hypermode candidate"),
        45: ("in-place motion, unidentified", "low", "41 frames in place"),
        48: ("upper-body pose (legs static)", "medium",
             "no root curve, feet static, only arms and torso; carries a facechange key"),
        49: ("in-place motion, unidentified", "low", "46 frames in place, arms and torso"),
        51: ("air attack (jump kick)", "low", "airborne all 37 frames, same air start pose"),
        52: ("static placeholder (no motion)", "high",
             "identical to 53-60 in every curve; 31 frames, no root curve"),
        53: ("static placeholder (no motion)", "high", "identical to 52 and 54-60"),
        54: ("static placeholder (no motion)", "high", "identical to 52-53 and 55-60"),
        55: ("static placeholder (no motion)", "high", "identical to 52-54 and 56-60"),
        56: ("static placeholder (no motion)", "high", "identical to 52-55 and 57-60"),
        57: ("static placeholder (no motion)", "high", "identical to 52-56 and 58-60"),
        58: ("static placeholder (no motion)", "high", "identical to 52-57 and 59-60"),
        59: ("static placeholder (no motion)", "high", "identical to 52-58 and 60"),
        60: ("static placeholder (no motion)", "high", "identical to 52-59"),
        61: ("in-place motion, unidentified", "low", "51 frames in place, bends to 55 deg"),
    }},
    "chrm18": {**CORE, **{
        16: ("jump/leap (airborne pose)", "low", "air 10 frames"),
        17: ("jump/leap (airborne pose)", "low", "25 frames, in place, no air"),
        18: ("jump/leap (airborne pose)", "low", "25 frames, air 8"),
        20: ("run cycle", "low-medium", "61 frames, air 7, returns to start pose"),
        22: ("air fall/dive", "medium",
             "airborne all 19 frames, body horizontal, drifts +9 z and -21 y"),
        24: ("in-place motion, unidentified", "low", "21 frames in place"),
        25: ("dash/lunge forward", "low", "travels +46 z and -20 y, never airborne"),
        26: ("taunt/gesture", "medium",
             "26 frames in place: steps, raises one arm overhead, returns"),
        27: ("drift back and rise", "low", "26 frames, -21 z, +13 y"),
        28: ("in-place motion, unidentified", "low-medium", "53 frames, loops, feet stay near the ground"),
        29: ("in-place motion, unidentified", "low", "40 frames, loops"),
        30: ("dive/roll and get up", "medium",
             "42 frames, air 17: dives flat, lies, rises to one knee, stands"),
        31: ("in-place motion, unidentified", "low", "27 frames in place, arm out to the side"),
        32: ("air idle", "medium",
             "airborne all 18 frames, one leg tucked, almost no travel"),
        33: ("knockdown (launched, on back)", "low-medium",
             "54 frames, air 38, pitch reaches 170 deg, ends -25 y"),
        34: ("in-place motion, unidentified", "low", "29 frames, loops"),
        35: ("drift back and rise", "low", "21 frames, -19 z, +11 y"),
        36: ("in-place motion, unidentified", "low", "35 frames, loops"),
        37: ("in-place motion, unidentified", "low", "42 frames"),
        39: ("in-place motion, unidentified", "low", "35 frames, air 6, loops"),
        41: ("in-place motion, unidentified", "low", "46 frames, loops"),
        43: ("in-place motion, unidentified", "low", "46 frames, loops"),
        45: ("drift back and rise", "low", "26 frames, +14 y"),
    }},
    "chrm19": {**CORE, **{
        16: ("in-place motion, unidentified", "low", "26 frames in place"),
        17: ("crouch (held stance)", "low", "23 frames in place"),
        18: ("crouch (held stance)", "low", "23 frames in place"),
        20: ("run cycle", "low-medium", "63 frames, air 4, loops"),
        22: ("air fall/dive", "medium",
             "airborne all 19 frames, body horizontal, drifts +8 z and -23 y"),
        24: ("crouch (held stance)", "low", "25 frames in place"),
        25: ("dash/lunge forward", "low-medium", "travels +55 z and +18 y, never airborne"),
        26: ("melee lunge/thrust", "low-medium", "41 frames in place, deep forward lunge"),
        27: ("drift back and rise", "low", "26 frames, -22 z, +27 y"),
        28: ("drift back and rise", "low", "36 frames, -38 z, +24 y"),
        29: ("in-place motion, unidentified", "low", "39 frames, air 5, loops"),
        30: ("in-place motion, unidentified", "low", "38 frames, loops"),
        31: ("in-place motion, unidentified", "low", "39 frames, loops"),
        33: ("air attack (jump kick)", "low-medium", "airborne 26 frames"),
        35: ("in-place motion, unidentified", "low", "26 frames, loops"),
        36: ("drift back and rise", "low", "31 frames, -30 z, +13 y, air 8"),
        37: ("in-place motion, unidentified", "low", "16 frames, loops"),
        38: ("in-place motion, unidentified", "low", "16 frames, +6 y"),
        39: ("in-place motion, unidentified", "low", "34 frames, +4 y"),
        41: ("in-place motion, unidentified", "low", "31 frames, loops"),
        43: ("in-place motion, unidentified", "low",
             "32 frames: crouches then extends an arm forward, returns"),
        46: ("in-place motion, unidentified", "low", "31 frames in place, arms extended"),
        47: ("side step/flip (lateral)", "medium",
             "travels +49 units on X with no forward travel, 19 frames airborne, "
             "tumbles through 164 deg pitch and lands upright"),
        48: ("side step/flip (lateral)", "medium",
             "mirror of 47: -60 units on X, 18 frames airborne, tumbles through 176 deg"),
        49: ("air idle", "low-medium",
             "airborne all 31 frames, arms forward, legs run; almost no travel"),
        50: ("in-place motion, unidentified", "low", "44 frames, loops"),
    }},
    "chrm02": {**CORE, **{
        16: ("jump/leap (airborne pose)", "low", "air 10 frames"),
        17: ("jump/leap (airborne pose)", "low", "25 frames, in place, no air"),
        18: ("jump/leap (airborne pose)", "low", "25 frames, air 8"),
        19: ("stop/brake from run", "low-medium",
             "10 frames: starts in a running stride, ends standing"),
        20: ("run cycle", "low-medium", "54 frames, air 34, loops"),
        22: ("air fall/dive", "medium", "airborne all 18 frames, body horizontal"),
        24: ("taunt/gesture", "low", "25 frames in place, loops"),
        25: ("dash/lunge forward", "low", "21 frames, +15 z"),
        26: ("melee lunge/thrust", "low-medium", "41 frames, arm forward, returns to idle"),
        27: ("drift back and rise", "low", "37 frames, -28 z, +20 y"),
        28: ("hit reaction (flail)", "low",
             "fastest hand travel 105 units/frame, pitch reaches 144 deg"),
        29: ("in-place motion, unidentified", "low", "33 frames, loops"),
        30: ("in-place motion, unidentified", "low", "35 frames, loops"),
        31: ("in-place motion, unidentified", "low", "25 frames, loops"),
        32: ("in-place motion, unidentified", "low", "38 frames, pitch reaches 62 deg"),
        33: ("air attack (jump kick)", "medium", "airborne all 37 frames"),
        34: ("air attack (jump kick)", "low", "airborne all 21 frames"),
        35: ("in-place motion, unidentified", "low", "22 frames, loops"),
        36: ("drift back and rise", "low", "27 frames, -42 z, +14 y"),
        37: ("in-place motion, unidentified", "low", "32 frames, loops"),
        41: ("in-place motion, unidentified", "low", "31 frames, +16 z"),
        43: ("in-place motion, unidentified", "low",
             "32 frames: crouches then extends an arm forward, returns"),
        45: ("in-place motion, unidentified", "low", "36 frames, loops"),
        48: ("upper-body pose (legs static)", "medium",
             "no root curve, feet static, only arms and torso"),
    }},
}


def read_tsv(path):
    with open(path) as f:
        header = f.readline().rstrip("\n").split("\t")
        return [dict(zip(header, line.rstrip("\n").split("\t"))) for line in f if line.strip()]


def main():
    rows = []
    for rig in RIGS:
        profile = {int(r["take_index"]): r
                   for r in read_tsv(os.path.join(NOTES, f"take_profile_{rig}.tsv"))}
        labels = LABELS[rig]
        have = set(profile)
        missing = have - set(labels)
        extra = set(labels) - have
        if missing or extra:
            raise SystemExit(f"{rig}: unlabelled {sorted(missing)}, stale {sorted(extra)}")
        # Every motion chunk, including the empty ones, so the table covers all 76 takes.
        names = {}
        import gmo
        model = gmo.parse_gmo(open(os.path.join(PSP, "dump", "g3d", rig + ".gmo"), "rb").read())
        for i, motion in enumerate(model.motions):
            names[i] = (motion.name, motion.range[1] - motion.range[0] + 1)
        for index in sorted(names):
            name, frames = names[index]
            if index in have:
                p = profile[index]
                label, confidence, note = labels[index]
                rows.append((FIGHTER[rig], index, name, int(p["frames"]),
                             float(p["net_dx"]), float(p["net_dy"]), float(p["net_dz"]),
                             label, confidence, note))
            else:
                rows.append((FIGHTER[rig], index, name, 1, 0.0, 0.0, 0.0,
                             "dummy (no curves)", "high",
                             "motion chunk with no bindings: nothing to play"))
    out = os.path.join(NOTES, "take_labels.tsv")
    with open(out, "w") as f:
        f.write("fighter\ttake_index\ttake_name\tframes\troot_dx\troot_dy\troot_dz\t"
                "label\tconfidence\tnotes\n")
        for r in rows:
            f.write("%s\t%d\t%s\t%d\t%.2f\t%.2f\t%.2f\t%s\t%s\t%s\n" % r)
    print("wrote", out, len(rows), "rows")
    for rig in RIGS:
        mine = [r for r in rows if r[0] == FIGHTER[rig]]
        high = sum(1 for r in mine if r[8] == "high")
        medium = sum(1 for r in mine if r[8] == "medium")
        lowmed = sum(1 for r in mine if r[8] == "low-medium")
        low = sum(1 for r in mine if r[8] == "low")
        real = [r for r in mine if r[7] != "dummy (no curves)"]
        print(f"  {rig}: {len(mine)} takes, {len(real)} non-dummy; high {high}, medium {medium}, "
              f"low-medium {lowmed}, low {low}")


if __name__ == "__main__":
    main()
