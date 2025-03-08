#pragma once

#include <cell-autom/Cell.hpp>
#include <utils/rect.h>

class Vertex;
class GraphicsData;

class CellView {
public:
    void setPosition(ut::Rectf newPosition) {
        position = newPosition;
    }

    void update(const ca::Cell& cell, ut::Pointf origin, GraphicsData& data) const;
private:
    ut::Rectf position;
};
