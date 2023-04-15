#include <iostream>
#include <string>
#include <string_view>
#include <fstream>
#include <sstream>
#include <filesystem>

#define GLEW_NO_GLU
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLASSERT(x) { if (!(x)) std::abort(); }

namespace {

void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

struct GLErrorCode {
    GLenum code;
};

std::ostream& operator<<(std::ostream& stream, GLErrorCode code) {
    return stream <<
        std::hex << std::showbase <<
        code.code <<
        std::noshowbase << std::dec;
}

void GLLogError(GLErrorCode code, const char* function, const char* file, int line) {
    std::cout <<
        "[OpenGl] error, code = " << code <<
        " in call " << function <<
        " on " << file << ":" << line <<
        std::endl;
}

bool GLCheckErrors(const char* function, const char* file, int line) {
    int errorsCount = 0;
    for (auto errorCode = glGetError(); errorCode != GL_NO_ERROR; errorCode = glGetError()) {
        ++errorsCount;
        GLLogError({errorCode}, function, file, line);
    }

    return errorsCount == 0;
}

struct GLErrorHandler {
    GLErrorHandler(const char* function, const char* file, int line)
        : function{function}
        , file{file}
        , line{line} {
        GLClearError();
    }
    ~GLErrorHandler() {
        GLASSERT(GLCheckErrors(function, file, line));
    }
private:
    const char* function;
    const char* file;
    int line;
};

} // namespace

#define GLCALL(x)                              \
    [&] {                                                \
        GLErrorHandler handler{#x, __FILE__, __LINE__};  \
        return (x);                                      \
    } ()


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
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    unsigned int vb = 0;
    glGenBuffers(1, &vb);
    glBindBuffer(GL_ARRAY_BUFFER, vb);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    unsigned int ib = 0;
    glGenBuffers(1, &ib);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    auto [vertexShaderSource, fragmentShaderSource] =
        parseShaderFile("res/shaders/basic.shader");

    unsigned int shader = compileProgram(vertexShaderSource, fragmentShaderSource);
    glUseProgram(shader);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}
