#include <iostream>

#define GLEW_NO_GLU
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glw/renderer.h>
#include <ui/defs.hpp>
#include <ui/KeyboardListener.hpp>
#include <ui/mouse_listener.h>

#include <utils/timer.h>
#include "prepare_views.h"
#include "field_view.h"
#include "FieldViewMouseAdapter.hpp"
#include "TimeController.hpp"

namespace
{

struct GLFWTerminator {
    ~GLFWTerminator() {
        glfwTerminate();
    }
};

constexpr int GLFW_INIT_FAILED = -1;
constexpr int GLFW_WINDOW_CREATION_FAILED = -2;
constexpr int GLEW_INIT_FAILED = -3;

constexpr int gKeySpace = 32;
constexpr int gKeyEsc = 256;

struct Holder {
    ui::MouseListener* mouseListener;
    ui::KeyboardListener* keyboardListener;
};

inline Holder& getHolder(GLFWwindow& window) {
    void* rawHolder = glfwGetWindowUserPointer(&window);
    return *static_cast<Holder*>(rawHolder);
}

inline ui::MouseListener& getMouseListener(GLFWwindow& window) {
    return *getHolder(window).mouseListener;
}

inline ui::KeyboardListener& getKeyboardListener(GLFWwindow& window) {
    return *getHolder(window).keyboardListener;
}

inline bool isPressed(int action) {
    switch (action) {
    case GLFW_PRESS: return true;
    case GLFW_RELEASE: return false;
    }

    std::cout << "Unknown mouse button action, action = " << action << std::endl;
    return false;
}

void setMouseCalbacks(GLFWwindow& window, ui::MouseListener& listener) {
    glfwSetCursorPosCallback(&window,
        +[] (GLFWwindow* window, double x, double y) {
            auto& listener = getMouseListener(*window);

            ut::Point rawPos{x, y};
            const auto glPos = ui::rawToGl(rawPos);
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

void setKeyboardCallbacks(GLFWwindow& window, ui::KeyboardListener& listener) {
    glfwSetKeyCallback(&window,
        +[] (GLFWwindow* window, int key, int scancode, int action, int mods) {
            auto& listener = getKeyboardListener(*window);

            switch (action) {
            case GLFW_RELEASE:
                listener.keyReleased(key);
                break;
            case GLFW_PRESS:
            case GLFW_REPEAT:
                listener.keyPressed(key);
                break;
            default:
                std::cout << "Unknown action " << action << std::endl;
            };
        }
    );
}

auto setInputListeners(GLFWwindow& window,
        ui::MouseListener& mouseListener,
        ui::KeyboardListener& keyboardListener) {
    auto holder = std::make_unique<Holder>(&mouseListener, &keyboardListener);
    glfwSetWindowUserPointer(&window, holder.get());

    setMouseCalbacks(window, mouseListener);
    setKeyboardCallbacks(window, keyboardListener);
    return holder;
}

} // namespace

int main() {
    if (!glfwInit()) {
        std::cout << "glfw cant init" << std::endl;
        return GLFW_INIT_FAILED;
    }
    const GLFWTerminator autoGlfwTerminator;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(ui::winWidth, ui::winHeight, "Hello GLFW", NULL, NULL);
    if (!window) {
        std::cout << "glfw window creation failed" << std::endl;
        return GLFW_WINDOW_CREATION_FAILED;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) {
        std::cout << "glew cant init" << std::endl;
        return GLEW_INIT_FAILED;
    }

    glw::Renderer renderer;

    std::cout << renderer.getOpenGlVersion() << std::endl;

    constexpr ut::normal_index_t sideSize{100};
    constexpr ca::NormalizedIndex fieldSize{sideSize, sideSize};
    const ut::Rect screenRect{-0.7f, 0.7f, 0.7f, -0.7f};

    ca::FieldModel field{fieldSize};
    ca::insertRPentamino(field, ca::CellIndex{fieldSize} / 2);

    GraphicsData gd{field.getSize()};
    FieldView fieldView{fieldSize, screenRect};

    ui::MouseListener mouseListener(*window);
    ui::KeyboardListener keyboardListener;
    auto holder = setInputListeners(*window, mouseListener, keyboardListener);

    FieldViewMouseAdapter viewMouseAdapter{fieldView};
    mouseListener.setStartDragCallback(
        [&viewMouseAdapter] (ut::Pointf mousePos) {
            viewMouseAdapter.startDrag(mousePos);
        }
    );
    mouseListener.setDragCallback(
        [&viewMouseAdapter] (ut::Pointf mousePos) {
            viewMouseAdapter.drag(mousePos);
        }
    );

    TimeController timeController{
        std::chrono::milliseconds{25},
        [&]() {
            field = ca::nextGeneration(field);
            fieldView.update(field, gd);
            gd.update();
        }
    };

    keyboardListener.setKeyPressedCallback(
        gKeySpace,
        [&timeController]() {
            timeController.togglePause();
        }
    );

    keyboardListener.setKeyPressedCallback(
        gKeyEsc,
        [window]() {
            glfwSetWindowShouldClose(window, 1);
        }
    );

    fieldView.update(field, gd);
    gd.update();

    while (!glfwWindowShouldClose(window)) {
        renderer.clear();

        timeController.tick();

        renderer.draw(gd.va, gd.i, gd.shader);

        glfwSetWindowTitle(window, mouseListener.makeCaption().c_str());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}
