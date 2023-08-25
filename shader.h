#pragma once

#include <string_view>

class Shader {
public:

    Shader(std::string_view vertextShaderSource,
           std::string_view fragmentShaderSource);
    ~Shader();

    void bind() const;
    void unbind() const;

    void setUniform4f(std::string_view name,
                      float v0,
                      float v1,
                      float v2,
                      float v3);

private:
    unsigned int id;
};
