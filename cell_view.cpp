#include "cell_view.h"

#include <span>

#include "storage.h"

namespace {

using GlProxy = std::span<Vertex, 4>;

using Color = float[4];

constexpr Color deathColor{1.f, 1.f, 0.f, 1.f};   // yellow
constexpr Color aliveColor{0.f, 0.f, 1.f, 1.f};   // blue
constexpr Color unknownColor{0.f, 0.f, 0.f, 1.f}; // black

const auto& pickColor(ca::Cell cell) {
    switch (cell) {
    case ca::Cell::Died: return deathColor;
    case ca::Cell::Alive: return aliveColor;
    };

    return unknownColor;
}

void updateColor(Color& target, const Color& source) {
    target[0] = source[0];
    target[1] = source[1];
    target[2] = source[2];
    target[3] = source[3];
}

} // namespace

void CellView::update(const ca::Cell& cell) {
    const auto& color = pickColor(cell);
    for (auto&& vertex : GlProxy{firstVertex, 4}) {
        updateColor(vertex.color, color);
    }
}
