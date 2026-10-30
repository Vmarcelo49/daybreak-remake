// =============================================================================
//  web_catalog_order.cpp — does the web catalog resolve duplicates the way the
//  native asset layer does?
//
//  Run from the repo root:
//
//      ./web_catalog_order                      # hermetic synthetic install only
//      GAME_DIR=Higurashi-Daybreak ./web_catalog_order
//      ./web_catalog_order <game_dir> <repo_dir>
//
//  Why this exists: the self-hosted service (webdelivery/) prepares one winning
//  copy per logical name and serves it. If the service's idea of "which copy
//  wins" ever drifts from `src/assets/dat_bundle.cpp`'s, the browser silently
//  gets different bytes than the game reads — the exact defect class
//  `dat_bundle_bytes.cpp` was written for, one layer up. A test that compares the
//  two orderings is worth more than a doc sentence saying they agree.
//
//  Two cases:
//
//   1. Synthetic (always runs, no game data). Six bundles are written in the
//      recovered precedence order with a table this test encrypts using
//      `dat_crypto` itself, carrying names that overlap across bundles in every
//      combination that matters: present in all six, in two, in the tail only,
//      and a case-variant pair. The native `DatBundleSet` resolves them, the
//      Python `daybreak_web order` resolves them, and the two must agree on
//      (winner bundle, table index, payload size) for every name — plus a
//      sha256 byte check on the winners, hashed independently by `sha256sum`.
//
//   2. Real install (skipped without one, like dat_bundle_bytes). The same
//      comparison over all 12,345 shipped entries, which is where the 983
//      multi-bundle names live.
//
//  Final line: "WEB_CATALOG_ORDER: ok" / "WEB_CATALOG_ORDER: FAIL (n ...)" /
//  "SKIP: ..." (exit 0) when a prerequisite is missing.
// =============================================================================
#include "assets/dat_bundle.h"
#include "assets/dat_crypto.h"

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

namespace fs = std::filesystem;
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
// One resolved name: what both sides must agree on.
// ---------------------------------------------------------------------------
struct Resolution {
    std::string bundle;
    uint32_t    index = 0;
    uint32_t    size = 0;
    std::string sha;        // only filled where hashing was requested
};

using Order = std::map<std::string, Resolution>;   // key: raw CP932 name bytes (hex)

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

std::string shell_quote(const std::string& s) {
    std::string out = "'";
    for (char c : s) {
        if (c == '\'') out += "'\\''";
        else out += c;
    }
    out += "'";
    return out;
}

std::string read_text(const fs::path& path) {
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
// The Python side: `daybreak_web order`, keyed by raw name bytes.
// ---------------------------------------------------------------------------
bool run_order(const fs::path& repo, const fs::path& install, bool hash, Order& out,
               std::string& log) {
    const fs::path pkg = repo / "remake" / "foundation" / "webdelivery";
    const fs::path logPath = fs::temp_directory_path() / "web_catalog_order.log";
    std::string cmd = "PYTHONPATH=" + shell_quote(pkg.string()) + " python3 -m daybreak_web order "
                      "--install " + shell_quote(install.string());
    if (hash) cmd += " --hash";
    cmd += " > " + shell_quote(logPath.string()) + " 2>&1";
    const int rc = std::system(cmd.c_str());
    log = read_text(logPath);
    if (rc != 0) {
        std::printf("python order failed (status %d):\n%s\n", rc, log.c_str());
        return false;
    }

    std::istringstream in(log);
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        const std::vector<std::string> f = split_tabs(line);
        if (f.size() < 5) continue;
        Resolution r;
        r.bundle = f[1];
        r.index  = static_cast<uint32_t>(std::stoul(f[2]));
        r.size   = static_cast<uint32_t>(std::stoul(f[3]));
        if (hash && f.size() >= 6) r.sha = f[4];
        out[f[0]] = r;
    }
    return !out.empty();
}

// ---------------------------------------------------------------------------
// The native side: DatBundleSet's own winner per name, keyed the same way.
// ---------------------------------------------------------------------------
Order native_order(const DatBundleSet& set) {
    Order out;
    for (const fnd::assets::DatBundle& b : set.bundles()) {
        for (const DatEntry& e : b.entries()) {
            const std::string key = hex_bytes(e.rawName.data(), e.rawName.size());
            if (out.find(key) != out.end()) continue;   // first bundle wins
            Resolution r;
            r.bundle = b.path().substr(b.path().find_last_of("/\\") + 1);
            r.index  = e.index;
            r.size   = e.length;
            out[key] = r;
        }
    }
    return out;
}

