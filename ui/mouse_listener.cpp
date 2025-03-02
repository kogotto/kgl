#include <ui/mouse_listener.h>

#include <GLFW/glfw3.h>

#include <ui/defs.hpp>

namespace ui {
namespace {

inline ui::MouseListener& getMouseListener(GLFWwindow& window) {
    void* rawListener = glfwGetWindowUserPointer(&window);
    return *static_cast<ui::MouseListener*>(rawListener);
}

inline bool isPressed(int action) {
    switch (action) {
    case GLFW_PRESS: return true;
    case GLFW_RELEASE: return false;
    }

    std::cout << "Unknown mouse button action, action = " << action << std::endl;
    return false;
}

void setMouseListener(GLFWwindow& window, MouseListener& listener) {
    glfwSetWindowUserPointer(&window, &listener);

    glfwSetCursorPosCallback(&window,
        +[] (GLFWwindow* window, double x, double y) {
            auto& listener = getMouseListener(*window);

            ut::Point rawPos{x, y};
            const auto glPos = rawToGl(rawPos);
            listener.setPosition(glPos);
        }
    );

    glfwSetMouseButtonCallback(&window,
        +[] (GLFWwindow* window, int button, int action, int mods) {
            auto& listener = getMouseListener(*window);

            switch (button) {
            case GLFW_MOUSE_BUTTON_LEFT:
                listener.setLeftButtonPressed(isPressed(action));
                break;
            case GLFW_MOUSE_BUTTON_RIGHT:
                listener.setRightButtonPressed(isPressed(action));
                break;
            default:
                std::cout << "Unknown mouse button pressed, button = " <<
                         button << std::endl;
            }
        }
    );
}

} // namespace
} // namespace ui

namespace ui {

MouseListener::MouseListener(GLFWwindow& window)
{
    setMouseListener(window, *this);
}

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
