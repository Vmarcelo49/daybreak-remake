// anim_frames_dump.cpp — dev-only: print the frame (bone) list of a .X, with
// parent chain, so the weapon/prop attachment is visible.

#define XMODEL_IMPLEMENTATION
#include "assets/xmodel.h"

#include <cstdio>

int main(int argc, char** argv) {
    if (argc < 2) { std::fprintf(stderr, "usage: %s <file.X>\n", argv[0]); return 1; }
    xm::Model m = xm::loadFile(argv[1]);
    for (size_t i = 0; i < m.frames.size(); ++i) {
        const xm::Frame& f = m.frames[i];
        std::printf("%2zu  %-24s parent=%s\n", i, f.name.c_str(),
                    f.parent >= 0 ? m.frames[(size_t)f.parent].name.c_str() : "(root)");
    }
    // Skinned meshes: which frame each hangs off.
    for (const xm::Mesh& ms : m.meshes) {
        std::printf("MESH %-24s frame=%s skinned=%d\n", ms.name.c_str(),
                    ms.frame >= 0 ? m.frames[(size_t)ms.frame].name.c_str() : "(none)",
                    (int)ms.skinned);
    }
    return 0;
}
