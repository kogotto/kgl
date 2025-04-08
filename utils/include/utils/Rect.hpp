#pragma once

#include <utils/Point.hpp>

namespace ut {

template <typename T> struct Rect {
    T left{};
    T top{};
    T right{};
    T bottom{};

    Point<T> leftTop() const { return {left, top}; }

    Point<T> rightTop() const { return {right, top}; }

    Point<T> leftBottom() const { return {left, bottom}; }

    Point<T> rightBottom() const { return {right, bottom}; }

    template <typename U = T> bool contains(ut::Point<U> position) const {
        return (left < position.x && position.x < right) &&
               (bottom < position.y && position.y < top);
    }
};

using Rectf = Rect<float>;

} // namespace ut
