// Issue #42: a BGM track's .sfl loop sheet is optional, and the port must play
// the track without one instead of failing the load. Device-free: the install is
// a map of bytes in, the sink is fnd::audio::NullEngine.
//
// Recovered behaviour this pins (FUN_00668820 in both binaries — the install's
// original DaybreakDX.exe via the Ghidra bridge, and the first-pass dump at
// research/decompiled/FUN_00668820.c:24-25, which states the same initialiser as
// a literal 0): the stream's loop start/end fields are set to 0.0 before the
// sheet is even looked for, so absent and unusable sheets both mean a
// zero-length loop region — play once to EOF, and the track still plays. Telling
// the two apart is a port rule; the original is silent in both cases.
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <map>
#include <string>
#include <vector>

#include "audio/audio.h"
#include "audio/audio_format.h"

#define CHECK(condition)                                                                  \
    do {                                                                                  \
        if (!(condition)) {                                                               \
            std::fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, #condition);          \
            return 1;                                                                     \
        }                                                                                 \
    } while (false)

using namespace fnd::audio;

namespace {

// The install's data/bgm: a path that is not in the map does not exist, which is
// exactly the difference between data/bgm/vs.ogg (no sheet at all) and a corrupt
// or truncated one.
struct Files {
    std::map<std::string, std::vector<uint8_t>> byPath;
    bool read(const std::string& path, std::vector<uint8_t>& out) const {
        const auto it = byPath.find(path);
        if (it == byPath.end()) return false;
        out = it->second;
        return true;
    }
};

void putU32(std::vector<uint8_t>& v, uint32_t x) {
    v.push_back((uint8_t)(x & 0xffu));
    v.push_back((uint8_t)((x >> 8) & 0xffu));
    v.push_back((uint8_t)((x >> 16) & 0xffu));
    v.push_back((uint8_t)((x >> 24) & 0xffu));
}

void putText(std::vector<uint8_t>& v, const char* s) {
    v.insert(v.end(), s, s + std::strlen(s));
}

// The shipped sheets are RIFF 'SFPL' blobs carrying a 'cue ' point plus an adtl
// 'labl' label for the same region (audio_format.h::parse_sfl_loop). This builds
// that shape from chosen numbers rather than copying game bytes.
std::vector<uint8_t> sflSheet(uint32_t cueStart, unsigned startMs, unsigned endMs) {
    char label[64];
    std::snprintf(label, sizeof(label), "Region %u:%u:%u.%u to %u:%u:%u.%u",
                  startMs / 3600000u, startMs / 60000u % 60u, startMs / 1000u % 60u,
                  startMs % 1000u, endMs / 3600000u, endMs / 60000u % 60u,
                  endMs / 1000u % 60u, endMs % 1000u);

    std::vector<uint8_t> adtl;
    putText(adtl, "adtl");
    putText(adtl, "labl");
    putU32(adtl, (uint32_t)(4 + std::strlen(label) + 1));  // dwName + text + NUL
    putU32(adtl, 1);
    putText(adtl, label);
    adtl.push_back(0);  // the shipped labels are NUL-terminated
    if (adtl.size() & 1u) adtl.push_back(0);

    std::vector<uint8_t> sheet;
    putText(sheet, "RIFF");
    putU32(sheet, 0);  // the parser never reads the RIFF size
    putText(sheet, "SFPL");
    putText(sheet, "cue ");
    putU32(sheet, 28);    // one 24-byte point plus its count
    putU32(sheet, 1);     // point count
    putU32(sheet, 1);     // dwName
    putU32(sheet, 0);     // dwPosition
    putText(sheet, "data");
    putU32(sheet, 0);     // dwChunkStart
    putU32(sheet, 0);     // dwBlockStart
    putU32(sheet, cueStart);  // dwSampleOffset: the loop start parse_sfl_loop reads
    putText(sheet, "LIST");
    putU32(sheet, (uint32_t)adtl.size());
    sheet.insert(sheet.end(), adtl.begin(), adtl.end());
    return sheet;
}

// One pass to EOF, driven the way the loaders drive it: set_source, then the
// region the loader applied. Returns the frames the sink accepted.
size_t stream_to_eof(LoopPlayer& player, NullEngine& engine, size_t frames) {
    size_t pushed = 0;
    for (size_t i = 0; i < frames / 1024 + 16 && player.position() < frames; ++i)
        pushed += player.push_next(engine, 1024);
    return pushed;
}

}  // namespace

