#pragma once

namespace ut {

struct Point {
    float x;
    float y;
};

inline Point operator+(Point lhs, Point rhs) {
    return {
        lhs.x + rhs.x,
        lhs.y + rhs.y
    };
}

inline Point operator-(Point lhs, Point rhs) {
    return {
        lhs.x - rhs.x,
        lhs.y - rhs.y
    };
}

} // namespace ut
