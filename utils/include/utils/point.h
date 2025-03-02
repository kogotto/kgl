#pragma once

#include <iostream>

namespace ut {

template <typename T>
struct Point {
    Point() = default;
    Point(T x, T y)
        : x{x}
        , y{y}
    {}

    template <typename U = T>
    explicit Point(const Point<U> other)
        : x(other.x)
        , y(other.y)
    {}

    T x{};
    T y{};
};

template <typename T>
inline Point<T> operator+(Point<T> lhs, Point<T> rhs) {
    return {
        lhs.x + rhs.x,
        lhs.y + rhs.y
    };
}

template <typename T>
inline Point<T> operator-(Point<T> lhs, Point<T> rhs) {
    return {
        lhs.x - rhs.x,
        lhs.y - rhs.y
    };
}

template <typename T>
std::ostream& operator<<(std::ostream& stream, Point<T> point) {
    return stream << "{" << point.x << ", " << point.y << "}";
}

using Pointf = Point<float>;

} // namespace ut
