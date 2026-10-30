#pragma once
#include "ui/screen.h"
#include "ui/frontend_state.h"
namespace ui {
enum class ResultPhase { Quote, Report, Done };
// The core plays FUN_00635d40 case 3's victory layers in the battle; the later beats await Z.
class ResultTimeline {
public:
    explicit ResultTimeline(bool draw = false) : phase_(draw ? ResultPhase::Report : ResultPhase::Quote) {}
    bool update(bool confirm) {
        if (phase_ == ResultPhase::Done) return true;
        ++frame_;
        if (confirm) {
            phase_ = phase_ == ResultPhase::Quote ? ResultPhase::Report : ResultPhase::Done;
            frame_ = 0;
        }
        return phase_ == ResultPhase::Done;
    }
    ResultPhase phase() const { return phase_; }
    int frame() const { return frame_; }
private:
    ResultPhase phase_ = ResultPhase::Quote;
    int frame_ = 0;
};
struct ResultQuote { std::string text, voice; };
// Scenario files alternate VOICE directives and quote lines (FUN_0065e500).
ResultQuote parseResultQuote(const std::string& utf8);
std::unique_ptr<Screen> makeResultScreen(SpriteRenderer& batch, FrontendState& state,
                                        std::string& error);
}
