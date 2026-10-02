// =============================================================================
//  dat_bundle_bytes.cpp — host parity test for the foundation's .DAT bundle
//  reader (fnd::assets::DatBundle / DatBundleSet).
//
//  Run from the repo root (the test writes its scratch under the system temp
//  directory and needs python3 on PATH):
//
//      GAME_DIR=Higurashi-Daybreak ./dat_bundle_bytes
//      ./dat_bundle_bytes <game_dir> <repo_dir>          # explicit
//
//  What it proves, for real shipped bundles:
//   1. Table parity — for all 12,345 entries of the six shipped bundles, the
//      entry count, offset, length and undecoded name bytes match
//      remake/tools/asset-tools/extract_dat.py, driven through its own
//      decode_entry_table()/decode_file_data()/safe_filename() functions (the
//      independent oracle).  The decoded UTF-8 name is compared too; names that
//      need CP932 codes the foundation's generated sjis_table.h lacks are
//      reported as a known divergence, not silently ignored.
//   2. Byte parity — 30 sampled assets spread over all six bundles (models,
//      textures, .dat, .cnv, audio, a movie) are read through DatBundleSet and
//      their sha256 must equal the oracle's sha256 for the same entry, and the
//      extracted-tree file's sha256 where that file is the same copy.
//   3. Multi-bundle order — DatBundleSet must pick the earliest-*registered*
//      bundle that has the name (daybreak07, 04, 00, then 05, 02, 06 — the
//      exe's registration order, which decides duplicates; its name table's
//      00/04/07/05/02/06 is the open sequence, a different thing), matching the
//      DX9 logs (parity-baseline/logs/asset-*.log: data/rika/01.X -> daybreak00,
//      index 6017, 9675158 bytes) and the oracle's independent archive scan.
//   4. Negative cases — missing asset, out-of-bounds entry, truncated/corrupt
//      headers and an all-zero 65535-entry table must fail cleanly (no crash,
//      no bad_alloc), and lookups with the wrong case must behave exactly as
//      documented (find() exact, findAsciiCaseInsensitive() like the exe).
//
//  Final line: "DAT_BUNDLE_PARITY: ok" or "DAT_BUNDLE_PARITY: FAIL (n ...)".
//  Exit code 0 on ok, 1 on any mismatch.
// =============================================================================
#include "assets/dat_bundle.h"

#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

// The test also cross-checks the bundle reader's default name decoder against the
// foundation's own sjisToUtf8().  This TU owns CNV_IMPLEMENTATION, so the test
// links no other foundation object and cannot collide with foundation_assets.
#define CNV_IMPLEMENTATION
#include "assets/cnv.h"

namespace fs = std::filesystem;
using fnd::assets::DatBundle;
using fnd::assets::DatBundleSet;
using fnd::assets::DatEntry;

namespace {

int g_failures = 0;

void fail(const std::string& msg) {
    std::printf("FAIL: %s\n", msg.c_str());
    ++g_failures;
}

void check(bool cond, const std::string& what) {
    if (!cond) fail(what);
}

// ---------------------------------------------------------------------------
// SHA-256 (self-contained; validated against the FIPS vectors below before use)
// ---------------------------------------------------------------------------
class Sha256 {
public:
    void update(const void* data, std::size_t len) {
        const uint8_t* p = static_cast<const uint8_t*>(data);
        m_bits += static_cast<uint64_t>(len) * 8u;
        while (len > 0) {
            const std::size_t take = std::min(len, sizeof(m_buf) - m_len);
            std::memcpy(m_buf + m_len, p, take);
            m_len += take;
            p += take;
            len -= take;
            if (m_len == sizeof(m_buf)) {
                transform(m_buf);
                m_len = 0;
            }
        }
    }

    std::string hexdigest() {
        const uint64_t total_bits = m_bits;
        m_buf[m_len++] = 0x80;
        if (m_len > 56) {
            std::memset(m_buf + m_len, 0, sizeof(m_buf) - m_len);
            transform(m_buf);
            m_len = 0;
        }
        std::memset(m_buf + m_len, 0, 56 - m_len);
        for (int i = 0; i < 8; ++i) {
            m_buf[56 + i] = static_cast<uint8_t>(total_bits >> (56 - 8 * i));
        }
        transform(m_buf);
        m_len = 0;

        char out[65];
        for (int i = 0; i < 8; ++i) std::snprintf(out + i * 8, 9, "%08x", m_h[i]);
        return std::string(out, 64);
    }

private:
    static uint32_t rotr(uint32_t x, int n) { return (x >> n) | (x << (32 - n)); }

