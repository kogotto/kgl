#include <glw/Shader.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

#define GLEW_NO_GLU
#include <GL/glew.h>

#include <glw/Debug.hpp>

namespace glw {

namespace {

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

Shader::~Shader() {
    GLCALL(glDeleteProgram(id));
}

Shader Shader::fromFile(const std::string& filepath) {
    auto [vertexShaderSource, fragmentShaderSource] =
        parseShaderFile(filepath);
    return Shader{compileProgram(vertexShaderSource, fragmentShaderSource)};
}

void Shader::bind() const {
    GLCALL(glUseProgram(id));
}

void Shader::unbind() const {
    GLCALL(glUseProgram(0));
}

UniformLocation Shader::getUniformLocation(const std::string& name) const {
    auto uniformId = GLCALL(glGetUniformLocation(id, name.data()));
    return UniformLocation{uniformId};
}

} // namespace glw
