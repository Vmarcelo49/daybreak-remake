// combat_audio.cpp — see the header for the recovered vocabulary, SE ids and the port rules.
#include "audio/combat_audio.h"

#include <cstdio>

namespace fnd::audio {
namespace {

// The 40 names in table order (DaybreakDX.exe VA 0x6b73b0, 16 bytes per entry).
constexpr const char* kVoiceEventNames[kVoiceEventCount] = {
    "addattack", "attackA",  "attackB",  "attackC",  "attackKO",  "backattack", "backdamage",
    "battlestart", "damage", "damagedown", "damageKO", "fire",     "guard",      "guarded",
    "HPcheck",   "intercept", "missdamage", "nearLose", "nearWin",  "oyashiro",   "oyashiroB",
    "poison",    "provoke",   "recovery",  "reloadNG", "reloadOK",  "revival",    "shotA",
    "shotB",     "shotC",     "shotFinal", "spark",    "specialA",  "specialB",   "tactics",
    "tagback",   "tagfront",  "tagOK",     "thank",    "specialC",
};

// FUN_00431e70:72 keeps the character's voice variant for exactly these four events; every
// other event takes the plain directory even for a B-persona character.
constexpr VoiceEvent kBVariantEvents[] = {VoiceEvent::AttackKO, VoiceEvent::BattleStart,
                                          VoiceEvent::DamageKO, VoiceEvent::Revival};

std::string numbered_stem(const char* dir, int alternative) {
    char number[16];
    std::snprintf(number, sizeof(number), "%03d", alternative < 0 ? 0 : alternative);
    return std::string(dir) + "/" + number;
}

}  // namespace

const char* voice_event_name(VoiceEvent e) {
    const int i = static_cast<int>(e);
    return (i >= 0 && i < kVoiceEventCount) ? kVoiceEventNames[i] : "";
}

bool voice_event_b_dir(VoiceEvent e) {
    for (VoiceEvent v : kBVariantEvents)
        if (v == e) return true;
    return false;
}

const char* combat_event_name(CombatEventKind k) {
    switch (k) {
        case CombatEventKind::MatchStart:    return "match-start";
        case CombatEventKind::MeleeSwing:    return "melee-swing";
        case CombatEventKind::ShotFired:     return "shot-fired";
        case CombatEventKind::Hit:           return "hit";
        case CombatEventKind::Overkill:      return "overkill";
        case CombatEventKind::Blocked:       return "blocked";
        case CombatEventKind::GuardStart:    return "guard";
        case CombatEventKind::Ko:            return "ko";
        case CombatEventKind::Respawn:       return "respawn";
        case CombatEventKind::HyperActivate: return "hyper";
        case CombatEventKind::Count:         break;
    }
    return "?";
}

uint64_t CombatEvent::id() const {
    // 24 bits of tick (2^24 ticks at 64 Hz = 72 hours of match), 4 bits of kind, 3 bits per
    // fighter index, 8 bits of per-tick sequence. Deterministic and collision-free for any
    // match this port can run.
    const uint64_t f = static_cast<uint64_t>(fighter < 0 ? 7 : fighter) & 0x7u;
    const uint64_t s = static_cast<uint64_t>(source < 0 ? 7 : source) & 0x7u;
    return (static_cast<uint64_t>(tick) << 24) |
           (static_cast<uint64_t>(kind) << 20) |
           (f << 17) | (s << 14) | (static_cast<uint64_t>(seq) & 0x3fu);
}

CombatEventList combat_events_for_frame(const CombatEventSource& source,
                                        const CombatFrameView& frame, uint32_t tick,
                                        bool match_start) {
    CombatEventList list;
    const int count = source.fighter_count() < 0 ? 0
                     : (source.fighter_count() > 4 ? 4 : source.fighter_count());
    auto emit = [&](CombatEventKind kind, int fighter, int src, uint8_t seq, bool shot) {
        CombatEvent e;
        e.kind = kind;
        e.fighter = fighter;
        e.source = src;
        e.tick = tick;
        e.seq = seq;
        e.shot = shot;
        list.add(e);
    };
    if (match_start)
        for (int i = 0; i < count; ++i) emit(CombatEventKind::MatchStart, i, -1, 0, false);
    for (int i = 0; i < count; ++i) {
        if (frame.swing_started[i]) emit(CombatEventKind::MeleeSwing, i, -1, 0, false);
        if (frame.shot_fired[i] || frame.shot_voice[i] >= 0) {
            emit(CombatEventKind::ShotFired, i, -1, 0, false);
            list.events[list.count - 1].voice_override = frame.shot_voice[i];
            list.events[list.count - 1].voice_alternative = frame.shot_voice_alternative[i];
            list.events[list.count - 1].source_voice_audited =
                frame.shot_voice_audited[i] && frame.shot_voice[i] < 0;
        }
        if (frame.hyper_started[i]) emit(CombatEventKind::HyperActivate, i, -1, 0, false);
        if (frame.guard_started[i]) emit(CombatEventKind::GuardStart, i, -1, 0, false);
        if (frame.respawned[i])     emit(CombatEventKind::Respawn, i, -1, 0, false);
    }
    bool ko_done[4] = {false, false, false, false};
    for (int i = 0; i < count; ++i) {
        const int victim = frame.melee_victim[i];
        if (!frame.melee_hit[i] || victim < 0 || victim >= 4) continue;
        if (!source.alive(victim)) {
            if (!ko_done[victim]) {
                emit(CombatEventKind::Ko, victim, i, 0, false);
                ko_done[victim] = true;
            }
        } else if (frame.blocked[victim]) {
            emit(CombatEventKind::Blocked, victim, i, 0, false);
        } else {
            emit(CombatEventKind::Hit, victim, i, 0, false);
        }
    }
    bool shot_on[4] = {false, false, false, false};
    for (int k = 0; k < frame.shot_hit_count && k < 8; ++k) {
        const CombatFrameView::ShotHit& hit = frame.shot_hits[k];
        if (hit.victim < 0 || hit.victim >= 4) continue;
        shot_on[hit.victim] = true;
        const uint8_t seq = static_cast<uint8_t>(k);
        if (!source.alive(hit.victim)) {
            if (!ko_done[hit.victim]) {
                emit(CombatEventKind::Ko, hit.victim, hit.shooter, seq, true);
                ko_done[hit.victim] = true;
            }
        } else if (hit.blocked) {
            emit(CombatEventKind::Blocked, hit.victim, hit.shooter, seq, true);
        } else {
            emit(CombatEventKind::Hit, hit.victim, hit.shooter, seq, true);
        }
    }
    for (int i = 0; i < count; ++i)
        if (frame.overkill_hits[i] > 0)
            emit(CombatEventKind::Overkill, i, -1, 0, shot_on[i]);
    return list;
}

CombatCue resolve_combat_event(const CombatEvent& e) {
    CombatCue cue;
    switch (e.kind) {
        case CombatEventKind::MatchStart:
            cue.has_voice = true;
            cue.voice = VoiceEvent::BattleStart;
            break;
        case CombatEventKind::MeleeSwing:
            // PORT RULE: the vocabulary names the melee chain's own three attacks and the
            // swing data carries no sound id, so the chain position picks them. seq is the
            // per-tick swing ordinal, which for one fighter is the chain step.
            cue.has_voice = true;
            cue.voice = e.seq == 0 ? VoiceEvent::AttackA
                                   : (e.seq == 1 ? VoiceEvent::AttackB : VoiceEvent::AttackC);
            break;
        case CombatEventKind::ShotFired:
            if (e.source_voice_audited && e.voice_override < 0) break;
            cue.has_voice = true;
            cue.voice = e.voice_override >= 0 && e.voice_override < kVoiceEventCount
                            ? static_cast<VoiceEvent>(e.voice_override) : VoiceEvent::Fire;
            break;
        case CombatEventKind::Hit:
            cue.has_voice = true;
            cue.voice = VoiceEvent::Damage;
            break;
        case CombatEventKind::Overkill:
            // "damagedown": the hit landed on a body that is already down (FUN_00637950's
            // overkill branch, which is also where SE 10 comes from).
            cue.has_voice = true;
            cue.voice = VoiceEvent::DamageDown;
            cue.se_id = 10;
            break;
        case CombatEventKind::Blocked:
            cue.has_voice = true;
            cue.voice = VoiceEvent::Guarded;
            break;
        case CombatEventKind::GuardStart:
            cue.has_voice = true;
            cue.voice = VoiceEvent::Guard;
            break;
        case CombatEventKind::Ko:
            // PORT RULE: the vocabulary's attack/damage pair is read as the two damage
            // SOURCES for the downed fighter's own line — "attackKO" for a melee blow,
            // "damageKO" for a shot. Which of the two the original plays where is NOT
            // recovered; what IS recovered is SE 9 on the blow that takes a live fighter
            // down, from both the melee (FUN_00639160:57) and shot (FUN_00637950:504) paths.
            cue.has_voice = true;
            cue.voice = e.shot ? VoiceEvent::DamageKO : VoiceEvent::AttackKO;
            cue.se_id = 9;
            break;
        case CombatEventKind::Respawn:
            cue.has_voice = true;
            cue.voice = VoiceEvent::Revival;
            break;
        case CombatEventKind::HyperActivate:
            // PORT RULE: the vocabulary has one hyper-mode line ("oyashiro", the mode the
            // game names) and no per-mode activation event, so all three port modes use it.
            cue.has_voice = true;
            cue.voice = VoiceEvent::Oyashiro;
            break;
        case CombatEventKind::Count:
            break;
    }
    cue.voice_b_dir = voice_event_b_dir(cue.voice);
    return cue;
}

std::string voice_asset_stem(const std::string& dir, VoiceEvent e, bool b_dir, int alternative) {
    const char* name = voice_event_name(e);
    if (dir.empty() || !name || !*name) return {};
    std::string event_dir = name;
    if (b_dir && voice_event_b_dir(e)) event_dir += "_B";
    return numbered_stem((dir + "/" + event_dir).c_str(), alternative);
}

// ---------------------------------------------------------------------------
// Dispatch
// ---------------------------------------------------------------------------
void CombatAudio::begin_match(int fighterCount) {
    end_match();
    fighter_count_ = fighterCount < 0 ? 0 : (fighterCount > 4 ? 4 : fighterCount);
}

void CombatAudio::set_fighter_voice(int fighter, std::string dir, bool b_persona) {
    if (fighter < 0 || fighter >= 4) return;
    voices_[static_cast<size_t>(fighter)].dir = std::move(dir);
    voices_[static_cast<size_t>(fighter)].b_persona = b_persona;
}

void CombatAudio::set_voice_alternatives(int fighter, VoiceEvent e, int count) {
    const int index = static_cast<int>(e);
    if (fighter < 0 || fighter >= 4 || index < 0 || index >= kVoiceEventCount) return;
    voices_[static_cast<size_t>(fighter)].alternatives[index] = count < 0 ? 0 : count;
}

bool CombatAudio::seen(uint64_t id) const {
    for (int i = 0; i < history_count_; ++i)
        if (history_[i] == id) return true;
    return false;
}

void CombatAudio::remember(uint64_t id) {
    history_[history_next_] = id;
    history_next_ = (history_next_ + 1) % kHistorySize;
    if (history_count_ < kHistorySize) ++history_count_;
}

void CombatAudio::reset_history() {
    history_count_ = 0;
    history_next_ = 0;
}

void CombatAudio::play_voice(const CombatEvent& e, const CombatCue& cue) {
    if (e.fighter < 0 || e.fighter >= 4) return;
    FighterVoice& v = voices_[static_cast<size_t>(e.fighter)];
    if (v.dir.empty()) return;
    const int count = v.alternatives[static_cast<int>(cue.voice)];
    if (count <= 0) {
        ++stats_.voice_missing;  // no shipped alternative: stay silent, never invent a file
        return;
    }
    // PORT RULE: the original picks the alternative with `rand % count`; the port picks
    // deterministically from the event's identity unless its move supplied an exact alternative.
    const int alternative = e.voice_alternative >= 0 ? e.voice_alternative : static_cast<int>(
        (static_cast<uint64_t>(e.tick) * 7u + static_cast<uint64_t>(e.fighter) * 3u + e.seq) %
        static_cast<uint64_t>(count));
    if (alternative >= count) { ++stats_.voice_missing; return; }
    const std::string stem = voice_asset_stem(v.dir, cue.voice, v.b_persona, alternative);
    if (stem.empty()) return;
    // One voice channel per fighter (the original's per-player audio object): the fighter's
    // own previous line is stopped so two fighters never clobber each other and one fighter
    // never stacks.
    const int channel = voice_channel_for(e.fighter);
    if (v.channel >= 0) sink_.stop(v.channel);
    const int played = sink_.play(stem, SfxBus::Voice, channel);
    if (played < 0) {
        v.channel = -1;
        ++stats_.voice_missing;
        return;
    }
    v.channel = played;
    last_voice_stem_ = stem;
    ++stats_.voice_plays;
}

void CombatAudio::play_se(const CombatEvent& e, const CombatCue& cue) {
    if (!cue.has_se()) return;
    // The SE bus auto-picks (the original's own bank is a 32-slot table, FUN_0064ade0).
    // The channel is not claimed: an SE is one-shot and frees itself when it drains.
    const std::string stem = numbered_stem("data/se", cue.se_id);
    if (sink_.play(stem, SfxBus::Sfx, -1) < 0) {
        ++stats_.se_missing;
        return;
    }
    last_se_id_ = cue.se_id;
    ++stats_.se_plays;
    (void)e;
}

void CombatAudio::dispatch(const CombatEvent& e) {
    const uint64_t id = e.id();
    if (seen(id)) {
        ++stats_.duplicates;  // same tick re-dispatched (a replayed frame): never twice
        return;
    }
    remember(id);
    last_event_id_ = id;
    const int kind = static_cast<int>(e.kind);
    if (kind >= 0 && kind < kCombatEventKindCount) ++stats_.dispatched[kind];
    if (suspended_) {
        ++stats_.suspended_drops;
        return;
    }
    const CombatCue cue = resolve_combat_event(e);
    if (cue.has_voice) play_voice(e, cue);
    play_se(e, cue);
}

void CombatAudio::suspend() {
    if (suspended_) return;
    suspended_ = true;
    for (FighterVoice& v : voices_) {
        if (v.channel >= 0) {
            sink_.stop(v.channel);
            v.channel = -1;
        }
    }
}

void CombatAudio::resume() { suspended_ = false; }

void CombatAudio::end_match() {
    // The SFX bus carries this match's one-shots (KO/overkill ids): they are cut with the
    // match, never left ringing into the result screen or the next match.
    sink_.stop_bus(SfxBus::Sfx);
    for (FighterVoice& v : voices_) {
        if (v.channel >= 0) {
            sink_.stop(v.channel);
            v.channel = -1;
        }
        v.dir.clear();
        v.b_persona = false;
        for (int& count : v.alternatives) count = 0;
    }
    fighter_count_ = 0;
    reset_history();
    last_voice_stem_.clear();
    last_se_id_ = -1;
    suspended_ = false;
}

int CombatAudio::claimed_channels() const {
    int n = 0;
    for (const FighterVoice& v : voices_)
        if (v.channel >= 0) ++n;
    return n;
}

int CombatAudio::claimed_voice(int fighter) const {
    if (fighter < 0 || fighter >= 4) return -1;
    return voices_[static_cast<size_t>(fighter)].channel;
}

}  // namespace fnd::audio