int main() {
    // --- absent sheet: the data/bgm/vs.ogg case -----------------------------
    {
        const Files install;  // no sheets at all, exactly like the shipped vs.ogg
        const LoopSheetResult sheet = resolve_loop_sheet(
            "data/bgm/vs.ogg", 44100,
            [&install](const std::string& p, std::vector<uint8_t>& out) {
                return install.read(p, out);
            });
        CHECK(sheet.status == LoopSheet::Absent);
        CHECK(!sheet.loop.valid);
        CHECK(sheet.note.empty());  // no error string: an absent sheet is not a fault
        CHECK(loop_sheet_path("data/bgm/vs.ogg") == "data/bgm/vs.sfl");

        // The loader then applies that empty region, so the track streams once to
        // EOF and completes without wrapping.
        NullEngine engine;
        CHECK(engine.open(Spec{}));
        std::vector<int16_t> pcm(3000 * 2, 900);
        LoopPlayer player;
        player.set_source(pcm.data(), 3000);
        player.set_loop(sheet.loop.startSample, sheet.loop.endSample);
        const size_t pushed = stream_to_eof(player, engine, 3000);
        CHECK(pushed == 3000);
        CHECK(engine.pushed_frames() == 3000);  // all of it reached the sink, once
        CHECK(player.position() == 3000);
        CHECK(player.loops_completed() == 0);   // no wrap
        CHECK(player.push_next(engine, 1024) == 0);  // and it stays finished
        CHECK(player.loops_completed() == 0);
    }

    // --- unparsable sheet: still plays, diagnosed as unparsable -------------
    {
        Files install;
        install.byPath["data/bgm/broken.sfl"] = {'R', 'I', 'F', 'F', 0, 0, 0, 0,
                                                 'S', 'F', 'P', 'L'};  // header, no cue
        const LoopSheetResult sheet = resolve_loop_sheet(
            "data/bgm/broken.ogg", 44100,
            [&install](const std::string& p, std::vector<uint8_t>& out) {
                return install.read(p, out);
            });
        CHECK(sheet.status == LoopSheet::Unparsable);
        CHECK(!sheet.loop.valid);
        // The unparsable case keeps its own diagnostic, distinct from absent.
        CHECK(sheet.note == "unparsable loop sheet data/bgm/broken.sfl");

        NullEngine engine;
        CHECK(engine.open(Spec{}));
        std::vector<int16_t> pcm(2048 * 2, 700);
        LoopPlayer player;
        player.set_source(pcm.data(), 2048);
        player.set_loop(sheet.loop.startSample, sheet.loop.endSample);
        CHECK(stream_to_eof(player, engine, 2048) == 2048);
        CHECK(engine.pushed_frames() == 2048);
        CHECK(player.loops_completed() == 0);
    }

    // --- a sheet that does parse still loops, unchanged ---------------------
    // The numbers are the shipped data/bgm/01.sfl region (cue 297312, label
    // 00:00:06.741 to 00:01:30.221), so a device-free run pins a real loop point.
    {
        Files install;
        install.byPath["data/bgm/01.sfl"] = sflSheet(297312, 6741, 90221);
        const LoopSheetResult sheet = resolve_loop_sheet(
            "data/bgm/01.ogg", 44100,
            [&install](const std::string& p, std::vector<uint8_t>& out) {
                return install.read(p, out);
            });
        CHECK(sheet.status == LoopSheet::Parsed);
        CHECK(sheet.note.empty());
        CHECK(sheet.loop.valid);
        CHECK(sheet.loop.startSample == 297312u);
        CHECK(sheet.loop.endSample == 3978746u);
    }
    {
        // ...and it really wraps: one 1024-frame push from a 1000-frame track
        // with a 100..396 region lands back inside the region after three wraps.
        Files install;
        install.byPath["data/bgm/short.sfl"] = sflSheet(100, 2, 9);
        const LoopSheetResult sheet = resolve_loop_sheet(
            "data/bgm/short.ogg", 44100,
            [&install](const std::string& p, std::vector<uint8_t>& out) {
                return install.read(p, out);
            });
        CHECK(sheet.status == LoopSheet::Parsed);
        // The cue offset is the start verbatim; the end is the label's millisecond
        // time at file rate: (9 ms * 44100 + 500) / 1000 = 397.
        CHECK(sheet.loop.startSample == 100u && sheet.loop.endSample == 397u);
        NullEngine engine;
        CHECK(engine.open(Spec{}));
        std::vector<int16_t> pcm(1000 * 2, 500);
        LoopPlayer player;
        player.set_source(pcm.data(), 1000);
        player.set_loop(sheet.loop.startSample, sheet.loop.endSample);
        CHECK(player.push_next(engine, 1024) == 1024);
        CHECK(player.loops_completed() == 3);
        CHECK(player.position() >= sheet.loop.startSample);
        CHECK(player.position() < sheet.loop.endSample);
    }

    // --- why the loaders must apply the region even when it is empty --------
    // A LoopPlayer reused across tracks keeps its previous region (set_source
    // resets position and wrap count only), so a track without a sheet has to
    // clear it. Without that, the next track would loop the previous one's bars.
    {
        NullEngine engine;
        CHECK(engine.open(Spec{}));
        std::vector<int16_t> pcm(1000 * 2, 500);
        LoopPlayer player;
        player.set_source(pcm.data(), 1000);
        player.set_loop(100, 400);           // track 1 loops
        player.push_next(engine, 1024);
        CHECK(player.loops_completed() > 0);
        player.set_source(pcm.data(), 1000);  // track 2: no sheet
        player.set_loop(0, 0);                // the loader's absent/unparsable region
        CHECK(stream_to_eof(player, engine, 1000) == 1000);
        CHECK(player.loops_completed() == 0);
    }

    std::puts("bgm_loop_test: absent sheet plays to EOF, unparsable is diagnosed, "
              "parsed sheets still loop");
    return 0;
}
