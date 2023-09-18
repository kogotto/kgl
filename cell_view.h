#pragma once

#include <span>

#include <cell.h>

class Vertex;

class CellView {
public:
    using GlProxy = std::span<Vertex, 4>;

    CellView(const Cell& cell, Vertex& vertex);

    void update();
private:
    const Cell* cell;
    GlProxy cellProxy;
};