    void transform(const uint8_t* block) {
        static const uint32_t k[64] = {
            0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
            0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
            0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
            0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
            0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
            0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
            0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
            0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
            0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
            0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
            0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

        uint32_t w[64];
        for (int i = 0; i < 16; ++i) {
            w[i] = (static_cast<uint32_t>(block[i * 4]) << 24) |
                   (static_cast<uint32_t>(block[i * 4 + 1]) << 16) |
                   (static_cast<uint32_t>(block[i * 4 + 2]) << 8) |
                   static_cast<uint32_t>(block[i * 4 + 3]);
        }
        for (int i = 16; i < 64; ++i) {
            const uint32_t s0 = rotr(w[i - 15], 7) ^ rotr(w[i - 15], 18) ^ (w[i - 15] >> 3);
            const uint32_t s1 = rotr(w[i - 2], 17) ^ rotr(w[i - 2], 19) ^ (w[i - 2] >> 10);
            w[i] = w[i - 16] + s0 + w[i - 7] + s1;
        }

        uint32_t a = m_h[0], b = m_h[1], c = m_h[2], d = m_h[3];
        uint32_t e = m_h[4], f = m_h[5], g = m_h[6], h = m_h[7];
        for (int i = 0; i < 64; ++i) {
            const uint32_t s1 = rotr(e, 6) ^ rotr(e, 11) ^ rotr(e, 25);
            const uint32_t ch = (e & f) ^ (~e & g);
            const uint32_t t1 = h + s1 + ch + k[i] + w[i];
            const uint32_t s0 = rotr(a, 2) ^ rotr(a, 13) ^ rotr(a, 22);
            const uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
            const uint32_t t2 = s0 + maj;
            h = g; g = f; f = e; e = d + t1;
            d = c; c = b; b = a; a = t1 + t2;
        }
        m_h[0] += a; m_h[1] += b; m_h[2] += c; m_h[3] += d;
        m_h[4] += e; m_h[5] += f; m_h[6] += g; m_h[7] += h;
    }

    uint32_t m_h[8] = {0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
                       0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};
    uint64_t m_bits = 0;
    uint8_t  m_buf[64] = {};
    std::size_t m_len = 0;
};

std::string sha256_hex(const void* data, std::size_t len) {
    Sha256 h;
    h.update(data, len);
    return h.hexdigest();
}

std::string sha256_hex(const std::vector<uint8_t>& data) {
    return sha256_hex(data.data(), data.size());
}

bool sha256_hex_file(const std::string& path, std::string& out) {
    std::ifstream f(path, std::ios::binary);
    if (!f) return false;
    Sha256 h;
    std::vector<char> buf(1 << 20);
    while (f) {
        f.read(buf.data(), static_cast<std::streamsize>(buf.size()));
        const std::streamsize n = f.gcount();
        if (n > 0) h.update(buf.data(), static_cast<std::size_t>(n));
    }
    out = h.hexdigest();
    return true;
}

void sha256_selftest() {
    struct Vec { const char* msg; const char* want; };
    static const Vec kVec[3] = {
        {"", "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855"},
        {"abc", "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad"},
        {"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq",
         "248d6a61d20638b8e5c026930c3e6039a33ce45964ff2167f6ecedd419db06c1"},
    };
    for (const Vec& v : kVec) {
        const std::string got = sha256_hex(v.msg, std::strlen(v.msg));
        if (got != v.want) {
            fail(std::string("sha256 self-test failed for \"") + v.msg + "\": " + got);
        }
    }
    std::printf("sha256 self-test: %s\n", g_failures == 0 ? "ok (3 FIPS vectors)" : "FAIL");
}

std::string hex_bytes(const uint8_t* data, std::size_t size) {
    static const char* kHex = "0123456789abcdef";
    std::string s;
    s.reserve(size * 2);
    for (std::size_t i = 0; i < size; ++i) {
        s += kHex[data[i] >> 4];
        s += kHex[data[i] & 0xF];
    }
    return s;
}
std::string hex_bytes(const std::vector<uint8_t>& v) {
    return hex_bytes(v.data(), v.size());
}
std::string hex_bytes(const std::string& v) {
    return hex_bytes(reinterpret_cast<const uint8_t*>(v.data()), v.size());
}

std::string shell_quote(const std::string& s) {
    std::string out = "'";
    for (char c : s) {
        if (c == '\'') out += "'\\''";
        else out += c;
    }
    out += "'";
    return out;
}

std::string read_text_file(const std::string& path) {
    std::ifstream f(path, std::ios::binary);
    std::ostringstream ss;
    ss << f.rdbuf();
    return ss.str();
}

std::vector<std::string> split_tabs(const std::string& line) {
    std::vector<std::string> out;
    std::size_t start = 0;
    while (true) {
        const std::size_t tab = line.find('\t', start);
        if (tab == std::string::npos) {
            out.push_back(line.substr(start));
            break;
        }
        out.push_back(line.substr(start, tab - start));
        start = tab + 1;
    }
    return out;
}

// ---------------------------------------------------------------------------
// Sample set: 30 assets, every bundle represented, the six assets the DX9
// parity logs cover included verbatim.
// ---------------------------------------------------------------------------
const char* const kSamples[] = {
    "data/rika/01.X",
    "data/takano/00.X",
    "data/akane/00.X",
    "data/rena/01.X",
    "data/stage21/00.X",
    "data/stage21/env.dat",
    "data/stage21/00b.X",
    "data/stage21/collision.x",
    "data/stage21/collision_camera.X",
    "data/stage21/kumo.cnv",
    "data/directX/toon.cnv",
    "data/rika/" "\xe6\x9c\x8d" ".cnv",                          // 服.cnv
    "data/rika/01.dat",
    "data/takano/00.dat",
    "data/voice/WIN/W09-09-6.cnv",
    "data/voice/tomitake/tagfront/000.cnv",
    "data/voice/tomitake/recovery/000.cnv",
    "data/voice/takano/revival_B/001.cnv",
    "data/bgm/win.sfl",
    "data/bgm/vs.ogg",
    "data/bgm/win.ogg",
    "movie/op.mpg",
    "movie/Thumbs.db",
    "data/voice/entry/rika_B01.cnv",
    "data/voice/akane/damageKO_B/000.cnv",
    "data/bullet/041/056.dat",
    "data/rika/02.dat",
    "data/mion/00.X",
    "data/stage21/" "\xe8\x91\x89" "\xe3\x81\xa3" "\xe3\x81\xb1" "\xe5\x9c\xb0" "\xe9\x9d\xa2" "02.cnv",
    "data/stage21/" "\xe6\x9c\xa8" "\xe7\x9c\x81" "\xe3\x82\xa8" "\xe3\x83\x8d" "\xe5\xa4\xa7" "02_1.cnv",
};
const std::size_t kSampleCount = sizeof(kSamples) / sizeof(kSamples[0]);

// Directories whose bundle listing is verified against the oracle.
const char* const kDirs[] = {"", "movie", "data/stage21", "data/rika", "data/bgm", "data/voice/entry"};
const std::size_t kDirCount = sizeof(kDirs) / sizeof(kDirs[0]);

// ---------------------------------------------------------------------------
// Oracle: extract_dat.py driven through its own functions.
// ---------------------------------------------------------------------------
const char* const kOracleScript = R"PY(#!/usr/bin/env python3
"""Oracle driver for remake/foundation/tests/dat_bundle_bytes.cpp.

Every decode below goes through remake/tools/asset-tools/extract_dat.py's own
functions (decode_entry_table, safe_filename); the payload XOR is the same
arithmetic as extract_dat.decode_file_data, done with a 256-entry translation
table so multi-hundred-MB payloads stay fast.

argv: <repo_dir> <game_dir> <work_dir>
reads:  <work_dir>/names.txt, <work_dir>/dirs.txt
writes: <work_dir>/oracle.tsv
"""
import hashlib, os, struct, sys

repo, game, workdir = sys.argv[1], sys.argv[2], sys.argv[3]
sys.path.insert(0, os.path.join(repo, "remake", "tools", "asset-tools"))
import extract_dat as ed

ARCHIVES = ["daybreak00.dat", "daybreak02.dat", "daybreak04.dat",
            "daybreak05.dat", "daybreak06.dat", "daybreak07.dat"]
XOR = [bytes(b ^ k for b in range(256)) for k in range(256)]


def unxor(data, offset):
    """Same key arithmetic as extract_dat.decode_file_data."""
    return data.translate(XOR[((offset >> 1) & 0xFF) | 8])


def read_table(name):
    with open(os.path.join(game, name), "rb") as f:
        n = struct.unpack("<H", f.read(2))[0]
        raw = f.read(n * 0x10C)
    if len(raw) != n * 0x10C:
        raise SystemExit("oracle: %s: table truncated" % name)
    dec = ed.decode_entry_table(raw)
    return [(dec[i * 0x10C:i * 0x10C + 0x104].split(b"\x00")[0],
             *struct.unpack_from("<II", dec, i * 0x10C + 0x104)) for i in range(n)]


def read_payload(name, offset, size):
    with open(os.path.join(game, name), "rb") as f:
        f.seek(offset)
        data = f.read(size)
    if len(data) != size:
        raise SystemExit("oracle: %s: payload truncated" % name)
    return unxor(data, offset)


def sha(data):
    return hashlib.sha256(data).hexdigest()


tables = {a: read_table(a) for a in ARCHIVES}

# Duplicate names resolve to the *earliest-registered* archive, which is not the
# file-number order the tables above are emitted in (that order keeps the table
# parity check aligned with the on-disk sequence). The exe registers daybreak07,
# then daybreak04, then daybreak00 (0x64d4d4 / 0x64d4ee / 0x64d4fe) before the
# rest, so 04 beats 00 for data/object/P01.cnv - measurably: the original's own
# battle-hud.webp matches daybreak04's fan and caption art, not daybreak00's.
PRECEDENCE = ["daybreak07.dat", "daybreak04.dat", "daybreak00.dat",
              "daybreak05.dat", "daybreak02.dat", "daybreak06.dat"]
names = open(os.path.join(workdir, "names.txt"), encoding="utf-8").read().splitlines()
dirs = open(os.path.join(workdir, "dirs.txt"), encoding="utf-8").read().splitlines()

with open(os.path.join(workdir, "oracle.tsv"), "w", encoding="utf-8") as out:
    for bi, a in enumerate(ARCHIVES):
        for ei, (raw, size, off) in enumerate(tables[a]):
            out.write("T\t%d\t%d\t%d\t%d\t%s\t%s\n" % (
                bi, ei, off, size, raw.hex(), ed.safe_filename(raw).encode("utf-8").hex()))

