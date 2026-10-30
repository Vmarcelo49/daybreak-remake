// Scene 5, the story team select: FUN_004057c0 ctor, 0x406310 update, FUN_00406850 per-player
// panel, FUN_004072b0 draw. Rects and positions are the original's; the sprite each draw uses was
// read from the calls' receivers, which the decompiler drops.
#include "frontend/screen_story.h"

#include <algorithm>
#include <array>
#include <cstdio>
#include <string>
#include <utility>

#include "frontend/frontend_launch.h"
#include "frontend/frontend_state.h"
#include "frontend/screen_select.h"
#include "hud/hud_atlas.h"

namespace ui {
namespace {

// Tables at 0x6b70f0..0x6b71bf, indexed by the team cursor.
constexpr int kTeams = 10, kChibis = 14;
constexpr std::array<std::array<int, 2>, kTeams> kPairs{{{2, 0}, {0, 4}, {4, 3}, {3, 5}, {1, 5},
                                                         {2, 1}, {7, 6}, {8, 9}, {10, 11}, {13, 12}}};
constexpr std::array<int, kTeams> kTeamFile{0, 9, 2, 8, 1, 7, 3, 4, 5, 6};
constexpr std::array<int, kTeams> kLeft{5, 0, 1, 4, 5, 5, 7, 6, 9, 9};
constexpr std::array<int, kTeams> kRight{1, 2, 2, 2, 3, 4, 7, 7, 8, 8};
constexpr std::array<int, kTeams> kUp{1, 9, 1, 2, 5, 0, 4, 6, 7, 8};
constexpr std::array<int, kTeams> kDown{5, 2, 3, 4, 6, 4, 7, 8, 9, 1};
constexpr std::array<int, kChibis> kChibiCharacter{2, 0, 4, 3, 5, 1, 7, 6, 8, 9, 10, 11, 12, 13};
constexpr std::array<float, kChibis> kChibiX{0, 1, 3, 3, 2, 0, 0, 1, 2, 3, 2, 3, 2, 1};
constexpr std::array<float, kChibis> kChibiY{0, -1, -1, 1, 2, 2, 4, 5, 6, 7, 8, 9, 10, 11};

enum Panel { kChoosing = 0, kController = 1, kWeapon = 3, kHyper = 4, kStamp = 8 };
enum Sheet { kP00, kP01, kP02, kP03, kSheets };

struct Sprite {
    int sheet;
    UiRect src;
    float pivotX, pivotY;
};
// The receivers at +0x2cd0, +0x16f0, +0x1bf0, +0x1970, +0x1a10, +0x29b0, +0x2a50, +0x2d70, +0x1c90
// and +0x1830.
constexpr Sprite kCursor{kP00, {0, 0x180, 0x80, 0x80}, 0x40, 0x40};
constexpr Sprite kButtons{kP01, {0x100, 0, 0x80, 0x40}, 0x40, 0x20};
constexpr Sprite kHeading{kP00, {0, 0, 0x140, 0x20}, 0xa0, 0x10};
constexpr Sprite kArrows{kP00, {0x180, 0xc0, 0x40, 0x80}, 0x20, 0x40};
constexpr Sprite kStampSprite{kP01, {0, 0x80, 0x100, 0x40}, 0x80, 0x20};
constexpr Sprite kPlayerTag{kP02, {0x100, 0x80, 0x40, 0x40}, 0x20, 0x20};
constexpr Sprite kControllerName{kP02, {0, 0x140, 0x100, 0x40}, 0x80, 0x20};
constexpr Sprite kHyperName{kP00, {0x140, 0, 0xc0, 0x40}, 0x60, 0x20};
constexpr Sprite kCharacterName{kP03, {0, 0, 0x100, 0x40}, 0x80, 0x20};
constexpr Sprite kHyperText{kP02, {0, 0, 0x100, 0x40}, 0x80, 0x20};

class StoryTeamScreen final : public Screen {
public:
    StoryTeamScreen(SpriteRenderer& batch, FrontendState& state, std::string& error)
        : batch_(batch), state_(state), error_(error) {
        load("data/teamselect/bg00", background_);
        load("data/select/p00", sheets_[kP00]);
        load("data/select/P01", sheets_[kP01]);
        load("data/select/P02", sheets_[kP02]);
        load("data/select/p03", sheets_[kP03]);
        load("data/select/s1p", frames_[0]);
        load("data/select/s2p", frames_[1]);
        load("data/teamselect/p00", labels_[0]);
        load("data/teamselect/p01", labels_[1]);
        char path[48];
        for (int i = 0; i < kChibis; ++i) {
            std::snprintf(path, sizeof path, "data/select/i%02d", kChibiCharacter[i]);
            load(path, chibis_[i]);
        }
        for (int i = 0; i < kTeams; ++i) {
            std::snprintf(path, sizeof path, "data/teamselect/t%02d", i);
            load(path, art_[i]);
        }
        for (auto& v : cursor_) v = -1;
        state_.story.active = true;
    }

