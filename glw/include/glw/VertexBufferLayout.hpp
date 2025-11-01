#pragma once

#include <cassert>
#include <cstdint>
#include <vector>

#define GLEW_NO_GLU
#include <GL/glew.h>

namespace glw {

namespace detail {

constexpr GLboolean toGlBoolean(bool b) { return b ? GL_TRUE : GL_FALSE; }

template <typename T> constexpr GLenum toGlType();

template <> constexpr GLenum toGlType<float>() { return GL_FLOAT; }

template <> constexpr GLenum toGlType<unsigned int>() {
    return GL_UNSIGNED_INT;
}

template <> constexpr GLenum toGlType<unsigned char>() {
    return GL_UNSIGNED_BYTE;
}

constexpr GLboolean isNormalized(GLenum glType) {
    switch (glType) {
    case GL_FLOAT:
        return GL_FALSE;
    case GL_UNSIGNED_INT:
        return GL_FALSE;
    case GL_UNSIGNED_BYTE:
        return GL_TRUE;
    };
    assert(false);
    return 0;
}

} // namespace detail

struct VertexBufferLayoutElement {
    unsigned int count;
    unsigned int type;
    unsigned int normalized;
    std::ptrdiff_t offset;
};

class VertexBufferLayout {
public:
    const auto& getElements() const { return elements; };

    auto getStride() const { return stride; }

    template <typename T> void push(unsigned int count) {
        auto glType = detail::toGlType<T>();
        elements.emplace_back(count, glType,
                              detail::toGlBoolean(detail::isNormalized(glType)),
                              stride);
        stride += count * sizeof(T);
    }

private:
    std::vector<VertexBufferLayoutElement> elements;
    unsigned int stride{0};
};

} // namespace glw
