#include "ui/screen_select.h"
#include "input/synthetic_pad.h"
#include <cstdio>

int main() {
    int failures=0;
    auto check=[&](bool value,const char* name) { if(!value) {std::fprintf(stderr,"FAIL %s\n",name); ++failures;} };
    ui::FrontendState state;
    ui::SelectMenu menu(state);
    ui::ScreenInput confirm; confirm.confirm=true;
    ui::ScreenInput cancel; cancel.cancel=true;
    ui::ScreenInput up; up.up=true;
    ui::ScreenInput down; down.down=true;
    ui::ScreenInput right; right.right=true;
    ui::FrontendState costumeState;
    ui::SelectMenu costumeMenu(costumeState);
    costumeMenu.update(confirm);
    costumeMenu.update(confirm);
    for (int i=0;i<4;++i) costumeMenu.update(right);
    check(costumeState.slots[0].costume==4,"Rena's fifth costume is selectable");
    costumeMenu.update(cancel);
    costumeMenu.update(right); costumeMenu.update(up); costumeMenu.update(up);
    check(costumeState.slots[0].character==12 && costumeState.slots[0].costume==0,
          "changing to Kasai resets the out-of-range costume");
    menu.update(confirm);
    check(menu.phase()==ui::SelectPhase::Character,"team claims panel");
    menu.update(up);
    check(state.slots[0].character==3,"diamond nearest vertical cell");
    menu.update(confirm);
    menu.update(up);
    check(state.slots[0].weapon==2,"weapon wraps");
    menu.update(confirm);
    menu.update(up);
    check(state.slots[0].hypermode==2,"hypermode wraps");
    menu.update(cancel);
    check(menu.phase()==ui::SelectPhase::Weapon,"mode cancel returns weapon");
    menu.update(confirm); menu.update(confirm); menu.update(confirm);
    check(state.slots[0].ready && state.slots[0].controller==0,"human locks choices");
    for(int i=0;i<16;++i) menu.tick();
    check(menu.phase()==ui::SelectPhase::Team,"ready releases controller after 16 frames");
    menu.update(cancel);
    check(state.slots[0].character==-1,"cancel clears configured panel");
    menu.update(up);
    check(menu.cursor()==2,"team cursor reaches decide");
    check(menu.update(confirm)==ui::SelectAction::Stage,"decide advances stage");
    check(state.stagePage && state.slots[3].controller==4 && state.slots[3].character>=0,"unset slots become COM");
    ui::FrontendState multi;
    ui::SelectMenu controllers(multi);
    controllers.update(confirm,0);
    controllers.update(confirm,2);
    check(controllers.owner(0)==0 && controllers.owner(2)==2,"independent controller claims");
    controllers.update(cancel,0);
    check(controllers.owner(2)==2,"cancel does not clear other controller");
    ui::FrontendState frameState;
    ui::SelectMenu frameMenu(frameState);
    ui::ScreenInput simultaneous;
    simultaneous.separatePlayers=true;
    simultaneous.players[0].confirm=true;
    simultaneous.players[2].confirm=true;
    frameMenu.updateFrame(simultaneous);
    check(frameMenu.owner(0)==0 && frameMenu.owner(2)==2,"simultaneous claims stay separate");
    simultaneous.players={};
    simultaneous.players[0].up=true;
    simultaneous.players[2].right=true;
    frameMenu.updateFrame(simultaneous);
    check(frameState.slots[0].character==3 && frameState.slots[2].character!=3,"simultaneous directions are independent");
    simultaneous.players={};
    simultaneous.players[0].cancel=true;
    simultaneous.players[2].confirm=true;
    frameMenu.updateFrame(simultaneous);
    check(frameState.slots[0].character==-1 && frameMenu.phase(2)==ui::SelectPhase::Weapon,"cancel does not swallow another controller confirm");
    ui::ScreenInput invalid; invalid.confirm=true; invalid.player=-1;
    check(frameMenu.updateFrame(invalid)==ui::SelectAction::None,"invalid player is ignored");
    ui::FrontendState randomA,randomB;
    randomA.randomState=randomB.randomState=42;
    ui::SelectMenu randomMenuA(randomA),randomMenuB(randomB);
    randomMenuA.update(up); randomMenuB.update(up);
    randomMenuA.update(confirm); randomMenuB.update(confirm);
    for (int i=0;i<4;++i) {
        const auto& a=randomA.slots[i]; const auto& b=randomB.slots[i];
        check(a.character==b.character && a.weapon==b.weapon && a.hypermode==b.hypermode && a.costume==b.costume,"seed reproduces complete COM choices");
        check(a.character>=0 && a.character<16 && a.weapon>=0 && a.weapon<(a.character<14?3:2) && a.hypermode>=0 && a.hypermode<3 && a.costume>=0 && a.costume<ui::kSelectCostumes[a.character],"random COM choices stay in recovered bounds");
    }
    check(randomA.randomState!=42,"COM autofill advances random stream");
    // Issue #13: the four pad-less controllers of a --local-players run walk the selection
    // with the synthetic menu pattern and open the stage page with four DISTINCT characters
    // and their own controllers. The picks are the pattern's documented ones — the diamond's
    // 0/2/4/1 neighbours, which are the roster entries whose slot-0 items join on this install
    // (Satoko, Oishi, Akasaka, Irie, Chie, Hanyu and Takano fail that join today).
    ui::FrontendState rosterState;
    ui::SelectMenu rosterMenu(rosterState);
    ui::SelectAction last = ui::SelectAction::None;
    for (uint64_t t = 0; t <= 200 && last != ui::SelectAction::Stage; ++t) {
        rosterMenu.tick();
        ui::ScreenInput frame;
        frame.separatePlayers = true;
        for (int c = 0; c < 4; ++c) {
            const auto pad = fnd::input::syntheticMenuPadState(c, t);
            auto& buttons = frame.players[c];
            buttons.up = pad.up; buttons.down = pad.down;
            buttons.left = pad.left; buttons.right = pad.right;
            buttons.confirm = pad.confirm; buttons.cancel = pad.cancel;
        }
        last = rosterMenu.updateFrame(frame);
    }
    check(last == ui::SelectAction::Stage, "the four synthetic controllers open the stage page");
    check(rosterState.stagePage, "the stage page is set");
    const int expected[4] = {0, 2, 4, 1};
    for (int i = 0; i < 4; ++i) {
        check(rosterState.slots[i].character == expected[i], "the panel picks its documented character");
        check(rosterState.slots[i].controller == i, "the panel keeps its own controller");
        check(rosterState.slots[i].ready, "the panel is ready");
    }
    std::printf("select_menu_test: %d failures\n",failures);
    return failures ? 1 : 0;
}
