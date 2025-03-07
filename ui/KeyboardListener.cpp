#include <ui/KeyboardListener.hpp>

#include <GLFW/glfw3.h>

#include <iostream>

namespace ui {
namespace {

} // namespace
} // namespace ui

namespace ui {

void KeyboardListener::keyPressed(int key) {
    std::cout << "Key " << key << " pressed" << std::endl;
}

void KeyboardListener::keyReleased(int key) {
    std::cout << "Key " << key << " released" << std::endl;
}

} // namespace ui
