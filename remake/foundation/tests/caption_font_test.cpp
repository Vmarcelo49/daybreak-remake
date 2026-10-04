#include "ui/caption.h"
#include <cstdio>

#define CHECK(x) do { if (!(x)) { std::fprintf(stderr,"FAIL: %s\n",#x); return 1; } } while (0)
int main() {
    ui::TextLayer latin;
    std::string error;
    CHECK(ui::loadCaptionFont(latin,22.f,error,ui::kCaptionFontFile,nullptr));
    CHECK(latin.faceCount() == 1 && latin.hasGlyph('A') && latin.hasGlyph('%'));
    CHECK(!latin.hasGlyph(0x65e5));
    auto caption = latin.layout("MAIN 12/24 CHARGE 100%");
    CHECK(caption.width(1) > 0 && !latin.glyphCoverage('M').empty());
    const auto revision = latin.atlasRevision();
    latin.layout("MAIN 12/24 CHARGE 100%");
    CHECK(latin.atlasRevision() == revision);
    ui::TextLayer linked;
    CHECK(ui::loadCaptionFont(linked,22.f,error));
    if (linked.faceCount() == 2) {
        CHECK(linked.hasGlyph(0x65e5));
        linked.layout("MAIN 日本語");
        CHECK(!linked.glyphCoverage(0x65e5).empty());
    }
    std::puts("caption_font_test: Gyrotrope CFF rasterization and font linking ok");
}
