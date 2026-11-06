#pragma once
// psp/psp_model.h — GMO -> the PC's binary .X, one costume at a time.
//
// The port draws what its own .X loader produces, and its simulation reads the same bytes
// through the vendored core's XObjectReader (design decision D-3a). So a PSP fighter
// becomes a file: frames for the PSP skeleton, skinned meshes with materials, and the
// motion file's takes as animation sets. Nothing converts at run time.
//
// Three rules here are decisions, documented in docs/psp/MODEL-CONVERSION.md:
//
//   * bone names  PSP bones are renamed onto the PC rig's names where the core looks a
//                 name up ("Bip01_Spine", "Bip01_Prop1", "Bip01_R_Hand", ...). Every
//                 other bone keeps its PSP name. The split the core makes between a
//                 lower-body channel and an upper-body one is by the "Bip01" prefix
//                 (core/actor_sampled_pose.hpp), so the rename is what gives the PSP rig
//                 the PC's two-layer animation behaviour.
//   * take order  the core registers animation sets in reverse file order, so the writer
//                 emits take N-1 first and take 0 last: index i in the core is PSP take i.
//   * scale       the fighter's draw scale multiplies the root frame's matrix, so the
//                 drawn mesh and every bone-anchored hit shape scale together.
#include <cstdint>
#include <iosfwd>
#include <string>
#include <vector>

#include "psp/gmo.h"
#include "psp/tga.h"

namespace psp {

struct PspFighter {
    std::string              name;      // data/<name>, the folder the port asks for
    std::string              rig;       // chrmNN.gmo: skeleton and every motion
    std::string              head;      // chrtNN.gim: the head pictures
    std::vector<std::string> costumes;  // chrNNk.gmo, costume 0 first
    float                    scale = 1.f;
};

// The three PSP-only fighters, with the scales docs/PSP-CHARACTERS-PLAN.md chose from the
// height table: Okonogi with the grown men, Satoshi between Keiichi and Satoko, Miyoko
// with the children.
const std::vector<PspFighter>& pspFighters();

// The PC bone name a PSP bone becomes, or the PSP name itself when it keeps it.
std::string pspBoneName(const std::string& name);

// The head picture inside chrtNN.gim for a texture name ("chr19__face" -> 0), or -1 when
// the name is not one of the three the atlas supplies.
int pspHeadPicture(const std::string& textureName);

struct PspConvertedModel {
    struct Texture {
        std::string               file;   // beside the .X, e.g. "chr190__body.cnv"
        std::vector<std::uint8_t> cnv;
    };
    std::vector<std::uint8_t> x;
    std::vector<Texture>      textures;
    std::vector<std::string>  boneNames;
    unsigned                  meshes = 0;
    unsigned                  triangles = 0;
    unsigned                  animationSets = 0;
    unsigned                  emptyTakes = 0;
};

// The pure conversion, so a test can hand the bytes to both readers without touching the
// filesystem.
PspConvertedModel buildPspModel(const GmoModel& rig, const GmoModel& costume,
                                const std::vector<RgbaImage>& headPictures, float scale);

// The extractor's converter: every fighter, every costume, into <dataDir>/data/...
std::vector<std::string> convertPspFighters(const std::string& dataDir, std::ostream& log);

}  // namespace psp