    // The stack keeps calling update through the fade out, so a decision to leave is final.
    ScreenId update(const ScreenInput& in) override {
        if (leaving_ != ScreenId::StoryTeam) return leaving_;
        return leaving_ = step(in);
    }

    void draw(SpriteRenderer& batch) const override {
        for (int i = 0; i < 2; ++i)
            if (stage_ > 0 && faces_[i] >= 0)
                batch.pushSprite(faces_[i], {0, 0, 256, 256}, 128, 256, 600, 300.f + 300.f * i);
        if (background_ >= 0) batch.pushTextured(background_, {0, 0, 800, 600}, uv(background_, {0, 0, 800, 600}), {});

        if (stage_ > 0)
            for (int p = 0; p < 2; ++p)
                if (cursor_[p] >= 0 && cursor_[p] < 2 && frames_[p] >= 0)
                    batch.pushTextured(frames_[p], {408, 304.f * cursor_[p], 400, 300}, uv(frames_[p], {0, 0, 400, 300}), {});

        drawChibis(batch);
        if (art_[team_] >= 0)
            batch.pushTextured(art_[team_], {144, 44, 512, 512}, uv(art_[team_], {0, 0, 512, 512}), {});
        const int labelSheet = labels_[team_ < 6 ? 0 : 1];
        const int labelIndex = team_ < 6 ? team_ : team_ - 6;
        if (labelSheet >= 0)
            batch.pushTextured(labelSheet, {272, 300, 256, 160},
                               uv(labelSheet, {labelIndex / 3 * 256.f, labelIndex % 3 * 160.f, 256, 160}), {});

        if (stage_ > 0) {
            for (int slot = 0; slot < 2; ++slot) drawSlot(batch, slot);
            drawCell(batch, kButtons, 336, 550, 0, 1);
            drawCell(batch, kButtons, 464, 550, 1, 1);
            for (int p = 0; p < 2; ++p)
                if (cursor_[p] > 1) drawCell(batch, kCursor, (cursor_[p] - 2) * 2 * 64.f - 64.f + 400.f, 550, p, 0);
        }
        if (fade_ > 0) batch.pushSolid({0, 0, 800, 600}, {0, 0, 0, fade_ / 255.f});
    }

    const char* name() const override { return "story team"; }
    int takeSound() override { return std::exchange(sound_, -1); }
    std::string takeVoice() override { return std::exchange(voice_, {}); }

private:
    void load(const std::string& stem, int& slot) {
        if (!uploadCnvSheet(batch_, stem.c_str(), slot, error_)) slot = -1;
    }

    UiRect uv(int texture, const UiRect& source) const {
        uint32_t w = 0, h = 0;
        if (!batch_.textureSize(texture, w, h) || !w || !h) return {0, 0, 1, 1};
        return {source.x / w, source.y / h, source.w / w, source.h / h};
    }

