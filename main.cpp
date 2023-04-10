#include <iostream>

#include <GLFW/glfw3.h>

struct GLFWTerminator {
    ~GLFWTerminator() {
        glfwTerminate();
    }
};

int main() {
    std::cout << "Hi" << std::endl;

    if (!glfwInit()) {
        return -1;
    }
    const GLFWTerminator autoGlfwTerminator;

    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello GLFW", NULL, NULL);
    if (!window) {
        return -2;
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
