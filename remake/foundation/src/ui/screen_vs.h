#pragma once
#include <array>
#include "ui/screen.h"
#include "ui/frontend_state.h"
namespace ui {
// FUN_004115f0 / FUN_00411ae0: slide first, then 5→1 scale after frame 90.
class VsTimeline {
public:
    explicit VsTimeline(int minimumFrames = 0) : minimumFrames_(minimumFrames) {}
    bool update(bool skip = false) {
        if (done_ || skip) { done_ = true; return true; }
        for (int i = 0; i < 4; ++i) {
            offsets_[i] -= i == 0 || i == 3 ? 30.f : 20.f;
            if (offsets_[i] < 0) offsets_[i] = 0;
        }
        if (frame_ > 90) {
            // FUN_00411ae0 ends the animation here. The host may keep the finished
            // logo visible until the one-shot VS sting has finished (port pacing).
            if (scale_ <= 1) done_ = frame_ >= minimumFrames_;
            else scale_ -= .25f;
        }
        ++frame_;
        return false;
    }
    int frame() const { return frame_; }
    float scale() const { return scale_; }
    float offset(int slot) const { return offsets_[slot]; }
private:
    int frame_ = 0;
    float scale_ = 5;
    bool done_ = false;
    int minimumFrames_ = 0;
    std::array<float,4> offsets_{{1200,800,800,1200}};
};
std::unique_ptr<Screen> makeVsScreen(SpriteRenderer& batch, FrontendState& state,
                                    std::string& error, int minimumFrames = 0);
}
