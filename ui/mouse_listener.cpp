#include <ui/mouse_listener.h>

namespace ui {

void MouseListener::setPosition(ut::Pointf position) {
    if (state_ == State::Drag) {
        dragCallback_(position);
    }

    position_ = position;
}

void MouseListener::setLeftButtonPressed(bool pressed) {
    if (!leftButtonPressed_ && pressed) {
        state_ = State::Drag;
        startDragCallback_(position_);
    }
    if (leftButtonPressed_ && !pressed) {
        state_ = State::Idle;
    }
    leftButtonPressed_ = pressed;
}

void MouseListener::setRightButtonPressed(bool pressed) {
    rightButtonPressed_ = pressed;
}

std::string MouseListener::makeCaption() const {
    return "(" + std::to_string(position_.x) +
           ", " + std::to_string(position_.y) + ")" +
           " LMB: " + std::to_string(leftButtonPressed_) +
           " RMB: " + std::to_string(rightButtonPressed_);
}

}
