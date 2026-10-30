#pragma once
// Local split-screen layout: how many views a match draws, which controller owns
// each one, and where each view's cell sits on the render target.
//
// All of it is recovered from the original's own frame dispatcher FUN_006396f0
// @0x006396f0, not invented:
//
//   * DAT_006cfba0 is the number of HUMAN controllers. FUN_0040d130 @0x0040d130:105-111
//     counts the controller slots whose DAT_006cfaf8[slot] is a real fighter index
//     (< 4; 4 is the unassigned/COM marker), and :115-119 forces that count to 1 with
//     slot 0 when there is no human at all — so a COM-only match still renders one view.
//   * FUN_006396f0:48 switches on it: case 1 one full 800x600 view, case 2 two views,
//     case 3 three humans, case 4 four humans. A view is keyed by CONTROLLER, not by
//     fighter: the loop writes the view's controller to game+0x44b4 (:110) and uses
//     `game + 0x454e + controller * 0x160` as that view's context before drawing it
//     (:112), the same 0x160-byte stride FUN_0063a130 HUD drawing uses
//     (`FUN_0063a130(game, controller, rect.left, rect.top)`, :185-186).
//   * case 1: SetRect(0,0,800,600) with DAT_006cfd00 = 1 (:49-53) — the whole frame.
//   * case 2: two views, cells (0,0,400,300) then (400,300,800,600) (:63-64), i.e. the
//     top-left and bottom-right cells of the same four-cell grid, DAT_006cfd00 = 0.
//     The two controller slots come from DAT_006cfba4/DAT_006cfba8 (:59-60), which are
//     filled in ascending slot order, so view 0 is the lowest human slot.
//   * case 3: the FOUR-cell grid again, but a controller with no human is marked -1 and
//     its cell is skipped (:74-81, :109); cell order is TL, BL, TR, BR (:82-85).
//   * case 4: the same four cells, all four assigned, view i = controller i (:90-96).
//   * whenever more than one view is drawn, a black cross goes over the whole frame
//     afterwards — vertical x 399..400, horizontal y 299..300 in the 800x600 frame
//     (:191-195) — and a human-less cell only gets the centre placeholder sprite (:196-201).
//
// The port keeps the geometry and the controller keying, and scales the 800x600 frame to
// the actual render target. Two things are explicit port rules, not recovered behavior:
// the separator thickness is the D8 HUD scale of the original's one pixel (so it stays
// one pixel at 800x600 and grows with the frame), and a human-less cell is left at the
// scene clear colour because the placeholder sprite FUN_006396f0:198 draws was not
// identified.
//
// Device-free (std only) on purpose: the layout is arithmetic, and the host tests pin it
// without a window or a GPU.
#include <cstdint>

