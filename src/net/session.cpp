#include "net/session.h"

#include <algorithm>
#include <cstring>
#include <gekkonet.h>
#include <stdexcept>

namespace net {

namespace {

// One slot's input on the wire: small, and the same bytes on every machine.
struct WireInput {
    std::int8_t x, z;
    std::uint8_t buttons;
};
static_assert(sizeof(WireInput) == 3);

WireInput to_wire(const sim::SlotInput& input) {
    return {static_cast<std::int8_t>(input.x), static_cast<std::int8_t>(input.z), static_cast<std::uint8_t>(input.buttons)};
}

sim::Inputs from_wire(const unsigned char* bytes) {
    sim::Inputs inputs{};
    for (size_t i = 0; i < inputs.size(); ++i) {
        WireInput wire;
        std::memcpy(&wire, bytes + i * sizeof wire, sizeof wire);
        inputs[i] = {wire.x, wire.z, wire.buttons};
    }
    return inputs;
}

void merge(game::BattleFrame& into, game::BattleFrame&& frame) {
    const auto append = [](auto& to, auto& from) { to.insert(to.end(), from.begin(), from.end()); };
    append(into.effectSpawns, frame.effectSpawns);
    append(into.soundCues, frame.soundCues);
    append(into.voiceCues, frame.voiceCues);
    frame.effectSpawns = std::move(into.effectSpawns);
    frame.soundCues = std::move(into.soundCues);
    frame.voiceCues = std::move(into.voiceCues);
    frame.roundOver = frame.roundOver || into.roundOver;
    into = std::move(frame);
}

}  // namespace

Session::Session(sim::CoreBattle& battle) : m_battle(battle) {}

Session::~Session() {
    if (m_session) gekko_destroy(&m_session);
}

std::unique_ptr<Session> Session::stress(sim::CoreBattle& battle, unsigned distance) {
    if (distance == 0 || distance + 2 > kSlots) throw std::invalid_argument("net: stress distance");
    std::unique_ptr<Session> session(new Session(battle));
    if (!gekko_create(&session->m_session, GekkoStressSession)) throw std::runtime_error("net: no session");
    GekkoConfig config{};
    config.num_players = 4;
    config.input_size = sizeof(WireInput);
    config.state_size = sizeof(std::uint32_t);
    config.desync_detection = true;
    config.check_distance = distance;
    gekko_start(session->m_session, &config);
    for (int i = 0; i < 4; ++i) gekko_add_actor(session->m_session, GekkoLocalPlayer, nullptr);
    return session;
}

game::BattleFrame Session::run(const sim::Inputs& inputs) {
    const auto start = std::chrono::steady_clock::now();
    for (int i = 0; i < 4; ++i) {
        WireInput wire = to_wire(inputs[static_cast<size_t>(i)]);
        gekko_add_local_input(m_session, i, &wire);
    }

    game::BattleFrame frame;
    int count = 0;
    GekkoGameEvent** events = gekko_update_session(m_session, &count);
    for (int i = 0; i < count; ++i) {
        const GekkoGameEvent& event = *events[i];
        if (event.type == GekkoAdvanceEvent) {
            if (event.data.adv.rolling_back) ++m_stats.replayedTicks;
            merge(frame, m_battle.advance(from_wire(event.data.adv.inputs)));
        } else if (event.type == GekkoSaveEvent) {
            const auto slot = static_cast<std::uint32_t>(event.data.save.frame + 1) % kSlots;
            m_battle.save_state(m_slots[slot]);
            const std::uint64_t hash = m_battle.state_hash();
            *event.data.save.checksum = static_cast<unsigned>(hash ^ (hash >> 32)) + (m_corruptNextHash ? 1u : 0u);
            m_corruptNextHash = false;
            *event.data.save.state_len = sizeof slot;
            std::memcpy(event.data.save.state, &slot, sizeof slot);
        } else if (event.type == GekkoLoadEvent) {
            std::uint32_t slot;
            std::memcpy(&slot, event.data.load.state, sizeof slot);
            m_battle.load_state(m_slots[slot]);
            ++m_stats.rollbacks;
        }
    }

    int sessionCount = 0;
    GekkoSessionEvent** sessionEvents = gekko_session_events(m_session, &sessionCount);
    for (int i = 0; i < sessionCount; ++i) {
        if (sessionEvents[i]->type != GekkoDesyncDetected) continue;
        const int desyncFrame = sessionEvents[i]->data.desynced.frame;
        if (m_stats.desyncs++ == 0) m_stats.firstDesyncFrame = desyncFrame;
    }

    const auto spent = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start);
    m_stats.worstUpdate = std::max(m_stats.worstUpdate, spent);
    m_stats.totalUpdate += spent;
    ++m_stats.updates;
    return frame;
}

}  // namespace net
