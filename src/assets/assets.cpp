// The single translation unit that owns the asset layer's implementations — the
// definitions in the headers are deliberately not `inline`, so this is the one TU the
// implementation macros may be defined in.
#define XMODEL_IMPLEMENTATION
#define CNV_IMPLEMENTATION
#define SCENE_IMPLEMENTATION
#include "assets.h"
