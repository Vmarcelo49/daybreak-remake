#!/usr/bin/env python3
"""
Paint Okonogi's head texture for the UV layout of Kasai's PC head, from the owner's portrait references.

    okonogi_face_paint.py out.png [--size 128]

Drawn at 1024 and scaled down, because the PC's heads are soft 128 pixel paintings. One half of the face
is painted: the mesh mirrors it across the centre line at x = 510. All coordinates are in the 1024 space.
"""
import argparse
import random

from PIL import Image, ImageDraw, ImageFilter

CANVAS = 1024
SKIN_LIGHT = (255, 230, 199)
SKIN_SHADE = (255, 204, 173)
SKIN_LINE = (214, 146, 122)
HAIR = (92, 134, 116)
HAIR_DARK = (44, 80, 68)
HAIR_LIGHT = (146, 182, 160)
INK = (28, 34, 32)
LIP = (138, 66, 58)

FOREHEAD_CENTRE = 300
HAIRLINE = [(510, FOREHEAD_CENTRE), (470, 262), (405, 240), (345, 262), (275, 335), (228, 425), (196, 510),
            (172, 590), (160, 640), (120, 610), (88, 598)]
HAIR_FRONT = [(0, 0), (540, 0), (540, FOREHEAD_CENTRE)] + HAIRLINE + [(0, 610)]
HAIR_BACK = [(540, 0), (CANVAS, 0), (CANVAS, 800), (835, 800), (740, 835), (540, 835)]
EAR = (835, 790, 1024, 1012)
BAND = (548, 20, 618, 90)
FACE_LIGHT = [(510, 240), (350, 240), (250, 370), (215, 500), (195, 640), (210, 770), (280, 870), (360, 945),
              (430, 995), (510, 1005)]


def layer(canvas, draw_on, blur=0, opacity=1.0):
    """Draw on a transparent layer, soften it, and lay it over the canvas."""
    over = Image.new("RGBA", canvas.size, (0, 0, 0, 0))
    draw_on(ImageDraw.Draw(over))
    if blur:
        # Premultiplied, or the blur pulls the transparent black into the colour and greys the skin.
        over = over.convert("RGBa").filter(ImageFilter.GaussianBlur(blur)).convert("RGBA")
    if opacity < 1.0:
        over.putalpha(over.getchannel("A").point(lambda a: int(a * opacity)))
    canvas.alpha_composite(over)


def stroke(points, colour, width, blur=0, opacity=1.0):
    return lambda canvas: layer(
        canvas, lambda d: d.line(points, fill=colour + (255,), width=width, joint="curve"), blur, opacity)


def paint_skin(canvas):
    layer(canvas, lambda d: d.polygon(FACE_LIGHT, fill=SKIN_LIGHT + (255,)), blur=26)
    for shade in (
        stroke([(232, 690), (292, 790), (330, 900)], SKIN_LINE, 26, blur=14, opacity=.55),  # under the cheekbone
        stroke([(210, 610), (300, 640), (400, 650)], SKIN_SHADE, 18, blur=12, opacity=.7),
        stroke([(495, 960), (420, 950)], SKIN_SHADE, 20, blur=10, opacity=.8),      # under the chin
        stroke([(440, 835), (505, 840)], SKIN_SHADE, 12, blur=5),                   # under the lip
        stroke([(470, 540), (450, 600), (436, 660)], SKIN_LINE, 18, blur=8, opacity=.6),  # beside the nose
    ):
        shade(canvas)
    # Eye socket, deep and tired, as on Kasai's and in the portraits.
    layer(canvas, lambda d: d.ellipse((215, 490, 470, 600), fill=(240, 178, 152, 255)), blur=22, opacity=.55)


def paint_lines(canvas):
    for line in (
        stroke([(440, 410), (505, 425)], SKIN_LINE, 6, blur=3, opacity=.5),                 # forehead crease
        stroke([(428, 688), (398, 730), (384, 762)], SKIN_LINE, 8, blur=2, opacity=.9),     # cheek fold
        stroke([(262, 700), (300, 770), (320, 840)], SKIN_LINE, 7, blur=3, opacity=.6),
        stroke([(330, 300), (282, 372), (262, 440)], SKIN_LINE, 6, blur=3, opacity=.6),     # temple
        stroke([(462, 712), (505, 722)], LIP, 9, blur=1),                                   # nostril
        stroke([(440, 672), (458, 708)], SKIN_LINE, 7, blur=2),
        stroke([(510, 796), (440, 797), (390, 784), (356, 758)], LIP, 9, blur=1),           # the smirk
    ):
        line(canvas)


