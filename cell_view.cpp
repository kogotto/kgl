#include "cell_view.h"

#include <span>

#include <utils/color.h>

#include "storage.h"

namespace {

using GlProxy = std::span<Vertex, 4>;

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

void updateColor(ut::Color& target, const ut::Color& source) {
    target[0] = source[0];
    target[1] = source[1];
    target[2] = source[2];
    target[3] = source[3];
}

void updatePosition(float target[2], ut::Point source) {
    target[0] = source.x;
    target[1] = source.y;
}

} // namespace

void CellView::update(const ca::Cell& cell, ut::Point origin) {
    GlProxy vertices{firstVertex, 4};
    const auto& color = pickColor(cell);
    for (auto&& vertex : vertices) {
        updateColor(vertex.color, color);
    }

    updatePosition(vertices[0].position, origin + position.leftTop());
    updatePosition(vertices[1].position, origin + position.rightTop());
    updatePosition(vertices[2].position, origin + position.leftBottom());
    updatePosition(vertices[3].position, origin + position.rightBottom());
}

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
