#include "frontend/screen_select.h"
#include "frontend/frontend_launch.h"
#include "assets/asset_source.h"
#include <cstdlib>
#include <filesystem>
#include "input/synthetic_pad.h"
#include <cstdio>

int main() {
    int failures=0;
    auto check=[&](bool value,const char* name) { if(!value) {std::fprintf(stderr,"FAIL %s\n",name); ++failures;} };
    // The character phase's cursor slides while a direction is held (issue #41, FUN_00409340
    // :239-244): 4.0 units/tick horizontally, 3.0 vertically, so reaching a character takes as
    // many ticks as the distance needs — Satoko sits 36 units up from Rena's seed, and only
    // from the 15th tick (45 units) is she inside the recovered 30-unit select radius. The
    // hold carries the press edge on its first tick and the held state after it, which is what
    // main.cpp's front-end loop builds.
    auto hold=[&](ui::SelectMenu& menu,ui::ScreenInput in,int ticks) {
        for (int i=0;i<ticks;++i) {
            if (i>0) in.up=in.down=in.left=in.right=false;
            menu.update(in);
        }
    };
    ui::FrontendState state;
    ui::SelectMenu menu(state);
    ui::ScreenInput confirm; confirm.confirm=true;
    ui::ScreenInput cancel; cancel.cancel=true;
    ui::ScreenInput up; up.up=true; up.upHeld=true;
    ui::ScreenInput down; down.down=true; down.downHeld=true;
    ui::ScreenInput right; right.right=true; right.rightHeld=true;
    ui::FrontendState costumeState;
    ui::SelectMenu costumeMenu(costumeState);
    costumeMenu.update(confirm);
    costumeMenu.update(confirm);
    for (int i=0;i<4;++i) costumeMenu.update(right);
    check(costumeState.slots[0].costume==4,"Rena's fifth costume is selectable");
    costumeMenu.update(cancel);
    hold(costumeMenu,right,12);   // (0,216) -> (48,216)
    hold(costumeMenu,up,60);      // -> (48,36): Kasai, whose costume table has one cell
    check(costumeState.slots[0].character==12 && costumeState.slots[0].costume==0,
          "changing to Kasai resets the out-of-range costume");
    menu.update(confirm);
    check(menu.phase()==ui::SelectPhase::Character,"team claims panel");
    hold(menu,up,15);
    check(state.slots[0].character==3,"a held direction slides the cursor onto the next character");
    // The character confirm reports the phase transition used for its cursor sound. The
    // entry voice is a separate event on the later Controller -> Ready confirm.
    ui::SelectTransition transition;
    menu.update(confirm,0,&transition);
    check(transition.from==ui::SelectPhase::Character && transition.to==ui::SelectPhase::Weapon,
          "the character confirm reports the Character -> Weapon transition");
    std::array<ui::SelectTransition,4> voiceTransitions{};
    voiceTransitions[0]=transition;
    check(ui::selectEntryVoices(state,menu,confirm,voiceTransitions).empty(),
          "the first character confirm does not play the entry voice");
    menu.update(up);
    check(state.slots[0].weapon==2,"weapon wraps");
    menu.update(confirm);
    menu.update(up);
    check(state.slots[0].hypermode==2,"hypermode wraps");
    menu.update(cancel);
    check(menu.phase()==ui::SelectPhase::Weapon,"mode cancel returns weapon");
    menu.update(confirm); menu.update(confirm);
    menu.update(confirm,0,&transition);
    check(transition.entered(ui::SelectPhase::Ready),
          "the controller confirm reports entering Ready (the screen's sound 3)");
    check(state.slots[0].ready && state.slots[0].controller==0,"human locks choices");
    voiceTransitions={};
    voiceTransitions[0]=transition;
    auto humanEntryVoices=ui::selectEntryVoices(state,menu,confirm,voiceTransitions);
    check(humanEntryVoices.size()==1 && humanEntryVoices[0]=="data/voice/entry/satoko",
          "a human gets one entry voice after PLAYER confirmation");
    ui::SelectVoiceQueue humanVoiceQueue;
    humanVoiceQueue.append(humanEntryVoices);
    check(humanVoiceQueue.take()=="data/voice/entry/satoko" && humanVoiceQueue.take().empty(),
          "the host voice seam drains a final-confirm cue exactly once");
    ui::ScreenInput idleInput;
    menu.update(idleInput,0,&transition);
    voiceTransitions={};
    voiceTransitions[0]=transition;
    check(transition.from==ui::SelectPhase::Ready && transition.to==ui::SelectPhase::Ready &&
          ui::selectEntryVoices(state,menu,idleInput,voiceTransitions).empty(),
          "holding the Ready state does not repeat the entry voice");
    for(int i=0;i<16;++i) menu.tick();
    check(menu.phase()==ui::SelectPhase::Team,"ready releases controller after 16 frames");
    menu.update(cancel);
    check(state.slots[0].character==-1,"cancel clears configured panel");
    menu.update(up);
    check(menu.cursor()==2,"team cursor reaches decide");
    check(menu.update(confirm)==ui::SelectAction::Stage,"decide advances stage");
    check(state.stagePage && state.slots[3].controller==4 && state.slots[3].character>=0,"unset slots become COM");

    ui::FrontendState comVoiceState;
    ui::SelectMenu comVoiceMenu(comVoiceState);
    auto comVoiceFor = [&](const ui::ScreenInput& input) {
        ui::SelectTransition changed;
        comVoiceMenu.update(input,0,&changed);
        std::array<ui::SelectTransition,4> changedByController{};
        changedByController[0]=changed;
        return ui::selectEntryVoices(comVoiceState,comVoiceMenu,input,changedByController);
    };
    comVoiceFor(confirm); // Team -> Character
    comVoiceFor(confirm); // Character -> Weapon
    check(comVoiceFor(confirm).empty(),"a COM candidate still has no voice before controller choice"); // Weapon -> Hypermode
    comVoiceFor(confirm); // Hypermode -> Controller
    check(comVoiceFor(up).empty(),"choosing COM alone does not play the entry voice");
    check(comVoiceFor(cancel).empty(),"canceling controller choice does not play the entry voice");
    check(comVoiceFor(confirm).empty(),"reopening controller choice does not play the entry voice");
    check(comVoiceFor(up).empty(),"editing back to COM does not play the entry voice");
    const auto comEntryVoices=comVoiceFor(confirm);
    check(comVoiceState.slots[0].controller==4 && comVoiceState.slots[0].ready,
          "the COM choice is committed on the final confirm");
    check(comEntryVoices.size()==1 && comEntryVoices[0]=="data/voice/entry/rena",
          "a COM fighter gets one entry voice after COM confirmation");

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
    simultaneous.players[0].up=true; simultaneous.players[0].upHeld=true;
    simultaneous.players[2].right=true; simultaneous.players[2].rightHeld=true;
    for (int i=0;i<12;++i) frameMenu.updateFrame(simultaneous);   // 12 right ticks = one cell
    simultaneous.players[0].up=false; simultaneous.players[2].right=false;
    for (int i=0;i<3;++i) frameMenu.updateFrame(simultaneous);    // the holds continue: 15/15
    check(frameState.slots[0].character==3 && frameState.slots[2].character==4,
          "simultaneous directions are independent");
    simultaneous.players={};
    simultaneous.players[0].cancel=true;
    simultaneous.players[2].confirm=true;
    frameMenu.updateFrame(simultaneous);
    check(frameState.slots[0].character==-1 && frameMenu.phase(2)==ui::SelectPhase::Weapon,"cancel does not swallow another controller confirm");

    // The screen may receive multiple final confirms in one local-player tick. Each path is
    // queued in controller order so SelectScreen::takeVoice can drain them without overwrite.
    ui::FrontendState voiceFrameState;
    ui::SelectMenu voiceFrameMenu(voiceFrameState);
    ui::ScreenInput voiceFrame;
    voiceFrame.separatePlayers=true;
    voiceFrame.players[0].confirm=true;
    voiceFrame.players[2].confirm=true;
    std::array<ui::SelectTransition,4> voiceFrameTransitions{};
    voiceFrameMenu.updateFrame(voiceFrame,nullptr,&voiceFrameTransitions);
    voiceFrame.players={};
    voiceFrame.players[0].up=true; voiceFrame.players[0].upHeld=true;
    voiceFrame.players[2].right=true; voiceFrame.players[2].rightHeld=true;
    for(int i=0;i<15;++i)
        voiceFrameMenu.updateFrame(voiceFrame,nullptr,&voiceFrameTransitions);
    check(voiceFrameState.slots[0].character==3 && voiceFrameState.slots[2].character==4,
          "local voice fixture selects different characters on panels 0 and 2");
    voiceFrame.players={};
    voiceFrame.players[0].confirm=true; voiceFrame.players[2].confirm=true;
    voiceFrameMenu.updateFrame(voiceFrame,nullptr,&voiceFrameTransitions); // Character -> Weapon
    check(ui::selectEntryVoices(voiceFrameState,voiceFrameMenu,voiceFrame,
                                voiceFrameTransitions).empty(),
          "local character confirms do not play entry voices");
    voiceFrameMenu.updateFrame(voiceFrame,nullptr,&voiceFrameTransitions); // Weapon -> Hypermode
    voiceFrameMenu.updateFrame(voiceFrame,nullptr,&voiceFrameTransitions); // Hypermode -> Controller
    voiceFrame.players={};
    voiceFrame.players[0].up=true; // panel 0 chooses COM
    voiceFrameMenu.updateFrame(voiceFrame,nullptr,&voiceFrameTransitions);
    check(ui::selectEntryVoices(voiceFrameState,voiceFrameMenu,voiceFrame,
                                voiceFrameTransitions).empty(),
          "a local controller edit does not play an entry voice");
    voiceFrame.players={};
    voiceFrame.players[2].cancel=true;
    voiceFrameMenu.updateFrame(voiceFrame,nullptr,&voiceFrameTransitions);
    check(ui::selectEntryVoices(voiceFrameState,voiceFrameMenu,voiceFrame,
                                voiceFrameTransitions).empty(),
          "a local controller cancel does not play an entry voice");
    voiceFrame.players={};
    voiceFrame.players[2].confirm=true; // Hypermode -> Controller
    voiceFrameMenu.updateFrame(voiceFrame,nullptr,&voiceFrameTransitions);
    voiceFrame.players={};
    voiceFrame.players[0].confirm=true; voiceFrame.players[2].confirm=true;
    voiceFrameMenu.updateFrame(voiceFrame,nullptr,&voiceFrameTransitions); // Controller -> Ready
    const auto localEntryVoices=ui::selectEntryVoices(voiceFrameState,voiceFrameMenu,voiceFrame,
                                                      voiceFrameTransitions);
    check(voiceFrameState.slots[0].controller==4 && voiceFrameState.slots[2].controller==2,
          "the two local panels retain independent COM/PLAYER choices");
    check(localEntryVoices.size()==2 &&
          localEntryVoices[0]=="data/voice/entry/satoko" &&
          localEntryVoices[1]=="data/voice/entry/rika",
          "simultaneous local confirms retain both selected-character voices");
    ui::SelectVoiceQueue localVoiceQueue;
    localVoiceQueue.append(localEntryVoices);
    check(localVoiceQueue.take()=="data/voice/entry/satoko" &&
          localVoiceQueue.take()=="data/voice/entry/rika" && localVoiceQueue.take().empty(),
          "the local voice queue drains every cue once without replacing a prior event");

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
    // and their own controllers. The picks are the pattern's documented 0/2/4/1
    // (Rena/Keiichi/Rika/Mion), each with weapon slot 0 — the pattern holds its direction for
    // the ticks the free cursor needs to reach that cell (issue #41).
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
            buttons.upHeld = pad.up; buttons.downHeld = pad.down;
            buttons.leftHeld = pad.left; buttons.rightHeld = pad.right;
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
    // A REMATCH re-enters the selection screen empty, whatever the previous round picked:
    // entering the select scene starts a new selection (issue #45, FUN_00408330:143-158 via
    // FrontendState::beginSelection), so the same walk runs again and lands on the same four
    // characters. That is also what keeps controller 2 off the Back cell (`pos == 5`), whose
    // confirm leaves to the title (measured before the panel walk existed: `scene: select
    // (tick 4984)` followed by `scene: title (tick 5177)`).
    ui::FrontendState rematchState;
    for (int i = 0; i < 4; ++i) {
        rematchState.slots[i] = {expected[i], 0, 0, 0, i, true};   // the finished round's picks
    }
    rematchState.stagePage = true;
    rematchState.beginSelection();
    ui::SelectMenu rematchMenu(rematchState);
    ui::SelectAction rematchAction = ui::SelectAction::None;
    for (uint64_t t = 0; t <= 200 && rematchAction != ui::SelectAction::Stage &&
                         rematchAction != ui::SelectAction::Back; ++t) {
        rematchMenu.tick();
        ui::ScreenInput frame;
        frame.separatePlayers = true;
        for (int c = 0; c < 4; ++c) {
            const auto pad = fnd::input::syntheticMenuPadState(c, t);
            auto& buttons = frame.players[c];
            buttons.up = pad.up; buttons.down = pad.down;
            buttons.left = pad.left; buttons.right = pad.right;
            buttons.upHeld = pad.up; buttons.downHeld = pad.down;
            buttons.leftHeld = pad.left; buttons.rightHeld = pad.right;
            buttons.confirm = pad.confirm; buttons.cancel = pad.cancel;
        }
        rematchAction = rematchMenu.updateFrame(frame);
        check(rematchAction != ui::SelectAction::Back, "a rematch pad never confirms the Back cell");
    }
    check(rematchAction == ui::SelectAction::Stage, "the rematch pads open the stage page");
    check(rematchState.stagePage, "a rematch re-opens the stage page");
    for (int i = 0; i < 4; ++i)
        check(rematchState.slots[i].character == expected[i],
              "the rematch re-picks the pattern's four characters");
    check(fnd::input::syntheticMenuStartPanel(1) == 1 &&
          fnd::input::syntheticMenuStartPanel(2) == 2 &&
          fnd::input::syntheticMenuStartPanel(3) == 3,
          "each pad knows the panel it starts on");
    // Issue #20's penalty session flag: a player who earned the penalty title last round has
    // their costume forced to the character's own penalty cell when they confirm a character
    // (FUN_00409340:165-172 reads DAT_006b72a0[character]). The table lives in the installed
    // exe, so the assertion is conditional: without it the flag cannot force anything.
    {
        // The costume table lives in the installed exe, so the flag can only force a cell when
        // an install is open (the host opens one before any screen exists).
        std::filesystem::path game = std::filesystem::path("Higurashi-Daybreak");
        if (const char* env = std::getenv("GAME_DIR")) game = std::filesystem::path(env);
        for (std::filesystem::path r = std::filesystem::current_path(); !r.empty();
             r = r.parent_path()) {
            if (std::filesystem::is_directory(r / "Higurashi-Daybreak" / "data")) {
                game = r / "Higurashi-Daybreak";
                break;
            }
            if (r == r.parent_path()) break;
        }
        const bool exe = std::filesystem::exists(game / "DaybreakDX.exe");
        if (exe) fnd::assets::AssetSource::instance().openInstall(game.string());
        ui::FrontendState penaltyState;
        penaltyState.penaltyDecided[0] = true;
        ui::SelectMenu penaltyMenu(penaltyState);
        penaltyMenu.update(confirm);
        check(penaltyState.slots[0].character == 0, "the penalized panel picks its character");
        penaltyMenu.update(confirm);
        const int forced = penaltyState.slots[0].costume;
        if (exe) check(forced == 5, "the penalty flag forces Rena's penalty costume cell");
        else check(forced == 0, "without the exe the penalty flag forces nothing");
        // Gear-up resolution for every roster pick (the issue #23 defect): the launch
        // resolves the item's first NON-EMPTY attachment mesh, and an item that ships no
        // mesh at all is ARMED, not fatal. FUN_00433eb0:90-116 walks every slot and loads
        // each non-empty name, skipping the empty ones at :111; the item's own data (move
        // table, bullets, damage) is read regardless of whether any mesh loaded.
        if (exe) {
            auto launch = [](int character, int weapon, ui::FrontendLaunch& out,
                             std::string& err) {
                ui::FrontendState state;
                state.slots[0].character = character;
                state.slots[0].weapon = weapon;
                state.slots[2].character = 0;
                state.slots[2].weapon = 0;
                return ui::frontendLaunch(state, out, err, 1u);
            };
            // (a) a mesh in a LATER slot is the item's mesh: takano's item 011 carries
            // 25.x in slot 2, and the slot-0-only reading produced an empty spec.
            ui::FrontendLaunch slot2;
            std::string launchError;
            check(launch(7, 0, slot2, launchError),
                  "takano + item 011 launches");
            check(slot2.fighters[0].weaponId == 11, "and binds item 011");
            check(slot2.fighters[0].weapon == "data/item/25.x",
                  "with item 011's slot-2 mesh, not slot 0's empty name");
            // (b) no mesh anywhere is legal: satoko's item 008 is armed and undrawn.
            ui::FrontendLaunch bare;
            check(launch(3, 0, bare, launchError),
                  "satoko + item 008 launches");
            check(bare.fighters[0].weaponId == 8, "and binds item 008");
            check(bare.fighters[0].weapon.empty(), "with no attachment mesh to draw");
            // (c) an unreadable item is still a loud failure that names the file.
            fnd::assets::AssetSource::instance().closeInstall();
            ui::FrontendLaunch broken;
            check(!launch(7, 0, broken, launchError),
                  "an unreadable item still fails the launch");
            check(launchError.find("data/item/011.dat") != std::string::npos,
                  "and the error names the file it could not read");
            fnd::assets::AssetSource::instance().openInstall(game.string());
        } else {
            check(true, "no install: the gear-up resolution is skipped");
        }

        // A panel without the flag keeps its own costume.
        ui::FrontendState cleanState;
        ui::SelectMenu cleanMenu(cleanState);
        cleanMenu.update(confirm);
        cleanMenu.update(confirm);
        check(cleanState.slots[0].costume == 0, "an unflagged panel keeps its costume");
    }
    std::printf("select_menu_test: %d failures\n",failures);
    return failures ? 1 : 0;
}
