#pragma once

#include <cell.h>

class Vertex;

class CellView {
public:
    CellView() noexcept
        : firstVertex(nullptr)
    {}

    CellView(Vertex& vertex) noexcept
        : firstVertex(&vertex)
    {}

    void update(const Cell& cell);
private:
    Vertex* firstVertex;
};
