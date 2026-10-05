#include "ui/screen_result.h"
#include <algorithm>
#include <sstream>
#include <cstdio>
#include "assets/asset_source.h"
#include "assets/cnv.h"
#include "ui/hud_atlas.h"
#include "ui/participants.h"
#include "ui/text.h"
#include "ui/caption.h"

namespace ui {
ResultQuote parseResultQuote(const std::string& utf8) {
    ResultQuote quote;
    std::istringstream lines(utf8);
    std::string line;
    while (std::getline(lines,line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (line.empty() || line[0] == '#') continue;
        if (line.compare(0,6,"VOICE ") == 0 || line.compare(0,6,"voice ") == 0)
            quote.voice = line.substr(6);
        else { quote.text = line; break; }
    }
    return quote;
}
namespace {
class ResultScreen final : public Screen {
public:
    ResultScreen(SpriteRenderer& batch, FrontendState& state, std::string& error) : state_(state), timeline_(state.resultWinner < 0) {
        // The winning TEAM (issue #13): resultWinner is the winning side (0 blue / 1 red,
        // MatchEconomy::roundOverSide), so the sting, the quote and the winner caption all
        // follow the team and never a single primary panel.
        const int side = state.resultWinner == 1 ? 1 : 0;
        participantCount_ = buildParticipants(state_.slots.data(), participants_);
        // The quote belongs to the winning team's FIRST member (the original loads
        // data/scenario/win/<char>.txt for the winning side's character).
        int quoteCharacter = -1;
        for (int i = 0; i < participantCount_ && quoteCharacter < 0; ++i)
            if (participants_[i].team == side) quoteCharacter = participants_[i].character;
        const char* stems[] = {side ? "data/object/P08" : "data/object/P05", "data/object/system"};
        for (int i = 0; i < 3; ++i) {
            if (state.resultWinner < 0 && i != 1) continue;
            char stem[64];
            if (i >= 2) std::snprintf(stem,sizeof(stem),"data/win/%02da",std::max(0,quoteCharacter));
            std::string failure;
            if (!uploadCnvSheet(batch,i < 2 ? stems[i] : stem,sheets_[i],failure) && error.empty())
                error = failure;
        }
        char path[96];
        std::snprintf(path,sizeof(path),"data/scenario/win/%02d.txt",std::max(0,quoteCharacter));
        std::vector<uint8_t> bytes;
        auto& assets = fnd::assets::assetSource();
        if (state.resultWinner >= 0) {
            // Ordinary characters ship only pair scripts; a missing single quote uses that
            // character's self-pair rather than attributing an absent teammate's voice.
            if (!assets.read(path,bytes)) {
                std::snprintf(path,sizeof(path),"data/scenario/win/%02d-%02d-1.txt",
                              std::max(0,quoteCharacter),std::max(0,quoteCharacter));
                assets.read(path,bytes);
            }
            if (!bytes.empty()) quote_ = parseResultQuote(xm::sjisToUtf8(std::string(bytes.begin(),bytes.end())));
        }
        if (state.resultWinner >= 0 && quote_.text.empty() && error.empty()) error = "result: no shipped victory quotation resolved";
        if (!loadCaptionFont(text_,30.f,error)) return;
        if (text_.faceCount() != 2) { if (error.empty()) error = "result: fetch the pinned CJK fallback font"; return; }
        quoteLayout_ = text_.layout(quote_.text.c_str());
        if (state.resultWinner < 0) drawLayout_ = text_.layout("DRAW");
        if (state.resultWinner >= 0)
            winnerLayout_ = text_.layout((std::string(teamLabel(side)) + " TEAM WINS").c_str());
        // One report row per ACTIVE participant (FUN_0063a740:64-85 walks all four slots),
        // carrying that participant's own statistics.
        for (int i = 0; i < participantCount_; ++i) {
            const auto& stats = state.resultStats[participants_[i].panel];
            char report[160];
            std::snprintf(report,sizeof(report),"KO %d  DEATH %d  DAMAGE %d / %d",
                          stats.kos,stats.deaths,stats.damageDealt,stats.damageTaken);
            statsLayout_[i] = text_.layout(report);
            rowLayout_[i] = text_.layout(participants_[i].combo().c_str());
        }
        textSlot_ = batch.addTexture(text_.atlasWidth(),text_.atlasHeight(),text_.atlasRGBA().data(),error);
    }
    bool loaded() const {
        if (sheets_[1] < 0) return false;
        if (state_.resultWinner >= 0 && (sheets_[0] < 0 || sheets_[2] < 0)) return false;
        return textSlot_ >= 0 && (state_.resultWinner < 0 || !quote_.text.empty());
    }
    const char* name() const override { return "result"; }
    ScreenId update(const ScreenInput& input) override {
        const auto previous = timeline_.phase();
        const bool done = timeline_.update(input.confirm);
        sound_ = previous != timeline_.phase() && input.confirm ? 0 : -1;
        if (done) { state_.stagePage = false; for (auto& slot : state_.slots) slot.ready = false; }
        return done ? ScreenId::Select : ScreenId::Result;
    }
    std::string takeVoice() override {
        if (timeline_.phase() != ResultPhase::Quote || voiceTaken_ || quote_.voice.empty()) return {};
        voiceTaken_ = true; return "data/voice/win/" + quote_.voice;
    }
    int takeSound() override { const int sound = sound_; sound_ = -1; return sound; }
    void draw(SpriteRenderer& batch) const override {
        batch.pushSolid({0,0,800,600},{.05f,.05f,.05f,1});
        if (timeline_.phase() == ResultPhase::Victory) {
            // The team sting is TWO layers at (400,200) and (400,400) (FUN_0063a130:89-98);
            // the second is armed when the first has 0x78 of its 0xb4 frames left
            // (FUN_00635d40:196-205), which is the transition ResultTimeline exposes.
            const float scale = std::max(1.f,8.f-timeline_.frame()*.5f);
            batch.pushSprite(sheets_[0],{0,0,512,256},256,128,400,200,scale);
            if (timeline_.victorySecondLayer()) {
                const float secondScale = std::max(1.f,8.f-(timeline_.frame()-60)*.5f);
                batch.pushSprite(sheets_[0],{0,256,512,256},256,128,400,400,secondScale);
            }
            return;
        }
        if (state_.resultWinner >= 0) {
            // FUN_0063a740's quote bands, with one centered portrait for the winning team's
            // first member.
            batch.pushSprite(sheets_[2],{0,0,512,512},0,0,144,60);
            batch.pushSolid({0,0,800,60},{0,0,0,1});
            batch.pushSolid({0,424,800,176},{0,0,0,1});
            drawText(batch,quoteLayout_,75,440);
            // Which TEAM won, as a caption (D7): the sting's own art says 青組/赤組, but the
            // report needs it in words once the bands are gone.
            if (!winnerLayout_.items.empty()) drawText(batch,winnerLayout_,560,28,.7f);
        }
        if (timeline_.phase() == ResultPhase::Report) {
            batch.pushSolid({0,0,800,600},{0,0,0,.75f});
            // FUN_00633ca0: activity report header at (0,320,288,64).
            batch.pushSprite(sheets_[1],{0,320,288,64},144,32,400,28);
            if (state_.resultWinner < 0) drawText(batch,drawLayout_,350,440);
            // FUN_0063a740:64-85: rows i = 0..3 at y = 100 + 72*i, the controller/COM badge
            // at x = 150, revealed one row per 30 frames after a 30-frame lead-in. The port
            // adds each participant's combo and statistics at the recovered text column.
            const int revealed = resultRowsRevealed(timeline_.frame());
            for (int i = 0; i < participantCount_ && i < revealed; ++i) {
                const ResultRow row = resultRow(i);
                const int controller = std::clamp(participants_[i].controller,0,4);
                batch.pushSprite(sheets_[1],{controller*64.f,384,64,32},0,0,row.badgeX,row.badgeY);
                drawText(batch,rowLayout_[i],row.textX,row.textY,.55f);
                drawText(batch,statsLayout_[i],row.textX,row.textY+24.f,.55f);
            }
        }
    }
private:
    void drawText(SpriteRenderer& batch, const TextLayout& layout, float x, float y, float scale=1) const {
        drawCaptionLayout(batch,text_,layout,textSlot_,bitmapSlot_,x,y,scale);
    }
    FrontendState& state_;
    ResultTimeline timeline_;
    ResultQuote quote_;
    bool voiceTaken_ = false;
    TextLayer text_;
    TextLayout quoteLayout_, drawLayout_, statsLayout_[kParticipantCount];
    TextLayout rowLayout_[kParticipantCount], winnerLayout_;
    Participant participants_[kParticipantCount];
    int participantCount_ = 0;
    mutable int bitmapSlot_ = -1;
    int sheets_[3] = {-1,-1,-1}, textSlot_=-1, sound_=-1;
};
}
std::unique_ptr<Screen> makeResultScreen(SpriteRenderer& batch, FrontendState& state,std::string& error) {
    auto screen = std::make_unique<ResultScreen>(batch,state,error);
    if (!screen->loaded()) return nullptr;
    return screen;
}
}
