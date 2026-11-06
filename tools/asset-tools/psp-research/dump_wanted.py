"""Extract the files this study needs into local-data/harness/psp/dump/, by name."""
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from psppack import Pack

HERE = os.path.dirname(os.path.abspath(__file__))
DUMP = os.path.normpath(os.path.join(HERE, "..", "dump"))


def wanted():
    out = []
    for nn in range(1, 20):
        out.append("g3d/chrm%02d.gmo" % nn)
        out.append("g3d/chrt%02d.gim" % nn)
        for k in range(9):
            out.append("g3d/chr%02d%d.gmo" % (nn, k))
        for w in "abcd":
            out.append("g3d/chrm%02d%s.gmo" % (nn, w))
            out.append("activity/chr%02d%s.acs" % (nn, w))
            out.append("activity/chr%02d%s.acv" % (nn, w))
            out.append("assault/chr%02d%s.atp" % (nn, w))
    for nn in range(1, 25):
        for w in "abcdefz":
            out.append("g3d/wpn%02d%s.gmo" % (nn, w))
            for s in ("r1", "r2", "l1", "l2"):
                out.append("g3d/wpn%02d%s%s.gmo" % (nn, w, s))
    for n in ("static_param.bin", "bullet_attack_data.bin", "com_param.bin",
              "chr.fpd", "gauge_data.bin", "shot_data.bin"):
        out.append("bin/" + n)
    # select / VS screen art
    names = ["bustup_%s" % c for c in
             ("akane", "akasaka", "chie", "hanyuu", "irie", "kasai", "keiichi",
              "mion", "miyoko", "natsumi", "okonogi", "ooishi", "rena", "rika",
              "satoko", "satoshi", "sion", "takano", "tomitake")]
    names += ["vs_enter_%s" % c for c in
              ("akane", "akasaka", "chie", "hanyu", "hanyu_2", "kasai", "keiichi",
               "kyosuke", "mion", "miyo", "miyoko", "natumi", "okonogi", "ooishi",
               "rena", "rika", "satoko", "satoshi", "shion", "takano", "tomi",
               "tomi_take", "vs", "chara_name00", "chara_name01")]
    names += ["vs_bg0", "vs_bg1", "vs_bg_blue", "vs_bg_center", "vs_bg_impact",
              "vs_bg_red", "vs_bg_thunder", "vs_cursor2_b", "vs_cursor2_r",
              "vs_head_icon", "vs_info_mes01", "vs_label_akagumi", "vs_label_aogumi",
              "vs_label_com_b", "vs_label_com_r", "vs_label_player_b",
              "vs_label_player_r", "char_name", "st_bg0", "st_bg1", "costume",
              "weapon", "new_weapon", "bukibase", "config", "config_bgm",
              "config_map", "config_map_sozai", "cursor__roll", "icon_off", "icon_on"]
    out += ["gra/gim/select/%s.gim" % n for n in names]
    out += ["gra/gim/result/%s.gim" % n for n in ("back", "back_2", "hanko", "button",
                                                 "key_word", "sel_1", "sel_2")]
    for n in ("meter", "moji", "syouri", "scope", "caution"):
        out.append("gra/gim/ongame/%s.gim" % n)
    for w in "abcd":
        for k in ("voice", "se", "eff"):
            out.append("activity/chr19%s_%s.pck" % (w, k))
            out.append("activity/chr00%s_%s.pck" % (w, k))
    return out


def main():
    pack = Pack()
    os.makedirs(DUMP, exist_ok=True)
    hit = miss = 0
    for path in wanted():
        data = pack.get(path)
        if data is None:
            miss += 1
            continue
        hit += 1
        dest = os.path.join(DUMP, path)
        os.makedirs(os.path.dirname(dest), exist_ok=True)
        with open(dest, "wb") as f:
            f.write(data)
    print("dumped", hit, "missing", miss)


if __name__ == "__main__":
    main()
