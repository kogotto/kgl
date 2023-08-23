#include <iostream>
#include <string>
#include <string_view>
#include <fstream>
#include <sstream>
#include <filesystem>

#define GLEW_NO_GLU
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "debug.h"

#include "vertex_buffer.h"
#include "index_buffer.h"
#include "vertex_array.h"

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

struct ShaderParseResult {
    std::string vertex;
    std::string fragment;
};

ShaderParseResult parseShaderFile(const std::string& filename) {
    std::ifstream stream(filename);
    if (!stream.is_open()) {
        std::cout << "Failed to open shader source file " << filename << std::endl;
        std::cout << "Current dir is " << std::filesystem::current_path() << std::endl;
        return {};
    }


    std::stringstream vertextStream;
    std::stringstream fragmentStream;

    std::stringstream* current = nullptr;

    std::string line;
    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                current = &vertextStream;
            } else if (line.find("fragment") != std::string::npos) {
                current = &fragmentStream;
            }
        } else {
            if (!current) {
                std::cout << "Warning: Next string do not belong to any shader type" << std::endl;
                std::cout << line << std::endl;
            } else {
                (*current) << line << '\n';
            }
        }
    }

    return {vertextStream.str(), fragmentStream.str()};
}

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
    const unsigned int id = GLCALL(glCreateShader(type));
    const char* sourceBegin = source.data();
    const int sourceSize = source.size();

    GLCALL(glShaderSource(id, 1, &sourceBegin, &sourceSize));
    GLCALL(glCompileShader(id));

    int result;
    GLCALL(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE) {
        int length;
        GLCALL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*) alloca(length);
        GLCALL(glGetShaderInfoLog(id, length, &length, message));
        std::cout << "Failed to compile " <<
            shaderTypeToStr(type) << " shader!" << std::endl;
        std::cout << message << std::endl;
        GLCALL(glDeleteShader(id));
        return 0;
    }

    return id;
}

unsigned int compileProgram(std::string_view vertexShaderSource, std::string_view fragmentShaderSource) {
    const unsigned int id = GLCALL(glCreateProgram());
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    GLCALL(glAttachShader(id, vs));
    GLCALL(glAttachShader(id, fs));
    GLCALL(glLinkProgram(id));

    GLCALL(glValidateProgram(id));

    GLCALL(glDeleteShader(vs));
    GLCALL(glDeleteShader(fs));

    return id;
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

    VertexArray vao;
    VertexBuffer vb(positions, sizeof(positions));

    VertexBufferLayout layout;
    layout.push<float>(2);

    vao.addBuffer(vb, layout);

    vao.bind();

    IndexBuffer ib(indices, 6);

    auto [vertexShaderSource, fragmentShaderSource] =
        parseShaderFile("res/shaders/basic.shader");

    unsigned int shader = compileProgram(vertexShaderSource, fragmentShaderSource);
    GLCALL(glUseProgram(shader));

    const int location = GLCALL(glGetUniformLocation(shader, "u_Color"));

    float r = 0.5;
    float increment = 0.05;

    while (!glfwWindowShouldClose(window)) {
        GLCALL(glClear(GL_COLOR_BUFFER_BIT));

        GLCALL(glUniform4f(location, r, 0.3f, 0.8f, 1.0));

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
