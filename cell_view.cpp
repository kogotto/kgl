#include "cell_view.h"

#include "storage.h"

namespace {

using Color = float[4];

constexpr Color deathColor{0.f, 0.f, 0.f, 0.f};
constexpr Color aliveColor{1.f, 1.f, 1.f, 1.f};
constexpr Color unknownColor{1.f, 0.f, 0.f, 0.f};

const auto& pickColor(Cell cell) {
    switch (cell) {
    case Cell::Died: return deathColor;
    case Cell::Alive: return aliveColor;
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

CellView::CellView(const Cell& cell, Vertex& vertex)
    : cell{&cell}
    , cellProxy{&vertex, 4}
{}

void CellView::update() {
    const auto& color = pickColor(*cell);
    for (auto&& vertex : cellProxy) {
        updateColor(vertex.color, color);
    }
}
