#include "ui/screen_select.h"
#include "assets/asset_source.h"
#include "assets/exe_strings.h"
#include "ui/frontend_launch.h"
#include "ui/hud_atlas.h"
#include "ui/screen_stage_select.h"
#include <algorithm>
#include <cstdio>

namespace ui {
namespace {
int cycle(int value, int delta, int count) { return (value + count + delta) % count; }
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
}
int SelectMenu::panel(int c) const { return cursor_[c] % 3 + cursor_[c] / 3 * 2; }
int SelectMenu::owner(int p) const {
    for (int c = 0; c < 4; ++c)
        if (phase_[c] != SelectPhase::Team && panel(c) == p) return c;
    return -1;
}
void SelectMenu::tick() {
    for (int c=0;c<4;++c)
        if (phase_[c] == SelectPhase::Ready && --cooldown_[c] <= 0) phase_[c] = SelectPhase::Team;
}
SelectAction SelectMenu::update(const ScreenInput& in, int c) {
    if (c < 0 || c >= 4) return SelectAction::None;
    int& pos = cursor_[c];
    if(pos<0) {
        if(!(in.confirm || in.cancel || in.up || in.down || in.left || in.right)) return SelectAction::None;
        pos=c+(c>1);
    }
    SelectPhase& phase = phase_[c];
    if (phase == SelectPhase::Ready) return SelectAction::None;
    if (phase == SelectPhase::Team) {
        if (in.left || in.right) pos = cycle(pos / 3, in.left ? -1 : 1, 2) * 3 + pos % 3;
        else if (in.up || in.down) pos = cycle(pos % 3, in.up ? -1 : 1, 3) + pos / 3 * 3;
        if (in.confirm && pos % 3 == 2) {
            if (pos == 5) return SelectAction::Back;
            for (auto p : phase_) if (p != SelectPhase::Team) return SelectAction::None;
            // FUN_0040d130: unset panels become COM with random character, weapon, mode and costume.
            for (int i=0;i<4;++i) if (state_.slots[i].character < 0) {
                auto& slot = state_.slots[i];
                slot.character = state_.nextRandom() % 16;
                slot.weapon = state_.nextRandom() % (slot.character < 14 ? 3 : 2);
                slot.hypermode = state_.nextRandom() % 3;
                slot.costume = state_.nextRandom() % kSelectCostumes[slot.character];
                slot.controller = 4;
            }
            state_.stagePage = true;
            return SelectAction::Stage;
        }
        if (pos % 3 < 2) {
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
                cursorX_[c] = kSelectRosterX[0] * 48.f;
                cursorY_[c] = kSelectRosterY[0] * 36.f;
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
            // PORT RULE (issue #41): the cursor may sit in empty space with character == -1,
            // and a panel with nothing selected must not confirm its way forward. The original
            // instead rolls a RANDOM character for the empty panel (FUN_00409340:305-317), and
            // this port's version of that roll is the COM autofill the stage page applies to
            // panels that are still unset — so refusing here leaves the panel for it. The
            // press itself still plays the confirm SE, as the original's unconditional
            // FUN_0064aed0(0) at :304 does.
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
            const float dx = kSelectRosterX[slot.character] * 48.f - cursorX_[c];
            const float dy = kSelectRosterY[slot.character] * 36.f - cursorY_[c];
            if (dx * dx + dy * dy < 400.f) {
                cursorX_[c] = kSelectRosterX[slot.character] * 48.f;
                cursorY_[c] = kSelectRosterY[slot.character] * 36.f;
            }
        }
        // Selection, every call (:272-300): the 50-unit pass (2500 squared) is the fallback and
        // the 30-unit pass (900) overrides it. Both take the FIRST icon in roster order, so one
        // pass recording each pass's first hit is the original's two loops.
        int outer = -1, inner = -1;
        for (int i = 0; i < 16; ++i) {
            const float dx = kSelectRosterX[i] * 48.f - cursorX_[c];
            const float dy = kSelectRosterY[i] * 36.f - cursorY_[c];
            const float distance = dx * dx + dy * dy;
            if (outer < 0 && distance < 2500.f) outer = i;
            if (inner < 0 && distance < 900.f) inner = i;
        }
        const int chosen = inner >= 0 ? inner : outer;
        if (chosen != slot.character) {
            slot.character = chosen;
            if (chosen < 0) return SelectAction::None;   // empty space is silent (:294)
            slot.costume %= kSelectCostumes[chosen];
            return SelectAction::Changed;   // the recovered cursor SE, FUN_0064aed0(2)
        }
        return SelectAction::None;
    }
    if (in.left || in.right) slot.costume = cycle(slot.costume,in.left ? -1 : 1,kSelectCostumes[slot.character]);
    if (phase == SelectPhase::Weapon) {
        if (in.up || in.down) slot.weapon = cycle(slot.weapon,in.up ? -1 : 1,slot.character<14 ? 3 : 2);
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

SelectAction SelectMenu::updateFrame(const ScreenInput& in, int* sound) {
    auto apply = [&](const ScreenInput& playerInput, int player) {
        const auto action = update(playerInput,player);
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
    menu_.tick();
    if (!in.separatePlayers && (in.player < 0 || in.player >= 4)) return ScreenId::Select;
    if(stage_) {
        ScreenId next=stage_->update(in);
        sound_=stage_->takeSound();
        if(!state_.stagePage) stage_.reset();
        return next;
    }
    std::array<SelectPhase,4> previous;
    for (int player=0;player<4;++player) previous[player]=menu_.phase(player);
    SelectAction action=menu_.updateFrame(in,&sound_);
    for (int player=0;player<4;++player) {
        if (!in.separatePlayers && player != in.player) continue;
        const SelectPhase current=menu_.phase(player);
        if (current == SelectPhase::Ready && previous[player] != SelectPhase::Ready) sound_=3;
        if (previous[player] == SelectPhase::Character && current == SelectPhase::Weapon) {
            const char* character = frontendCharacterDirectory(state_.slots[menu_.panel(player)].character);
            if (character) voice_=std::string("data/voice/entry/")+character;
        }
    }
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
    sprite(shared_[0],{0,0,800,600},0,0,0,0);
    // Portrait pivots are (128,256), resolving the apparent 150px panel-anchor mismatch (§2.3).
    for(int i=0;i<4;++i) if(state_.slots[i].character>=0)
        sprite(portraits_[state_.slots[i].character],{0,0,256,256},128,256,(i/2)*400.f+200,(i%2)*300.f+300,1,i>=2);
    sprite(shared_[1],{0,0,800,600},0,0,0,0);
    for(int c=0;c<4;++c) if(menu_.phase(c)==SelectPhase::Team) {
        int pos=menu_.cursor(c);
        if(pos<0) continue;
        int col=pos/3,row=pos%3;
        if(row<2) sprite(shared_[6+c],{0,float((row+col)%2)*300,400,300},200,0,col*400.f+200,row*300.f);
        else sprite(shared_[2],{float(c)*128,384,128,128},64,64,col==0?336:464,550);
    }
    for(int i:kSelectRosterOrder) {
        bool selected=false;
        for(const auto& slot:state_.slots) selected |= slot.character==i;
        int cell=selected ? (frames_%40)/10+1 : 0;
        sprite(chibi_[i],{float(cell%3)*80,float(cell/3)*128,80,128},40,80,
               kSelectRosterX[i]*48.f+400,kSelectRosterY[i]*36.f+(selected?150:160));
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
        int header=phase==SelectPhase::Character?0:phase==SelectPhase::Weapon?1:phase==SelectPhase::Hypermode?3:4;
        sprite(shared_[2],{0,float(header)*32,320,32},160,16,x,y+50);
        if(phase==SelectPhase::Character) {
            // The nameplate exists only for a real selection: the free cursor can sit in empty
            // space with character == -1 (FUN_00409340:294).
            if(slot.character>=0)
                sprite(shared_[5],{float(slot.character/8)*256,float(slot.character%8)*64,256,64},128,32,x,y+90);
            // The marker rides the CURSOR's position, not the selected icon's (+400/+150 are
            // the icon draw's own offsets): the two come apart by up to the 30-unit select
            // radius, and the cursor has to stay visible while it is over empty space. PORT
            // RULE — the marker's anchor; the positions themselves are recovered.
            sprite(shared_[2],{owner*128.f,384,128,128},64,64,menu_.cursorX(owner)+400,menu_.cursorY(owner)+150);
        } else if(phase==SelectPhase::Controller) {
            for(int row=0;row<2;++row) sprite(shared_[4],{0,float(320+row*128),256,64},128,32,x+row*8,y+110+row*20,1,false,{1,1,1,slot.controller==(row==0?owner:4)?1.f:.5f});
        } else {
            int count=phase==SelectPhase::Weapon?(slot.character<14?3:2):3;
            int choice=phase==SelectPhase::Weapon?slot.weapon:slot.hypermode;
            for(int row=count-1;row>=0;--row) sprite(phase==SelectPhase::Weapon?weapons_[slot.character]:shared_[2],
                {phase==SelectPhase::Weapon?0.f:320.f,float((choice+row)%count)*64,phase==SelectPhase::Weapon?256.f:192.f,64},phase==SelectPhase::Weapon?128.f:96.f,32,x+row*8,y+110+row*20,1,false,{1,1,1,1.f/(1<<row)});
            sprite(phase==SelectPhase::Weapon?weapons_[slot.character]:shared_[4],
                {phase==SelectPhase::Weapon?256.f:0.f,float(choice+(phase==SelectPhase::Weapon?0:2))*64,256,64},128,32,x,y+200);
        }
        if(phase!=SelectPhase::Character) sprite(shared_[2],{384,192,64,128},32,64,x,y+110);
    }
    sprite(shared_[3],{256,64,128,64},64,32,336,550);
    sprite(shared_[3],{384,64,128,64},64,32,464,550);
}
std::unique_ptr<Screen> makeSelectScreen(SpriteRenderer& batch,FrontendState& state,std::string& error) {
    auto screen=std::make_unique<SelectScreen>(batch,state,error);
    return screen->loaded() ? std::move(screen) : nullptr;
}
}
