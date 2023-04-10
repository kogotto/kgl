#include <iostream>

#include <GLFW/glfw3.h>

struct GLFWTerminator {
    ~GLFWTerminator() {
        glfwTerminate();
    }
};

constexpr int GLFW_INIT_FAILED = -1;
constexpr int GLFW_WINDOW_CREATION_FAILED = -1;

int main() {
    std::cout << "Hi" << std::endl;

    if (!glfwInit()) {
        std::cout << "glfw cant init" << std::endl;
        return GLFW_INIT_FAILED;
    }
    const GLFWTerminator autoGlfwTerminator;

    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello GLFW", NULL, NULL);
    if (!window) {
        std::cout << "glfw window creation failed" << std::endl;
        return GLFW_WINDOW_CREATION_FAILED;
    }

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f, 0.0f);
        glVertex2f( 0.5f, 0.0f);
        glVertex2f( 0.0f, 0.5f);
        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}
