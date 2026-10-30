#include "frontend/screen_select.h"
#include "assets/asset_source.h"
#include "assets/exe_strings.h"
#include "battle/weapon_definition.h"
#include "frontend/frontend_launch.h"
#include "hud/hud_atlas.h"
#include "frontend/screen_stage_select.h"
#include <algorithm>
#include <cstdio>

namespace ui {
namespace {
// The roster tables in screen_select.h are transcriptions of the binary's 16-character roster;
// gameplay::kCharacterCount is what the launch validates against, so the two must agree.
static_assert(sizeof(kSelectRosterX) / sizeof(kSelectRosterX[0]) ==
                  (size_t)gameplay::kCharacterCount,
              "the roster tables must cover every character gameplay knows");
int cycle(int value, int delta, int count) { return (value + count + delta) % count; }
// The team cursor's grid, the original's own cell numbering (+0x3c48): two columns of three
// rows, packed column-major (cursor = column * kSelectPanelRows + row). The bottom row is the
// decide row — its left cell goes to the stage page and its right cell is back — and the other
// four cells are panels 0..3, which is why a panel's own cell is not simply its number.
constexpr int kSelectPanelCols = 2;
constexpr int kSelectPanelRows = 3;
constexpr int kSelectDecideCell = kSelectPanelRows - 1;   // column 0, bottom row
constexpr int kSelectBackCell = (kSelectPanelCols - 1) * kSelectPanelRows + kSelectDecideCell;
// The cell a panel owns: panel()'s inverse, so the four panels sit on cells 0, 1, 3 and 4 and
// the decide row's cells (2 and 5) belong to no panel.
int cellForPanel(int panel) {
    return panel / kSelectPanelCols * kSelectPanelRows + panel % kSelectPanelCols;
}
// The per-character penalty costume cell (VA 0x6b72a0 in DaybreakDX.exe, 16 bytes; 0 = the
// character has none). Read from the installed exe, like the earned-title names, so the table
// stays out of this repository. -1 when the exe is not reachable.
int penaltyCostume(int character) {
    static std::vector<uint8_t> table;
    // Loaded on first use WITH an install open and cached only on success: a screen built before
    // the install exists (a unit test, or a capture path that opens it later) must not latch an
    // empty table for the rest of the process.
    if (table.empty()) {
        const std::string& install = fnd::assets::assetSource().installDir();
        if (install.empty()) return -1;
        std::vector<uint8_t> loaded;
        std::string error;
        if (!fnd::assets::readExeBytes(install + "/DaybreakDX.exe", 0x6b72a0, 16, loaded, error)) {
            static bool reported = false;
            if (!reported) {
                reported = true;
                std::fprintf(stderr, "[select] penalty costumes: %s\n", error.c_str());
            }
            return -1;
        }
        table = std::move(loaded);
    }
    if (character < 0 || (size_t)character >= table.size()) return -1;
    const int value = table[(size_t)character];
    return value > 0 ? value : -1;
}

// The roster icon's own position in the free cursor's units (FUN_00409340's +0x3cd8/+0x3ce8
// space): its kSelectRosterX/Y cell times the icon's 48x36 pitch. The draw, the magnet and
// both selection passes all measure against this one pair.
struct RosterPos { float x = 0.f, y = 0.f; };
RosterPos rosterPos(int i) {
    return RosterPos{kSelectRosterX[i] * 48.f, kSelectRosterY[i] * 36.f};
}

// The original's two selection passes (FUN_00409340:272-286 and the 30-unit pass beside it) in
// one walk: the 50-unit pass (2500 squared) is the fallback and the 30-unit pass (900) overrides
// it. Both take the FIRST icon in roster order, so one walk recording each pass's first hit is
// the original's two loops — and the confirm path's off-grid test reads the same outer pass.
struct RosterHits { int outer = -1, inner = -1; };
RosterHits nearestRosterIcon(float x, float y) {
    RosterHits hits;
    for (int i = 0; i < gameplay::kCharacterCount; ++i) {
        const RosterPos p = rosterPos(i);
        const float dx = p.x - x;
        const float dy = p.y - y;
        const float distance = dx * dx + dy * dy;
        if (hits.outer < 0 && distance < 2500.f) hits.outer = i;
        if (hits.inner < 0 && distance < 900.f) hits.inner = i;
    }
    return hits;
}
}
int SelectMenu::panel(int c) const {
    return cursor_[c] % kSelectPanelRows + cursor_[c] / kSelectPanelRows * kSelectPanelCols;
}
int SelectMenu::owner(int p) const {
    for (int c = 0; c < 4; ++c)
        if (phase_[c] != SelectPhase::Team && panel(c) == p) return c;
    return -1;
}
// The outer pass of the original's two selection loops (FUN_00409340:272-286): nothing within
// 50 units (2500 squared) means the cursor is off the diamond. The 30-unit inner pass is the
// override and cannot reach further, so this one test decides the question.
bool SelectMenu::cursorOffGrid(int c) const {
    if (c < 0 || c >= 4) return false;
    return nearestRosterIcon(cursorX_[c], cursorY_[c]).outer < 0;
}
void SelectMenu::tick() {
    for (int c=0;c<4;++c)
        if (phase_[c] == SelectPhase::Ready && --cooldown_[c] <= 0) phase_[c] = SelectPhase::Team;
}
SelectAction SelectMenu::update(const ScreenInput& in, int c, SelectTransition* transition) {
    if (c < 0 || c >= 4) return SelectAction::None;
    const SelectPhase before = phase_[c];
    const SelectAction action = updatePanel(in, c);
    // FUN_00409340:589-595, the update's own tail: a phase change during this call restarts
    // this controller's row slide at 300.0 and the same call already steps it once.
    slide_.step(c, phase_[c] != before);
    if (transition) *transition = SelectTransition{before, phase_[c]};
    return action;
}
SelectAction SelectMenu::updatePanel(const ScreenInput& in, int c) {
    int& pos = cursor_[c];
    if(pos<0) {
        if(!(in.confirm || in.cancel || in.up || in.down || in.left || in.right)) return SelectAction::None;
        pos=cellForPanel(c);
    }
    SelectPhase& phase = phase_[c];
    if (phase == SelectPhase::Ready) return SelectAction::None;
    if (phase == SelectPhase::Team) {
        if (in.left || in.right)
            pos = cycle(pos / kSelectPanelRows, in.left ? -1 : 1, kSelectPanelCols) * kSelectPanelRows +
                  pos % kSelectPanelRows;
        else if (in.up || in.down)
            pos = cycle(pos % kSelectPanelRows, in.up ? -1 : 1, kSelectPanelRows) +
                  pos / kSelectPanelRows * kSelectPanelRows;
        if (in.confirm && pos % kSelectPanelRows == kSelectDecideCell) {
            if (pos == kSelectBackCell) return SelectAction::Back;
            for (auto p : phase_) if (p != SelectPhase::Team) return SelectAction::None;
            // FUN_0040d130: unset panels become COM with random character, weapon, mode and costume.
            for (int i=0;i<4;++i) if (state_.slots[i].character < 0) {
                auto& slot = state_.slots[i];
                slot.character = state_.nextRandom() % gameplay::kCharacterCount;
                slot.weapon =
                    state_.nextRandom() % gameplay::weaponCountForCharacter(slot.character);
                slot.hypermode = state_.nextRandom() % 3;
                slot.costume = state_.nextRandom() % kSelectCostumes[slot.character];
                slot.controller = 4;
            }
            state_.stagePage = true;
            return SelectAction::Stage;
        }
        if (pos % kSelectPanelRows < kSelectDecideCell) {
            auto& slot = state_.slots[panel(c)];
            if (in.cancel && owner(panel(c)) < 0 && (slot.controller == c || slot.controller == 4)) {
                slot = FrontendSlot{};
                return SelectAction::Changed;
            }
            if (in.confirm && owner(panel(c)) < 0 && slot.character < 0) {
                // FUN_00409340:114-127: the team confirm claims the panel, puts it on
                // character 0 and seeds the free cursor (+0x3cd8/+0x3ce8) onto that
                // character's own position — which is why the character phase never opens
                // without a character under the cursor, and why the magnet's <20 window then
                // holds the panel there. Issue #45's empty-on-entry selection therefore needs
                // no special seed case: every fresh panel takes this path.
                phase = SelectPhase::Character;
                slot.character = 0;
                const RosterPos seed = rosterPos(0);
                cursorX_[c] = seed.x;
                cursorY_[c] = seed.y;
                return SelectAction::Changed;
            }
        }
        return in.cancel ? SelectAction::Back :
               (in.up || in.down || in.left || in.right ? SelectAction::Changed : SelectAction::None);
    }
    auto& slot = state_.slots[panel(c)];
    if (phase == SelectPhase::Character) {
        if (in.cancel) { slot = FrontendSlot{}; phase = SelectPhase::Team; return SelectAction::Changed; }
        if (in.confirm) {
            // Off the diamond the panel is the original's RANDOM pick (FUN_00409340:305-317):
            // the portrait has been rolling characters (see the selection step below) and the
            // confirm TAKES THE ONE SHOWING rather than rolling again, which is what makes the
            // roll feel like it "stops on" the last character. The costume is rolled here, at
            // the moment of the pick — the original's `rng() % 3` (or `% 2` for 14/15), kept to
            // the character's own costume count so a roll cannot land on a cell it does not
            // own. The original then goes to phase 4 (Hypermode), skipping Weapon, and so does
            // this: the weapon is clamped to the new character's count so it cannot be stale.
            if (cursorOffGrid(c)) {
                slot.character = rolled_[panel(c)];
                slot.costume = (int)(state_.nextRandom() %
                                     (uint32_t)kSelectCostumes[slot.character]);
                slot.weapon =
                    std::min(slot.weapon, gameplay::weaponCountForCharacter(slot.character) - 1);
                phase = SelectPhase::Hypermode;
                return SelectAction::Changed;
            }
            if (slot.character >= 0) {
                // The penalty game's costume (issue #20): a player who earned the penalty title
                // last round has their costume forced to the character's own penalty cell
                // (FUN_00409340:165-172 reads DAT_006b72a0[character]; 0 means that character has
                // none). The original also marks the panel forced/auto-ready there — that part is
                // NOT implemented, so the player can still change this costume. Session state only:
                // penaltyDecided lives in FrontendState and is never persisted.
                const int penalty = penaltyCostume(slot.character);
                if (penalty >= 0 && state_.penaltyDecided[panel(c)]) slot.costume = penalty;
                phase = SelectPhase::Weapon;
            }
            return SelectAction::Changed;
        }
        // The free cursor (FUN_00409340:232-256): a fixed RATE per call on the SIGN of the
        // stick — 4.0/tick horizontally (0x40800000) and 3.0/tick vertically (0x40400000) —
        // clamped to [-200,200] (0xc3480000/0x43480000) and [-60,300] (0xc2700000/0x43960000).
        // The order of the clamps is the original's; the two axes are independent. What
        // accumulates is the HELD direction (screen.h's `*Held` fields): the original reads the
        // stick every call, and a press edge alone would move the cursor 4 units and hand it
        // straight back to the magnet below.
        const bool left = in.leftHeld, right = in.rightHeld;
        const bool up = in.upHeld, down = in.downHeld;
        if (left) cursorX_[c] -= 4.f; else if (right) cursorX_[c] += 4.f;
        if (up) cursorY_[c] -= 3.f; else if (down) cursorY_[c] += 3.f;
        cursorX_[c] = std::clamp(cursorX_[c], -200.f, 200.f);
        cursorY_[c] = std::clamp(cursorY_[c], -60.f, 300.f);
        // The magnet (:257-270), only while the stick is CENTRED: a cursor within 20 units
        // (400 squared) of the currently selected character snaps exactly onto it, so a
        // release settles on the icon it picked. A panel with no selection has nothing to
        // snap to, which is also how the original guards it (`-1 < character`).
        if (!left && !right && !up && !down && slot.character >= 0) {
            const RosterPos target = rosterPos(slot.character);
            const float dx = target.x - cursorX_[c];
            const float dy = target.y - cursorY_[c];
            if (dx * dx + dy * dy < 400.f) {
                cursorX_[c] = target.x;
                cursorY_[c] = target.y;
            }
        }
        // Selection, every call (:272-300): see nearestRosterIcon for the two passes.
        const RosterHits hits = nearestRosterIcon(cursorX_[c], cursorY_[c]);
        const int chosen = hits.inner >= 0 ? hits.inner : hits.outer;
        if (chosen < 0) {
            // Off the diamond: the panel's PORTRAIT ROLLS THROUGH RANDOM CHARACTERS, one per
            // tick, and a confirm takes whichever is showing (the branch above). The original
            // reaches the same place from the other end — its confirm rolls `rng() % 16` for an
            // empty panel (FUN_00409340:305-317) — so the two agree on what a random pick is;
            // rolling here as well is what makes the portrait move before the press, which the
            // recovered code alone does not show but the original's screen does.
            //
            // It writes rolled_, NOT the slot. The chibi draw animates every character any
            // slot matches (FUN_0040b2b0:106-131 tests the confirmed field), so a roll written
            // into the slot made all sixteen chibis twitch as it cycled; the slot keeps meaning
            // "the cursor is on this one, or it is confirmed", which is what the original's
            // screen shows — the chibis are still while the portrait rolls.
            //
            // Silent on purpose: the portrait is redrawn every frame, so the roll needs no
            // action, and returning Changed would play the cursor SE (updateFrame maps a
            // non-None action with no button to sound 2) — one roll per tick would be a machine
            // gun. Empty space stays silent, which is also the original's own rule at :294.
            slot.character = -1;
            rolled_[panel(c)] = (int)(state_.nextRandom() % (uint32_t)gameplay::kCharacterCount);
            return SelectAction::None;
        }
        if (chosen != slot.character) {
            slot.character = chosen;
            slot.costume %= kSelectCostumes[chosen];
            return SelectAction::Changed;   // the recovered cursor SE, FUN_0064aed0(2)
        }
        return SelectAction::None;
    }
    if (in.left || in.right) slot.costume = cycle(slot.costume,in.left ? -1 : 1,kSelectCostumes[slot.character]);
    if (phase == SelectPhase::Weapon) {
        if (in.up || in.down)
            slot.weapon = cycle(slot.weapon, in.up ? -1 : 1,
                               gameplay::weaponCountForCharacter(slot.character));
        if (in.confirm) phase = SelectPhase::Hypermode;
        else if (in.cancel) { phase = SelectPhase::Character; slot.weapon = 0; }
    } else if (phase == SelectPhase::Hypermode) {
        if (in.up || in.down) slot.hypermode = cycle(slot.hypermode,in.up ? -1 : 1,3);
        if (in.confirm) { phase = SelectPhase::Controller; slot.controller = c; }
        else if (in.cancel) phase = SelectPhase::Weapon;
    } else if (phase == SelectPhase::Controller) {
        if (in.up || in.down) slot.controller = slot.controller == 4 ? c : 4;
        if (in.confirm) {
            // A controller may drive one panel, FUN_00409340 +0x3ca0.
            if (slot.controller != 4)
                for (int i=0;i<4;++i) if (i!=panel(c) && state_.slots[i].controller==c)
                    state_.slots[i].controller=4;
            slot.ready=true; phase=SelectPhase::Ready; cooldown_[c]=16;
        } else if (in.cancel) phase=SelectPhase::Hypermode;
    }
    return in.confirm || in.cancel || in.up || in.down || in.left || in.right ? SelectAction::Changed : SelectAction::None;
}

SelectAction SelectMenu::updateFrame(const ScreenInput& in, int* sound,
                                     std::array<SelectTransition, 4>* transitions) {
    if (transitions) transitions->fill(SelectTransition{});
    auto apply = [&](const ScreenInput& playerInput, int player) {
        SelectTransition transition;
        const auto action = update(playerInput, player, &transition);
        if (transitions) (*transitions)[(size_t)player] = transition;
        if (sound && action != SelectAction::None)
            *sound = playerInput.cancel ? 1 : playerInput.confirm ? 0 : 2;
        return action;
    };
    if (!in.separatePlayers) return apply(in,in.player);
    SelectAction result = SelectAction::None;
    for (int player = 0; player < 4; ++player) {
        const auto& buttons = in.players[player];
        ScreenInput playerInput;
        playerInput.up=buttons.up; playerInput.down=buttons.down;
        playerInput.left=buttons.left; playerInput.right=buttons.right;
        playerInput.upHeld=buttons.upHeld; playerInput.downHeld=buttons.downHeld;
        playerInput.leftHeld=buttons.leftHeld; playerInput.rightHeld=buttons.rightHeld;
        playerInput.confirm=buttons.confirm; playerInput.cancel=buttons.cancel;
        const auto action = apply(playerInput,player);
        if (action == SelectAction::Stage || action == SelectAction::Back) result = action;
        else if (result == SelectAction::None) result = action;
    }
    return result;
}

std::vector<std::string> selectEntryVoices(
    const FrontendState& state, const SelectMenu& menu, const ScreenInput& input,
    const std::array<SelectTransition, 4>& transitions) {
    std::vector<std::string> voices;
    auto collect = [&](int controller) {
        const SelectTransition& transition = transitions[(size_t)controller];
        if (transition.from != SelectPhase::Controller ||
            transition.to != SelectPhase::Ready)
            return;
        const int selectedPanel = menu.panel(controller);
        if (selectedPanel < 0 || selectedPanel >= (int)state.slots.size()) return;
        const char* character =
            frontendCharacterDirectory(state.slots[(size_t)selectedPanel].character);
        if (character) voices.emplace_back(std::string("data/voice/entry/") + character);
    };

    if (input.separatePlayers) {
        for (int controller = 0; controller < 4; ++controller) collect(controller);
    } else if (input.player >= 0 && input.player < 4) {
        collect(input.player);
    }
    return voices;
}

SelectScreen::SelectScreen(SpriteRenderer& batch, FrontendState& state, std::string& error)
    : state_(state), menu_(state), batch_(batch) {
    // The scene's own state, as FUN_00408330:143-158 initialises it: this constructor IS the
    // original's scene-3 constructor, so an entry that follows a battle (FUN_00403b70 returns 3)
    // starts with the same empty selection as a fresh title->select trip. Settings that live
    // outside the scene survive — see FrontendState::beginSelection.
    state_.beginSelection();
    const char* paths[] = {"bg00","bg01","p00","P01","P02","p03","s1p","s2p","s3p","s4p"};
    auto load = [&](const char* stem,int& slot) {
        std::string failure;
        slot=-1;
        if (!uploadCnvSheet(batch,stem,slot,failure) && error.empty()) error=failure;
    };
    char path[64];
    for(int i=0;i<10;++i) { std::snprintf(path,sizeof(path),"data/select/%s",paths[i]); load(path,shared_[i]); }
    for(int i=0;i<16;++i) {
        std::snprintf(path,sizeof(path),"data/select/%02d",i); load(path,portraits_[i]);
        std::snprintf(path,sizeof(path),"data/select/i%02d",i); load(path,chibi_[i]);
        std::snprintf(path,sizeof(path),"data/select/cos%02d",i); load(path,costumes_[i]);
        std::snprintf(path,sizeof(path),"data/select/w%02d",i); load(path,weapons_[i]);
    }
    if (state_.stagePage) stage_=makeStageSelectScreen(batch,state_,error);
}
bool SelectScreen::loaded() const {
    for (int i : shared_) if(i<0) return false;
    for(int i=0;i<16;++i) if(portraits_[i]<0 || chibi_[i]<0 || costumes_[i]<0 || weapons_[i]<0) return false;
    return !state_.stagePage || stage_!=nullptr;
}
ScreenId SelectScreen::update(const ScreenInput& in) {
    ++frames_;
    // FUN_004090a0:9/24-26: the scene's tick, then the entry ramp, then the panels' input.
    reveal_.tick((int)frames_);
    menu_.tick();
    if (!in.separatePlayers && (in.player < 0 || in.player >= 4)) return ScreenId::Select;
    if(stage_) {
        ScreenId next=stage_->update(in);
        sound_=stage_->takeSound();
        if(!state_.stagePage) stage_.reset();
        return next;
    }
    std::array<SelectTransition,4> transitions;
    SelectAction action=menu_.updateFrame(in,&sound_,&transitions);
    for (int player=0;player<4;++player) {
        if (!in.separatePlayers && player != in.player) continue;
        const SelectTransition& transition=transitions[(size_t)player];
        if (transition.entered(SelectPhase::Ready)) sound_=3;
    }
    // FUN_00409340 @0x409340:178-214 chooses the entry voice in the branch that commits the
    // controller/COM choice and enters Ready. Preserve every local player's event
    // when multiple panels confirm on one simulation tick.
    voiceQueue_.append(selectEntryVoices(state_, menu_, in, transitions));
    if(action==SelectAction::Back) return ScreenId::Title;
    if(action==SelectAction::Stage) {
        std::string error;
        stage_=makeStageSelectScreen(batch_,state_,error);
        if(!stage_) { state_.stagePage=false; std::fprintf(stderr,"[select] %s\n",error.c_str()); }
    }
    return ScreenId::Select;
}
void SelectScreen::draw(SpriteRenderer& b) const {
    if(stage_) { stage_->draw(b); return; }
    auto sprite=[&](int tex,UiRect src,float px,float py,float x,float y,float scale=1.f,bool mirror=false,UiColor color=UiColor{}) {
        if(!mirror) { b.pushSprite(tex,src,px,py,x,y,scale,0,color); return; }
        uint32_t w=0,h=0;
        if(b.textureSize(tex,w,h)) b.pushTextured(tex,{x-(src.w-px)*scale,y-py*scale,src.w*scale,src.h*scale},
            {(src.x+src.w)/w,src.y/h,-src.w/w,src.h/h},color);
    };
    // The entry reveal's own draw: FUN_00655830's quad with an INDEPENDENT x/y scale (+0x84 /
    // +0x88), where pushSprite is the uniform FUN_00655d60 path. Same UVs, so a settled slot
    // (1,1) lands on exactly pushSprite's rect.
    auto spriteScaled=[&](int tex,UiRect src,float px,float py,float x,float y,float sx,float sy) {
        const UiRect dst=scaledSpriteDst(x,y,src.w,src.h,px,py,sx,sy);
        uint32_t w=0,h=0;
        if(dst.w<=0.f||dst.h<=0.f||!b.textureSize(tex,w,h)) return;
        b.pushTextured(tex,dst,{src.x/w,src.y/h,src.w/w,src.h/h},UiColor{});
    };
    sprite(shared_[0],{0,0,800,600},0,0,0,0);
    // Portrait pivots are (128,256), resolving the apparent 150px panel-anchor mismatch (§2.3).
    // menu_.shown(i), not the slot: off the diamond the slot is empty on purpose (so no chibi
    // animates) while the portrait keeps rolling. See SelectMenu::shown.
    for(int i=0;i<4;++i) if(menu_.shown(i)>=0)
        sprite(portraits_[menu_.shown(i)],{0,0,256,256},128,256,(i/2)*400.f+200,(i%2)*300.f+300,1,i>=2);
    sprite(shared_[1],{0,0,800,600},0,0,0,0);
    for(int c=0;c<4;++c) if(menu_.phase(c)==SelectPhase::Team) {
        int pos=menu_.cursor(c);
        if(pos<0) continue;
        int col=pos/kSelectPanelRows,row=pos%kSelectPanelRows;
        if(row<kSelectDecideCell) sprite(shared_[6+c],{0,float((row+col)%2)*300,400,300},200,0,col*400.f+200,row*300.f);
        else sprite(shared_[2],{float(c)*128,384,128,128},64,64,col==0?336:464,550);
    }
    for(int i:kSelectRosterOrder) {
        bool selected=false;
        for(const auto& slot:state_.slots) selected |= slot.character==i;
        // FUN_0040b2b0:106-131: a selected slot's idle-cycle cell, else the (2,1) flashing cell
        // while that slot's ramp is below 1.0 and (0,0) once it has settled.
        const SelectChibiCell cell=selectChibiCell(selected,(int)frames_,reveal_.revealing(i));
        // FUN_0040b2b0:96-104: the slot's ramp is the (v, 2-v) scale pair on its own chibi quad,
        // about the (40,80) pivot FUN_00408330:0x408be7 gave it.
        const RosterPos icon = rosterPos(i);
        spriteScaled(chibi_[i],{float(cell.col)*80,float(cell.row)*128,80,128},40,80,
               icon.x+400,icon.y+(selected?150:160),
               reveal_.scaleX(i),reveal_.scaleY(i));
    }
    for(int p=0;p<4;++p) {
        const auto& slot=state_.slots[p];
        float x=(p/2)*420.f+190,y=(p%2)*300.f;
        int owner=menu_.owner(p);
        auto phase=owner<0 ? SelectPhase::Team : menu_.phase(owner);
        float summary=(p/2)*660.f+70;
        if(slot.character>=0) {
            sprite(shared_[5],{float(slot.character/8)*256,float(slot.character%8)*64,256,64},128,32,summary,y+210,.5f);
            sprite(costumes_[slot.character],{float(slot.costume%3)*80,float(slot.costume/3)*128,80,128},40,80,summary,y+120,1,p<2);
            if(phase!=SelectPhase::Weapon && phase!=SelectPhase::Character) sprite(weapons_[slot.character],{0,float(slot.weapon)*64,256,64},128,32,summary,y+240,.5f);
            if(phase==SelectPhase::Controller || slot.ready) sprite(shared_[2],{320,float(slot.hypermode)*64,192,64},96,32,summary,y+265,.5f);
        }
        if(slot.ready) {
            sprite(shared_[3],{0,128,256,64},128,32,(p/2)*400.f+200,y+110);
            if(slot.controller==4) sprite(shared_[4],{0,448,256,64},128,32,summary,y+180);
            else sprite(shared_[4],{256.f+slot.controller*64.f,128,64,64},32,32,summary,y+180);
        }
        if(owner<0 || phase==SelectPhase::Ready) continue;
        // FUN_0040b2b0:0x40c09f-0x40c0c4: the owner's slide offset, signed by the panel's
        // column, moves the phase header and every draw inside the panel's phase block —
        // including the row arrow and the big choice sprite — but not the cursor marker below,
        // whose anchors are the free cursor's own (+0x3cd8/+0x3ce8).
        const float slide=rowSlideOffset(menu_.rowSlide(owner),p);
        // The phase header's cell row in shared_[2]. A switch, not an array indexed by the
        // phase: SelectPhase::Ready is 8, past every header the sheet has.
        float headerRow=4.f;
        switch (phase) {
        case SelectPhase::Character: headerRow=0.f; break;
        case SelectPhase::Weapon:    headerRow=1.f; break;
        case SelectPhase::Hypermode: headerRow=3.f; break;
        default: break;   // Controller (and Team, which has no owner) keep the last header
        }
        sprite(shared_[2],{0,headerRow*32,320,32},160,16,x+slide,y+50);
        if(phase==SelectPhase::Character) {
            // The nameplate exists only for a real selection: the free cursor can sit in empty
            // space with character == -1 (FUN_00409340:294).
            if(slot.character>=0)
                sprite(shared_[5],{float(slot.character/8)*256,float(slot.character%8)*64,256,64},128,32,x+slide,y+90);
            // The marker rides the CURSOR's position, not the selected icon's (+400/+150 are
            // the icon draw's own offsets): the two come apart by up to the 30-unit select
            // radius, and the cursor has to stay visible while it is over empty space. PORT
            // RULE — the marker's anchor; the positions themselves are recovered.
            sprite(shared_[2],{owner*128.f,384,128,128},64,64,menu_.cursorX(owner)+400,menu_.cursorY(owner)+150);
        } else if(phase==SelectPhase::Controller) {
            for(int row=0;row<2;++row) sprite(shared_[4],{0,float(320+row*128),256,64},128,32,x+slide+row*8,y+110+row*20,1,false,{1,1,1,slot.controller==(row==0?owner:4)?1.f:.5f});
        } else {
            int count=phase==SelectPhase::Weapon?gameplay::weaponCountForCharacter(slot.character):3;
            int choice=phase==SelectPhase::Weapon?slot.weapon:slot.hypermode;
            for(int row=count-1;row>=0;--row) sprite(phase==SelectPhase::Weapon?weapons_[slot.character]:shared_[2],
                {phase==SelectPhase::Weapon?0.f:320.f,float((choice+row)%count)*64,phase==SelectPhase::Weapon?256.f:192.f,64},phase==SelectPhase::Weapon?128.f:96.f,32,x+slide+row*8,y+110+row*20,1,false,{1,1,1,1.f/(1<<row)});
            sprite(phase==SelectPhase::Weapon?weapons_[slot.character]:shared_[4],
                {phase==SelectPhase::Weapon?256.f:0.f,float(choice+(phase==SelectPhase::Weapon?0:2))*64,256,64},128,32,x+slide,y+200);
        }
        if(phase!=SelectPhase::Character) sprite(shared_[2],{384,192,64,128},32,64,x+slide,y+110);
    }
    sprite(shared_[3],{256,64,128,64},64,32,336,550);
    sprite(shared_[3],{384,64,128,64},64,32,464,550);
    // FUN_0040b2b0:466-475: the entry's full-screen WHITE flash, on the scene's own tick and
    // over everything the scene drew. The black cross-fade FUN_0040b1f0:23-24 draws afterwards
    // is the screen stack's own fade in this port, so it lands on top here too.
    if(const UiColor flash=SelectFlash::color((int)frames_);flash.a>0.f)
        b.pushSolid({0,0,800,600},flash);
}
std::unique_ptr<Screen> makeSelectScreen(SpriteRenderer& batch,FrontendState& state,std::string& error) {
    auto screen=std::make_unique<SelectScreen>(batch,state,error);
    return screen->loaded() ? std::move(screen) : nullptr;
}
}
