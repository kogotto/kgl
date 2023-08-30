#pragma once

#include <string_view>

class Shader {
public:

    explicit Shader(unsigned int id)
        : id{id} {}
    ~Shader();

    static Shader fromFile(std::string_view filepath);

    void bind() const;
    void unbind() const;

    unsigned int getUniformLocation(std::string_view name) const;

    void setUniform4f(std::string_view name,
                      float v0,
                      float v1,
                      float v2,
                      float v3);

private:
    unsigned int id;
};
