#include <iostream>
#include <string_view>

#define GLEW_NO_GLU
#include <GL/glew.h>
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

const char* shaderTypeToStr(unsigned int type) {
    switch (type) {
    case GL_VERTEX_SHADER:
        return "vertex";
    case GL_FRAGMENT_SHADER:
        return "fragment";
    default:
        return "unknown shader type";
    };
}

unsigned int compileShader(unsigned int type, std::string_view source) {
    const unsigned int id = glCreateShader(type);
    const char* sourceBegin = source.data();
    const int sourceSize = source.size();

    glShaderSource(id, 1, &sourceBegin, &sourceSize);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*) alloca(length);
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " <<
            shaderTypeToStr(type) << " shader!" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

unsigned int compileProgram(std::string_view vertexShaderSource, std::string_view fragmentShaderSource) {
    const unsigned int id = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    glAttachShader(id, vs);
    glAttachShader(id, fs);
    glLinkProgram(id);

    glValidateProgram(id);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return id;
}

} // namespace

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

    if (glewInit() != GLEW_OK) {
        std::cout << "glew cant init" << std::endl;
        return GLEW_INIT_FAILED;
    }

    float positions[] = {
        -0.5f, 0.0f,
         0.5f, 0.0f,
         0.0f, 0.5f
    };

    unsigned int vb = 0;
    glGenBuffers(1, &vb);
    glBindBuffer(GL_ARRAY_BUFFER, vb);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    const std::string_view vertexShaderSource =
        "#version 330 core\n"
        "layout(location = 0) in vec4 position;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = position;\n"
        "}\n"
    ;

    const std::string_view fragmentShaderSource =
        "#version 330 core\n"
        "out vec4 color;\n"
        "void main()\n"
        "{\n"
        "   color = vec4(1.0, 1.0, 0.0, 1.0);\n"
        "}\n"
    ;

    unsigned int shader = compileProgram(vertexShaderSource, fragmentShaderSource);
    glUseProgram(shader);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}