// sha256 of the native winner's bytes, hashed by the system tool so the check
// does not depend on a hash implementation this test also wrote.
std::string sha256sum(const fs::path& path) {
    const fs::path logPath = fs::temp_directory_path() / "web_catalog_order.sha";
    const std::string cmd = "sha256sum " + shell_quote(path.string()) + " > " +
                            shell_quote(logPath.string()) + " 2>&1";
    if (std::system(cmd.c_str()) != 0) return {};
    const std::string text = read_text(logPath);
    const std::size_t space = text.find(' ');
    return space == std::string::npos ? std::string() : text.substr(0, space);
}

void compare(const Order& native, const Order& python, const std::string& label,
             bool compareSha) {
    std::size_t compared = 0, missing = 0, mismatched = 0;
    for (const auto& kv : native) {
        const auto it = python.find(kv.first);
        if (it == python.end()) {
            if (missing < 5) fail(label + ": python has no entry for " + kv.first);
            ++missing;
            continue;
        }
        ++compared;
        const Resolution& a = kv.second;
        const Resolution& b = it->second;
        if (a.bundle != b.bundle || a.index != b.index || a.size != b.size) {
            if (mismatched < 5) {
                fail(label + ": " + kv.first + " native=" + a.bundle + "#" +
                     std::to_string(a.index) + "/" + std::to_string(a.size) + " python=" +
                     b.bundle + "#" + std::to_string(b.index) + "/" + std::to_string(b.size));
            }
            ++mismatched;
            continue;
        }
        if (compareSha && !b.sha.empty() && !a.sha.empty() && a.sha != b.sha) {
            if (mismatched < 5) fail(label + ": " + kv.first + " bytes differ (sha256)");
            ++mismatched;
        }
    }
    std::printf("%s: %zu names compared, %zu missing on the python side, %zu mismatched\n",
                label.c_str(), compared, missing, mismatched);
    check(missing == 0, label + ": every native name must appear in the python ordering");
    check(mismatched == 0, label + ": every name must resolve identically on both sides");
}

// ---------------------------------------------------------------------------
// Synthetic install: six bundles, precedence-exercising duplicates.
// ---------------------------------------------------------------------------
struct SyntheticEntry {
    const char* name;
    std::string payload;
};

struct SyntheticBundle {
    const char* file;                     // bundleFileName() spelling
    std::vector<SyntheticEntry> entries;
};

std::string payload(char fill, std::size_t size) { return std::string(size, fill); }

std::vector<SyntheticBundle> synthetic_plan() {
    // Names chosen so every precedence rule is exercised:
    //  * "all/six.X"      in all six bundles, different bytes and sizes each time
    //  * "pair/07-04.X"   in the first two (07 must win)
    //  * "pair/04-00.X"   in 04 and 00 (04 must win — the P01.cnv case)
    //  * "pair/00-05.X"   in 00 and 05 (00 must win over the tail)
    //  * "tail/02-06.X"   in the last two (02 before 06: the untested tail order,
    //                     pinned here so a reorder cannot pass unnoticed)
    //  * "case/coll.X"    lowercase in 07, uppercase in 04 — the folded lookup
    //  * "only/06.X"      only in the last bundle
    return {
        {"daybreak07.dat", {
            {"data/all/six.X", payload('7', 700)},
            {"data/pair/07-04.X", payload('a', 71)},
            {"data/case/coll.x", payload('c', 17)},
        }},
        {"daybreak04.dat", {
            {"data/all/six.X", payload('4', 400)},
            {"data/pair/07-04.X", payload('b', 72)},
            {"data/pair/04-00.X", payload('d', 41)},
            {"data/case/coll.X", payload('C', 18)},
        }},
        {"daybreak00.dat", {
            {"data/all/six.X", payload('0', 100)},
            {"data/pair/04-00.X", payload('e', 42)},
            {"data/pair/00-05.X", payload('f', 43)},
        }},
        {"daybreak05.dat", {
            {"data/all/six.X", payload('5', 500)},
            {"data/pair/00-05.X", payload('g', 44)},
        }},
        {"daybreak02.dat", {
            {"data/all/six.X", payload('2', 200)},
            {"data/tail/02-06.X", payload('h', 21)},
        }},
        {"daybreak06.dat", {
            {"data/all/six.X", payload('6', 600)},
            {"data/tail/02-06.X", payload('i', 22)},
            {"data/only/06.X", payload('j', 66)},
        }},
    };
}

