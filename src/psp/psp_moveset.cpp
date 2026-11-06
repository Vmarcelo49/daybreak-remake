#include "psp/psp_moveset.h"

#include "actor_animation_clock.hpp"
#include "actor_animation_settings.hpp"
#include "actor_frame_data.hpp"
#include "asset_search_path.hpp"
#include "character_names.hpp"
#include "psp/psp_take_table.h"
#include "psp_roster.hpp"
#include "x_animation_keys.hpp"
#include "x_compression.hpp"
#include "x_objects.hpp"

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <map>
#include <tuple>
#include <stdexcept>

namespace daybreak::psp {
namespace {

// ---------------------------------------------------------------- little-endian readers
struct Bytes {
    const std::vector<std::uint8_t>& data;
    std::size_t pos = 0;
    void need(std::size_t n) const {
        if (n > data.size() - pos) throw std::runtime_error("PSP moveset: truncated file");
    }
    std::uint32_t word() { need(4); const auto p = data.data() + pos; pos += 4;
        return std::uint32_t(p[0]) | (std::uint32_t(p[1]) << 8) | (std::uint32_t(p[2]) << 16) | (std::uint32_t(p[3]) << 24); }
    std::int32_t integer() { const auto u = word(); std::int32_t v; std::memcpy(&v, &u, 4); return v; }
    float real() { const auto u = word(); float v; std::memcpy(&v, &u, 4); return v; }
};

// Marker times the PSP uses for "this record does not fire" / "never".
bool psp_time_finite(float time) { return std::isfinite(time) && time >= 0.f && time < 1e9f; }

// ---------------------------------------------------------------- the PSP trio
// `.acs` (fighter.md §5.1): header {size, 1, block, 350}, then per row {stride, count,
// (f32 time, u32 code)[count]}. Read only to validate the file and to report populated rows; the
// events it holds are PSP voice/effect ids with no PC equivalent, so none of them are ported.
struct AcsSummary {
    unsigned rows = 0, populated = 0, entries = 0;
};
AcsSummary parse_acs(const std::vector<std::uint8_t>& bytes) {
    if (bytes.size() < 16) throw std::runtime_error("PSP .acs: too small");
    Bytes b{bytes};
    const auto total = b.word();
    b.word();  // version or block count
    b.word();  // payload size
    const auto rows = b.word();
    if (rows == 0 || rows > 4096) throw std::runtime_error("PSP .acs: bad row count");
    if (total != bytes.size()) throw std::runtime_error("PSP .acs: header size does not match the file");
    AcsSummary out{rows, 0, 0};
    for (unsigned row = 0; row < rows; ++row) {
        const auto stride = b.word();
        const auto count = b.word();
        if (stride != 8 + 8 * count) throw std::runtime_error("PSP .acs: row stride mismatch");
        if (count > 64) throw std::runtime_error("PSP .acs: excessive row entries");
        for (unsigned i = 0; i < count; ++i) { b.real(); b.word(); }
        if (count) { ++out.populated; out.entries += count; }
    }
    if (b.pos != bytes.size()) throw std::runtime_error("PSP .acs: unconsumed bytes");
    return out;
}

// `.atp` (fighter.md §5.3): header {size, version, payload, rows}, then `rows` records; the record
// the game reads for row R is atp[acv.S4[R]], not atp[R] (docs/psp/notes/combat.md §1.3).
struct AttackRecord {
    float power = 0.f, charge = 0.f, reflect = 0.f;
    std::array<std::uint8_t, 4> field_0x14{};
    float scale = 1.f;   // +0x90, multiplies the power
    std::uint32_t motion = 0;
};
struct AtpTable {
    std::vector<AttackRecord> records;
};
AtpTable parse_atp(const std::vector<std::uint8_t>& bytes) {
    if (bytes.size() < 16) throw std::runtime_error("PSP .atp: too small");
    Bytes b{bytes};
    const auto total = b.word();
    const auto version = b.word();
    b.word();
    const auto rows = b.word();
    if (version != 1) throw std::runtime_error("PSP .atp: unsupported container version");
    if (total != bytes.size() || rows == 0 || rows > 4096) throw std::runtime_error("PSP .atp: bad header");
    const std::size_t payload = bytes.size() - b.pos;
    if (payload % rows) throw std::runtime_error("PSP .atp: record stride is not whole");
    const std::size_t stride = payload / rows;
    if (stride < 0x94) throw std::runtime_error("PSP .atp: record too short");
    AtpTable out;
    out.records.reserve(rows);
    auto word_at = [&](std::size_t offset) -> std::uint32_t {
        std::uint32_t u; std::memcpy(&u, bytes.data() + offset, 4); return u;
    };
    auto real_at = [&](std::size_t offset) -> float {
        const auto u = word_at(offset); float v; std::memcpy(&v, &u, 4); return v;
    };
    for (unsigned row = 0; row < rows; ++row) {
        const std::size_t base = b.pos + std::size_t(row) * stride;
        AttackRecord record;
        record.power = real_at(base + 0x00);
        record.charge = real_at(base + 0x04);
        record.reflect = real_at(base + 0x08);
        for (unsigned i = 0; i < 4; ++i) record.field_0x14[i] = bytes[base + 0x14 + i];
        record.motion = word_at(base + 0x8c);  // the PSP motion id this row names (+0x8c)
        record.scale = real_at(base + 0x90);
        if (!std::isfinite(record.power) || !std::isfinite(record.scale)) throw std::runtime_error("PSP .atp: non-finite power");
        out.records.push_back(record);
    }
    return out;
}

// `.acv` (formats.md §4.3, all twelve PSP weapons are version 1): four sections, each
// {section_bytes, rows} then its records. Sections 0-2 give every record a {bytes, count} header;
// section 3 is 350 bare (u16, u16) pairs, which is why the walk below falls back to a fixed stride
// when the headers do not tile the section. Section 2 holds the timed hit-window records, section 4
// the row -> handler id map.
struct AcvTable {
    std::vector<std::vector<float>> window_times;  // per row, the finite record times
    std::vector<float> row_frames;                 // per row, the longest finite S1 row-program time
    std::vector<unsigned> handler;                 // per row, S4 handler id (0xffffffff = unused)
};
std::vector<std::pair<std::size_t, std::size_t>> acv_rows(const std::vector<std::uint8_t>& bytes,
                                                          std::size_t section_start,
                                                          std::size_t section_bytes,
                                                          std::size_t gap, std::size_t rows) {
    std::vector<std::pair<std::size_t, std::size_t>> out;
    out.reserve(rows);
    const std::size_t end = section_start + section_bytes;
    std::size_t at = section_start + gap;
    bool headers = true;
    for (std::size_t row = 0; row < rows && headers; ++row) {
        if (at + 8 > end) { headers = false; break; }
        std::uint32_t row_bytes = 0, count = 0;
        std::memcpy(&row_bytes, bytes.data() + at, 4);
        std::memcpy(&count, bytes.data() + at + 4, 4);
        if (row_bytes < 8 || at + row_bytes > end) { headers = false; break; }
        out.emplace_back(at, row_bytes);
        at += row_bytes;
    }
    if (headers && at == end) return out;
    // No per-record headers: one fixed stride for the whole payload.
    out.clear();
    const std::size_t payload = section_bytes - gap;
    if (rows == 0 || payload % rows) throw std::runtime_error("PSP .acv: section is neither headed nor fixed-stride");
    const std::size_t stride = payload / rows;
    for (std::size_t row = 0; row < rows; ++row) out.emplace_back(section_start + gap + row * stride, stride);
    return out;
}
AcvTable parse_acv(const std::vector<std::uint8_t>& bytes) {
    if (bytes.size() < 16) throw std::runtime_error("PSP .acv: too small");
    Bytes header{bytes};
    const auto total = header.word();
    const auto version = header.word();
    header.word();
    const auto sections = header.word();
    if (version != 1) throw std::runtime_error("PSP .acv: unsupported container version");
    if (total != bytes.size() || sections != 4) throw std::runtime_error("PSP .acv: bad header");
    std::size_t pos = 16;
    std::vector<std::vector<std::pair<std::size_t, std::size_t>>> rows_of_section;
    for (unsigned section = 0; section < sections; ++section) {
        if (pos + 8 > bytes.size()) throw std::runtime_error("PSP .acv: truncated section header");
        std::uint32_t section_bytes = 0, count = 0;
        std::memcpy(&section_bytes, bytes.data() + pos, 4);
        std::memcpy(&count, bytes.data() + pos + 4, 4);
        if (count == 0 || count > 4096 || section_bytes < 8 || pos + section_bytes > bytes.size())
            throw std::runtime_error("PSP .acv: bad section");
        rows_of_section.push_back(acv_rows(bytes, pos, section_bytes, 8, count));
        pos += section_bytes;
    }
    if (pos != bytes.size()) throw std::runtime_error("PSP .acv: unconsumed bytes");
    AcvTable out;
    out.window_times.resize(rows_of_section[1].size());
    for (std::size_t row = 0; row < rows_of_section[1].size(); ++row) {
        const auto [at, row_bytes] = rows_of_section[1][row];
        std::uint32_t stride = 0, count = 0;
        if (row_bytes >= 8) { std::memcpy(&stride, bytes.data() + at, 4); std::memcpy(&count, bytes.data() + at + 4, 4); }
        if (!count || stride < 8) continue;
        const std::size_t item = (stride - 8) / count;
        if (item < 4) throw std::runtime_error("PSP .acv: window record too short");
        for (unsigned i = 0; i < count; ++i) {
            float time = 0.f;
            std::memcpy(&time, bytes.data() + at + 8 + std::size_t(i) * item, 4);
            if (psp_time_finite(time)) out.window_times[row].push_back(time);
        }
        std::sort(out.window_times[row].begin(), out.window_times[row].end());
    }
    // Section 0 is the row program: {f32 time, u32 flags} entries walked by the row timer, so its
    // longest finite time is how long the PSP keeps the row. The terminator is a "never" marker.
    out.row_frames.assign(rows_of_section[0].size(), 0.f);
    for (std::size_t row = 0; row < rows_of_section[0].size(); ++row) {
        const auto [at, row_bytes] = rows_of_section[0][row];
        std::uint32_t stride = 0, count = 0;
        if (row_bytes >= 8) { std::memcpy(&stride, bytes.data() + at, 4); std::memcpy(&count, bytes.data() + at + 4, 4); }
        if (!count || stride < 16) continue;
        const std::size_t item = (stride - 8) / count;
        if (item < 8) throw std::runtime_error("PSP .acv: row program record too short");
        for (unsigned i = 0; i < count; ++i) {
            float time = 0.f;
            std::memcpy(&time, bytes.data() + at + 8 + std::size_t(i) * item, 4);
            if (psp_time_finite(time)) out.row_frames[row] = std::max(out.row_frames[row], time);
        }
    }
    out.handler.resize(rows_of_section[3].size(), 0xffffffffu);
    for (std::size_t row = 0; row < rows_of_section[3].size(); ++row) {
        const auto [at, row_bytes] = rows_of_section[3][row];
        if (row_bytes < 4) throw std::runtime_error("PSP .acv: handler map row too short");
        std::uint32_t hid = 0;
        std::memcpy(&hid, bytes.data() + at, 4);
        out.handler[row] = hid;
    }
    return out;
}

// ---------------------------------------------------------------- writers
void put_word(std::vector<std::uint8_t>& out, std::uint32_t value) {
    out.push_back(std::uint8_t(value));
    out.push_back(std::uint8_t(value >> 8));
    out.push_back(std::uint8_t(value >> 16));
    out.push_back(std::uint8_t(value >> 24));
}
void put_integer(std::vector<std::uint8_t>& out, std::int32_t value) {
    std::uint32_t u; std::memcpy(&u, &value, 4); put_word(out, u);
}
void put_text(std::vector<std::uint8_t>& out, const std::string& text, std::size_t width) {
    if (text.size() >= width) throw std::runtime_error("PSP moveset: name too long: " + text);
    out.insert(out.end(), text.begin(), text.end());
    out.insert(out.end(), width - text.size(), 0);
}
void append(std::vector<std::uint8_t>& out, const std::string& text) { out.insert(out.end(), text.begin(), text.end()); }

std::string format(const char* pattern, ...) {
    char buffer[512];
    va_list args;
    va_start(args, pattern);
    std::vsnprintf(buffer, sizeof buffer, pattern, args);
    va_end(args);
    return buffer;
}

// The PSP works in 30 Hz motion frames; the PC's row timers count 1/62.5 s frames
// (actor_animation_clock.hpp: one frame is 0.016 s). Time-keyed data, and only that, is converted
// here; row ids, damage and hit radii are not times.
constexpr double kPspFramesToPcFrames = (1.0 / 30.0) / 0.01600000075995922088623046875;
std::int32_t convert_time(float psp_frames) {
    const double scaled = double(psp_frames) * kPspFramesToPcFrames;
    if (!std::isfinite(scaled) || scaled > 1e6) throw std::runtime_error("PSP moveset: hit time out of range");
    return std::int32_t(std::lround(scaled));
}
std::uint32_t scaled_word(float value, double scale) {
    const double scaled = double(value) * scale;
    if (!std::isfinite(scaled) || scaled < -2e9 || scaled > 2e9) throw std::runtime_error("PSP moveset: value out of range");
    return std::uint32_t(std::int32_t(std::lround(scaled)));
}

// ---------------------------------------------------------------- the conversion
bool psp_row_of_state(unsigned state, unsigned& row) {
    for (const auto& [pc_state, psp_row] : kMoveRows)
        if (pc_state == state) { row = psp_row; return true; }
    return false;
}

}  // namespace

std::vector<unsigned> registered_animation_frame_counts(const std::vector<std::uint8_t>& model) {
    const auto roots = XObjectReader(model).read();
    const double ticks = actor_ticks_per_second(roots);
    std::vector<unsigned> out;
    for (auto it = roots.rbegin(); it != roots.rend(); ++it) {
        if (it->type != "AnimationSet" || it->reference) continue;
        const auto keys = read_x_animation_keys(*it);
        if (keys.tracks.empty()) continue;  // 43c2df registers only non-empty sets
        if (out.size() >= 256) throw std::runtime_error("Too many model animation sets");
        unsigned last = 0;
        for (const auto& track : keys.tracks) last = std::max(last, track.keys.back().time);
        out.push_back(actor_animation_frame_count(last, ticks));
    }
    return out;
}

namespace {

const TakeChoice* take_choice(unsigned character, unsigned pc_state) {
    const auto& fighter = kFighterTakes[psp_character_index(character)];
    for (unsigned i = 0; i < fighter.count; ++i)
        if (fighter.rows[i].pc_state == pc_state) return &fighter.rows[i];
    return nullptr;
}

bool take_listed_unusable(unsigned character, unsigned take) {
    const auto& fighter = kFighterTakes[psp_character_index(character)];
    for (unsigned i = 0; i < fighter.unusable_count; ++i)
        if (fighter.unusable[i] == take) return true;
    return false;
}

// The dispatch combo's settings section, as records, so a derived set can copy its PC set's.
std::vector<ActorAnimationSettings> dispatch_settings(const std::vector<std::uint8_t>& table) {
    const auto frames = read_actor_frame_data(table);
    return read_actor_animation_settings(table, frames.consumed).animations;
}

}  // namespace

AnimationPlan plan_psp_animation(unsigned character, const std::vector<std::uint8_t>& dispatch_frame_table,
                                 const std::vector<unsigned>& dispatch_set_frames,
                                 const std::vector<TakeInfo>& takes) {
    if (!is_psp_character(character)) throw std::invalid_argument("PSP animation plan: not a PSP fighter");
    if (takes.empty() || takes.size() > 256) throw std::invalid_argument("PSP animation plan: bad take list");
    const auto frames = read_actor_frame_data(dispatch_frame_table);
    const auto settings = dispatch_settings(dispatch_frame_table);

    AnimationPlan plan;
    plan.take_count = unsigned(takes.size());
    std::vector<unsigned> usable;
    for (unsigned i = 0; i < takes.size(); ++i)
        if (takes[i].usable && takes[i].frames > 0 && !take_listed_unusable(character, i)) usable.push_back(i);
    if (usable.empty()) throw std::runtime_error("PSP animation plan: the model has no usable take");

    // The fallback for a state the table does not name: the usable take whose length is nearest
    // the state's own PC length, ties to the lower index. Deterministic and never an index the
    // model does not have; it says nothing about what the take shows, which is why every state the
    // borrowed code commonly enters is in the table instead.
    const auto nearest = [&](unsigned pc_frames) {
        // PC frames are 1/62.5 s, PSP frames 1/30 s.
        const double target = double(pc_frames) * 0.016 * 30.0;
        unsigned best = usable.front();
        double best_error = 1e18;
        for (const unsigned take : usable) {
            const double error = std::abs(double(takes[take].frames) - target);
            if (error < best_error) { best = take; best_error = error; }
        }
        return best;
    };

    std::map<std::tuple<unsigned, unsigned, unsigned, unsigned>, unsigned> derived_index;
    unsigned listed = 0, fallen_back = 0;
    for (const auto& state : frames.states) {
        if (state.phases.empty()) { plan.phases.emplace_back(); continue; }
        std::vector<unsigned> weights;
        unsigned total = 0;
        // A phase's share of its state is its PC set's own length, which is how long the row
        // timer keeps it before advancing.
        for (const auto& phase : state.phases) {
            const unsigned length = phase.value < dispatch_set_frames.size() ? dispatch_set_frames[phase.value] : 0;
            weights.push_back(std::max(1u, length));
            total += weights.back();
        }

        unsigned take = 0, from = 0, to = 0;
        const TakeChoice* choice = take_choice(character, state.id);
        if (choice && choice->psp_take < takes.size() && std::find(usable.begin(), usable.end(), choice->psp_take) != usable.end()) {
            take = choice->psp_take;
            const unsigned last = takes[take].frames;
            from = std::min<unsigned>(choice->from, last);
            to = choice->to ? std::min<unsigned>(choice->to, last) : last;
            if (to <= from) to = std::min(last, from + 1);
            ++listed;
        } else {
            if (choice) plan.report += format("  state %u: table names take %u, which this model cannot play; fallback\n",
                                              state.id, unsigned(choice->psp_take));
            take = nearest(total);
            from = 0;
            to = takes[take].frames;
            ++fallen_back;
        }

        // Consecutive slices of [from, to], proportional to each phase's share, sharing their
        // boundary keys; a slice is at least one PSP frame so it has a length.
        std::vector<unsigned> sets;
        unsigned consumed = 0;
        for (std::size_t k = 0; k < state.phases.size(); ++k) {
            const unsigned span = to - from;
            const unsigned a = from + unsigned(std::lround(double(span) * consumed / total));
            consumed += weights[k];
            unsigned b = from + unsigned(std::lround(double(span) * consumed / total));
            if (b <= a) b = std::min(to, a + 1);
            const unsigned pc_set = state.phases[k].value;
            // A derived set copies the PC set's settings; the PC set must exist in the section.
            const unsigned settings_of = pc_set < settings.size() ? pc_set : ~0u;
            const auto key = std::make_tuple(take, a, b, settings_of);
            auto found = derived_index.find(key);
            if (found == derived_index.end()) {
                if (plan.take_count + plan.derived.size() >= 256)
                    throw std::runtime_error("PSP animation plan: more than 256 animation sets");
                found = derived_index.emplace(key, plan.take_count + unsigned(plan.derived.size())).first;
                plan.derived.push_back({take, a, b, settings_of});
            }
            sets.push_back(found->second);
        }
        plan.phases.push_back(std::move(sets));
    }
    plan.report += format("  animation plan: %u states from the take table, %u by the nearest-length fallback, "
                          "%zu derived sets after the %u takes\n",
                          listed, fallen_back, plan.derived.size(), plan.take_count);
    return plan;
}

std::vector<std::uint8_t> plan_animation_settings(const AnimationPlan& plan,
                                                  const std::vector<std::uint8_t>& dispatch_frame_table) {
    const auto settings = dispatch_settings(dispatch_frame_table);
    std::vector<std::uint8_t> out;
    const auto record = [&](const ActorAnimationSettings& setting) {
        put_word(out, setting.blend_frames);
        put_word(out, setting.hold_phase);
        put_word(out, std::uint32_t(setting.events.size()));
        for (const auto& event : setting.events) {
            for (const auto value : event.timing) put_word(out, value);
            put_text(out, event.source_texture, 60);
            put_text(out, event.replacement_texture, 60);
        }
    };
    put_word(out, std::uint32_t(plan.take_count + plan.derived.size()));
    // The takes themselves: the core's default for a set with no record (blend 1, no hold), so a
    // phase that names a raw take behaves as a PC set without settings does.
    ActorAnimationSettings plain;
    plain.blend_frames = 1;
    for (unsigned i = 0; i < plan.take_count; ++i) record(plain);
    for (const auto& derived : plan.derived) record(derived.pc_set < settings.size() ? settings[derived.pc_set] : plain);
    return out;
}

ConvertResult convert_psp_moveset(const ConvertRequest& request) {
    if (request.character.empty()) throw std::invalid_argument("PSP moveset: no character directory");
    if (request.weapon > 3) throw std::invalid_argument("PSP moveset: weapon slot");

    const auto acs = parse_acs(request.moveset.acs);
    const auto acv = parse_acv(request.moveset.acv);
    const auto atp = parse_atp(request.moveset.atp);
    if (acv.handler.size() != 350 || acv.window_times.size() != 350)
        throw std::runtime_error("PSP moveset: .acv row count is not 350");

    // The dispatch combo's table is the base: every row its recovered code addresses already
    // exists, with its own idle, guard, hurt, jump and shot rows.
    auto frame_data = read_actor_frame_data(request.dispatch.frame_table);
    const auto settings_offset = frame_data.consumed;
    if (settings_offset > request.dispatch.frame_table.size())
        throw std::runtime_error("PSP moveset: dispatch frame table has no animation section");
    read_actor_animation_settings(request.dispatch.frame_table, settings_offset);  // validates the tail
    if (request.dispatch.weapon_item.empty()) throw std::invalid_argument("PSP moveset: empty dispatch item");

    std::string report;
    report += format("psp_moveset: %s weapon %u from the dispatch combo's table (%zu states)\n",
                     request.character.c_str(), request.weapon, frame_data.states.size());
    report += format("  .acs %u rows, %u populated, %u events (not ported: PSP voice/effect ids)\n",
                     acs.rows, acs.populated, acs.entries);
    report += format("  .atp %zu attack records, .acv handler map and %u window lists\n",
                     atp.records.size(), acv.window_times.size());

    // Every phase of every state names a set of the fighter's own model (docs/psp/COMBAT.md §3.1).
    // Done first, because the hit windows below are scaled into the length of the set a phase plays.
    if (request.plan) {
        if (request.plan->phases.size() != frame_data.states.size())
            throw std::runtime_error("PSP moveset: the animation plan was made over another frame table");
        for (std::size_t i = 0; i < frame_data.states.size(); ++i) {
            auto& state = frame_data.states[i];
            const auto& sets = request.plan->phases[i];
            if (sets.size() != state.phases.size())
                throw std::runtime_error(format("PSP moveset: the animation plan does not cover state %u", state.id));
            for (std::size_t k = 0; k < state.phases.size(); ++k) state.phases[k].value = sets[k];
        }
        report += request.plan->report;
    } else {
        report += "  animation set indices kept from the dispatch combo (its PC model stands in)\n";
    }

    unsigned converted_moves = 0;
    for (auto& state : frame_data.states) {
        unsigned row = 0;
        if (!psp_row_of_state(state.id, row)) continue;
        const unsigned handler = acv.handler[row];
        if (handler >= atp.records.size()) {
            report += format("  state %u: PSP row %u names handler %u, no attack record; kept\n",
                             state.id, row, handler);
            continue;
        }
        const auto& attack = atp.records[handler];
        const auto& windows = acv.window_times[row];
        // A window timed beyond the phase's own length never opens (the row timer advances the
        // phase first), so the PSP's hit times are proportional-mapped inside 85% of that length.
        for (auto& phase : state.phases) {
            double limit = 0.0;
            if (phase.value < request.set_frames.size())
                limit = 0.85 * double(std::max(1u, request.set_frames[phase.value]));
            double scale = 1.0;
            if (limit > 0.0 && !windows.empty()) {
                const double last_window = double(convert_time(windows.back()));
                if (last_window > limit) scale = limit / last_window;
            }
            std::int32_t last = 0;
            for (std::size_t i = 0; i < phase.frames.size(); ++i) {
                auto& frame = phase.frames[i];
                // Timing: the PSP's own hit-window record times, converted to PC frames, scaled into
                // the phase's real length and kept monotonic so the frame cursor can walk them.
                if (i > 0 && i - 1 < windows.size()) {
                    frame.start = std::max(last, std::int32_t(std::lround(double(convert_time(windows[i - 1])) * scale)));
                } else {
                    frame.start = std::max(last, frame.start);
                }
                last = frame.start;
                const bool damaging = frame.extent != 0 || frame.fields[0] != 0;
                if (!damaging) continue;
                // Damage: the four fields the moveset study matched against .atp (word 0 = combat[0]
                // /1000, word 1 = combat[5]/100, word 2 = combat[6]/100, byte 3 of word 5 = combat[8]).
                frame.fields[0] = scaled_word(attack.power * attack.scale, 1000.0);
                frame.fields[5] = scaled_word(attack.charge, 100.0);
                frame.fields[6] = scaled_word(attack.reflect, 100.0);
                frame.fields[8] = attack.field_0x14[3];
                // Volume: the PSP test is a sphere around the attacker's weapon bone
                // (combat.md §1.3); the PC's shape 0 is a sphere at the record's bone, so the
                // record is re-anchored on the weapon bone with that radius.
                frame.bone = "Bip01_Prop1";
                frame.first = {0, 0, 0};
                frame.second = {0, 0, 0};
                frame.extent = kAttackSphereRadius;
                frame.shape = 0;
            }
        }
        report += format("  state %u <- PSP row %u (handler %u, motion %u, %u hit windows, %g frame row)\n",
                         state.id, row, handler, attack.motion, unsigned(windows.size()),
                         double(acv.row_frames[row]));
        ++converted_moves;
    }
    report += format("  %u of %zu moves took PSP damage, timing and volume\n",
                     converted_moves, frame_data.states.size());

    // Rewrite the frame table: same magic, the PSP model name, the PSP item id, and a settings
    // section that ends the file, as the reader's consumed == size contract requires: the plan's
    // when there is one, else the dispatch combo's own, byte for byte.
    std::vector<std::uint8_t> table;
    put_word(table, frame_data.magic);
    put_text(table, request.model, 260);
    auto parameters = frame_data.parameters;
    parameters[3] = request.item_id;
    for (const auto value : parameters) put_word(table, value);
    put_word(table, std::uint32_t(frame_data.states.size()));
    for (const auto& state : frame_data.states) {
        put_word(table, state.id);
        put_word(table, state.a);
        put_word(table, state.b);
        put_word(table, std::uint32_t(state.phases.size()));
        for (const auto& phase : state.phases) {
            put_word(table, phase.value);
            put_word(table, std::uint32_t(phase.frames.size()));
            for (const auto& frame : phase.frames) {
                put_text(table, frame.bone, 30);
                put_integer(table, frame.start);
                for (const auto value : frame.first) put_integer(table, value);
                put_word(table, frame.extent);
                for (const auto value : frame.fields) put_word(table, value);
                put_word(table, frame.flags28);
                put_word(table, frame.flags2c);
                put_word(table, frame.shape);
                for (const auto value : frame.second) put_integer(table, value);
            }
        }
    }
    if (request.plan) {
        const auto section = plan_animation_settings(*request.plan, request.dispatch.frame_table);
        table.insert(table.end(), section.begin(), section.end());
    } else {
        table.insert(table.end(), request.dispatch.frame_table.begin() + std::ptrdiff_t(settings_offset),
                     request.dispatch.frame_table.end());
    }

    ConvertResult result;
    result.files.push_back({"data/" + request.character + "/" + format("%02u.dat", request.weapon), std::move(table)});
    // The item keeps the dispatch combo's magazines and bullet list: the PSP's magazine numbers
    // are not decoded, and its bullet motion is not decoded at all (combat.md §3, §10), so the PC
    // item is the honest base under the PSP item id.
    result.files.push_back({format("data/item/%03u.dat", request.item_id), request.dispatch.weapon_item});
    report += format("  wrote data/%s/%02u.dat and data/item/%03u.dat\n",
                     request.character.c_str(), request.weapon, request.item_id);
    result.report = std::move(report);
    return result;
}

namespace {

std::vector<std::uint8_t> read_file(const std::filesystem::path& path) {
    std::ifstream file(path, std::ios::binary);
    if (!file) throw std::runtime_error("PSP moveset: cannot read " + path.u8string());
    return {std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};
}

void write_file(const std::filesystem::path& path, const std::vector<std::uint8_t>& bytes) {
    std::filesystem::create_directories(path.parent_path());
    std::ofstream file(path, std::ios::binary);
    if (!file) throw std::runtime_error("PSP moveset: cannot write " + path.u8string());
    file.write(reinterpret_cast<const char*>(bytes.data()), std::streamsize(bytes.size()));
    if (!file) throw std::runtime_error("PSP moveset: short write " + path.u8string());
}

// The study dumped the pack's paths with their separators replaced; the extractor may write them
// at their real paths. Both are accepted, real path first.
std::filesystem::path raw_path(const std::filesystem::path& root, const std::string& name) {
    const auto direct = root / name;
    if (std::filesystem::exists(direct)) return direct;
    std::string flat = name;
    std::replace(flat.begin(), flat.end(), '/', '_');
    const auto underscored = root / flat;
    if (std::filesystem::exists(underscored)) return underscored;
    throw std::runtime_error("PSP moveset: missing raw file " + name + " under " + root.u8string());
}

AssetSearchPath mount_install(const std::filesystem::path& install) {
    if (!std::filesystem::exists(install / "daybreak00.dat"))
        throw std::runtime_error("PSP moveset: no install at " + install.u8string());
    // The same three archives sim::Battle mounts, so the dispatch files are the ones the match uses.
    AssetSearchPath assets;
    for (const char* name : {"daybreak07.dat", "daybreak04.dat", "daybreak00.dat"}) assets.append((install / name).u8string());
    return assets;
}

}  // namespace

std::vector<AnimationPlan> plan_psp_animations(const std::string& install_dir,
                                               const std::vector<std::vector<TakeInfo>>& takes) {
    if (takes.size() != psp_character_names.size()) throw std::invalid_argument("PSP animation plan: one take list per fighter");
    AssetSearchPath assets = mount_install(std::filesystem::u8path(install_dir));
    std::vector<AnimationPlan> plans;
    for (unsigned index = 0; index < psp_character_names.size(); ++index) {
        const unsigned character = psp_character_first + index;
        const std::string dispatch_dir(character_names[psp_dispatch_character(character)]);
        // One plan per fighter, not per weapon: the four weapons share the model, so they share
        // its set list. Every weapon dispatches to the same PC slot (psp_roster.hpp), so they
        // also share the table the plan is made over; the check below keeps that true.
        const unsigned dispatch_weapon = psp_dispatch_weapon(character, 0);
        for (unsigned weapon = 1; weapon < psp_weapon_count; ++weapon)
            if (psp_dispatch_weapon(character, weapon) != dispatch_weapon)
                throw std::logic_error("PSP animation plan: a fighter's weapons dispatch to different PC slots");
        const auto table = assets.read(format("data/%s/%02u.dat", dispatch_dir.c_str(), dispatch_weapon)).bytes;
        auto model = assets.read("data/" + dispatch_dir + "/" + read_actor_frame_data(table).model).bytes;
        if (compressed_x(model)) model = expand_x(model);
        plans.push_back(plan_psp_animation(character, table, registered_animation_frame_counts(model), takes[index]));
    }
    return plans;
}

TreeResult prepare_psp_data_tree(const TreeRequest& request) {
    namespace fs = std::filesystem;
    const fs::path install = fs::u8path(request.install_dir);
    const fs::path raw = fs::u8path(request.raw_dir);
    const fs::path output = fs::u8path(request.output_dir);
    if (!fs::is_directory(raw)) throw std::runtime_error("PSP moveset: no raw directory at " + raw.u8string());
    AssetSearchPath assets = mount_install(install);

    TreeResult result;
    const auto read_install = [&](const std::string& path) { return assets.read(path).bytes; };
    for (unsigned index = 0; index < psp_character_names.size(); ++index) {
        const unsigned character = psp_character_first + index;
        const std::string name(psp_character_name(character));
        const unsigned psp_number = 17 + index;  // the pack numbers the fighters 17, 18, 19
        const unsigned dispatch_character = psp_dispatch_character(character);
        const std::string dispatch_dir(character_names[dispatch_character]);
        for (unsigned weapon = 0; weapon < psp_weapon_count; ++weapon) {
            const char suffix = char('a' + weapon);
            const std::string base = format("chr%02u%c", psp_number, suffix);
            ConvertRequest convert;
            convert.moveset.acs = read_file(raw_path(raw, "activity/" + base + ".acs"));
            convert.moveset.acv = read_file(raw_path(raw, "activity/" + base + ".acv"));
            convert.moveset.atp = read_file(raw_path(raw, "assault/" + base + ".atp"));
            // The dispatch combo supplies the rows the borrowed code addresses; its weapon slot is
            // from psp_roster.hpp so the converter and the runtime binding cannot disagree.
            const unsigned dispatch_weapon = psp_dispatch_weapon(character, weapon);
            convert.dispatch.frame_table = read_install(format("data/%s/%02u.dat", dispatch_dir.c_str(), dispatch_weapon));
            const auto dispatch_frames = read_actor_frame_data(convert.dispatch.frame_table);
            convert.dispatch.weapon_item = read_install(format("data/item/%03u.dat", dispatch_frames.parameters[3]));
            convert.character = name;
            convert.weapon = weapon;
            convert.item_id = psp_item_id(character, weapon);

            // The model this table will be paired with fixes both the file name and the animation
            // index space: a phase value must exist among the sets the load path registers.
            const fs::path converted_model = output / "data" / name / "00.X";
            fs::path model = converted_model;
            // The stand-in is the dispatch combo's PC model, copied in by this call for an earlier
            // weapon or by an earlier tree build; it is recognised by its bytes, because it is also
            // named 00.X. The fighter's own model is anything else at that path.
            const std::string stand_in_key = "data/" + dispatch_dir + "/" + dispatch_frames.model;
            const auto stand_in_bytes = read_install(stand_in_key);
            const bool present = fs::exists(model);
            std::vector<std::uint8_t> model_bytes = present ? read_file(model) : stand_in_bytes;
            const bool is_stand_in = present && model_bytes == stand_in_bytes;
            if (present && !is_stand_in) {
                // The fighter's own model: its set list is the plan's, takes then derived slices.
                if (!request.plans || request.plans->size() != psp_character_names.size())
                    throw std::runtime_error("PSP moveset: " + converted_model.u8string() +
                                             " is the fighter's own model, and no animation plan was given for it");
                convert.plan = &(*request.plans)[index];
            } else if (!present) {
                if (!request.copy_dispatch_model)
                    throw std::runtime_error("PSP moveset: no converted model at " + converted_model.u8string());
                model = output / "data" / name / dispatch_frames.model;
                write_file(model, stand_in_bytes);
                result.written.push_back((fs::path("data") / name / dispatch_frames.model).generic_u8string());
            }
            convert.model = model.filename().u8string();
            if (compressed_x(model_bytes)) model_bytes = expand_x(model_bytes);
            convert.set_frames = registered_animation_frame_counts(model_bytes);
            if (convert.plan && convert.set_frames.size() != convert.plan->take_count + convert.plan->derived.size())
                throw std::runtime_error(format("PSP moveset: %s registers %zu animation sets, its plan %zu",
                                                converted_model.u8string().c_str(), convert.set_frames.size(),
                                                convert.plan->take_count + convert.plan->derived.size()));

            auto converted = convert_psp_moveset(convert);
            result.report += converted.report;
            for (auto& file : converted.files) {
                write_file(output / fs::u8path(file.path), file.bytes);
                result.written.push_back(file.path);
            }
        }
    }
    result.report += format("psp_moveset: %zu files written under %s\n", result.written.size(), output.u8string().c_str());
    return result;
}

}  // namespace daybreak::psp
