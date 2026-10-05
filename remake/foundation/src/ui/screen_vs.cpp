#include "ui/screen_vs.h"
#include <algorithm>
#include <cstdio>
#include <string>
#include <vector>
#include "ui/caption.h"
#include "ui/hud.h"
#include "ui/hud_atlas.h"
#include "ui/participants.h"
namespace ui {
namespace {
class VsScreen final : public Screen {
public:
    VsScreen(SpriteRenderer& batch, FrontendState& state, std::string& error) {
        const char* stems[] = {"data/vs/vs01", "data/vs/vs02", "data/vs/vs03", "data/select/p03"};
        // The roster is the selection (issue #13): two participants in a 1v1, four in a 2v2,
        // three in a 2v1. FUN_00411cb0 draws four portraits and four name cells in its versus
        // branch because the original always has four player slots; the port draws one per
        // actual participant.
        participantCount_ = buildParticipants(state.slots.data(), participants_);
        vsSlotsFor(participants_, participantCount_, slots_);
        for (int i = 0; i < 4; ++i) {
            std::string failure;
            if (!uploadCnvSheet(batch, stems[i], sheets_[i], failure) && error.empty())
                error = failure;
        }
        // One portrait per participant, from the selection sheet that participant chose
        // (FUN_00411cb0:78-92's four FUN_00655d60 calls).
        for (int i = 0; i < participantCount_; ++i) {
            char portrait[64];
            std::snprintf(portrait, sizeof(portrait), "data/select/%02d",
                          std::max(0, participants_[i].character));
            std::string failure;
            if (!uploadCnvSheet(batch, portrait, portraits_[i], failure) && error.empty())
                error = failure;
        }
        // Combo + controller captions (D7 path). PORT EXTENSION: the original's VS screen
        // draws bands, portraits, names and the logo only, so this text is the port making
        // the selected equipment and the controller/COM assignment visible, which issue #13
        // requires. A missing caption font simply drops the lines (the names and portraits
        // still identify the participants).
        if (!participantCount_ || !loadCaptionFont(text_, 20.f, error)) return;
        std::vector<std::string> lines;
        for (int i = 0; i < participantCount_; ++i) {
            lines.push_back(captionFor(i));
            captionLayout_[i] = text_.layout(lines.back().c_str());
        }
        textSlot_ = batch.addTexture(text_.atlasWidth(), text_.atlasHeight(),
                                     text_.atlasRGBA().data(), error);
    }
    bool loaded() const {
        for (int i = 0; i < 4; ++i) if (sheets_[i] < 0) return false;
        for (int i = 0; i < participantCount_; ++i) if (portraits_[i] < 0) return false;
        return true;
    }
    const char* name() const override { return "vs"; }
    ScreenId update(const ScreenInput& input) override {
        // Confirm skip is a port extension; FUN_00411ae0 has no input branch.
        return timeline_.update(input.confirm) ? ScreenId::Battle : ScreenId::VsIntro;
    }
    void draw(SpriteRenderer& batch) const override {
        batch.pushTextured(sheets_[0], {0,0,800,300}, {0,0,1,1}, {});
        batch.pushTextured(sheets_[1], {0,300,800,300}, {0,0,1,1}, {});
        // Names: the p03 name sheet, cell (character/8, character%8), at each participant's
        // name anchor (FUN_00411cb0:28-50's four FUN_00655830 calls).
        for (int i = 0; i < participantCount_; ++i) {
            const int character = std::max(0, participants_[i].character);
            batch.pushSprite(sheets_[3], {(character / 8) * 256.f, (character % 8) * 64.f,256,64},
                             128,32,slots_[i].nameX,slots_[i].nameY);
        }
        // Portraits: pivot (128,256), sliding in on the recovered per-slot offsets
        // (FUN_00411ae0:12-21 decays them by 30/20/20/30 px per frame). The blue team's
        // portraits are mirrored, which is the existing port choice for the slide-in pair —
        // FUN_00411cb0 itself draws them unmirrored, so it stays flagged here.
        for (int i = 0; i < participantCount_; ++i) {
            const VsSlot& slot = slots_[i];
            const float offset = timeline_.offset(slot.slide);
            const float x = slot.portraitX + (participants_[i].team == 0 ? -offset : offset);
            uint32_t w = 0, h = 0;
            if (!batch.textureSize(portraits_[i], w, h)) continue;
            const float u = 256.f / w, v = 256.f / h;
            const bool mirror = participants_[i].team == 0;
            batch.pushTextured(portraits_[i], {x-128, slot.portraitY-256, 256, 256},
                               {mirror ? u : 0.f, 0, mirror ? -u : u, v}, {});
        }
        if (timeline_.frame() > 90)
            batch.pushSprite(sheets_[2], {0,0,256,256},128,128,400,300,timeline_.scale(),
                             (timeline_.scale()-1)*42);
        if (textSlot_ < 0) return;
        // Captions sit inside their own band: below the blue portraits (whose pivot is at
        // y 295) and above the red ones (pivot 600, so 332 is the top of the lower band).
        for (int i = 0; i < participantCount_; ++i) {
            const VsSlot& slot = slots_[i];
            const float y = participants_[i].team == 0 ? slot.portraitY + 12.f
                                                       : slot.portraitY - 268.f;
            drawCaptionLayout(batch, text_, captionLayout_[i], textSlot_, bitmapSlot_,
                              slot.portraitX - 96.f, y, .8f, kHudWhite, 2.f);
        }
    }
private:
    // "Rena 1  1P": the combo label (AGENTS.md rule 7 — never a bare fighter) plus the
    // controller slot or COM.
    std::string captionFor(int i) const {
        const Participant& p = participants_[i];
        return p.combo() + "  " + controllerLabel(p.controller);
    }
    Participant participants_[kParticipantCount];
    VsSlot slots_[kParticipantCount];
    int participantCount_ = 0;
    VsTimeline timeline_;
    TextLayer text_;
    TextLayout captionLayout_[kParticipantCount];
    mutable int bitmapSlot_ = -1;
    int sheets_[4] = {-1,-1,-1,-1};
    int portraits_[kParticipantCount] = {-1,-1,-1,-1};
    int textSlot_ = -1;
};
}
std::unique_ptr<Screen> makeVsScreen(SpriteRenderer& batch, FrontendState& state, std::string& error) {
    auto screen = std::make_unique<VsScreen>(batch,state,error);
    if (!screen->loaded()) return nullptr;
    return screen;
}
}
