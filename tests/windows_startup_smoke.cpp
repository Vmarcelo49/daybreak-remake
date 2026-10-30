// Exercise Windows automatic startup and settings discovery, without
// distributing this developer-only executable in the release ZIP.
#define SDL_MAIN_HANDLED 1
#include "../src/app/main.cpp"
#undef main
#include <thread>
#include <chrono>

int main(int, char** argv) {
    int failures = 0;
    for (int run = 0; run < 2; ++run) {
        void* state = nullptr;
        char muteOption[] = "--no-audio";
        char* startupArgs[] = {argv[0], muteOption, nullptr};
        SDL_AppResult result = SDL_AppInit(&state, 2, startupArgs);
        App* app = static_cast<App*>(state);
        if (!app || result != SDL_APP_CONTINUE) {
            std::fprintf(stderr, "STARTUP: %s\n", app ? app->error.c_str() : "no application state");
            if (app) SDL_AppQuit(app, SDL_APP_SUCCESS);
            return 1;
        }
        if (!app->settingsActive || app->settingsPath.empty() ||
            !fnd::assets::assetSource().bundlesOpen()) ++failures;
        for (int frame = 0; frame < 60 && result == SDL_APP_CONTINUE; ++frame) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) SDL_AppEvent(app, &event);
            result = SDL_AppIterate(app);
            std::this_thread::sleep_for(std::chrono::milliseconds(16));
        }
        if (result == SDL_APP_FAILURE) ++failures;
        const std::string config = app->settingsPath;
        app->settingsDirty = true;
        flushUserSettings(*app);
        if (app->settingsDirty) ++failures;
        if (!std::filesystem::is_regular_file(std::filesystem::u8path(config))) ++failures;
        settings::UserSettings saved;
        settings::LoadReport report;
        if (!settings::load(config, saved, report)) ++failures;
        std::printf("STARTUP run=%d settings=%s errors=%d\n", run + 1, config.c_str(), failures);
        SDL_AppQuit(app, SDL_APP_SUCCESS);
    }
    return failures ? 1 : 0;
}
