#include <iostream>

#define GLEW_NO_GLU
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "debug.h"

#include "vertex_buffer.h"
#include "index_buffer.h"
#include "vertex_array.h"
#include "shader.h"

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

    std::cout << GLCALL(glGetString(GL_VERSION)) << std::endl;

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

    VertexArray vao;
    VertexBuffer vb(positions, sizeof(positions));

    VertexBufferLayout layout;
    layout.push<float>(2);

    vao.addBuffer(vb, layout);

    vao.bind();

    IndexBuffer ib(indices, 6);

    auto shader = Shader::fromFile(shaderFilepath);
    auto location = shader.getUniformLocation(colorUniformName);
    shader.bind();

    float r = 0.5;
    float increment = 0.05;

    while (!glfwWindowShouldClose(window)) {
        GLCALL(glClear(GL_COLOR_BUFFER_BIT));

        location.set(r, 0.3f, 0.8f, 1.0);

        // TODO Bind this call to IndexBuffer to fulfill DRY principle
        GLCALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));

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
