#include <iostream>
#include <string>

#define GLEW_NO_GLU
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glw/renderer.h>
#include <ui/mouse.h>

#include "timer.h"
#include "prepare_views.h"

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

void SetCursorPosCallback(GLFWwindow& window, ui::Mouse& receiver) {
    glfwSetWindowUserPointer(&window, &receiver);

    glfwSetCursorPosCallback(&window,
        +[] (GLFWwindow* window, double x, double y) {
            void* rawReceiver = glfwGetWindowUserPointer(window);

            auto& receiver = *static_cast<ui::Mouse*>(rawReceiver);
            receiver.setPosition(x, y);
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
    ca::FieldModel field{fieldSize};
    ca::insertRPentamino(field, ca::CellIndex{fieldSize} / 2);

    GraphicsData gd{field.getSize()};
    Timer time{std::chrono::milliseconds{25}};

    ui::Mouse mouse;
    SetCursorPosCallback(*window, mouse);

    while (!glfwWindowShouldClose(window)) {
        renderer.clear();

        if (time.hasCome()) {
            field = ca::nextGeneration(field);
        }

        gd.update(field);
        renderer.draw(gd.va, gd.i.handler(), gd.shader);

        glfwSetWindowTitle(window, mouse.makeCaption().c_str());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}
