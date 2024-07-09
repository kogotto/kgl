#include <iostream>

#define GLEW_NO_GLU
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glw/renderer.h>
#include <ui/mouse_listener.h>

#include "timer.h"
#include "prepare_views.h"
#include "field_view.h"

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

inline bool isPressed(int action) {
    switch (action) {
    case GLFW_PRESS: return true;
    case GLFW_RELEASE: return false;
    }

    std::cout << "Unknown mouse button action, action = " << action << std::endl;
    return false;
}

inline ui::MouseListener& getMouseListener(GLFWwindow& window) {
    void* rawListener = glfwGetWindowUserPointer(&window);
    return *static_cast<ui::MouseListener*>(rawListener);
}

void setMouseListener(GLFWwindow& window, ui::MouseListener& listener) {
    glfwSetWindowUserPointer(&window, &listener);

    glfwSetCursorPosCallback(&window,
        +[] (GLFWwindow* window, double x, double y) {
            auto& listener = getMouseListener(*window);

            listener.setPosition(x, y);
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

    Timer time{std::chrono::milliseconds{25}};

    ui::MouseListener mouseListener{
        [&fieldView] (int oldX, int oldY, int newX, int newY) {
            const float x = static_cast<float>(newX) / ui::winWidth * 2 - 1.f;
            const float y = -static_cast<float>(newY) / ui::winHeight * 2 + 1.f;
            fieldView.setOrigin(x, y);
        }
    };
    setMouseListener(*window, mouseListener);

    while (!glfwWindowShouldClose(window)) {
        renderer.clear();

        if (time.hasCome()) {
            field = ca::nextGeneration(field);
            fieldView.update(field, gd);
            gd.update();
        }

        renderer.draw(gd.va, gd.i, gd.shader);

        glfwSetWindowTitle(window, mouseListener.makeCaption().c_str());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}
