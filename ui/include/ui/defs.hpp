#pragma once

#include <utils/Point.hpp>

namespace ui {

constexpr int winWidth = 1280;
constexpr int winHeight = 960;

template <typename T>
ut::Pointf rawToGl(ut::Point<T> rawPos) {
    const float xGl = static_cast<float>(rawPos.x) / ui::winWidth * 2 - 1.f;
    const float yGl = -static_cast<float>(rawPos.y) / ui::winHeight * 2 + 1.f;
    return {xGl, yGl};
}

} // namespace ui
