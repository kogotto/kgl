#pragma once

#include <utils/point.h>

namespace ut {

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

} // namespace ut
