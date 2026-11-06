// Prepares a psp-data tree from raw PSP files and the player's own install (issue #91, plan
// D-3a). The extractor will call the same library function; this tool exists so the tree can be
// built and inspected by hand, and so the whole-match test has something to mount.
//
//   psp_moveset_convert --install <game dir> --raw <dir> --out <psp-data dir> [--no-model-copy]
//
// --raw holds the twelve combos' activity/chrNNx.{acs,acv} and assault/chrNNx.atp, at those paths
// or with the separators replaced by '_'. Without --no-model-copy a fighter's own 00.X, when the
// converted one is missing, is the dispatch combo's PC model (a simulation-only stand-in; the
// renderer needs the real one).
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
