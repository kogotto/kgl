#include "shader.h"

Shader::Shader(std::string_view vertextShaderSource,
               std::string_view fragmentShaderSource) {
}

Shader::~Shader() {
}

void Shader::bind() const {
}

void Shader::unbind() const {
}

void Shader::setUniform4f(std::string_view name,
                          float v0,
                          float v1,
                          float v2,
                          float v3) {
}

