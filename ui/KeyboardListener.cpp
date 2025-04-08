#include <ui/KeyboardListener.hpp>

#include <GLFW/glfw3.h>

namespace ui {
namespace {} // namespace
} // namespace ui

namespace ui {

void KeyboardListener::keyPressed(int key) { keys_[key] = true; }

void KeyboardListener::keyReleased(int key) {
    if (keys_[key]) {
        callCallback(key);
    }
    keys_[key] = false;
}

void KeyboardListener::setKeyPressedCallback(int key, Callback callback) {
    callbacks_[key] = std::move(callback);
}

void KeyboardListener::callCallback(int key) {
    const auto it = callbacks_.find(key);
    if (it == callbacks_.end()) {
        return;
    }
    (it->second)();
}

} // namespace ui
