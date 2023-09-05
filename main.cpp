#include <iostream>

#include "vertex_buffer.h"
#include "index_buffer.h"
#include "vertex_array.h"
#include "shader.h"
#include "renderer.h"

#include <GLFW/glfw3.h>

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

    Renderer renderer;

    std::cout << renderer.getOpenGlVersion() << std::endl;

    float positions[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    const std::string shaderFilepath{"res/shaders/basic.shader"};
    const std::string colorUniformName{"u_Color"};

    VertexBuffer vb(positions, sizeof(positions));
    VertexBufferLayout layout;
    layout.push<float>(2);

    VertexArray vao;
    vao.addBuffer(vb, layout);

    IndexBuffer ib(indices, 6);

    auto shader = Shader::fromFile(shaderFilepath);
    auto location = shader.getUniformLocation(colorUniformName);

    float r = 0.5;
    float increment = 0.05;

    while (!glfwWindowShouldClose(window)) {
        renderer.clear();

        shader.bind();
        location.set(r, 0.3f, 0.8f, 1.0);

        renderer.draw(vao, ib, shader);

        if (r > 1.0) {
            increment = -0.05;
        } else if (r < 0.0) {
            increment = +0.05;
        }
        r += increment;

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}
