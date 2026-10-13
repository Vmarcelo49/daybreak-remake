#pragma once
// combat_audio.h — live combat SE/voice policy for issue #16 (device-free).
//
// RECOVERED FROM THE ORIGINAL (DaybreakDX.exe):
//
//  * The per-character voice vocabulary is a 40-entry table of 16-byte names at VA
//    0x6b73b0 ("addattack", "attackA".."specialC"). FUN_00431e70 walks it and loads each
//    event's alternatives from `data/voice/<dir>/<event>/NNN.wav`, probing NNN upward until
//    the file is missing — so the ALTERNATIVE COUNT is discovered by the same probe here,
//    never assumed. For events 4/7/10/26 (attackKO / battlestart / damageKO / revival) it
//    takes the `<event>_B` directory instead when the character's voice variant is 1
//    (FUN_00431e70:72-77, 85-131).
//  * FUN_0041e180:196-206 picks the voice directory itself: `data/voice/<name>B` for the B
//    persona, otherwise `data/voice/<name>`. The install ships renaB/rikaB/chieB/hanyuB.
//  * The gameplay SE bank is `data/se/%03d.wav` with 32 slots (FUN_0064ade0's `< 0x20`
//    bound, played through FUN_0065a220); the menu/system bank is `data/sysse/%03d.wav`
//    (FUN_00647e00), which the host already loads for the UI. The two are separate.
//  * SE ids recovered from their call sites: 9 = the blow that takes a LIVE fighter down
//    (FUN_00639160:57 melee, FUN_00637950:504 shot), 10 = a hit on an already-down body
//    (FUN_00637950:489), 0xb/0xc = the two victory-sting layers (FUN_00635d40:165 and :203,
//    the second when the first layer's timer has counted down to 0x78 = 60 frames in),
//    0x16 = the report appearing and 0x15 = its per-row reveal tick (FUN_00635d40:495-508,
//    every 0x1e frames from 0x3c), 0x11 = a menu press (FUN_00634f60:38, FUN_0064c090:23),
//    0xd/0xe/0xf = the target-switch gesture (FUN_00421e30:24-32, FUN_00421f30:21).
//  * Independent per-player voice bookkeeping is the original's own design: FUN_0064ada0
//    returns a per-player audio object (`scene+0x5600 + player*0x34`, or `scene+0x56d0` for
//    "no player"), and FUN_0064ab30 wires each player's own volumes/ids into it.
//
// NOT RECOVERED, AND THEREFORE NOT INVENTED HERE: the SE ids for a melee swing, a shot being
// fired, a block and a respawn. Those actions carry the character's own VOICE, whose table
// names them exactly (attackA/B/C, fire/shotA-C, guard/guarded, revival, oyashiro); the SE
// bus carries only the ids listed above. `CombatCue::se_id` is -1 where nothing is evidenced.
//
// The module is policy only: it resolves events to asset stems and channel assignments and
// hands them to a sink. The host adapts its sample cache/engine to CombatAudioSink; tests
// record the calls. No SDL, no device, no file I/O here.
//
// PAUSE CONTRACT (issue #15, whose pause gates Match::step and returns an empty MatchFrame):
//  1. No pause test lives here. A paused step produces no events, so no cue can start.
//  2. Already-ringing SFX are the pause feature's to stop (it cuts the Sfx bus); stop_bus() is
//     the seam it can use instead of its own 16..31 loop.
//  3. Music is never touched by this layer.
//  4. Voices are NOT cut on pause: suspend() exists for a caller that wants that, and the host
//     does not call it from the pause path.
//  5. The pause cue itself is the recovered system SE 0x11 (data/sysse), the host's UI bus —
//     not a combat event.
//  6. end_match() is "stop everything this match started": it cuts the SFX bus and releases
//     every voice channel, so a leave path cannot strand a cue.
//  7/8. There is no looping combat cue here; every cue is a one-shot.

#include <array>
#include <cstdint>
#include <string>

#include "audio/audio_engine.h"  // SfxBus + the channel reservation constants