    void drawCell(SpriteRenderer& batch, const Sprite& sprite, float x, float y, int col, int row,
                  float scale = 1.f, UiColor tint = {}) const {
        const int texture = sheets_[sprite.sheet];
        if (texture < 0) return;
        const UiRect src{sprite.src.x + col * sprite.src.w, sprite.src.y + row * sprite.src.h, sprite.src.w, sprite.src.h};
        batch.pushSprite(texture, src, sprite.pivotX, sprite.pivotY, x, y, scale, 0.f, tint);
    }

    bool highlighted(int chibi) const {
        if (team_ < 5) return chibi == team_ || chibi == team_ + 1;
        if (team_ == 5) return chibi == 5 || chibi == 0;
        return chibi == team_ * 2 - 6 || chibi == team_ * 2 - 5;
    }

    void drawChibis(SpriteRenderer& batch) const {
        for (int i = 0; i < kChibis; ++i) {
            if (chibis_[i] < 0) continue;
            int col = 0, row = 0;
            UiColor tint{0.5f, 0.5f, 0.5f, 1.f};
            if (highlighted(i)) {
                const int frame = (tick_ % 40) / 10 + 1;
                col = frame % 3;
                row = frame / 3;
                tint = {};
            }
            batch.pushSprite(chibis_[i], {col * 80.f, row * 128.f, 80, 128}, 40, 80,
                             kChibiX[i] * 47.f + 112.f, kChibiY[i] * 34.f + 112.f, 1.f, 0.f, tint);
        }
    }

    void drawSlot(SpriteRenderer& batch, int slot) const {
        const float base = 300.f * slot;
        const int character = kPairs[team_][slot];
        const int owner = owner_[slot];
        const int panel = owner >= 0 ? panel_[owner] : -1;
        const float slide = owner >= 0 ? slide_[owner] : 0.f;

        if ((done_[slot] || owner >= 0) && costumes_[slot] >= 0)
            batch.pushSprite(costumes_[slot], {costume_[slot] % 3 * 80.f, costume_[slot] / 3 * 128.f, 80, 128},
                             40, 80, 730, base + 120);
        if (controller_[slot] >= 0 && panel != kController) {
            if (controller_[slot] < 4) drawCell(batch, kPlayerTag, 730, base + 180, controller_[slot], 0);
            else drawCell(batch, kControllerName, 730, base + 180, 0, 2);
        }
        if (hyper_[slot] >= 0 && panel != kHyper) drawCell(batch, kHyperName, 730, base + 265, 0, hyper_[slot], 0.5f);
        if (weapon_[slot] >= 0 && panel != kWeapon && weapons_[slot] >= 0)
            batch.pushSprite(weapons_[slot], {0, weapon_[slot] * 64.f, 256, 64}, 128, 32, 730, base + 240, 0.5f);
        if (owner >= 0 || controller_[slot] >= 0)
            drawCell(batch, kCharacterName, 730, base + 210, character >> 3, character & 7);

        if (owner >= 0) {
            const int choice = choice_[slot];
            if (panel == kController) {
                drawCell(batch, kHeading, slide + 610, base + 50, 0, 4);
                const bool taken = claimed_[owner] >= 0;
                drawCell(batch, kControllerName, slide + 618, base + 130, taken && choice == 1 ? 1 : 0, (1 - choice) * 2, 1.f,
                         {1, 1, 1, 0.5f});
                drawCell(batch, kControllerName, 610, base + 110, taken && choice == 0 ? 1 : 0, choice * 2);
                drawCell(batch, kArrows, 610, base + 110, 0, 0);
            } else if (panel == kWeapon || panel == kHyper) {
                drawCell(batch, kHeading, slide + 610, base + 50, 0, panel == kWeapon ? 1 : 3);
                for (int i = 2; i >= 0; --i) {
                    const UiColor tint{1, 1, 1, (0xff >> i) / 255.f};
                    const float x = i * 8.f + 610.f, y = base + i * 20.f + 110.f;
                    const int row = (choice + i) % 3;
                    if (panel == kHyper) {
                        drawCell(batch, kHyperName, x, y, 0, row, 1.f, tint);
                    } else if (weapons_[slot] >= 0) {
                        batch.pushSprite(weapons_[slot], {0, row * 64.f, 256, 64}, 128, 32, x, y, 1.f, 0.f, tint);
                    }
                }
                if (panel == kHyper) {
                    drawCell(batch, kHyperText, 610, base + 200, 0, choice + 2);
                } else if (weapons_[slot] >= 0) {
                    batch.pushSprite(weapons_[slot], {256, choice * 64.f, 256, 64}, 128, 32, 610, base + 200);
                }
                drawCell(batch, kArrows, 610, base + 110, 0, 0);
            }
        }
        if (done_[slot]) drawCell(batch, kStampSprite, 600, base + 110, 0, 0, stamp_[slot]);
    }

