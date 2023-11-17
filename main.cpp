#include <iostream>

#define GLEW_NO_GLU
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glw/renderer.h>
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
constexpr int GLFW_WINDOW_CREATION_FAILED = -1;
constexpr int GLEW_INIT_FAILED = -3;

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

    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello GLFW", NULL, NULL);
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

    ca::FieldModel field{32, 32};
    ca::insertGlider(field, ca::CellIndex{ca::RowIndex{0}, ca::ColIndex{0}});
    ca::insertStick(field, ca::CellIndex{ca::RowIndex{10}, ca::ColIndex{10}});
    GraphicsData gd{field.getSize()};
    Timer time{std::chrono::milliseconds{250}};

    while (!glfwWindowShouldClose(window)) {
        renderer.clear();

        if (time.hasCome()) {
            field = ca::nextGeneration(field);
        }

        gd.update(field);
        renderer.draw(gd.va, gd.ib, gd.shader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}