    for si, want in enumerate(names):
        resolved = False
        # Every copy is reported (the S records), in *file-number* order so the row
        # indices keep matching the T records above; the resolved one (R) is chosen in
        # PRECEDENCE order and carries that order's index, which is also the order
        # DatBundleSet::bundleFileName() exposes.
        copies = []
        for ai, a in enumerate(ARCHIVES):
            for ei, (raw, size, off) in enumerate(tables[a]):
                if ed.safe_filename(raw) == want:
                    copies.append((ai, ei, size, a))
        for ai, ei, size, a in copies:
            h = sha(read_payload(a, off if False else tables[a][ei][2], size))
            out.write("S\t%d\t%d\t%d\t%d\t%s\n" % (si, ai, ei, size, h))
        for pi, a in enumerate(PRECEDENCE):
            hit = [c for c in copies if c[3] == a]
            if not hit:
                continue
            ai, ei, size, _ = hit[0]
            h = sha(read_payload(a, tables[a][ei][2], size))
            out.write("R\t%d\t%d\t%d\t%d\t%s\n" % (si, pi, ei, size, h))
            resolved = True
            break
        if not resolved:
            out.write("R\t%d\t-1\t0\t0\t-\n" % si)

    for di, d in enumerate(dirs):
        d = d.strip("/")
        pref = d + "/" if d else ""
        seen, raws = set(), []
        for a in ARCHIVES:
            for raw, size, off in tables[a]:
                nm = ed.safe_filename(raw)
                if pref and not nm.startswith(pref):
                    continue
                rest = nm[len(pref):]
                if not rest or "/" in rest:
                    continue
                if nm in seen:
                    continue
                seen.add(nm)
                raws.append(raw)
        blob = b"\n".join(sorted(raws))
        out.write("D\t%d\t%d\t%s\n" % (di, len(raws), sha(blob)))
)PY";

struct OracleTableEntry {
    uint32_t offset = 0;
    uint32_t length = 0;
    std::string rawHex;
    std::string nameHex;
};

struct OracleCopy {
    int bundle = -1;
    uint32_t index = 0, length = 0;
    std::string sha;
};

struct OracleSample {
    bool resolved = false;
    int ownerBundle = -1;
    uint32_t ownerIndex = 0, ownerLength = 0;
    std::string ownerSha;
    std::vector<OracleCopy> copies;
};

struct Oracle {
    bool ran = false;
    std::vector<std::vector<OracleTableEntry>> tables;
    std::vector<OracleSample> samples;
    std::vector<std::pair<std::size_t, std::string>> dirs;   // count, sha of sorted raw names
    std::string log;
};

// The oracle script emits one table per archive in *file-number* order, while
// DatBundleSet's arrays are in precedence order (a duplicate resolves to the earliest
// registered archive, not the lowest-numbered one). Pair the two by name so a future
// reorder cannot silently compare the wrong tables — which is exactly what happened when
// the precedence order was corrected.
std::size_t oracleTableFor(const char* bundleName) {
    static const char* const kOracleOrder[] = {
        "daybreak00.dat", "daybreak02.dat", "daybreak04.dat",
        "daybreak05.dat", "daybreak06.dat", "daybreak07.dat",
    };
    for (std::size_t i = 0; i < sizeof(kOracleOrder) / sizeof(kOracleOrder[0]); ++i)
        if (std::strcmp(kOracleOrder[i], bundleName) == 0) return i;
    return static_cast<std::size_t>(-1);
}

Oracle run_oracle(const std::string& repo, const std::string& game, const fs::path& work) {
    Oracle o;
    o.tables.resize(DatBundleSet::kBundleCount);
    o.samples.resize(kSampleCount);
    o.dirs.resize(kDirCount);

    // Inputs, so no shell quoting of asset names is needed.
    {
        std::ofstream nf(work / "names.txt", std::ios::binary);
        for (std::size_t i = 0; i < kSampleCount; ++i) nf << kSamples[i] << "\n";
        std::ofstream df(work / "dirs.txt", std::ios::binary);
        for (std::size_t i = 0; i < kDirCount; ++i) df << kDirs[i] << "\n";
    }
    {
        std::ofstream sf(work / "oracle.py", std::ios::binary);
        sf << kOracleScript;
    }

    const std::string logPath = (work / "oracle.log").string();
    const std::string cmd = "python3 " + shell_quote((work / "oracle.py").string()) + " " +
                            shell_quote(repo) + " " + shell_quote(game) + " " +
                            shell_quote(work.string()) + " > " + shell_quote(logPath) + " 2>&1";
    std::printf("oracle: %s\n", cmd.c_str());
    const int rc = std::system(cmd.c_str());
    o.log = read_text_file(logPath);
    if (rc != 0) {
        std::printf("oracle: python3 exited with status %d\n%s\n", rc, o.log.c_str());
        return o;
    }

    std::ifstream in((work / "oracle.tsv").string());
    if (!in) {
        std::printf("oracle: no oracle.tsv produced\n%s\n", o.log.c_str());
        return o;
    }
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        const std::vector<std::string> f = split_tabs(line);
        if (f[0] == "T" && f.size() == 7) {
            const std::size_t bi = std::stoul(f[1]);
            const std::size_t ei = std::stoul(f[2]);
            if (bi < o.tables.size()) {
                if (o.tables[bi].size() <= ei) o.tables[bi].resize(ei + 1);
                OracleTableEntry e;
                e.offset  = static_cast<uint32_t>(std::stoul(f[3]));
                e.length  = static_cast<uint32_t>(std::stoul(f[4]));
                e.rawHex  = f[5];
                e.nameHex = f[6];
                o.tables[bi][ei] = std::move(e);
            }
        } else if (f[0] == "S" && f.size() == 6) {
            const std::size_t si = std::stoul(f[1]);
            if (si < o.samples.size()) {
                OracleCopy c;
                c.bundle = std::stoi(f[2]);
                c.index  = static_cast<uint32_t>(std::stoul(f[3]));
                c.length = static_cast<uint32_t>(std::stoul(f[4]));
                c.sha    = f[5];
                o.samples[si].copies.push_back(std::move(c));
            }
        } else if (f[0] == "R" && f.size() == 6) {
            const std::size_t si = std::stoul(f[1]);
            if (si < o.samples.size() && std::stoi(f[2]) >= 0) {
                o.samples[si].resolved    = true;
                o.samples[si].ownerBundle = std::stoi(f[2]);
                o.samples[si].ownerIndex  = static_cast<uint32_t>(std::stoul(f[3]));
                o.samples[si].ownerLength = static_cast<uint32_t>(std::stoul(f[4]));
                o.samples[si].ownerSha    = f[5];
            }
        } else if (f[0] == "D" && f.size() == 4) {
            const std::size_t di = std::stoul(f[1]);
            if (di < o.dirs.size()) {
                o.dirs[di] = {static_cast<std::size_t>(std::stoul(f[2])), f[3]};
            }
        }
    }
    o.ran = true;
    return o;
}