def paint_eye(canvas):
    white = [(262, 520), (320, 512), (400, 532), (448, 566), (360, 568), (295, 552)]
    # The lid cuts the top of the iris, so draw it clipped to the white.
    mask = Image.new("L", canvas.size, 0)
    ImageDraw.Draw(mask).polygon(white, fill=255)
    eye = Image.new("RGBA", canvas.size, (0, 0, 0, 0))
    draw = ImageDraw.Draw(eye)
    draw.polygon(white, fill=(245, 245, 240, 255))
    draw.ellipse((328, 506, 394, 572), fill=(38, 42, 44, 255))
    draw.ellipse((350, 526, 374, 550), fill=(12, 14, 16, 255))
    draw.ellipse((360, 526, 374, 540), fill=(235, 240, 240, 255))
    eye.putalpha(Image.composite(eye.getchannel("A"), Image.new("L", canvas.size, 0), mask))
    canvas.alpha_composite(eye)
    for line in (
        stroke([(244, 520), (320, 503), (404, 524), (458, 570)], INK, 15, blur=1),          # upper lid
        stroke([(285, 548), (360, 574), (448, 570)], (110, 66, 58), 5, blur=1),             # lower lid
        stroke([(270, 590), (360, 606), (430, 600)], SKIN_LINE, 5, blur=3, opacity=.5),     # bag under the eye
    ):
        line(canvas)
    brow = [(226, 480), (300, 452), (400, 486), (490, 548), (470, 556), (392, 510), (300, 480), (240, 494)]
    layer(canvas, lambda d: d.polygon(brow, fill=(26, 44, 38, 255)), blur=2)


def paint_hair(canvas, rng):
    hair = Image.new("RGBA", canvas.size, HAIR + (255,))
    draw = ImageDraw.Draw(hair, "RGBA")
    # Slicked back: in front the strands fan out from the hairline; behind they run down to the nape.
    focus = (560, 620)
    for _ in range(70):
        x, y = rng.uniform(0, 540), rng.uniform(0, 620)
        k = rng.uniform(.6, 1.4)
        colour = rng.choice((HAIR_DARK, HAIR_LIGHT))
        draw.line([(x, y), (focus[0] + (x - focus[0]) * k, focus[1] + (y - focus[1]) * k)],
                  fill=colour + (rng.randint(30, 70),), width=rng.randint(10, 26))
    for _ in range(60):
        x, y = rng.uniform(540, CANVAS), rng.uniform(0, 835)
        length = rng.uniform(150, 400)
        colour = rng.choice((HAIR_DARK, HAIR_LIGHT))
        draw.line([(x, y), (x + rng.uniform(-14, 14), y + length)],
                  fill=colour + (rng.randint(30, 70),), width=rng.randint(10, 26))
    hair = hair.filter(ImageFilter.GaussianBlur(5))
    # The nape falls into shadow, as on the PC's other heads.
    shade = Image.new("L", canvas.size, 0)
    ImageDraw.Draw(shade).rectangle((540, 600, CANVAS, 900), fill=170)
    hair.paste(HAIR_DARK + (255,), mask=shade.filter(ImageFilter.GaussianBlur(70)))

    mask = Image.new("L", canvas.size, 0)
    shape = ImageDraw.Draw(mask)
    shape.polygon(HAIR_FRONT, fill=255)
    shape.polygon(HAIR_BACK, fill=255)
    hair.putalpha(mask.filter(ImageFilter.GaussianBlur(1)))
    canvas.alpha_composite(hair)
    # Hairline: a dark edge, jagged by a few strands biting into the skin.
    stroke(HAIRLINE, HAIR_DARK, 14, blur=2)(canvas)
    for a, b in zip(HAIRLINE, HAIRLINE[1:]):
        for t in range(1, 5):
            x = a[0] + (b[0] - a[0]) * t / 5
            y = a[1] + (b[1] - a[1]) * t / 5
            out = (x + (560 - x) * .05 + rng.uniform(-6, 6), y + (620 - y) * .06 + rng.uniform(-3, 3))
            stroke([(x, y), out], HAIR_DARK, 8, blur=1)(canvas)


def paint_ear(canvas):
    left, top, right, bottom = EAR
    layer(canvas, lambda d: d.ellipse((left, top, right, bottom), fill=SKIN_LIGHT + (255,)), blur=4)
    layer(canvas, lambda d: d.arc((left + 18, top + 18, right - 18, bottom - 18), 150, 40,
                                  fill=SKIN_LINE + (255,), width=14), blur=3)
    layer(canvas, lambda d: d.ellipse((left + 70, top + 80, right - 60, bottom - 60), fill=SKIN_LINE + (255,)), blur=8)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("out")
    parser.add_argument("--size", type=int, default=128)
    args = parser.parse_args()

    rng = random.Random(19)
    canvas = Image.new("RGBA", (CANVAS, CANVAS), SKIN_SHADE + (255,))
    paint_skin(canvas)
    paint_lines(canvas)
    paint_eye(canvas)
    paint_hair(canvas, rng)
    paint_ear(canvas)
    ImageDraw.Draw(canvas).rectangle(BAND, fill=(30, 36, 34, 255))
    canvas.convert("RGB").resize((args.size, args.size), Image.LANCZOS).save(args.out)


if __name__ == "__main__":
    main()
