// =============================================================================
//  x_file_preprocessor.cpp — see header for docs.
//
//  Verbatim port of X2Blend's io/x_file_preprocessor.cpp, minus the LOG_*
//  calls (daybreak uses std::fprintf directly).
// =============================================================================
#include "x_file_preprocessor.h"

#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>

namespace daybreak::x_file_preprocessor {

namespace {

// Mesh-extension templates that Wine's d3dxof parser does not pre-register.
// GUIDs and field layouts are verbatim from the DirectX 9 SDK (rmxftmpl.x).
static const char* k_missingTemplates = R"x(
template XSkinMeshHeader {
  <3CF169CE-FF7C-44AB-93C0-F78F62D172E2>
  WORD nMaxSkinWeightsPerVertex;
  WORD nMaxSkinWeightsPerFace;
  WORD nBones;
}

template VertexDuplicationIndices {
  <B8D65549-D7C9-4995-89CF-53A9A8B031E3>
  DWORD nIndices;
  DWORD nOriginalVertices;
  array DWORD indices[nIndices];
}

template SkinWeights {
  <6F0D123B-BAD2-4167-A0D0-80224F25FABB>
  STRING transformNodeName;
  DWORD nWeights;
  array DWORD vertexIndices[nWeights];
  array float weights[nWeights];
  Matrix4x4 matrixOffset;
}
)x";

static const char* const k_templateMarkers[] = {
    "template XSkinMeshHeader",
    "template VertexDuplicationIndices",
    "template SkinWeights",
};

// Extracts the body of one template (identified by its marker) from
// k_missingTemplates.  Body starts at the marker and ends just before the
// next `template ` keyword (or at the end of k_missingTemplates).
static std::string extractTemplateBody(const std::string& marker) {
    static const std::string src = k_missingTemplates;
    auto start = src.find(marker);
    if (start == std::string::npos) return std::string();
    auto next = src.find("template ", start + 1);
    return (next == std::string::npos) ? src.substr(start)
                                        : src.substr(start, next - start);
}

} // namespace

bool read_and_preprocess(const std::string& filepath, std::string& outContent) {
    std::ifstream file(filepath, std::ios::binary);
    if (!file.is_open()) {
        std::fprintf(stderr, "[daybreak] x_file_preprocessor: cannot open %s\n",
                     filepath.c_str());
        return false;
    }

    std::ostringstream oss;
    oss << file.rdbuf();
    outContent = oss.str();
    file.close();

    // Only text-format .x files begin with "xof 0303txt" or "xof 0302txt".
    bool isTextFormat = (outContent.size() >= 11 &&
                         outContent.compare(0, 7, "xof 030") == 0 &&
                         (outContent[10] == 't' || outContent[10] == 'T'));

    if (isTextFormat) {
        size_t headerEnd = outContent.find('\n');
        if (headerEnd == std::string::npos) {
            headerEnd = outContent.size();
        } else {
            ++headerEnd;
        }

        std::string injection;
        for (const char* marker : k_templateMarkers) {
            if (outContent.find(marker) == std::string::npos) {
                injection += extractTemplateBody(marker);
            }
        }

        if (!injection.empty()) {
            outContent.insert(headerEnd, std::string("\n") + injection);
        }
    }

    return true;
}

} // namespace daybreak::x_file_preprocessor