namespace fnd::audio {

// ---------------------------------------------------------------------------
// The recovered vocabulary (VA 0x6b73b0, 40 entries).
// ---------------------------------------------------------------------------
enum class VoiceEvent : int {
    AddAttack = 0, AttackA, AttackB, AttackC, AttackKO, BackAttack, BackDamage, BattleStart,
    Damage, DamageDown, DamageKO, Fire, Guard, Guarded, HpCheck, Intercept, MissDamage,
    NearLose, NearWin, Oyashiro, OyashiroB, Poison, Provoke, Recovery, ReloadNG, ReloadOK,
    Revival, ShotA, ShotB, ShotC, ShotFinal, Spark, SpecialA, SpecialB, Tactics, TagBack,
    TagFront, TagOK, Thank, SpecialC,
};
inline constexpr int kVoiceEventCount = 40;

// The event's own name from the table ("attackKO", "revival", ...), or "" out of range.
const char* voice_event_name(VoiceEvent e);
// True for the four events whose alternatives live in the `<event>_B` directory when the
// character's voice variant is the B persona (FUN_00431e70:72).
bool voice_event_b_dir(VoiceEvent e);

// ---------------------------------------------------------------------------
// What the simulation did.
// ---------------------------------------------------------------------------
enum class CombatEventKind : int {
    MatchStart = 0,  // a fighter's battle-start line
    MeleeSwing,      // a melee swing was armed
    MeleeVoice,      // a melee body's own voice cue (FUN_004223d0/FUN_00422490)
    SoundEffect,     // an action body's SE request (FUN_0042c8b0/FUN_0042c880)
    ShotFired,       // a shot was accepted, or its source move emitted a voice cue
    Hit,             // a landed hit that left the victim standing
    Overkill,        // a landed hit on an already-down body
    Blocked,         // a landed hit the victim was guarding
    GuardStart,      // a fighter raised its guard
    Ko,              // the blow that took a live fighter down
    Respawn,         // a downed fighter came back
    HyperActivate,   // hypermode activation
    Count,
};
inline constexpr int kCombatEventKindCount = static_cast<int>(CombatEventKind::Count);
const char* combat_event_name(CombatEventKind k);

// One event, as the audio layer sees it. `fighter` is the ACTOR for
// MatchStart/MeleeSwing/ShotFired/HyperActivate and the VICTIM for Hit/Overkill/Blocked/Ko/
// Respawn; `source` is the other party where there is one (the attacker, or the victim of a
// KO for the actor's side), else -1.
struct CombatEvent {
    CombatEventKind kind = CombatEventKind::MeleeSwing;
    int      fighter = -1;
    int      source  = -1;
    uint32_t tick    = 0;   // the fixed 64 Hz simulation tick that produced it
    uint8_t  seq     = 0;   // disambiguates several events of one kind in one tick
    // The blow came from a projectile rather than a melee swing. Only the KO pair reads it
    // (see resolve_combat_event); it is not part of the identity, which needs uniqueness
    // per occurrence, not every attribute.
    bool     shot    = false;
    int voice_override = -1;
    int voice_alternative = -1;
    // The `data/se/%03d.wav` id an action body requested (FUN_0042c8b0's positional form
    // and FUN_0042c880's non-positional one both pass it here).
    int se_override = -1;
    // The positional form supplies actor +0x14 to FUN_0065a260; the non-positional
    // form (0042c880) has no source position. This is not part of event identity.
    bool se_positional = false;
    AudioPoint3 se_position{};
    AudioPoint3 se_listener_position{};
    AudioPoint3 se_listener_forward{0.f, 0.f, 1.f};
    bool se_listener_valid = false;
    bool source_voice_audited = false;  // suppress Fire fallback when a bound body is silent
    // Stable identity: tick + kind + the two fighters + the per-tick sequence. Two
    // simulations of the same ticks derive identical ids, and no id repeats within a match,
    // which is what makes replay/rollback reconciliation possible and double-fire impossible.
    uint64_t id() const;
};

// ---------------------------------------------------------------------------
// Frame -> events. ONE derivation, shared by the host and the asset-backed match test, so
// the policy cannot drift from what the release path dispatches.
// ---------------------------------------------------------------------------
// The little the derivation needs from the simulation; gameplay::Match satisfies it through
// the adapter in main.cpp, a test can satisfy it directly.
class CombatEventSource {
public:
    virtual ~CombatEventSource() = default;
    virtual int  fighter_count() const = 0;
    virtual bool alive(int fighter) const = 0;
};

// The frame's own fields, copied so this header does not depend on gameplay/.
struct CombatFrameView {
    bool swing_started[4] = {};
    // The melee body's own cue: the id IS a VoiceEvent index (the vocabulary is the
    // original's 40-name table), the alternative the FUN_00422490 choice where the body
    // draws one. `melee_voice_audited` marks rows whose cue policy is recovered, so the
    // fallback swing voice stands down exactly as the shot voice's audited flag does.
    int melee_voice[4] = {-1, -1, -1, -1};
    int melee_voice_alternative[4] = {-1, -1, -1, -1};
    bool melee_voice_audited[4] = {};
    // The action body's SE request: a data/se id, -1 when silent. The source-position
    // form calls FUN_0042c8b0 and uses fighter +0x14; FUN_0042c880 is non-positional.
    int sound_effect_id[4] = {-1, -1, -1, -1};
    bool sound_effect_positional[4] = {};
    AudioPoint3 sound_effect_position[4] = {};
    AudioPoint3 listener_position{};
    AudioPoint3 listener_forward{0.f, 0.f, 1.f};
    bool listener_valid = false;
    bool shot_fired[4] = {};
    int shot_voice[4] = {-1, -1, -1, -1};
    int shot_voice_alternative[4] = {-1, -1, -1, -1};
    bool shot_voice_audited[4] = {};
    bool hyper_started[4] = {};
    bool guard_started[4] = {};
    bool respawned[4] = {};
    bool blocked[4] = {};
    bool melee_hit[4] = {};
    int  melee_victim[4] = {-1, -1, -1, -1};
    int  overkill_hits[4] = {};
    int  shot_hit_count = 0;
    struct ShotHit {
        int  shooter = -1;
        int  victim  = -1;
        bool blocked = false;
    };
    ShotHit shot_hits[8];
};

// At most one event per fighter per kind, plus the shot contacts.
inline constexpr int kMaxCombatEventsPerTick = 24;

struct CombatEventList {
    CombatEvent events[kMaxCombatEventsPerTick];
    int count = 0;
    void add(const CombatEvent& e) {
        if (count < kMaxCombatEventsPerTick) events[count++] = e;
    }
};

// `match_start` emits the battle-start line for every fighter (the caller passes true on the
// match's first stepped tick only). A KO is emitted at most once per victim per tick: the
// melee contact is resolved first because the melee loop runs before the projectile pool, so
// a shot landing on the body it just downed is the overkill the pool itself reports.
CombatEventList combat_events_for_frame(const CombatEventSource& source,
                                        const CombatFrameView& frame, uint32_t tick,
                                        bool match_start);

// ---------------------------------------------------------------------------
// Event -> cue resolution (pure function; tests pin it with no device).
// ---------------------------------------------------------------------------
struct CombatCue {
    bool       has_voice = false;
    VoiceEvent voice = VoiceEvent::AttackA;
    bool       voice_b_dir = false;  // use the <event>_B directory
    int        se_id = -1;           // -1 = no evidenced SE for this event (see the header)
    bool       se_positional = false;
    AudioPoint3 se_position{};
    AudioPoint3 se_listener_position{};
    AudioPoint3 se_listener_forward{0.f, 0.f, 1.f};
    bool       se_listener_valid = false;
    bool has_se() const { return se_id >= 0; }
};
CombatCue resolve_combat_event(const CombatEvent& e);

// The asset stem for a voice alternative: "<dir>/<event>[_B]/<NNN>". The host resolves it to
// .cnv/.wav like every other sound asset.
std::string voice_asset_stem(const std::string& dir, VoiceEvent e, bool b_dir, int alternative);

// ---------------------------------------------------------------------------
// Dispatch.
// ---------------------------------------------------------------------------
// The host adapts its loaded-sample cache to this. `play` returns the channel it played on
// (or -1 when the sample is missing or the bus is full, which is backpressure, not an error).
class CombatAudioSink {
public:
    struct SpatialRequest {
        AudioPoint3 source{};
        AudioPoint3 listener{};
        AudioPoint3 listenerForward{0.f, 0.f, 1.f};
        float rolloffFactor = 0.0005f;  // FUN_00648ad0/006492f0 battle-stage SetRolloffFactor
        float minDistance = 3.f;        // FUN_006676d0 SetMinDistance, DS3D default init
    };
    virtual ~CombatAudioSink() = default;
    virtual int play(const std::string& asset_stem, SfxBus bus, int channel) = 0;
    virtual int play_spatial(const std::string& asset_stem, int channel,
                             const SpatialRequest& request) {
        (void)request;
        return play(asset_stem, SfxBus::Sfx, channel);
    }
    virtual void stop(int channel) = 0;
    // Stop one whole bus. end_match() uses it so leaving a battle cannot leave a combat cue
    // ringing (issue #15's rule 6); it is also the seam #15 offered to use for its own
    // pause-time SFX stop instead of a 16..31 channel loop.
    virtual void stop_bus(SfxBus bus) = 0;
};

// One voice channel per fighter, exactly like the original's per-player audio object, so two
// fighters never clobber each other's line. Four fighters stay inside the voice bus (1..15).
inline int voice_channel_for(int fighter) { return kVoiceFirst + (fighter < 0 ? 0 : fighter % 4); }

class CombatAudio {
public:
    explicit CombatAudio(CombatAudioSink& sink) : sink_(sink) {}

