import sys, numpy as np
from polish import *
def compare(svgpath, origpath, out, bg=(70,90,110,255), z=2):
    svg = open(svgpath).read()
    o = Image.open(origpath).convert('RGBA'); W,H = o.size
    v = render(svg, width=W*z)
    o2 = o.resize((W*z,H*z), Image.NEAREST)
    A = Image.new('RGBA', o2.size, bg); A.alpha_composite(o2)
    B = Image.new('RGBA', v.size, bg); B.alpha_composite(v)
    d = np.abs(np.array(A).astype(int)-np.array(B).astype(int)).mean()
    s = Image.new('RGB', (W*z*2+20, H*z), (30,30,30)); s.paste(A.convert('RGB'),(0,0)); s.paste(B.convert('RGB'),(W*z+20,0)); s.save(out)
    return d
if __name__ == '__main__':
    print(compare(sys.argv[1], sys.argv[2], sys.argv[3]))
