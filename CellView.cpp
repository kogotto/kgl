#include "CellView.hpp"

#include <utils/Color.hpp>

#include "PrepareViews.hpp"

namespace {

constexpr ut::Color deathColor{1.f, 1.f, 0.f, 1.f};   // yellow
constexpr ut::Color aliveColor{0.f, 0.f, 1.f, 1.f};   // blue
constexpr ut::Color unknownColor{0.f, 0.f, 0.f, 1.f}; // black

const auto& pickColor(ca::Cell cell) {
    switch (cell) {
    case ca::Cell::Died:
        return deathColor;
    case ca::Cell::Alive:
        return aliveColor;
    };

    return unknownColor;
}

} // namespace

void CellView::update(const ca::Cell& cell, ut::Pointf origin,
                      GraphicsData& data) const {
    const auto& color = pickColor(cell);

    const auto leftTop = data.pushVertex(origin + position.leftTop(), color);
    const auto rightTop = data.pushVertex(origin + position.rightTop(), color);
    const auto leftBottom =
        data.pushVertex(origin + position.leftBottom(), color);
    const auto rightBottom =
        data.pushVertex(origin + position.rightBottom(), color);

    data.pushPolygon(leftTop, rightTop, leftBottom);

    data.pushPolygon(rightTop, rightBottom, leftBottom);
}