    // Per-match setup: clears the previous match's channels and history, then takes each
    // fighter's voice directory (data/voice/<name>, or <name>B for the B persona).
    void begin_match(int fighterCount);
    void set_fighter_voice(int fighter, std::string dir, bool b_persona);
    // The probed alternative count for one (fighter, event), as FUN_00431e70 discovers it.
    // 0 means "no shipped alternative": the event stays silent rather than inventing a file.
    void set_voice_alternatives(int fighter, VoiceEvent e, int count);

    // Resolve and play. An event whose id was already dispatched is dropped (duplicates),
    // and while suspended nothing is played (the #15 pause expectation).
    void dispatch(const CombatEvent& e);

    // #15 coordination: suspending stops this layer's voice channels so a pause during a
    // swing/KO leaves nothing playing, and drops events until resume. BGM policy is the
    // pause feature's own; this layer only owns its SFX/voice.
    void suspend();
    void resume();
    bool suspended() const { return suspended_; }

    // "Stop everything this match started": releases every voice channel this layer claimed,
    // stops the SFX bus (a one-shot does not survive a match), and forgets the history, so the
    // next match starts clean. This is the entry point a battle-leave path calls (#15's
    // rule 6); the decoded sample cache stays, because the next match reuses the same stems.
    void end_match();

