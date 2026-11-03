#pragma once
// update/manifest_status.h — the result both manifest parsers return.
//
// An unknown `format` is its own status, not a parse failure: step 3 tells the player that
// this release has to be downloaded by hand instead of reporting a corrupt file.
namespace update {

enum class ParseStatus { Ok, UnknownFormat, Invalid };

}  // namespace update