    static ScreenButtons buttonsFor(const ScreenInput& in, int player) {
        if (in.separatePlayers) return in.players[player];
        ScreenButtons merged;
        if (player == 0) {
            merged.up = in.up;
            merged.down = in.down;
            merged.left = in.left;
            merged.right = in.right;
            merged.confirm = in.confirm;
            merged.cancel = in.cancel;
        }
        return merged;
    }

    ScreenId step(const ScreenInput& in) {
        ++tick_;
        switch (stage_) {
        case 0: {
            const ScreenButtons p0 = buttonsFor(in, 0);
            if (p0.confirm) {
                cursor_ = {0, -1};
                sound_ = 0;
                loadMember(0, kPairs[team_][0]);
                loadMember(1, kPairs[team_][1]);
                stage_ = 1;
            } else if (p0.cancel) {
                sound_ = 1;
                return ScreenId::Title;
            } else if (p0.right) { team_ = kRight[team_]; sound_ = 2; }
            else if (p0.left) { team_ = kLeft[team_]; sound_ = 2; }
            else if (p0.down) { team_ = kDown[team_]; sound_ = 2; }
            else if (p0.up) { team_ = kUp[team_]; sound_ = 2; }
            break;
        }
        case 1:
            updatePanel(buttonsFor(in, 0), 0);
            updatePanel(buttonsFor(in, 1), 1);
            if (panelResult_ != 0) {
                const int result = std::exchange(panelResult_, 0);
                if (result == 2) stage_ = 2;
                else { stage_ = 0; resetPanels(); }
            }
            break;
        case 2:
            if (fade_ == 255) {
                stage_ = 3;
            } else {
                fade_ = std::min(255, fade_ + 15);
            }
            break;
        case 3:
            if (!applyTeam()) return ScreenId::Title;
            return ScreenId::StoryAdv;
        }
        return ScreenId::StoryTeam;
    }

    void resetPanels() {
        cursor_ = {-1, -1};
        panel_ = {kChoosing, kChoosing};
        claimed_ = {-1, -1};
        owner_ = {-1, -1};
        choice_ = {0, 0};
        controller_ = {-1, -1};
        weapon_ = {-1, -1};
        hyper_ = {-1, -1};
        costume_ = {0, 0};
        done_ = {false, false};
    }

    void loadMember(int slot, int character) {
        char path[48];
        std::snprintf(path, sizeof path, "data/select/%02d", character);
        load(path, faces_[slot]);
        std::snprintf(path, sizeof path, "data/select/cos%02d", character);
        load(path, costumes_[slot]);
        std::snprintf(path, sizeof path, "data/select/w%02d", character);
        load(path, weapons_[slot]);
    }

