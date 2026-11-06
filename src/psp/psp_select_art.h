#pragma once
// psp/psp_select_art.h — the select, VS and result sheets the port reads for indices 16..18.
//
// The contract is docs/psp/FRONTEND-ART.md §2: five file families per PSP fighter, at the PC
// sheets' own sizes and cell grids, so the select, VS and result screens need no per-character
// branch. The pixels are the PSP's own select art (gra/gim/select/*.gim), cropped and repacked;
// the chibi, costume and weapon cells are place-holders because the PSP ships no such art.
//
// This is the C++ port of tools/asset-tools/psp_select_art.py, which defined the sheets and
// remains their reference implementation (it keeps a --dump input and PNG previews a player's
// extractor has no use for). A player has no Python, so the extractor writes them:
//
//   <psp-data>/data/select/NN.cnv      256x256  one portrait, pivot bottom-centre
//   <psp-data>/data/select/iNN.cnv     256x256  3x2 grid of 80x128 chibi cells
//   <psp-data>/data/select/cosNN.cnv   256x384  3x3 grid, one cell per costume
//   <psp-data>/data/select/wNN.cnv     512x256  4 rows of 256x64, weapon slots a..d
//   <psp-data>/data/win/NNa.cnv        512x512  the result screen's winner portrait
//
// The resampling is the reference's box filter, reproduced exactly — a premultiplied-alpha box
// average with integer division, so the two implementations write the same bytes. That is
// checkable, and it is why the sheets the screens read do not depend on which one wrote them.
#include <iosfwd>
#include <string>
#include <vector>

namespace psp {

// The extractor's `select art` converter: reads only <dataDir>/psp/gra/gim/select/ and writes the
// five families for each of the three PSP fighters. Returns the files it wrote, relative to
// dataDir.
std::vector<std::string> convertPspSelectArt(const std::string& dataDir, std::ostream& log);

}  // namespace psp
