#pragma once

namespace ut {

template <typename T>
struct Point {
    T x;
    T y;
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

using Pointf = Point<float>;

} // namespace ut