    // FUN_00406850.
    void updatePanel(const ScreenButtons& b, int p) {
        const bool horizontal = b.left || b.right, vertical = b.up || b.down;
        if (cursor_[p] < 0 && (horizontal || vertical || b.confirm)) cursor_[p] = p;
        if (cursor_[p] < 0) return;
        const int previous = panel_[p];
        const int slot = cursor_[p];
        switch (panel_[p]) {
        case kChoosing:
            if (b.cancel && panel_[0] == kChoosing && panel_[1] == kChoosing) {
                sound_ = 1;
                panelResult_ = 1;
                return;
            }
            if (vertical) {
                int& c = cursor_[p];
                if (b.up) c = c == 0 ? 2 : c < 2 ? c + 1 : 1;
                else c = c < 2 ? c + 1 : 0;
                sound_ = 2;
            } else if (horizontal) {
                if (cursor_[p] == 2) cursor_[p] = 3;
                else if (cursor_[p] == 3) cursor_[p] = 2;
                sound_ = 2;
            }
            if (cursor_[p] < 2) {
                const int s = cursor_[p];
                if (b.cancel && owner_[s] < 0 && (controller_[s] == p || controller_[s] == 4)) {
                    if (controller_[s] == p) claimed_[p] = -1;
                    controller_[s] = -1;
                    done_[s] = false;
                } else if (b.confirm && owner_[s] < 0 && controller_[s] < 0) {
                    sound_ = 0;
                    done_[s] = false;
                    owner_[s] = p;
                    panel_[p] = kWeapon;
                    choice_[s] = 0;
                }
            } else if (b.confirm && panel_[0] == kChoosing && panel_[1] == kChoosing) {
                sound_ = cursor_[p] == 3 ? 1 : 0;
                panelResult_ = cursor_[p] == 3 ? 1 : 2;
                return;
            }
            break;
        case kController:
            if (vertical && claimed_[p] < 0) {
                sound_ = 2;
                choice_[slot] = 1 - choice_[slot];
            }
            if (b.confirm) {
                sound_ = 0;
                if (choice_[slot] == 0) {
                    claimed_[p] = slot;
                    controller_[slot] = p;
                } else {
                    controller_[slot] = 4;
                }
                panel_[p] = kStamp;
                stamp_[slot] = 4.f;
                done_[slot] = true;
                const char* name = frontendCharacterDirectory(kPairs[team_][slot]);
                if (name) voice_ = std::string("data/voice/entry/") + name;
            } else if (b.cancel) {
                sound_ = 1;
                if (claimed_[p] == slot) claimed_[p] = -1;
                panel_[p] = kHyper;
                choice_[slot] = hyper_[slot];
                controller_[slot] = -1;
            }
            break;
        case kWeapon:
            if (vertical) {
                sound_ = 2;
                choice_[slot] = (choice_[slot] + 3 + (b.down ? 1 : -1)) % 3;
            }
            weapon_[slot] = choice_[slot];
            if (b.confirm) {
                sound_ = 0;
                panel_[p] = kHyper;
                choice_[slot] = 0;
            } else if (b.cancel) {
                sound_ = 1;
                if (claimed_[p] == slot) claimed_[p] = -1;
                panel_[p] = kChoosing;
                controller_[slot] = -1;
                weapon_[slot] = -1;
                owner_[slot] = -1;
            }
            break;
        case kHyper:
            if (vertical) {
                sound_ = 2;
                choice_[slot] = (choice_[slot] + 3 + (b.down ? 1 : -1)) % 3;
            }
            hyper_[slot] = choice_[slot];
            if (b.confirm) {
                sound_ = 0;
                panel_[p] = kController;
                if (claimed_[p] == slot) {
                    claimed_[p] = -1;
                    choice_[slot] = 0;
                } else {
                    choice_[slot] = claimed_[p] >= 0 ? 1 : 0;
                }
            } else if (b.cancel) {
                sound_ = 1;
                panel_[p] = kWeapon;
                choice_[slot] = weapon_[slot];
            }
            break;
        case kStamp:
            if (stamp_[slot] <= 1.f) {
                sound_ = 3;
                panel_[p] = kChoosing;
                owner_[slot] = -1;
            } else {
                stamp_[slot] -= 0.25f;
            }
            break;
        }
        if ((panel_[p] == kHyper || panel_[p] == kWeapon || panel_[p] == kController) && horizontal) {
            const int count = kSelectCostumes[kPairs[team_][slot]];
            costume_[slot] = (costume_[slot] + count + (b.right ? 1 : -1)) % count;
        }
        if (panel_[p] != previous) slide_[p] = 300.f;
        if (slide_[p] > 0.f) slide_[p] -= 20.f;
    }

