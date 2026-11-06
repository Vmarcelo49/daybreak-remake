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
#include <map>
#include <ostream>
#include <string>
#include <vector>

#include "psp/psp_extract.h"
#include "psp/psp_model.h"
#include "psp/psp_moveset.h"
#include "psp_roster.hpp"

namespace psp {

namespace {

// The animation plans are the contract between the two converters (docs/psp/COMBAT.md §3.1): the
// model converter appends each fighter's derived take slices after its 76 takes, and the moveset
// converter points every phase at one of them. Both must use the same plan, so it is made once per
// extraction, before the models, and kept here for the movesets. Without an install there are no
// dispatch tables to plan over, so the models carry their takes alone and the movesets are skipped.
std::vector<daybreak::psp::AnimationPlan>& extractionPlans() {
    static std::vector<daybreak::psp::AnimationPlan> plans;
    return plans;
}

std::vector<daybreak::psp::AnimationPlan> planFighters(const PspConverterContext& context) {
    // plan_psp_animations takes the fighters in roster order (16, 17, 18); the model converter's
    // list is the same three, and this keeps the two orders from drifting apart silently.
    const std::vector<PspFighter>& fighters = pspFighters();
    if (fighters.size() != daybreak::psp_character_names.size())
        throw std::logic_error("psp: the model converter and the roster disagree on the fighters");
    for (std::size_t i = 0; i < fighters.size(); ++i)
        if (fighters[i].name != daybreak::psp_character_names[i])
            throw std::logic_error("psp: fighter " + fighters[i].name + " is out of roster order");
    std::vector<std::vector<daybreak::psp::TakeInfo>> takes;
    for (const PspFighter& fighter : fighters) {
        std::vector<daybreak::psp::TakeInfo> info;
        for (const PspTakeFacts& facts : pspTakeFacts(context.dataDir, fighter))
            info.push_back({facts.lastFrame, facts.animated});
        takes.push_back(std::move(info));
    }
    return daybreak::psp::plan_psp_animations(context.installDir, takes);
}

}  // namespace

void registerAllPspConverters() {
    static bool registered = false;
    if (registered) return;
    registered = true;

    registerPspConverter("models", [](const PspConverterContext& context) {
        auto& plans = extractionPlans();
        plans.clear();
        if (!context.installDir.empty()) plans = planFighters(context);
        // planFighters checked that the plans are in pspFighters() order.
        std::map<std::string, std::vector<PspTakeSlice>> slices;
        for (std::size_t i = 0; i < plans.size(); ++i)
            for (const daybreak::psp::DerivedSet& set : plans[i].derived)
                slices[pspFighters()[i].name].push_back({set.take, set.from, set.to});
        return convertPspFighters(context.dataDir, *context.log,
                                  [&](const std::string& name) -> const std::vector<PspTakeSlice>* {
                                      const auto found = slices.find(name);
                                      return found == slices.end() ? nullptr : &found->second;
                                  });
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
        request.plans = &extractionPlans();
        const daybreak::psp::TreeResult result = daybreak::psp::prepare_psp_data_tree(request);
        if (!result.report.empty()) *context.log << result.report;
        return result.written;
    });
}

}  // namespace psp
