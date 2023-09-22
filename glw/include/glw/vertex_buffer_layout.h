#pragma once

#include <vector>
#include <cassert>
#include <cstdint>

#define GLEW_NO_GLU
#include <GL/glew.h>

namespace {

constexpr GLboolean toGlBoolean(bool b) {
    return b
        ? GL_TRUE
        : GL_FALSE;
}

template <typename T>
constexpr GLenum toGlType();

template <>
constexpr GLenum toGlType<float>() {
    return GL_FLOAT;
}

template <>
constexpr GLenum toGlType<unsigned int>() {
    return GL_UNSIGNED_INT;
}

template <>
constexpr GLenum toGlType<unsigned char>() {
    return GL_UNSIGNED_BYTE;
}

constexpr GLboolean isNormalized(GLenum glType) {
    switch (glType) {
        case GL_FLOAT: return GL_FALSE;
        case GL_UNSIGNED_INT: return GL_FALSE;
        case GL_UNSIGNED_BYTE: return GL_TRUE;
    };
    assert(false);
    return 0;
}

} // namespace

struct VertexBufferLayoutElement {
    unsigned int count;
    unsigned int type;
    unsigned int normalized;
    std::ptrdiff_t offset;
};

class VertexBufferLayout {
public:
    const auto& getElements() const {
        return elements;
    };

    auto getStride() const {
        return stride;
    }

    template<typename T>
    void push(unsigned int count) {
        auto glType = toGlType<T>();
        elements.emplace_back(
            count,
            glType,
            toGlBoolean(isNormalized(glType)),
            stride
        );
        stride += count * sizeof(T);
    }

private:
    std::vector<VertexBufferLayoutElement> elements;
    unsigned int stride{0};
};