// Writes one .DAT the way the game's own reader expects it: header, encrypted
// table, then payloads XOR'd with the offset-derived key (dat_crypto is its own
// inverse, so this is the reader's own cipher used backwards).
void write_bundle(const fs::path& path, const std::vector<SyntheticEntry>& entries) {
    constexpr std::size_t kEntrySize = 268;
    constexpr std::size_t kNameBytes = 260;
    const uint16_t count = static_cast<uint16_t>(entries.size());
    const std::size_t tableBytes = static_cast<std::size_t>(count) * kEntrySize;

    std::vector<uint8_t> table(tableBytes, 0);
    std::vector<std::string> names;
    std::vector<uint32_t> offsets, lengths;
    uint32_t cursor = static_cast<uint32_t>(2 + tableBytes);
    for (const SyntheticEntry& e : entries) {
        names.push_back(e.name);
        offsets.push_back(cursor);
        lengths.push_back(static_cast<uint32_t>(e.payload.size()));
        cursor += static_cast<uint32_t>(e.payload.size());
    }
    for (std::size_t i = 0; i < entries.size(); ++i) {
        uint8_t* slot = table.data() + i * kEntrySize;
        std::memcpy(slot, names[i].data(), std::min(names[i].size(), kNameBytes));
        std::memcpy(slot + kNameBytes, &lengths[i], 4);
        std::memcpy(slot + kNameBytes + 4, &offsets[i], 4);
    }
    fnd::assets::dat_crypto::file_table_xor(0, table);

    std::ofstream out(path, std::ios::binary);
    const uint8_t header[2] = {static_cast<uint8_t>(count & 0xFF),
                               static_cast<uint8_t>(count >> 8)};
    out.write(reinterpret_cast<const char*>(header), 2);
    out.write(reinterpret_cast<const char*>(table.data()),
              static_cast<std::streamsize>(table.size()));
    for (std::size_t i = 0; i < entries.size(); ++i) {
        std::vector<uint8_t> data(entries[i].payload.begin(), entries[i].payload.end());
        fnd::assets::dat_crypto::file_data_xor(offsets[i], data);
        out.write(reinterpret_cast<const char*>(data.data()),
                  static_cast<std::streamsize>(data.size()));
    }
}

// ---------------------------------------------------------------------------

fs::path find_repo_root(fs::path start) {
    std::error_code ec;
    for (int depth = 0; depth < 12 && !start.empty(); ++depth) {
        if (fs::exists(start / "remake" / "foundation" / "webdelivery" / "daybreak_web"
                             / "bundles.py", ec))
            return start;
        const fs::path parent = start.parent_path();
        if (parent == start) break;
        start = parent;
    }
    return {};
}

// The winner bytes for one raw name, written to `out` for the system hasher.
bool native_winner_bytes(const DatBundleSet& set, const std::string& rawHex,
                         std::vector<uint8_t>& out) {
    for (const fnd::assets::DatBundle& b : set.bundles()) {
        for (const DatEntry& e : b.entries()) {
            if (hex_bytes(e.rawName.data(), e.rawName.size()) == rawHex)
                return b.read(e, out);
        }
    }
    return false;
}

int run_case(const fs::path& repo, const fs::path& install, const std::string& label,
             bool hashWinners, std::size_t minDuplicateNames) {
    DatBundleSet set;
    const std::size_t opened = set.openAll(install.string());
    std::printf("\n%s: %s — %zu/%zu bundles open, %zu entries\n", label.c_str(),
                install.string().c_str(), opened, DatBundleSet::kBundleCount,
                set.entryCount());
    if (opened == 0) {
        fail(label + ": no bundle could be opened");
        return 1;
    }

    Order native = native_order(set);
    Order python;
    std::string log;
    if (!run_order(repo, install, hashWinners, python, log)) {
        fail(label + ": the python ordering could not be produced");
        return 1;
    }

    // Byte parity for the winners, hashed by sha256sum rather than by this test.
    if (hashWinners) {
        const fs::path tmp = fs::temp_directory_path() / "web_catalog_order.bin";
        std::size_t hashed = 0;
        for (auto& kv : native) {
            std::vector<uint8_t> bytes;
            if (!native_winner_bytes(set, kv.first, bytes)) continue;
            std::ofstream(tmp, std::ios::binary).write(
                reinterpret_cast<const char*>(bytes.data()),
                static_cast<std::streamsize>(bytes.size()));
            kv.second.sha = sha256sum(tmp);
            ++hashed;
        }
        std::printf("%s: %zu winner payloads hashed with sha256sum\n", label.c_str(), hashed);
        check(hashed > 0, label + ": at least one winner must be hashable");
    }

    compare(native, python, label, hashWinners);

    // The rule is only proven if duplicates were actually present.
    std::map<std::string, int> copies;
    for (const fnd::assets::DatBundle& b : set.bundles())
        for (const DatEntry& e : b.entries())
            copies[hex_bytes(e.rawName.data(), e.rawName.size())]++;
    std::size_t duplicates = 0;
    for (const auto& kv : copies)
        if (kv.second > 1) ++duplicates;
    std::printf("%s: %zu names in more than one bundle\n", label.c_str(), duplicates);
    check(duplicates >= minDuplicateNames,
          label + ": the case must exercise duplicate resolution");
    return 0;
}

}  // namespace

