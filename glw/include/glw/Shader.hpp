#pragma once

#include <string>

#include <glw/UniformLocation.hpp>

namespace glw {

class Shader {
public:
    explicit Shader(unsigned int id)
        : id{id} {}
    ~Shader();

    static Shader fromFile(const std::string& filepath);

    void bind() const;
    void unbind() const;

    UniformLocation getUniformLocation(const std::string& name) const;

private:
    unsigned int id;
};

} // namespace glw
