#include "audio/combat_audio.h"
#include "combo_fixture.h"
#include "gameplay/fixed_step.h"
#include "gameplay/match.h"
#include "gameplay/move_behavior.h"

#include <array>
#include <cstdio>
#include <string>

namespace {

using fnd::audio::CombatEventKind;
using fnd::audio::CombatEventList;
using fnd::audio::CombatEventSource;
using fnd::audio::CombatFrameView;
using fnd::audio::VoiceEvent;

struct ComboId { int character; int slot; const char* label; };

constexpr ComboId kBoundPrograms[] = {
    {0,0,"Rena+0"}, {0,1,"Rena+1"}, {0,2,"Rena+2"},
    {1,0,"Mion+0"}, {1,1,"Mion+1"}, {1,2,"Mion+2"},
    {2,0,"Keiichi+0"}, {2,1,"Keiichi+1"}, {2,2,"Keiichi+2"},
    {3,0,"Satoko+0"}, {3,1,"Satoko+1"}, {3,2,"Satoko+2"},
    {4,0,"Rika+0"}, {4,1,"Rika+1"}, {4,2,"Rika+2"},
    {6,2,"Tomitake+2"}, {7,0,"Takano+0"}, {10,1,"Irie+1"},
    {11,2,"Chie+2"}, {12,1,"Kasai+1"}, {15,0,"Natsumi+0"},
};

int failures = 0;

void check(bool condition, const char* what) {
    if (condition) return;
    std::fprintf(stderr, "FAIL: %s\n", what);
    ++failures;
}

class MatchSource final : public CombatEventSource {
public:
    explicit MatchSource(const gameplay::Match& match) : match_(match) {}
    int fighter_count() const override { return match_.config().fighterCount; }
    bool alive(int fighter) const override { return match_.fighter(fighter).is_alive(); }
private:
    const gameplay::Match& match_;
};

CombatFrameView voiceView(const gameplay::MatchFrame& frame) {
    CombatFrameView view;
    for (int i = 0; i < gameplay::kMatchFighterCount; ++i) {
        view.shot_fired[i] = frame.shotFired[i];
        view.shot_voice[i] = frame.shotVoice[i];
        view.shot_voice_alternative[i] = frame.shotVoiceAlternative[i];
        view.shot_voice_audited[i] = frame.sourceShotVoiceAudited[i];
    }
    return view;
}

bool hasEvent(const CombatEventList& list, CombatEventKind kind, int fighter) {
    for (int i = 0; i < list.count; ++i)
        if (list.events[i].kind == kind && list.events[i].fighter == fighter) return true;
    return false;
}

void testBoundProgramCensus() {
    int boundStates = 0;
    int voiceRules = 0;
    bool sawShotA = false, sawShotB = false, sawShotC = false;
    bool sawShotFinal = false, sawSpecialA = false;
    for (const ComboId comboId : kBoundPrograms) {
        test::Combo combo;
        std::string error;
        if (!combo.load(comboId.character, comboId.slot, error)) {
            std::fprintf(stderr, "%s failed to load: %s\n", comboId.label, error.c_str());
            ++failures;
            continue;
        }
        check(combo.moves.weapon_id() == gameplay::kWeaponIds[comboId.character][comboId.slot],
              "voice audit binds the NN.dat character and its matching item weapon");
        const gameplay::MoveProgram* program = gameplay::move_program(&combo.moves);
        check(program != nullptr, "every censused combo has an active move program");
        if (!program) continue;
        for (const auto& tier : program->shot) {
            for (int move : tier) {
                if (move < 0) {
                    check(!gameplay::shot_voice_policy_audited(program, move),
                          "unbound shot slots stay outside the source voice policy");
                    continue;
                }
                ++boundStates;
                check(gameplay::shot_voice_policy_audited(program, move),
                      "every bound shot state has an audited voice or silent policy");
            }
        }
        for (size_t i = 0; i < program->count; ++i) {
            const gameplay::MoveRule& rule = program->rules[i];
            if (rule.operation != gameplay::MoveOp::Voice) continue;
            ++voiceRules;
            const auto validEvent = [](int event) {
                return event == -1 || event == int(VoiceEvent::ShotA) ||
                       event == int(VoiceEvent::ShotB) || event == int(VoiceEvent::ShotC) ||
                       event == int(VoiceEvent::ShotFinal) || event == int(VoiceEvent::SpecialA);
            };
            check(validEvent(rule.voice.event) && validEvent(rule.voice.finalEvent),
                  "move voice specs use recovered shooting event ids");
            sawShotA |= rule.voice.event == int(VoiceEvent::ShotA) ||
                        rule.voice.finalEvent == int(VoiceEvent::ShotA);
            sawShotB |= rule.voice.event == int(VoiceEvent::ShotB) ||
                        rule.voice.finalEvent == int(VoiceEvent::ShotB);
            sawShotC |= rule.voice.event == int(VoiceEvent::ShotC) ||
                        rule.voice.finalEvent == int(VoiceEvent::ShotC);
            sawShotFinal |= rule.voice.event == int(VoiceEvent::ShotFinal) ||
                            rule.voice.finalEvent == int(VoiceEvent::ShotFinal);
            sawSpecialA |= rule.voice.event == int(VoiceEvent::SpecialA);
            if (rule.voice.alternativeFirst >= 0 || rule.voice.alternativeSecond >= 0) {
                check(rule.voice.event == int(VoiceEvent::SpecialA) &&
                          rule.voice.alternativeFirst == 1 &&
                          rule.voice.alternativeSecond == 2 &&
                          rule.voice.alternativeSecondPercent == 51,
                      "Rena+0 SpecialA keeps FUN_00422490's alternatives and 51-percent split");
            }
        }
    }
    check(sizeof(kBoundPrograms) / sizeof(kBoundPrograms[0]) == 21,
          "current move-program boundary is 21 bound character+weapon combos");
    check(boundStates >= 60, "census sees every mapped tap and first-charge state");
    check(voiceRules >= 40, "source cue rows cover the registered program set");
    check(sawShotA && sawShotB && sawShotC && sawShotFinal && sawSpecialA,
          "bound programs cover all source-backed event families used by this slice");
}

void testRena1CuePrecedesRequest() {
    test::Combo rena1, rena0;
    std::string error;
    if (!rena1.load(0, 1, error) || !rena0.load(0, 0, error)) {
        std::fprintf(stderr, "Rena+1/Rena+0 fixture failed to load: %s\n", error.c_str());
        ++failures;
        return;
    }

    gameplay::MatchConfig config;
    config.fighterCount = 2;
    config.side[0] = 0;
    config.side[1] = 1;
    config.spawn[0] = {-500.f, 0.f, 0.f};
    config.spawn[1] = {500.f, 0.f, 0.f};
    config.weapon[0] = &rena1.weapon;
    config.weapon[1] = &rena0.weapon;
    config.moves[0] = &rena1.moves;
    config.moves[1] = &rena0.moves;
    const xm::Model* models[gameplay::kMatchFighterCount] = {
        &rena1.model, &rena0.model, nullptr, nullptr};
    xm::Controller* animations[gameplay::kMatchFighterCount] = {
        rena1.controller(), rena0.controller(), nullptr, nullptr};
    gameplay::Match match;
    match.reset(config, models, animations, nullptr, nullptr);

    fnd::input::PlayerState p1, p2;
    const fnd::input::PlayerState* inputs[gameplay::kMatchFighterCount] = {
        &p1, &p2, nullptr, nullptr};
    auto step = [&]() {
        fnd::input::compute_edges(p1);
        fnd::input::compute_edges(p2);
        return match.step(inputs, gameplay::FixedStep::seconds);
    };
    for (int i = 0; i < 70; ++i) (void)step();
    p1.down[fnd::input::Shoot] = true;
    (void)step();
    p1.down[fnd::input::Shoot] = false;
    (void)step();
    check(match.fighter(0).shot_move_id() == 400,
          "Rena+1 starts its bound ground state400 with the equipped item");

    MatchSource source(match);
    int cueTick = -1, shotTick = -1;
    bool cueWasShotC = false, shotWasAuditedSilent = false;
    uint32_t audioTick = 1;
    for (int update = 0; update < 24; ++update, ++audioTick) {
        const int sourceTick = match.fighter(0).phase_elapsed();
        const gameplay::MatchFrame frame = step();
        const CombatEventList events = combat_events_for_frame(source, voiceView(frame),
                                                               audioTick, false);
        if (frame.shotVoice[0] >= 0) {
            cueTick = sourceTick;
            check(frame.sourceShotVoiceAudited[0],
                  "Rena+1 voice-only cue belongs to an audited move state");
            for (int i = 0; i < events.count; ++i) {
                const auto& event = events.events[i];
                if (event.kind != CombatEventKind::ShotFired || event.fighter != 0) continue;
                const auto cue = fnd::audio::resolve_combat_event(event);
                cueWasShotC = cue.has_voice && cue.voice == VoiceEvent::ShotC;
            }
        }
        if (frame.shotFired[0]) {
            shotTick = sourceTick;
            check(frame.shotVoice[0] < 0 && frame.sourceShotVoiceAudited[0],
                  "Rena+1 accepted shot carries the source-audited silence marker");
            for (int i = 0; i < events.count; ++i) {
                const auto& event = events.events[i];
                if (event.kind != CombatEventKind::ShotFired || event.fighter != 0) continue;
                const auto cue = fnd::audio::resolve_combat_event(event);
                shotWasAuditedSilent = event.source_voice_audited && !cue.has_voice;
            }
        }
    }
    check(cueTick == 15, "FUN_00448220 calls Rena+1 ShotC at state400 tick15");
    check(shotTick == 18, "FUN_00448220's bound Rena+1 request occurs at tick18");
    check(cueTick < shotTick && cueWasShotC,
          "the tick15 ShotC is the only voice line before the tick18 request");
    check(shotWasAuditedSilent,
          "the later accepted request does not invent a second generic Fire line");
}

}  // namespace

int main() {
    const std::string install = test::gameInstall();
    if (install.empty() || !fnd::assets::assetSource().openInstall(install)) {
        std::puts("combat_shot_voice_test: no install, skipped");
        return 77;
    }
    testBoundProgramCensus();
    testRena1CuePrecedesRequest();
    if (failures) {
        std::fprintf(stderr, "combat_shot_voice_test: %d failure(s)\n", failures);
        return 1;
    }
    std::puts("combat_shot_voice_test: 21 bound combos, source voice timing and silence passed");
    return 0;
}