    // --- observability (tests + the host's evidence log) ---------------------
    struct Stats {
        int dispatched[kCombatEventKindCount] = {};
        int duplicates = 0;        // dropped because the id was already played
        int suspended_drops = 0;   // dropped while suspended
        int voice_plays = 0;
        int voice_missing = 0;     // no alternative registered for that (fighter, event)
        int se_plays = 0;
        int se_missing = 0;        // the sink refused (no sample / bus full)
    };
    const Stats& stats() const { return stats_; }
    int  claimed_channels() const;      // channels this layer currently holds
    int  claimed_voice(int fighter) const;
    uint64_t last_event_id() const { return last_event_id_; }
    const std::string& last_voice_stem() const { return last_voice_stem_; }
    int  last_se_id() const { return last_se_id_; }
    // Clears the duplicate history only. A future rollback resimulates ticks whose events
    // were already dispatched; clearing lets them play again while keeping the channels.
    void reset_history();

private:
    struct FighterVoice {
        std::string dir;
        bool b_persona = false;
        int  alternatives[kVoiceEventCount] = {};  // probed counts, 0 = silent
        int  channel = -1;                          // -1 = nothing claimed
    };
    static constexpr int kHistorySize = 64;

    CombatAudioSink& sink_;
    std::array<FighterVoice, 4> voices_{};
    int      fighter_count_ = 0;
    bool     suspended_ = false;
    Stats    stats_{};
    uint64_t history_[kHistorySize] = {};
    int      history_count_ = 0;   // valid entries (grows to kHistorySize)
    int      history_next_ = 0;    // ring cursor
    uint64_t last_event_id_ = 0;
    std::string last_voice_stem_;
    int      last_se_id_ = -1;

    bool seen(uint64_t id) const;
    void remember(uint64_t id);
    void play_voice(const CombatEvent& e, const CombatCue& cue);
    void play_se(const CombatCue& cue);
};

}  // namespace fnd::audio
