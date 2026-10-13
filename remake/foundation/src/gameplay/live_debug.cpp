#include "gameplay/live_debug.h"
#include <sstream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <cerrno>
#if defined(__linux__)
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#endif

namespace gameplay {
namespace {
std::string jsonQuote(const std::string& value) {
    std::ostringstream s; s << '"';
    for (unsigned char c : value) {
        if (c == '"' || c == '\\') s << '\\' << c;
        else if (c < 32 || c >= 127) s << "\\u00" << std::hex << std::setw(2) << std::setfill('0') << int(c) << std::dec;
        else s << c;
    }
    s << '"'; return s.str();
}
const char* names[] = {"Forward", "Back", "Left", "Right", "Attack", "Guard", "Shoot", "Jump", "Special", "Tactics", "Lock", "Pause"};
std::string actions(const bool* flags) {
    std::string s = "["; bool comma = false;
    for (int a = 0; a < fnd::input::ActionCount; ++a) if (flags[a]) {
        if (comma) s += ','; comma = true; s += jsonQuote(names[a]);
    }
    return s + ']';
}
void vector(std::ostream& s, const glm::vec3& v) { s << '[' << v.x << ',' << v.y << ',' << v.z << ']'; }
}
LiveDebug::~LiveDebug() {
#if defined(__linux__)
    disconnect();
    if (m_socket >= 0) { close(m_socket); unlink((m_directory + "/control.sock").c_str()); }
    if (!m_directory.empty()) { unlink((m_directory + "/session").c_str()); rmdir(m_directory.c_str()); }
#endif
}
bool LiveDebug::start(std::string& error) {
#if defined(__linux__)
    char path[] = "/tmp/daybreak-debug-XXXXXX";
    char* dir = mkdtemp(path);
    if (!dir) { error = "cannot create private debug directory"; return false; }
    m_directory = dir;
    unsigned char random[32];
    const int fd = open("/dev/urandom", O_RDONLY | O_CLOEXEC);
    const auto n = fd < 0 ? -1 : read(fd, random, sizeof(random));
    if (fd >= 0) close(fd);
    if (n != sizeof(random)) { error = "cannot create debug session credential"; return false; }
    std::ostringstream token;
    for (auto c : random) token << std::hex << std::setw(2) << std::setfill('0') << int(c);
    m_token = token.str();
    m_socket = socket(AF_UNIX, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, 0);
    sockaddr_un address{}; address.sun_family = AF_UNIX;
    const std::string socketPath = m_directory + "/control.sock";
    std::copy(socketPath.begin(), socketPath.end(), address.sun_path);
    if (m_socket < 0 || bind(m_socket, reinterpret_cast<sockaddr*>(&address), sizeof(address)) ||
        chmod(socketPath.c_str(), 0600) || listen(m_socket, 1)) {
        error = "cannot bind private debug socket"; return false;
    }
    const int manifest = open((m_directory + "/session").c_str(), O_WRONLY | O_CREAT | O_EXCL | O_CLOEXEC, 0600);
    if (manifest < 0) { error = "cannot write debug session identity"; return false; }
    const std::string text = std::to_string(getpid()) + "\n" + m_token + "\n";
    const bool ok = write(manifest, text.data(), text.size()) == static_cast<ssize_t>(text.size());
    close(manifest);
    if (!ok) { error = "cannot write debug session identity"; return false; }
    return true;
#else
    error = "live debug transport is available only in explicitly enabled Linux development launches";
    return false;
#endif
}
void LiveDebug::disconnect() {
#if defined(__linux__)
    if (m_client >= 0) close(m_client);
#endif
    m_client = -1; m_authenticated = false; m_buffer.clear();
    m_paused = true; m_budget = 0; m_pending = false;
    m_events.clear(); m_breaks.clear();
    for (auto& input : m_inputs) input = {};
}
void LiveDebug::reply(const std::string& text) {
#if defined(__linux__)
    const std::string line = text + '\n';
    // A stalled client cannot stall presentation or retain control. Bounded
    // responses fit a local socket buffer; a partial send fails closed.
    if (m_client >= 0 && send(m_client, line.data(), line.size(), MSG_NOSIGNAL | MSG_DONTWAIT) != static_cast<ssize_t>(line.size())) disconnect();
#endif
}
void LiveDebug::poll(uint64_t tick, uint64_t renders, const Match& match) {
#if defined(__linux__)
    if (!enabled()) return;
    if (m_client < 0) {
        const int fd = accept4(m_socket, nullptr, nullptr, SOCK_NONBLOCK | SOCK_CLOEXEC);
        if (fd >= 0) {
            ucred peer{}; socklen_t size = sizeof(peer);
            if (getsockopt(fd, SOL_SOCKET, SO_PEERCRED, &peer, &size) || peer.uid != getuid()) close(fd);
            else m_client = fd;
        }
    }
    if (m_client < 0) return;
    char bytes[4096];
    for (int reads = 0; reads < 8; ++reads) {
        const auto n = recv(m_client, bytes, sizeof(bytes), MSG_DONTWAIT);
        if (n == 0) { disconnect(); return; }
        if (n < 0) { if (errno != EAGAIN && errno != EWOULDBLOCK) disconnect(); break; }
        m_buffer.append(bytes, static_cast<size_t>(n));
        if (m_buffer.size() > 16384) { disconnect(); return; }
        if (m_buffer.find('\n') != std::string::npos) break;
    }
    for (int commands = 0; commands < 32 && m_client >= 0; ++commands) {
        const auto end = m_buffer.find('\n'); if (end == std::string::npos) break;
        const std::string line = m_buffer.substr(0, end); m_buffer.erase(0, end + 1);
        command(line, tick, renders, match);
    }
#else
    (void)tick; (void)renders; (void)match;
#endif
}
void LiveDebug::command(const std::string& line, uint64_t tick, uint64_t renders, const Match& match) {
    std::istringstream s(line); std::string op, extra; s >> op;
    auto error = [&]() { reply("{\"version\":1,\"error\":\"invalid command or busy\"}"); };
    auto ack = [&]() { reply("{\"version\":1,\"ok\":true,\"effect_tick\":" + std::to_string(tick) + "}"); };
    if (!m_authenticated) {
        std::string token; s >> token;
        if (op != "HELLO" || token != m_token || s >> extra) { disconnect(); return; }
        m_authenticated = true; ack(); return;
    }
    if (op == "STATUS" && !(s >> extra)) { reply(snapshot(tick, renders, match)); return; }
    if (op == "PAUSE" && !(s >> extra)) {
        m_paused = true; m_budget = 0; m_pending = true; m_effectTick = tick; m_reason = "pause"; return;
    }
    if (m_pending || m_budget > 0) { error(); return; }
    if (op == "RESUME" && !(s >> extra)) { m_paused = false; ack(); return; }
    if (op == "STATUS" || op == "HELLO") { error(); return; }
    if (op == "STEP") {
        int n = 0;
        if (!(s >> n) || s >> extra || !m_paused || n < 1 || n > 100000) { error(); return; }
        m_budget = static_cast<uint64_t>(n); m_pending = true; m_effectTick = tick + 1; m_reason = "step"; return;
    }
    if (op == "INPUT") {
        int fighter = -1, span = 0; std::string list;
        if (!(s >> fighter >> span >> list) || s >> extra || !m_paused || fighter < 0 || fighter >= match.config().fighterCount || span < 1 || span > 100000 || m_events.size() >= 1024) { error(); return; }
        uint32_t mask = 0;
        if (list != "-") {
            std::istringstream a(list); std::string name;
            while (std::getline(a, name, ',')) {
                int i = 0; for (; i < fnd::input::ActionCount; ++i) if (name == names[i]) break;
                if (i == fnd::input::ActionCount || i == fnd::input::Pause) { error(); return; }
                mask |= 1u << i;
            }
        }
        uint64_t first = tick + 1;
        for (const auto& event : m_events) if (event.fighter == fighter) first = std::max(first, event.tick);
        m_events.push_back({first, fighter, mask}); m_events.push_back({first + static_cast<uint64_t>(span), fighter, 0});
        std::stable_sort(m_events.begin(), m_events.end(), [](const Event& a, const Event& b) { return a.tick < b.tick; });
        reply("{\"version\":1,\"ok\":true,\"first_tick\":" + std::to_string(first) + ",\"release_tick\":" + std::to_string(first + span) + "}"); return;
    }
    if (op == "BREAK") {
        Break b;
        if (!(s >> b.kind >> b.fighter >> b.value >> b.character >> b.weapon) || s >> extra || b.fighter < 0 || b.fighter >= match.config().fighterCount || m_breaks.size() >= 64 ||
            (b.kind != "state" && b.kind != "move" && b.kind != "bind" && b.kind != "volume" && b.kind != "contact")) { error(); return; }
        m_breaks.push_back(b); ack(); return;
    }
    if (op == "CLEAR" && !(s >> extra)) {
        m_breaks.clear(); m_events.clear();
        for (auto& input : m_inputs) for (bool& held : input.down) held = false;
        ack(); return;
    }
    if (op == "STOP" && !(s >> extra)) { m_paused = true; m_budget = 0; m_stop = true; ack(); return; }
    if (op == "DETACH" && !(s >> extra)) { ack(); disconnect(); return; }
    error();
}
void LiveDebug::inputs(uint64_t tick, const fnd::input::PlayerState* out[4]) {
    while (!m_events.empty() && m_events.front().tick <= tick) {
        const Event e = m_events.front(); m_events.pop_front();
        for (int a = 0; a < fnd::input::ActionCount; ++a) m_inputs[e.fighter].down[a] = (e.mask & (1u << a)) != 0;
    }
    for (int i = 0; i < 4; ++i) { fnd::input::compute_edges(m_inputs[i]); out[i] = &m_inputs[i]; }
}
void LiveDebug::after_tick(uint64_t tick, const Match& match, const MatchFrame& frame) {
    m_frame = frame;
    for (const auto& b : m_breaks) {
        const auto& f = match.fighter(b.fighter); const auto* moves = f.moves();
        if ((b.character >= 0 && (!moves || moves->character_index() != b.character)) || (b.weapon >= 0 && (!moves || moves->weapon_id() != b.weapon))) continue;
        const bool changedState = m_state[b.fighter] != int(f.state());
        const bool changedMove = m_move[b.fighter] != f.bound_move_id();
        const bool changedBind = changedMove || m_set[b.fighter] != f.anim_set_index() || m_phase[b.fighter] != f.move_phase();
        const bool hit = (b.kind == "state" && changedState && (b.value < 0 || b.value == int(f.state()))) ||
            (b.kind == "move" && changedMove && (b.value < 0 || b.value == f.bound_move_id())) ||
            (b.kind == "bind" && changedBind && (b.value < 0 || b.value == f.anim_set_index())) ||
            (b.kind == "volume" && f.hitbox_debug().attacking && f.current_move_record() && f.current_move_record()->hitRadius != 0) ||
            (b.kind == "contact" && (frame.meleeHit[b.fighter] ||
                std::any_of(frame.shotHits, frame.shotHits + frame.shotHitCount,
                    [&](const MatchFrame::ShotHit& hit) { return hit.shooter == b.fighter || hit.victim == b.fighter; })));
        if (hit) { m_paused = true; m_budget = 0; m_pending = true; m_effectTick = tick; m_reason = b.kind; break; }
    }
    for (int i = 0; i < match.config().fighterCount; ++i) {
        const auto& f = match.fighter(i); m_state[i] = int(f.state()); m_move[i] = f.bound_move_id(); m_set[i] = f.anim_set_index(); m_phase[i] = f.move_phase();
    }
    if (m_budget) --m_budget;
}
void LiveDebug::presented(uint64_t tick, uint64_t renders, const Match& match) {
    if (m_pending && m_budget == 0) {
        m_pending = false;
        std::string state = snapshot(tick, renders, match);
        state.pop_back(); state += ",\"reason\":" + jsonQuote(m_reason) + ",\"effect_tick\":" + std::to_string(m_effectTick) + ",\"screenshot\":" + jsonQuote(evidence_path(tick)) + ",\"image_source\":\"same-renderer-offscreen\"}";
        reply(state);
    }
}
std::string LiveDebug::snapshot(uint64_t tick, uint64_t renders, const Match& match) const {
    std::ostringstream s; s << std::boolalpha << std::setprecision(9);
    s << "{\"version\":1,\"session\":" << jsonQuote(m_token) << ",\"tick\":" << tick << ",\"renders\":" << renders << ",\"paused\":" << m_paused << ",\"fighters\":[";
    for (int i = 0; i < match.config().fighterCount; ++i) {
        if (i) s << ',';
        const auto& f = match.fighter(i); const auto* moves = f.moves();
        s << "{\"index\":" << i << ",\"character\":" << (moves ? moves->character_index() : -1) << ",\"weapon\":" << (f.weapon() ? f.weapon()->id : -1) << ",\"position\":";
        vector(s, f.position());
        s << ",\"yaw\":" << f.facing_yaw() << ",\"airborne\":" << f.airborne() << ",\"grounded\":" << !f.airborne() << ",\"state\":" << int(f.state())
          << ",\"attack_move\":" << f.attack_move_id() << ",\"bound_move\":" << f.bound_move_id() << ",\"dash_move\":" << f.dash_move_id() << ",\"air_dash\":" << f.air_dash_context()
          << ",\"phase\":" << f.move_phase() << ",\"elapsed\":" << f.phase_elapsed() << ",\"set\":" << f.anim_set_index() << ",\"set_name\":" << jsonQuote(f.anim_set_name())
          << ",\"tag\":" << (moves && moves->find(f.bound_move_id()) ? moves->find(f.bound_move_id())->phase_set_index(f.move_phase()) : -1)
          << ",\"fallback\":" << f.anim_fallback() << ",\"held\":" << actions(m_inputs[i].down) << ",\"pressed\":" << actions(m_inputs[i].just_pressed) << ",\"released\":" << actions(m_inputs[i].just_released)
          << ",\"target\":" << match.locked_target(i) << ",\"contact\":" << m_frame.meleeHit[i] << ",\"victim\":" << m_frame.meleeVictim[i];
        s << ",\"collision_occurred\":" << (m_frame.meleeHit[i] ||
            std::any_of(m_frame.shotHits, m_frame.shotHits + m_frame.shotHitCount,
                [&](const MatchFrame::ShotHit& hit) { return hit.shooter == i || hit.victim == i; }));
        s << ",\"shot_contacts\":[";
        bool comma = false;
        for (int j = 0; j < m_frame.shotHitCount; ++j) {
            const auto& hit = m_frame.shotHits[j];
            if (hit.shooter != i && hit.victim != i) continue;
            if (comma) s << ','; comma = true;
            s << "{\"shooter\":" << hit.shooter << ",\"victim\":" << hit.victim << ",\"blocked\":" << hit.blocked << ",\"point\":";
            vector(s, hit.point); s << '}';
        }
        s << ']';
        const auto volume = f.hitbox_debug();
        s << ",\"volume\":{\"active\":" << volume.attacking << ",\"radius\":" << volume.attackRadius << ",\"capsule\":" << volume.capsule << ",\"center\":"; vector(s, volume.attackCenter); s << ",\"end\":"; vector(s, volume.attackEnd); s << '}';
        const auto* r = f.current_move_record(); s << ",\"record\":";
        if (!r) s << "null";
        else {
            s << "{\"bone\":" << jsonQuote(r->boneName) << ",\"active_frame\":" << r->activeFrame << ",\"radius\":" << r->hitRadius << ",\"state_flags\":" << r->stateFlags << ",\"attack_flags\":" << r->attackFlags << ",\"shape\":" << r->collisionShape << ",\"anchor\":[" << r->anchor[0] << ',' << r->anchor[1] << ',' << r->anchor[2] << "],\"end_anchor\":[" << r->endAnchor[0] << ',' << r->endAnchor[1] << ',' << r->endAnchor[2] << "],\"combat\":[";
            for (size_t j = 0; j < r->combat.size(); ++j) { if (j) s << ','; s << r->combat[j]; } s << "]}";
        }
        s << '}';
    }
    s << "]}"; return s.str();
}
}