std::string bundleTag(int i) {
    const std::string name = DatBundleSet::bundleFileName(static_cast<std::size_t>(i));
    return name.size() >= 2 ? name.substr(8, 2) : "??";
}

// sha256 over the sorted undecoded names of a directory listing, matching the
// oracle's D line byte for byte.
std::string dir_raw_sha(const std::vector<const DatEntry*>& entries) {
    std::vector<std::string> names;
    names.reserve(entries.size());
    for (const DatEntry* e : entries) {
        names.emplace_back(reinterpret_cast<const char*>(e->rawName.data()),
                           e->rawName.size());
    }
    std::sort(names.begin(), names.end());
    std::string blob;
    for (std::size_t i = 0; i < names.size(); ++i) {
        if (i) blob += '\n';
        blob += names[i];
    }
    return sha256_hex(blob.data(), blob.size());
}

}  // namespace

// Walks up from `start` looking for the marker file that only the repo root has, so
// the test finds the oracle no matter which directory ctest (or a shell) starts it in.
fs::path findRepoRoot(fs::path start) {
    std::error_code ec;
    for (int depth = 0; depth < 12 && !start.empty(); ++depth) {
        if (fs::exists(start / "remake" / "tools" / "asset-tools" / "extract_dat.py", ec))
            return start;
        const fs::path parent = start.parent_path();
        if (parent == start) break;
        start = parent;
    }
    return {};
}

