#include <iostream>

#define GLEW_NO_GLU
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glw/renderer.h>
#include <ui/defs.hpp>
#include <ui/mouse_listener.h>

#include "timer.h"
#include "prepare_views.h"
#include "field_view.h"
#include "FieldViewMouseAdapter.hpp"

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

    ui::MouseListener mouseListener(*window);

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

    fieldView.update(field, gd);
    gd.update();

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
