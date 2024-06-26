#include <ui/mouse_listener.h>

namespace ui {

void MouseListener::setPosition(double x, double y) {
    x_ = x;
    y_ = y;
}

void MouseListener::setLeftButtonPressed(bool pressed) {
    leftButtonPressed_ = pressed;
}

void MouseListener::setRightButtonPressed(bool pressed) {
    rightButtonPressed_ = pressed;
}

std::string MouseListener::makeCaption() const {
    return "(" + std::to_string(x_) + ", " + std::to_string(y_) + ")" +
           " LMB: " + std::to_string(leftButtonPressed_) +
           " RMB: " + std::to_string(rightButtonPressed_);
}

}