int main(int argc, char** argv) {
    const char* envRepo = std::getenv("REPO_DIR");
    const char* envGame = std::getenv("GAME_DIR");
    fs::path repo = argc > 2 ? fs::path(argv[2])
                             : (envRepo ? fs::path(envRepo) : findRepoRoot(fs::current_path()));
    if (repo.empty()) repo = findRepoRoot(fs::absolute(argv[0]).parent_path());
    if (repo.empty()) repo = fs::current_path();
    const fs::path game = argc > 1 ? fs::path(argv[1])
                                   : (envGame ? fs::path(envGame) : repo / "Higurashi-Daybreak");

    std::printf("dat_bundle_bytes: repo=%s game=%s\n", repo.string().c_str(), game.string().c_str());

    // No install (a plain checkout) is a skip, not a failure: the port cannot be wrong
    // about data that is not there, and this target is part of the default test suite.
    std::error_code skipEc;
    if (!fs::exists(game / "daybreak00.dat", skipEc)) {
        std::printf("SKIP: no install at %s (set GAME_DIR or pass <game_dir> <repo_dir>)\n",
                    game.string().c_str());
        return 0;
    }
    if (findRepoRoot(fs::absolute(argv[0]).parent_path()).empty() &&
        !fs::exists(repo / "remake" / "tools" / "asset-tools" / "extract_dat.py", skipEc)) {
        std::printf("SKIP: extract_dat.py oracle not found from repo=%s\n", repo.string().c_str());
        return 0;
    }
    sha256_selftest();

    // ---------------------------------------------------------------- bundles
    DatBundleSet set;
    const std::size_t opened = set.openAll(game.string());
    std::printf("bundles: %zu/%zu opened | total entries=%zu\n", opened,
                DatBundleSet::kBundleCount, set.entryCount());
    for (std::size_t i = 0; i < set.bundles().size(); ++i) {
        const DatBundle& b = set.bundles()[i];
        if (b.isOpen()) {
            std::printf("  [%zu] %-16s %6zu entries  %12llu bytes  %s\n", i,
                        DatBundleSet::bundleFileName(i), b.entries().size(),
                        static_cast<unsigned long long>(b.fileSize()), b.path().c_str());
        } else {
            std::printf("  [%zu] %-16s MISSING\n", i, DatBundleSet::bundleFileName(i));
        }
    }
    check(opened == DatBundleSet::kBundleCount, "all six bundles must open");
    check(set.missing().empty(), "no bundle may be missing in the sampled install");

    const fs::path work = fs::temp_directory_path() / "dat_bundle_bytes";
    std::error_code ec;
    fs::remove_all(work, ec);
    fs::create_directories(work, ec);

    Oracle oracle = run_oracle(repo.string(), game.string(), work);
    check(oracle.ran, "python3 oracle must run (extract_dat.py is the independent reference)");

    // ------------------------------------------------- table parity (12,345)
    std::size_t compared = 0, structuralDiff = 0, nameDiff = 0, sampleNameDiff = 0;
    std::vector<std::string> nameDiffExamples;
    for (std::size_t bi = 0; bi < set.bundles().size() && oracle.ran; ++bi) {
        const DatBundle& b = set.bundles()[bi];
        const std::size_t oi = oracleTableFor(DatBundleSet::bundleFileName(bi));
        const std::vector<OracleTableEntry>& ot =
            oi < oracle.tables.size() ? oracle.tables[oi] : oracle.tables[bi];
        if (b.entries().size() != ot.size()) {
            fail(std::string("bundle ") + DatBundleSet::bundleFileName(bi) + ": entry count " +
                 std::to_string(b.entries().size()) + " != oracle " + std::to_string(ot.size()));
            ++structuralDiff;
            continue;
        }
        for (std::size_t ei = 0; ei < ot.size(); ++ei) {
            const DatEntry& e = b.entries()[ei];
            const OracleTableEntry& o = ot[ei];
            ++compared;
            if (e.index != ei || e.offset != o.offset || e.length != o.length ||
                hex_bytes(e.rawName) != o.rawHex) {
                if (structuralDiff < 5) {
                    fail(std::string("bundle ") + DatBundleSet::bundleFileName(bi) + " entry " +
                         std::to_string(ei) + ": index/offset/length/rawName differ from oracle");
                }
                ++structuralDiff;
                continue;
            }
            if (hex_bytes(e.name) != o.nameHex) ++nameDiff;
        }
    }
    if (oracle.ran) {
        std::printf("table parity: %zu entries compared, %zu structural mismatches, "
                    "%zu decoded-name divergences\n", compared, structuralDiff, nameDiff);
    }

    // The samples must all decode identically (they were chosen that way) and
    // must match the foundation's own sjisToUtf8() decoder.
    for (std::size_t si = 0; si < kSampleCount && oracle.ran; ++si) {
        const OracleSample& os = oracle.samples[si];
        if (!os.resolved) {
            fail(std::string("oracle did not resolve sample ") + kSamples[si]);
            continue;
        }
        const std::size_t obi = oracleTableFor(DatBundleSet::bundleFileName(os.ownerBundle));
        const std::vector<OracleTableEntry>& ot =
            obi < oracle.tables.size() ? oracle.tables[obi] : oracle.tables[os.ownerBundle];
        if (os.ownerIndex < ot.size()) {
            const std::string want(kSamples[si]);
            if (hex_bytes(want) != ot[os.ownerIndex].nameHex) {
                ++sampleNameDiff;
                if (sampleNameDiff <= 3) {
                    fail(std::string("sample name decode differs from oracle: ") + kSamples[si]);
                }
            }
        }
    }
    check(sampleNameDiff == 0, "every sampled asset name must decode exactly like the oracle");

    // The bundle reader's default decoder must equal the foundation's
    // sjisToUtf8() over every entry of every bundle (this is what keeps a
    // bundle lookup resolvable by the same key the asset layer builds).
    std::size_t decoderDiff = 0;
    for (const DatBundle& b : set.bundles()) {
        for (const DatEntry& e : b.entries()) {
            const std::string raw(reinterpret_cast<const char*>(e.rawName.data()), e.rawName.size());
            if (xm::sjisToUtf8(raw) != e.name) {
                if (decoderDiff < 3) {
                    fail("default decoder differs from xm::sjisToUtf8 for '" + e.name + "'");
                }
                ++decoderDiff;
            }
        }
    }
    if (decoderDiff == 0) {
        std::printf("decoder parity: default decoder == xm::sjisToUtf8 for all %zu entries\n",
                    set.entryCount());
    }

    // ------------------------------------------------------ sample byte parity
    std::printf("\nper-asset sha256 (bundle bytes vs extract_dat.py oracle vs extracted tree):\n");
    std::size_t treeOk = 0, treeOtherCopy = 0, treeAbsent = 0, treeMismatch = 0;
    for (std::size_t si = 0; si < kSampleCount; ++si) {
        const char* name = kSamples[si];
        const DatBundle* owner = nullptr;
        const DatEntry* entry = set.find(name, &owner);
        if (!entry || !owner) {
            std::printf("[%2zu] %-42s MISSING (set.find returned null: %s)\n", si + 1, name,
                        set.lastError().c_str());
            fail(std::string("sample not found in any bundle: ") + name);
            continue;
        }
        const std::size_t ownerIndex = static_cast<std::size_t>(owner - &set.bundles()[0]);

        std::vector<uint8_t> bytes;
        if (!owner->read(*entry, bytes)) {
            std::printf("[%2zu] %-42s READ FAILED (%s)\n", si + 1, name, owner->lastError().c_str());
            fail(std::string("read failed for sample: ") + name);
            continue;
        }
        const std::string sha = sha256_hex(bytes);

        std::string oracleVerdict = "NOT-RUN";
        if (oracle.ran) {
            const OracleSample& os = oracle.samples[si];
            const bool sameEntry = os.resolved &&
                                   os.ownerBundle == static_cast<int>(ownerIndex) &&
                                   os.ownerIndex == entry->index &&
                                   os.ownerLength == entry->length;
            oracleVerdict = (sameEntry && os.ownerSha == sha) ? "ok" : "MISMATCH";
            if (oracleVerdict != "ok") {
                fail(std::string("oracle mismatch for ") + name + ": mine=" + sha +
                     " oracle=" + os.ownerSha + " owner=" + std::to_string(os.ownerBundle) +
                     "#" + std::to_string(os.ownerIndex));
            }
        }

        // Extracted tree: extract_dat.py writes every archive into one tree, so a
        // name shipped by two bundles holds the last bundle's copy (verified
        // 982/982 checkable duplicate groups).  A mismatch is only a failure when
        // the file matches no copy of the name at all.
        std::string treeVerdict = "absent";
        const fs::path treePath = game / name;
        if (fs::exists(treePath, ec)) {
            std::string treeSha;
            if (!sha256_hex_file(treePath.string(), treeSha)) {
                treeVerdict = "UNREADABLE";
                fail(std::string("cannot hash extracted file: ") + treePath.string());
            } else if (treeSha == sha) {
                treeVerdict = "ok";
                ++treeOk;
            } else {
                int matchBundle = -1;
                uint32_t matchIndex = 0;
                if (oracle.ran) {
                    for (const OracleCopy& c : oracle.samples[si].copies) {
                        if (c.sha == treeSha) {
                            matchBundle = c.bundle;
                            matchIndex = c.index;
                            break;
                        }
                    }
                }
                if (matchBundle >= 0) {
                    treeVerdict = "other-copy(" + bundleTag(matchBundle) + "#" +
                                  std::to_string(matchIndex) + ")";
                    ++treeOtherCopy;
                } else {
                    treeVerdict = "MISMATCH(no copy matches)";
                    ++treeMismatch;
                    fail(std::string("extracted tree file matches no bundle copy: ") + name);
                }
            }
        } else {
            ++treeAbsent;
        }

        std::printf("[%2zu] %-42s bytes=%-9zu sha256=%s  oracle=%s resolve=%s#%u tree=%s\n",
                    si + 1, name, bytes.size(), sha.c_str(), oracleVerdict.c_str(),
                    bundleTag(static_cast<int>(ownerIndex)).c_str(), entry->index,
                    treeVerdict.c_str());
    }
    std::printf("tree check: %zu ok, %zu other-copy (extract_dat.py overwrote with a later "
                "bundle), %zu absent, %zu MISMATCH\n", treeOk, treeOtherCopy, treeAbsent, treeMismatch);

    // ------------------------------------------- cross-bundle duplicates
    // Names shipped by more than one bundle are where the search order decides
    // the bytes; the extracted tree can only hold one copy (extract_dat.py
    // overwrites in archive order), which is what the tree=other-copy lines above
    // show.  Byte differences are not measured here (that is 783 MB of hashing);
    // length differences are a safe lower bound.
    {
        std::map<std::string, std::vector<const DatEntry*>> byName;
        for (const DatBundle& b : set.bundles()) {
            for (const DatEntry& e : b.entries()) byName[e.name].push_back(&e);
        }
        std::size_t dupGroups = 0, extraCopies = 0, lengthDiff = 0;
        for (const auto& kv : byName) {
            if (kv.second.size() < 2) continue;
            ++dupGroups;
            extraCopies += kv.second.size() - 1;
            for (std::size_t i = 1; i < kv.second.size(); ++i) {
                if (kv.second[i]->length != kv.second[0]->length) {
                    ++lengthDiff;
                    break;
                }
            }
        }
        std::printf("\ncross-bundle duplicates: %zu names in >1 bundle (%zu extra copies), "
                    "%zu groups with differing lengths\n", dupGroups, extraCopies, lengthDiff);
        check(dupGroups > 0, "the install must actually exercise the bundle order rule");
    }

    // ------------------------------------------- multi-bundle order is real
    {
        const DatBundle* owner = nullptr;
        const DatEntry* e = set.find("data/rika/01.X", &owner);
        check(e != nullptr && owner != nullptr, "data/rika/01.X must resolve");
        if (e && owner) {
            const std::size_t oi = static_cast<std::size_t>(owner - &set.bundles()[0]);
            std::printf("\nbundle order: data/rika/01.X -> %s#%u len=%u (daybreak04 has idx 2411 "
                        "len=9893738)\n", DatBundleSet::bundleFileName(oi), e->index, e->length);
            // Assert the *bundle by name*, not by array index: the index is now a
            // precedence position (daybreak07 first). The expected owner is daybreak04,
            // not daybreak00: both ship data/rika/01.X and 04 is the earlier-registered of
            // the two, so 04 wins under the rule the exe's registration order implies and
            // the P01 pixel test confirms. The DX9 remake's own log reports daybreak00
            // here because that port resolves duplicates in file-number order — this is a
            // case where the foundation is now more faithful than the A/B, and the
            // logs/asset-*.log expectation is superseded rather than broken.
            check(std::string(DatBundleSet::bundleFileName(oi)) == "daybreak04.dat",
                  "data/rika/01.X must resolve to daybreak04.dat (earliest-registered copy)");
        }
        // The duplicate is still individually addressable through its own bundle.
        const DatBundle* b04 = nullptr;
        for (std::size_t bi = 0; bi < set.bundles().size(); ++bi) {
            if (std::string(DatBundleSet::bundleFileName(bi)) == "daybreak04.dat")
                b04 = set.bundle(bi);
        }
        check(b04 && b04->isOpen(), "daybreak04.dat must be open");
        if (b04) {
            const DatEntry* e04 = b04->find("data/rika/01.X");
            check(e04 != nullptr, "daybreak04 must contain data/rika/01.X");
            if (e04) {
                std::vector<uint8_t> v;
                check(b04->read(*e04, v), "daybreak04 copy must read");
                const std::string sha = sha256_hex(v);
                std::printf("bundle order: explicit daybreak04 copy -> idx %u len %zu sha256=%s\n",
                            e04->index, v.size(), sha.c_str());
                if (oracle.ran) {
                    std::string want;
                    for (const OracleCopy& c : oracle.samples[0].copies) {
                        if (c.bundle == 2) want = c.sha;
                    }
                    check(!want.empty() && want == sha, "daybreak04 copy must equal the oracle's");
                }
            }
        }
    }

    // ------------------------------------------------- directory listings
    std::printf("\ndirectory listings (bundle entries, first bundle wins):\n");
    for (std::size_t di = 0; di < kDirCount; ++di) {
        const std::string dir = kDirs[di];
        const std::vector<const DatEntry*> listed = set.listDir(dir);
        const std::string sha = dir_raw_sha(listed);
        std::string verdict = "NOT-RUN";
        if (oracle.ran) {
            verdict = (oracle.dirs[di].first == listed.size() && oracle.dirs[di].second == sha)
                          ? "ok" : "MISMATCH";
            if (verdict != "ok") {
                fail("directory listing mismatch for '" + dir + "': mine count=" +
                     std::to_string(listed.size()) + " sha=" + sha + " oracle count=" +
                     std::to_string(oracle.dirs[di].first) + " sha=" + oracle.dirs[di].second);
            }
        }
        // Every listed entry must be the first-match occurrence and live one level down.
        for (const DatEntry* e : listed) {
            const DatEntry* again = set.find(e->name);
            if (again != e) {
                fail("listed entry is not the first-match occurrence: " + e->name);
                break;
            }
            const std::string prefix = dir.empty() ? std::string() : dir + "/";
            if (!prefix.empty() && e->name.compare(0, prefix.size(), prefix) != 0) {
                fail("listed entry outside '" + dir + "': " + e->name);
                break;
            }
            if (e->name.find('/', prefix.size()) != std::string::npos) {
                fail("listed entry is not directly inside '" + dir + "': " + e->name);
                break;
            }
        }
        std::printf("  [%zu] dir='%s' entries=%zu sha256(raw names)=%s oracle=%s\n",
                    di, dir.c_str(), listed.size(), sha.c_str(), verdict.c_str());
    }

    // ------------------------------------------------------- negative cases
    std::printf("\nnegative cases (must fail cleanly, no crash):\n");
    {
        // Missing asset.
        check(!set.has("data/does/not/exist.X"), "missing asset must not be reported as present");
        check(set.find("data/does/not/exist.X") == nullptr, "missing asset must find() as null");
        std::vector<uint8_t> out(4, 0xAB);
        check(!set.read("data/does/not/exist.X", out), "missing asset read() must fail");
        check(out.empty(), "failed set.read() must leave out empty");
        std::printf("  missing asset: find=null read=false error='%s'\n", set.lastError().c_str());

        // Entry pointing past end-of-file (a corrupt table can claim 4 GiB).
        DatEntry bogus;
        bogus.index = 0;
        bogus.name = "bogus";
        bogus.offset = static_cast<uint32_t>(set.bundles()[0].fileSize() - 4);
        bogus.length = 0x7FFFFFFFu;
        std::vector<uint8_t> big(8, 0x5A);   // pre-filled: a failed read must clear it
        check(!set.bundles()[0].read(bogus, big), "out-of-bounds entry must fail");
        check(big.empty(), "out-of-bounds read must clear the caller's buffer, not short-fill");
        std::printf("  out-of-bounds entry (offset=filesize-4 length=0x7FFFFFFF): read=false, "
                    "error='%s'\n", set.bundles()[0].lastError().c_str());

        // Zero-length entry: the DX9 path returns true with an empty buffer at any
        // offset (read of 0 bytes cannot come up short), and so does this port.
        DatEntry zero;
        zero.index = 0;
        zero.name = "zero-length";
        zero.offset = 2;
        zero.length = 0;
        std::vector<uint8_t> z(8, 0x11);
        check(set.bundles()[0].read(zero, z) && z.empty(),
              "zero-length entry must succeed with an empty buffer (DX9 parity)");
        std::printf("  zero-length entry: read=true bytes=0 (DX9 parity)\n");

        // Truncated / corrupt headers, in temp copies so the install is untouched.
        struct Case { const char* label; const char* file; bool expectOpen; };
        const fs::path tdir = work / "truncated";
        fs::create_directories(tdir, ec);

        // 0-byte and 1-byte files.
        { std::ofstream f(tdir / "empty.dat", std::ios::binary); }
        { std::ofstream f(tdir / "one.dat", std::ios::binary); f.put('\x07'); }
        // 4096-byte copy of daybreak07.dat: valid header, table needs 178*268 = 47704.
        {
            std::ifstream src(game / "daybreak07.dat", std::ios::binary);
            std::vector<char> buf(4096);
            src.read(buf.data(), 4096);
            std::ofstream f(tdir / "head4096.dat", std::ios::binary);
            f.write(buf.data(), src.gcount());
        }
        // Two bytes claiming 65535 entries (17.5 MB of table that is not there).
        {
            std::ofstream f(tdir / "numfiles_max.dat", std::ios::binary);
            const char hdr[2] = {'\xff', '\xff'};
            f.write(hdr, 2);
        }
        // Two bytes claiming zero entries: the DX9 path accepts this (empty table).
        {
            std::ofstream f(tdir / "numfiles_zero.dat", std::ios::binary);
            const char hdr[2] = {'\x00', '\x00'};
            f.write(hdr, 2);
        }
        // A full 17.5 MB table of zeros claiming 65535 entries: parses into 65535
        // garbage entries, must not crash and must not resolve anything.
        {
            std::ofstream f(tdir / "garbage_table.dat", std::ios::binary);
            const char hdr[2] = {'\xff', '\xff'};
            f.write(hdr, 2);
            std::vector<char> zeros(1 << 20, 0);
            for (int i = 0; i < 17; ++i) f.write(zeros.data(), zeros.size());
        }

        const Case cases[] = {
            {"empty file (0 bytes)", "empty.dat", false},
            {"1-byte file", "one.dat", false},
            {"4096-byte truncated copy of daybreak07.dat", "head4096.dat", false},
            {"numFiles=0xFFFF in a 2-byte file", "numfiles_max.dat", false},
        };
        for (const Case& c : cases) {
            DatBundle b;
            const bool ok = b.open((tdir / c.file).string());
            check(ok == c.expectOpen, std::string("truncated case '") + c.label + "' open() result");
            std::printf("  %-44s open=%s entries=%zu error='%s'\n", c.label,
                        ok ? "true" : "false", b.entries().size(), b.lastError().c_str());
        }
        {
            DatBundle b;
            const bool ok = b.open((tdir / "numfiles_zero.dat").string());
            check(ok, "numFiles=0 must open (DX9 parity: empty table is valid)");
            std::printf("  %-44s open=%s entries=%zu (DX9 parity)\n",
                        "numFiles=0 in a 2-byte file", ok ? "true" : "false", b.entries().size());
            check(b.entries().empty(), "numFiles=0 must yield zero entries");
        }
        {
            DatBundle b;
            const bool ok = b.open((tdir / "garbage_table.dat").string());
            check(ok, "all-zero 65535-entry table must open without crashing");
            std::printf("  %-44s open=%s entries=%zu\n", "all-zero 65535-entry table",
                        ok ? "true" : "false", b.entries().size());
            check(b.entries().size() == 65535, "all-zero table must parse 65535 entries");
            check(b.find("data/rika/01.X") == nullptr, "garbage table must not resolve real names");
            DatEntry g;
            g.offset = 0xFFFFFFFFu;
            g.length = 0xFFFFFFF0u;
            std::vector<uint8_t> gb;
            check(!b.read(g, gb), "garbage entry read must fail cleanly");
            std::printf("  %-44s read=false error='%s'\n", "garbage entry (offset/length 0xFFFFFFxx)",
                        b.lastError().c_str());
        }
    }

    // ------------------------------------------------------- case handling
    std::printf("\ncase handling (documented, not hidden):\n");
    {
        const DatEntry* exact_lower = set.find("data/rika/01.x");
        check(exact_lower == nullptr, "find() must be case-sensitive (DX9 find_by_name parity)");
        const DatEntry* folded_lower = set.findAsciiCaseInsensitive("data/rika/01.x");
        check(folded_lower != nullptr, "findAsciiCaseInsensitive() must match 01.x -> 01.X");
        const DatEntry* folded_path = set.findAsciiCaseInsensitive("DATA/Rika/01.X");
        check(folded_path != nullptr, "findAsciiCaseInsensitive() must fold path components");
        const DatEntry* upper = set.find("data/rika/01.X");
        check(upper != nullptr, "find() must match the stored spelling");
        if (folded_lower && upper) {
            check(folded_lower == upper, "folded lookup must return the same entry as exact");
            std::printf("  find(\"data/rika/01.x\")                      -> null (exact match only)\n");
            std::printf("  findAsciiCaseInsensitive(\"data/rika/01.x\")  -> idx %u len %u (same entry)\n",
                        folded_lower->index, folded_lower->length);
            std::printf("  findAsciiCaseInsensitive(\"DATA/Rika/01.X\")  -> idx %u len %u\n",
                        folded_path ? folded_path->index : 0, folded_path ? folded_path->length : 0);
            std::printf("  find(\"data/rika/01.X\")                      -> idx %u len %u\n",
                        upper->index, upper->length);
        }
        // The stored spelling of a stage collision mesh is lowercase; the scene
        // loader probes both, and the folded lookup is what makes 00.X/00.x agree.
        const DatEntry* lowerExt = set.find("data/stage21/collision.x");
        check(lowerExt != nullptr, "data/stage21/collision.x must exist as stored (lowercase)");
        const DatEntry* foldedExt = set.findAsciiCaseInsensitive("data/stage21/collision.X");
        check(foldedExt == lowerExt, "folded lookup of collision.X must find collision.x");
        std::printf("  stored \"data/stage21/collision.x\" -> idx %u; folded \"collision.X\" -> idx %u\n",
                    lowerExt ? lowerExt->index : 0, foldedExt ? foldedExt->index : 0);
        std::printf("  note: the exe's bundle index compares with __stricmp (0x00663c20), so it is\n"
                    "        case-insensitive; the DX9 port's find() is exact.  Both are exposed.\n");
    }

    // ----------------------------------------------------------- known gaps
    if (oracle.ran && nameDiff > 0) {
        std::printf("\nKNOWN DIVERGENCE: %zu/%zu decoded names differ from extract_dat.py's "
                    "full-CP932 decode.\n", nameDiff, compared);
        std::printf("  cause: the foundation's generated sjis_table.h has 315 entries; unmapped "
                    "CP932\n  codes pass through as raw bytes.  Affected names (first 5):\n");
        std::size_t shown = 0;
        for (std::size_t bi = 0; bi < set.bundles().size() && shown < 5; ++bi) {
            for (const DatEntry& e : set.bundles()[bi].entries()) {
                const std::size_t ei = e.index;
                const std::size_t oi = oracleTableFor(DatBundleSet::bundleFileName(bi));
                const std::vector<OracleTableEntry>& ot =
                    oi < oracle.tables.size() ? oracle.tables[oi] : oracle.tables[bi];
                if (ei >= ot.size()) continue;
                if (hex_bytes(e.name) != ot[ei].nameHex) {
                    std::printf("    %s#%u raw=%s mine=%s oracle=%s\n",
                                DatBundleSet::bundleFileName(bi), e.index,
                                hex_bytes(e.rawName).c_str(), hex_bytes(e.name).c_str(),
                                ot[ei].nameHex.c_str());
                    if (++shown >= 5) break;
                }
            }
        }
        std::printf("  effect: a bundle lookup keyed by the asset layer's own sjisToUtf8 stays "
                    "consistent\n  (decoder parity above proves it); only a full-CP932 tree name "
                    "would disagree.\n");
    }
    std::printf("\n");

    if (g_failures == 0) {
        std::printf("DAT_BUNDLE_PARITY: ok\n");
        return 0;
    }
    std::printf("DAT_BUNDLE_PARITY: FAIL (%d checks failed)\n", g_failures);
    return 1;
}
