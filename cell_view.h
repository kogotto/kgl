#pragma once

#include <cell.h>
#include <utils/rect.h>

class Vertex;
class GraphicsData;

class CellView {
public:
    void setPosition(ut::Rect newPosition) {
        position = newPosition;
    }

    void update(const ca::Cell& cell, ut::Point origin, GraphicsData& data);
private:
    ut::Rect position;
};
