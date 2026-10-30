#include "frontend/screen_result.h"
#include <algorithm>
#include <cstdio>
#include "assets/asset_source.h"
#include "assets/cnv.h"
#include "hud/hud_atlas.h"
#include "frontend/participants.h"
#include "frontend/result_quote.h"
#include "ui/text.h"
#include "ui/caption.h"

namespace ui {

ResultQuote parseResultQuote(const std::string& utf8) {
    const std::vector<ResultQuoteEntry> entries = parseResultQuotes(utf8);
    ResultQuote quote;
    if (!entries.empty()) {
        quote.text = entries.front().text;
        quote.voice = entries.front().voice;
    }
    return quote;
}

namespace {
class ResultScreen final : public Screen {
public:
    ResultScreen(SpriteRenderer& batch, FrontendState& state, std::string& error)
        : state_(state), timeline_(state.resultWinner < 0) {
        // The winning TEAM (issue #13): resultWinner is the winning side (0 blue / 1 red,
        // MatchEconomy::roundOverSide), so the sting, the quote and the winner caption all
        // follow the team and never a single primary panel.
        const int side = state.resultWinner == 1 ? 1 : 0;
        participantCount_ = buildParticipants(state_.slots.data(), participants_);
        // The winning side's selections in panel order (issue #20). A one-member side repeats
        // its member: the port's 1v1, and every character ships a self-pair script.
        std::array<WinnerSlot, 2> winners{};
        int winnerCount = 0;
        for (int i = 0; i < participantCount_ && winnerCount < 2; ++i) {
            if (participants_[i].team != side) continue;
            winners[(size_t)winnerCount].character = participants_[i].character;
            winners[(size_t)winnerCount].weapon = participants_[i].weapon;
            ++winnerCount;
        }
        // The winner art: one 512x512 sheet per winning slot, data/win/%02da, or %02db for the
        // persona variant (character 0/4 with weapon 2) — FUN_00635d40:255-273 loads one per
        // winning slot, so a 2v2 shows BOTH winners and a one-member side shows its one.
        winnerSlots_ = winnerPortraitCount(winnerCount);
        for (int i = 0; i < winnerCount; ++i) {
            WinnerSlot& winner = winners[(size_t)i];
            winner.persona = resultPersonaId(winner.character, winner.weapon) != winner.character;
            if (winner.character < 0) continue;
            char stem[64];
            std::snprintf(stem, sizeof(stem), "data/win/%02d%c", winner.character,
                          winner.persona ? 'b' : 'a');
            std::string failure;
            if (!uploadCnvSheet(batch, stem, winnerSheets_[i], failure) && error.empty())
                error = failure;
        }
        // The quote pair repeats a one-member side's fighter (planWinnerQuote), so the evidence
        // line reports that member's persona for both pair slots.
        if (winnerCount == 1) winners[1].persona = winners[0].persona;
        {
            std::string failure;
            if (!uploadCnvSheet(batch, "data/object/system", systemSheet_, failure) && error.empty())
                error = failure;
        }
        if (state.resultWinner >= 0 && winnerCount > 0) {
            // The grade needs the round's margin and the winners' HP, which the host measured
            // when the round resolved (FUN_00635d40:288-318); the plan then names the pair
            // script and the recovered single-script fallback (FUN_00635d40:323-346).
            // planWinnerQuote takes the pair as plain arrays; the slots above are the state.
            int characters[2] = {-1, -1}, weapons[2] = {0, 0};
            for (int i = 0; i < 2; ++i) {
                characters[i] = winners[(size_t)i].character;
                weapons[i] = winners[(size_t)i].weapon;
            }
            plan_ = planWinnerQuote(characters, weapons, winnerCount, state.resultMargin,
                                    state.resultWinnersHurt);
            auto& assets = fnd::assets::assetSource();
            std::vector<uint8_t> bytes;
            if (assets.read(plan_.pairScript, bytes) && !bytes.empty()) {
                quotePath_ = plan_.pairScript;
            } else if (assets.read(plan_.fallbackScript, bytes) && !bytes.empty()) {
                quotePath_ = plan_.fallbackScript;
            }
            if (!bytes.empty()) {
                entries_ = parseResultQuotes(
                    xm::sjisToUtf8(std::string(bytes.begin(), bytes.end())));
                const int pick = resultQuoteEntryIndex((int)entries_.size(), side, state.matchFrame);
                if (pick >= 0) {
                    quote_.text = entries_[(size_t)pick].text;
                    quote_.voice = entries_[(size_t)pick].voice;
                }
            }
        }
        if (state.resultWinner >= 0 && quote_.text.empty() && error.empty())
            error = "result: no shipped victory quotation resolved for " + plan_.pairScript;
        if (state.resultWinner >= 0) {
            // Evidence line: which script answered, which alternative was picked and which
            // voice it names — the run's own record of the recovered rule's decision.
            std::printf("[result] side %d pair %d-%d grade %d margin %d script %s "
                        "persona %d/%d voice %s\n",
                        side, plan_.pairA, plan_.pairB, plan_.grade, state.resultMargin,
                        quotePath_.empty() ? plan_.pairScript.c_str() : quotePath_.c_str(),
                        winners[0].persona ? 1 : 0, winners[1].persona ? 1 : 0,
                        quote_.voice.empty() ? "(none)" : quote_.voice.c_str());
        }
        if (!loadCaptionFont(text_,30.f,error)) return;
        if (text_.faceCount() != 2) {
            // Same user-facing shape as caption.cpp's missing-face message: the Japanese
            // fallback ships in the package's assets/fonts, so a missing one means the
            // package was unpacked incompletely.
            if (error.empty())
                error = "the Japanese caption fallback (NotoSansCJKjp-Regular.otf) is missing "
                        "from assets/fonts next to the executable — unpack the release "
                        "archive again";
            return;
        }
        quoteLayout_ = text_.layout(quote_.text.c_str());
        if (state.resultWinner < 0) drawLayout_ = text_.layout("DRAW");
        if (state.resultWinner >= 0)
            winnerLayout_ = text_.layout((std::string(teamLabel(side)) + " TEAM WINS").c_str());
        // One report row per ACTIVE participant (FUN_0063a740:64-85 walks all four slots),
        // carrying that participant's earned title and its own statistics.
        for (int i = 0; i < participantCount_; ++i) {
            const auto& stats = state.resultStats[participants_[i].panel];
            char report[160];
            std::snprintf(report,sizeof(report),"KO %d  DEATH %d  DAMAGE %d / %d",
                          stats.kos,stats.deaths,stats.damageDealt,stats.damageTaken);
            statsLayout_[i] = text_.layout(report);
            rowLayout_[i] = text_.layout(participants_[i].combo().c_str());
            titleLayout_[i] = text_.layout(state.resultTitleText[participants_[i].panel].c_str());
        }
        textSlot_ = batch.addTexture(text_.atlasWidth(),text_.atlasHeight(),text_.atlasRGBA().data(),error);
    }
    // `error` names the reason a screen the port cannot present was refused: a silent null
    // here used to end the run as a successful quit with the result screen missing.
    bool loaded(std::string& error) const {
        if (systemSheet_ < 0) {
            if (error.empty()) error = "the result screen's report art did not load";
            return false;
        }
        for (int i = 0; i < winnerSlots_; ++i) {
            if (winnerSheets_[i] < 0) {
                if (error.empty())
                    error = "the winning character's result portrait did not load";
                return false;
            }
        }
        if (textSlot_ < 0) {
            if (error.empty()) error = "the result screen's caption atlas did not load";
            return false;
        }
        return state_.resultWinner < 0 || !quote_.text.empty();
    }
    const char* name() const override { return "result"; }
    ScreenId update(const ScreenInput& input) override {
        const auto previous = timeline_.phase();
        const bool done = timeline_.update(input.confirm);
        sound_ = previous != timeline_.phase() && input.confirm ? 0 : -1;
        // Leaving for the selection is a fresh select entry: its own construction clears the
        // selection, the stage page and the ready flags (issue #45, FUN_00408330:143-158).
        return done ? ScreenId::Select : ScreenId::Result;
    }
    std::string takeVoice() override {
        if (timeline_.phase() != ResultPhase::Quote || voiceTaken_ || quote_.voice.empty()) return {};
        voiceTaken_ = true; return "data/voice/win/" + quote_.voice;
    }
    int takeSound() override { const int sound = sound_; sound_ = -1; return sound; }
    void draw(SpriteRenderer& batch) const override {
        if (state_.resultWinner >= 0) {
            // Both winners, at the recovered settled positions (FUN_0063a740's sub-phases 1/5
            // draw them at (progress-32,60) and (progress+352,60)); the port slides them in over
            // the quote phase instead of following that progress counter, whose rate the corpus
            // does not pin. PORT RULE, animation only.
            const float slide = timeline_.phase() == ResultPhase::Quote ? std::min(1.f, (float)timeline_.frame() / 24.f) : 1.f;
            if (winnerSlots_ == 1) {
                // A one-member side (the port's 1v1) has no recovered layout — the original
                // always fields two winners — so its portrait keeps the centred position the
                // 1v1 result screen shipped before the two-winner layout (PORT RULE).
                if (winnerSheets_[0] >= 0)
                    batch.pushTextured(winnerSheets_[0],{144.f,60,512,512},{0,0,1,1},{});
            } else {
                const float x0 = -32.f - (1.f - slide) * 320.f;
                const float x1 = 352.f + (1.f - slide) * 320.f;
                if (winnerSheets_[0] >= 0) batch.pushTextured(winnerSheets_[0],{x0,60,512,512},{0,0,1,1},{});
                if (winnerSheets_[1] >= 0) batch.pushTextured(winnerSheets_[1],{x1,60,512,512},{0,0,1,1},{});
            }
            // FUN_0063a740's quote bands: the black strip above and the black band below.
            batch.pushSolid({-800,0,2400,60},{0,0,0,1});
            batch.pushSolid({-800,424,2400,176},{0,0,0,1});
            drawText(batch,quoteLayout_,75,440);
            // Which TEAM won, as a caption (D7): the sting's own art says 青組/赤組, but the
            // report needs it in words once the bands are gone.
            if (!winnerLayout_.items.empty()) drawText(batch,winnerLayout_,560,28,.7f);
        }
        // Done is the fade out of the report, which must stay as it was.
        if (timeline_.phase() != ResultPhase::Quote) {
            batch.pushSolid({-800,0,2400,600},{0,0,0,.75f});
            // FUN_00633ca0: activity report header at (0,320,288,64).
            batch.pushSprite(systemSheet_,{0,320,288,64},144,32,400,28);
            if (state_.resultWinner < 0) drawText(batch,drawLayout_,350,440);
            // FUN_0063a740:64-85: rows i = 0..3 at y = 100 + 72*i, the controller/COM badge
            // (system sheet, cell (controller,0)) at x = 200, the earned title at (300, y+32),
            // revealed one row per 30 frames after a 30-frame lead-in. The combo and the
            // statistics are the port's additions, placed around the recovered title line.
            const int revealed = timeline_.phase() == ResultPhase::Done ? participantCount_ : resultRowsRevealed(timeline_.frame());
            for (int i = 0; i < participantCount_ && i < revealed; ++i) {
                const ResultRow row = resultRow(i);
                const int controller = std::clamp(participants_[i].controller,0,4);
                batch.pushSprite(systemSheet_,{controller*64.f,384,64,32},0,0,row.badgeX,row.badgeY);
                drawText(batch,rowLayout_[i],row.textX,row.textY,.5f);
                drawText(batch,titleLayout_[i],row.textX,row.titleY,.8f);
                drawText(batch,statsLayout_[i],row.textX,row.statsY,.5f);
            }
        }
    }
private:
    void drawText(SpriteRenderer& batch, const TextLayout& layout, float x, float y, float scale=1) const {
        drawCaptionLayout(batch,text_,layout,textSlot_,bitmapSlot_,x,y,scale);
    }
    FrontendState& state_;
    ResultTimeline timeline_;
    WinnerQuotePlan plan_;
    std::string quotePath_;
    std::vector<ResultQuoteEntry> entries_;
    ResultQuote quote_;
    bool voiceTaken_ = false;
    TextLayer text_;
    TextLayout quoteLayout_, drawLayout_, statsLayout_[kParticipantCount];
    TextLayout rowLayout_[kParticipantCount], titleLayout_[kParticipantCount], winnerLayout_;
    Participant participants_[kParticipantCount];
    int participantCount_ = 0;
    mutable int bitmapSlot_ = -1;
    int systemSheet_ = -1;
    int winnerSheets_[2] = {-1,-1};
    int winnerSlots_ = 0;    // portraits the winning side draws (1 for the port's 1v1)
    int textSlot_=-1, sound_=-1;
};
}
std::unique_ptr<Screen> makeResultScreen(SpriteRenderer& batch, FrontendState& state,std::string& error) {
    auto screen = std::make_unique<ResultScreen>(batch,state,error);
    if (!screen->loaded(error)) return nullptr;
    return screen;
}
}
