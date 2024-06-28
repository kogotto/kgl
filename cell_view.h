#pragma once

#include <cell.h>

class Vertex;

struct Point {
    float x;
    float y;
};

struct Rect {
    float left;
    float top;
    float right;
    float bottom;

    Point leftTop() const {
        return {left, top};
    }

    Point rightTop() const {
        return {right, top};
    }

    Point leftBottom() const {
        return {left, bottom};
    }

    Point rightBottom() const {
        return {right, bottom};
    }
};

class CellView {
public:
    CellView() noexcept
        : firstVertex(nullptr)
    {}

    CellView(Vertex& vertex) noexcept
        : firstVertex(&vertex)
    {}

    void setPosition(Rect newPosition) {
        position = newPosition;
    }

    void update(const ca::Cell& cell);
private:
    Vertex* firstVertex;
    Rect position;
};
