#pragma once

#include <cell.h>
#include <utils/rect.h>

class Vertex;

class CellView {
public:
    CellView() noexcept
        : firstVertex(nullptr)
    {}

    CellView(Vertex& vertex) noexcept
        : firstVertex(&vertex)
    {}

    void setPosition(ut::Rect newPosition) {
        position = newPosition;
    }

    void update(const ca::Cell& cell, ut::Point origin);
private:
    Vertex* firstVertex;
    ut::Rect position;
};
