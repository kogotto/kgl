#pragma once

#include <utils/point.h>

namespace ut {

template <typename T>
struct Rect {
    T left;
    T top;
    T right;
    T bottom;

    Point<T> leftTop() const {
        return {left, top};
    }

    Point<T> rightTop() const {
        return {right, top};
    }

    Point<T> leftBottom() const {
        return {left, bottom};
    }

    Point<T> rightBottom() const {
        return {right, bottom};
    }
};

using Rectf = Rect<float>;

} // namespace ut
