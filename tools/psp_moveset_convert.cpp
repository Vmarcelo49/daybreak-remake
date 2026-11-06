// Prepares a simulation-only psp-data tree from raw PSP files and the player's own install
// (issue #91, plan D-3a): the frame tables and items, over the dispatch combos' PC models copied in
// as stand-ins. It is how the moveset is built and inspected without the model converter.
//
//   psp_moveset_convert --install <game dir> --raw <dir> --out <psp-data dir> [--no-model-copy]
//
// --raw holds the twelve combos' activity/chrNNx.{acs,acv} and assault/chrNNx.atp, at those paths
// or with the separators replaced by '_'. A tree that already holds a fighter's own converted 00.X
// is refused: that model's animation sets and the tables' phases come from one animation plan, and
// only `daybreak --extract-psp` builds both from it (docs/psp/COMBAT.md §3.1).
#include "psp/psp_moveset.h"

#include <cstdio>
#include <exception>
#include <stdexcept>
#include <string>

int main(int argc, char** argv) {
    daybreak::psp::TreeRequest request;
    for (int i = 1; i < argc; ++i) {
        const std::string flag = argv[i];
        auto value = [&](std::string& into) {
            if (i + 1 >= argc) throw std::runtime_error(flag + " needs a value");
            into = argv[++i];
        };
        if (flag == "--install") value(request.install_dir);
        else if (flag == "--raw") value(request.raw_dir);
        else if (flag == "--out") value(request.output_dir);
        else if (flag == "--no-model-copy") request.copy_dispatch_model = false;
        else {
            std::fprintf(stderr,
                         "usage: psp_moveset_convert --install <game dir> --raw <dir> --out <dir>"
                         " [--no-model-copy]\n");
            return 2;
        }
    }
    if (request.install_dir.empty() || request.raw_dir.empty() || request.output_dir.empty()) {
        std::fprintf(stderr, "psp_moveset_convert: --install, --raw and --out are required\n");
        return 2;
    }
    try {
        const auto result = daybreak::psp::prepare_psp_data_tree(request);
        std::fputs(result.report.c_str(), stdout);
        return 0;
    } catch (const std::exception& error) {
        std::fprintf(stderr, "psp_moveset_convert: %s\n", error.what());
        return 1;
    }
}