namespace game {

// The original holds four controller slots (FUN_0040d130 loops 0..3).
inline constexpr int kMaxHumanViews = 4;

// One view: the controller slot that owns it and the fighter it renders.
struct HumanView {
    int controller = -1;
    int fighter = -1;
    bool active() const { return controller >= 0 && fighter >= 0; }
};

// The original's three layouts, named by the number of cells they draw (its local_8:
// 1 for case 1, 2 for case 2, 4 for cases 3 and 4).
enum class SplitLayout : unsigned char { Single, Two, Four };

// Cells a layout draws. Three humans reuse Four: FUN_006396f0 case 3 sets local_8 = 4 and
// leaves the human-less cell empty rather than defining a three-cell layout.
inline constexpr int viewCellCount(SplitLayout layout) {
    return layout == SplitLayout::Single ? 1 : (layout == SplitLayout::Two ? 2 : 4);
}

inline constexpr SplitLayout splitLayoutFor(int humanCount) {
    if (humanCount <= 1) return SplitLayout::Single;
    if (humanCount == 2) return SplitLayout::Two;
    return SplitLayout::Four;
}

// Pixel rect, top-left origin — the space the original's SetRect cells and D3D's
// SetViewport live in.
struct ViewRect {
    float x = 0.f, y = 0.f, w = 0.f, h = 0.f;
    bool empty() const { return w <= 0.f || h <= 0.f; }
};

// The original's cell for `viewIndex` of `layout`, scaled to `targetW` x `targetH`.
// Half-splits use integer division so the cells tile the target exactly at odd sizes:
// the second column/row takes the remainder. Out-of-range indices return an empty cell
// (the caller skips them), which is also what the original's -1 cells do.
inline ViewRect viewCell(SplitLayout layout, int viewIndex, uint32_t targetW, uint32_t targetH) {
    const float w = (float)targetW, h = (float)targetH;
    const float left = (float)(targetW / 2), top = (float)(targetH / 2);
    const float right = w - left, bottom = h - top;
    switch (layout) {
        case SplitLayout::Single:
            return viewIndex == 0 ? ViewRect{0.f, 0.f, w, h} : ViewRect{};
        case SplitLayout::Two:
            // FUN_006396f0:63-64 — top-left first, bottom-right second.
            if (viewIndex == 0) return ViewRect{0.f, 0.f, left, top};
            if (viewIndex == 1) return ViewRect{left, top, right, bottom};
            return ViewRect{};
        case SplitLayout::Four:
            // FUN_006396f0:82-85 — TL, BL, TR, BR.
            switch (viewIndex) {
                case 0: return ViewRect{0.f, 0.f, left, top};
                case 1: return ViewRect{0.f, top, left, bottom};
                case 2: return ViewRect{left, 0.f, right, top};
                case 3: return ViewRect{left, top, right, bottom};
                default: return ViewRect{};
            }
    }
    return ViewRect{};
}

// Views the frame draws, in controller-slot order, exactly as FUN_006396f0 keys them.
// `controllerOfFighter[i]` is fighter i's controller slot, or negative for COM. Fighter
// index and controller index are different spaces: a slot that
// owns no fighter gets no view, which is how COM participants never allocate one.
// Returns the number of views; `out` is only written where a view exists, and a match
// with no human at all gets the original's forced single view on controller 0 following
// fighter 0 (FUN_0040d130:115-119).
inline int buildHumanViews(const int controllerOfFighter[], int fighterCount,
                           HumanView out[kMaxHumanViews]) {
    for (int i = 0; i < kMaxHumanViews; ++i) out[i] = HumanView{};
    int views = 0;
    for (int controller = 0; controller < kMaxHumanViews; ++controller) {
        for (int fighter = 0; fighter < fighterCount; ++fighter) {
            if (controllerOfFighter[fighter] != controller) continue;
            out[views++] = HumanView{controller, fighter};
            break;   // one panel per controller: the first fighter claiming it owns it
        }
    }
    if (views == 0) {
        out[0] = HumanView{0, fighterCount > 0 ? 0 : -1};
        views = 1;
    }
    return views;
}

// Separator bars: two black rects (vertical then horizontal) drawn over the whole frame
// whenever more than one view is on screen, as FUN_006396f0:191-195 does. The original's
// bars are one pixel of its 800x600 frame; the port scales that pixel with the D8 HUD
// scale and centres the bar on the cell boundary. Zero separators for a single view.
inline int separatorCount(SplitLayout layout) { return viewCellCount(layout) > 1 ? 2 : 0; }

inline ViewRect separatorRect(int index, uint32_t targetW, uint32_t targetH) {
    const float w = (float)targetW, h = (float)targetH;
    if (w <= 0.f || h <= 0.f) return ViewRect{};
    const float scale = w / 800.f < h / 600.f ? w / 800.f : h / 600.f;
    const float thickness = scale > 1.f ? (float)(int)(scale + 0.5f) : 1.f;
    if (index == 0) return ViewRect{w * .5f - thickness * .5f, 0.f, thickness, h};
    if (index == 1) return ViewRect{0.f, h * .5f - thickness * .5f, w, thickness};
    return ViewRect{};
}

}  // namespace game