int main(int argc, char** argv) {
    const char* envRepo = std::getenv("REPO_DIR");
    const char* envGame = std::getenv("GAME_DIR");
    fs::path repo = argc > 2 ? fs::path(argv[2])
                             : (envRepo ? fs::path(envRepo) : find_repo_root(fs::current_path()));
    if (repo.empty()) repo = find_repo_root(fs::absolute(argv[0]).parent_path());
    if (repo.empty()) repo = fs::current_path();
    const fs::path game = argc > 1 ? fs::path(argv[1])
                                   : (envGame ? fs::path(envGame) : repo / "Higurashi-Daybreak");

    std::printf("web_catalog_order: repo=%s game=%s\n", repo.string().c_str(),
                game.string().c_str());

    const fs::path pkg = repo / "remake" / "foundation" / "webdelivery" / "daybreak_web";
    std::error_code ec;
    if (!fs::exists(pkg / "bundles.py", ec)) {
        std::printf("SKIP: webdelivery package not found under %s\n", repo.string().c_str());
        return 0;
    }
    if (std::system("python3 -c 'import sys' >/dev/null 2>&1") != 0) {
        std::printf("SKIP: python3 is not on PATH\n");
        return 0;
    }

    // ------------------------------------------------------------- synthetic
    const fs::path work = fs::temp_directory_path() / "web_catalog_order";
    fs::remove_all(work, ec);
    fs::create_directories(work, ec);
    for (const SyntheticBundle& b : synthetic_plan())
        write_bundle(work / b.file, b.entries);
    // Five raw-name duplicates in the plan; the sixth overlap is the case-variant
    // pair, which is a *folded* duplicate and is checked on its own below.
    run_case(repo, work, "synthetic", true, 5);

    // The case-fold rule on its own: "data/case/coll.x" is stored lowercase in
    // daybreak07 and uppercase in daybreak04, so the winner is 07's lowercase
    // entry and a folded lookup of either spelling must land on it.
    {
        DatBundleSet set;
        set.openAll(work.string());
        const std::string key = hex_bytes(
            reinterpret_cast<const uint8_t*>("data/case/coll.x"), 16);
        Order native = native_order(set);
        const auto it = native.find(key);
        check(it != native.end() && it->second.bundle == "daybreak07.dat",
              "the lowercase spelling in the earlier bundle must win the case-variant pair");
        const DatEntry* folded = set.findAsciiCaseInsensitive("data/case/coll.X");
        check(folded != nullptr && folded->index == (it == native.end() ? 0xFFFFFFFFu : it->second.index),
              "the folded lookup of the uppercase spelling must reach the same entry");
        std::printf("case variant: data/case/coll.x -> %s#%u; folded \"coll.X\" -> index %u\n",
                    it == native.end() ? "?" : it->second.bundle.c_str(),
                    it == native.end() ? 0 : it->second.index,
                    folded ? folded->index : 0xFFFFFFFFu);
    }

    // ---------------------------------------------------------- real install
    if (fs::exists(game / "daybreak00.dat", ec)) {
        run_case(repo, game, "install", false, 900);
    } else {
        std::printf("\ninstall case: SKIP (no install at %s; set GAME_DIR or pass "
                    "<game_dir> <repo_dir>)\n", game.string().c_str());
    }

    std::printf("\n");
    if (g_failures == 0) {
        std::printf("WEB_CATALOG_ORDER: ok\n");
        return 0;
    }
    std::printf("WEB_CATALOG_ORDER: FAIL (%d checks failed)\n", g_failures);
    return 1;
}
