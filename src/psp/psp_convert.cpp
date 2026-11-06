// psp/psp_convert.cpp — the one place the converter list is spelled out.
//
// A converter reads only <psp-data>/psp/ and writes the remake's own formats under
// <psp-data>/. Order matters: the model converter goes first because it is also the
// reference for what a converter may assume about the raw layout.
#include "psp/psp_extract.h"
#include "psp/psp_model.h"

namespace psp {

void registerAllPspConverters() {
    static bool registered = false;
    if (registered) return;
    registered = true;
    registerPspConverter("models", convertPspFighters);
    // Track C's moveset converter (data/<name>/0W.dat and data/item/1NN.dat, from the
    // .acs/.acv/.atp files the raw stage collected) registers here next.
}

}  // namespace psp
