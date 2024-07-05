#include <ui/mouse_listener.h>

namespace ui {
namespace {

MouseListener::Callback prepareCallback(MouseListener::Callback callback) {
    if (callback) {
        return callback;
    }

    return [] (int, int, int, int) {};
}

} // namespace
} // namespace ui

namespace ui {

MouseListener::MouseListener(Callback callback)
    : callback_{prepareCallback(std::move(callback))}
{}

void MouseListener::setPosition(double x, double y) {
    callback_(x_, y_, x, y);

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
