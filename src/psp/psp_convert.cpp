// psp/psp_convert.cpp — the one place the converter list is spelled out.
//
// A converter reads only <psp-data>/psp/ and the PC install, and writes the remake's own
// formats under <psp-data>/. Order is the order they run in, and it matters:
//
//   1. models    PSP GMO -> data/<name>[_B..]/00.X and its textures (this track).
//   2. movesets  the frame tables and weapon items (data/<name>/0W.dat, data/item/1NN.dat) from
//                the PSP .acs/.acv/.atp, built on the PC dispatch combo's own table. It reads
//                the converted model first, for the take count and each take's length, and only
//                falls back to copying the dispatch combo's PC model when there is none — so
//                running models first is what makes the two agree.
#include <ostream>
#include <string>
#include <vector>

#include "psp/psp_extract.h"
#include "psp/psp_model.h"
#include "psp/psp_moveset.h"

namespace psp {

void registerAllPspConverters() {
    static bool registered = false;
    if (registered) return;
    registered = true;

    registerPspConverter("models", [](const PspConverterContext& context) {
        return convertPspFighters(context.dataDir, *context.log);
    });

    registerPspConverter("movesets", [](const PspConverterContext& context) {
        std::vector<std::string> written;
        if (context.installDir.empty()) {
            // The frame tables are built on a PC dispatch combo's own table, which only the
            // install has. A player who runs the extractor without one still gets the models;
            // nothing here is worth failing the whole extraction over.
            *context.log << "psp: movesets skipped: no PC install given, so the dispatch combo's "
                            "frame table cannot be read (pass --install=<game folder>)\n";
            return written;
        }
        daybreak::psp::TreeRequest request;
        request.install_dir = context.installDir;
        request.raw_dir = pspRawPath(context.dataDir, "");
        request.output_dir = context.dataDir;
        const daybreak::psp::TreeResult result = daybreak::psp::prepare_psp_data_tree(request);
        if (!result.report.empty()) *context.log << result.report;
        return result.written;
    });
}

}  // namespace psp
