// psp/psp_convert.cpp — the one place the converter list is spelled out.
//
// A converter reads only <psp-data>/psp/ and writes the remake's own formats under
// <psp-data>/. Registration order is the order they run in.
#include "psp/psp_extract.h"

namespace psp {

void registerAllPspConverters() {
    static bool registered = false;
    if (registered) return;
    registered = true;
    // The model converter (GMO -> .X) and the moveset converter (data/<name>/0W.dat and
    // data/item/1NN.dat from .acs/.acv/.atp) join here.
}

}  // namespace psp
