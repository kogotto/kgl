#pragma once

#include <functional>
#include <unordered_map>

namespace ui {

class KeyboardListener {
public:
    using Callback = std::function<void()>;

    void keyPressed(int key);
    void keyReleased(int key);

    void setKeyPressedCallback(int key, Callback callback);

private:
    void callCallback(int key);

    std::unordered_map<int, bool> keys_;
    std::unordered_map<int, Callback> callbacks_;
};

} // namespace ui
