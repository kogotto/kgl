#include "cell_view.h"

#include <utils/color.h>

#include "prepare_views.h"

namespace {

constexpr ut::Color deathColor{1.f, 1.f, 0.f, 1.f};   // yellow
constexpr ut::Color aliveColor{0.f, 0.f, 1.f, 1.f};   // blue
constexpr ut::Color unknownColor{0.f, 0.f, 0.f, 1.f}; // black

const auto& pickColor(ca::Cell cell) {
    switch (cell) {
    case ca::Cell::Died: return deathColor;
    case ca::Cell::Alive: return aliveColor;
    };

    return unknownColor;
}

} // namespace

void CellView::update(const ca::Cell& cell, ut::Point origin, GraphicsData& data) {
    const auto& color = pickColor(cell);

    const auto leftTop = data.pushVertex(position.leftTop(), color);
    const auto rightTop = data.pushVertex(position.rightTop(), color);
    const auto leftBottom = data.pushVertex(position.leftBottom(), color);
    const auto rightBottom = data.pushVertex(position.rightBottom(), color);

    data.pushPolygon(
        leftTop,
        rightTop,
        leftBottom
    );

    data.pushPolygon(
        rightTop,
        rightBottom,
        leftBottom
    );
}
