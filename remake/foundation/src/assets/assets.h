#pragma once
// The Daybreak asset layer: .X mesh/animation loading (three encodings), .cnv
// texture decoding, Shift-JIS name resolution, and stage/character/weapon scene
// assembly. Header-only, with the implementations compiled once in assets.cpp.
//
// It carries no windowing or rendering dependency beyond a vertex-layout helper,
// which is why it moves to a new backend unchanged — decision D3 (the originals
// are loaded as shipped, no conversion pipeline).
#include "cnv.h"
#include "scene.h"
#include "sjis_table.h"
#include "xmodel.h"
