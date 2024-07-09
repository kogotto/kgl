#pragma once

#include <cell.h>
#include <utils/rect.h>

class Vertex;
class GraphicsData;

class CellView {
public:
    void setPosition(ut::Rectf newPosition) {
        position = newPosition;
    }

    void update(const ca::Cell& cell, ut::Pointf origin, GraphicsData& data);
private:
    ut::Rectf position;
};
