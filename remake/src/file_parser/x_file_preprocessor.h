// =============================================================================
//  x_file_preprocessor.h — .x file reader with idempotent template injection.
//
//  Ported (and trimmed) from X2Blend's io/x_file_preprocessor.{h,cpp}.
//  Reads a .x file from disk into memory and, for text-format files, injects
//  the mesh-extension templates (XSkinMeshHeader, VertexDuplicationIndices,
//  SkinWeights) that Wine's d3dxof parser does not pre-register.
//
//  The injection is idempotent: templates whose `template <Name>` marker is
//  already present in the file are NOT re-injected, so repeated preprocessing
//  of the same file is a no-op.
// =============================================================================
#pragma once

#include <string>

namespace daybreak {

namespace x_file_preprocessor {

// Reads `filepath` from disk into `outContent`. For text-format .x files,
// injects the missing mesh-extension templates right after the magic header
// line.  Returns false on read failure.
bool read_and_preprocess(const std::string& filepath, std::string& outContent);

} // namespace x_file_preprocessor

} // namespace daybreak