    // 0x406675: an unset member becomes a random COM, and both COM makes the first one human.
    bool applyTeam() {
        const auto& pair = kPairs[team_];
        for (int slot = 0; slot < 2; ++slot) {
            FrontendSlot& member = state_.slots[slot];
            member = FrontendSlot{};
            member.character = pair[slot];
            if (done_[slot]) {
                member.weapon = weapon_[slot];
                member.hypermode = hyper_[slot];
                member.controller = controller_[slot];
                member.costume = costume_[slot];
            } else {
                member.hypermode = static_cast<int>(state_.nextRandom() % 3);
                // The original tests the first member for Rena and each member for Rika.
                const bool twoWeapons = pair[0] == 0 || pair[slot] == 4;
                member.weapon = static_cast<int>(state_.nextRandom() % (twoWeapons ? 2u : 3u));
                member.controller = 4;
            }
        }
        if (state_.slots[0].controller == 4 && state_.slots[1].controller == 4) state_.slots[0].controller = 0;
        return beginStoryTeam(state_, kTeamFile[team_], error_);
    }

    SpriteRenderer& batch_;
    FrontendState& state_;
    std::string& error_;
    ScreenId leaving_ = ScreenId::StoryTeam;
    int background_ = -1;
    std::array<int, kSheets> sheets_{{-1, -1, -1, -1}};
    std::array<int, 2> frames_{{-1, -1}}, labels_{{-1, -1}};
    std::array<int, kChibis> chibis_{};
    std::array<int, kTeams> art_{};
    std::array<int, 2> faces_{{-1, -1}}, costumes_{{-1, -1}}, weapons_{{-1, -1}};
    int stage_ = 0;        // +0x2e18
    int team_ = 0;         // +0x2e20
    int tick_ = 0;         // +0x2e14
    int fade_ = 0;         // +0x2ebc
    int panelResult_ = 0;  // 1 back to the team cursor, 2 go
    std::array<int, 2> cursor_{};                 // +0x2e28, per player
    std::array<int, 2> panel_{{0, 0}};            // +0x2e98, per player
    std::array<int, 2> claimed_{{-1, -1}};        // +0x2ea0, per player
    std::array<float, 2> slide_{{0.f, 0.f}};      // +0x2eb4, per player
    std::array<int, 2> owner_{{-1, -1}};          // +0x2e90, per slot
    std::array<int, 2> choice_{{0, 0}};           // +0x2e30
    std::array<int, 2> controller_{{-1, -1}};     // +0x2e40
    std::array<int, 2> weapon_{{-1, -1}};         // +0x2e60
    std::array<int, 2> hyper_{{-1, -1}};          // +0x2e70
    std::array<int, 2> costume_{{0, 0}};          // +0x2e80
    std::array<bool, 2> done_{{false, false}};    // +0x2ea8
    std::array<float, 2> stamp_{{1.f, 1.f}};      // +0x2eac
    int sound_ = -1;
    std::string voice_;
};

}  // namespace

std::unique_ptr<Screen> makeStoryTeamScreen(SpriteRenderer& batch, FrontendState& state, std::string& error) {
    auto screen = std::make_unique<StoryTeamScreen>(batch, state, error);
    if (!error.empty()) return nullptr;
    return screen;
}

}  // namespace ui
