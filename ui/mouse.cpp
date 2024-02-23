#include <ui/mouse.h>

namespace ui {

void Mouse::setPosition(double x, double y) {
    x_ = x;
    y_ = y;
}

std::string Mouse::makeCaption() const {
    return "(" + std::to_string(x_) + ", " + std::to_string(y_) + ")";
}

}
