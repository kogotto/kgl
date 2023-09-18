#include "vertex_buffer.h"

#include <utility>

#define GLEW_NO_GLU
#include <GL/glew.h>

#include "debug.h"

VertexBuffer::VertexBuffer(const void* data, std::ptrdiff_t size) {
    GLCALL(glGenBuffers(1, &id));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, id));
    GLCALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));

}

VertexBuffer::VertexBuffer(VertexBuffer&& rhs) noexcept
    : id{std::exchange(rhs.id, 0)}
{}

VertexBuffer& VertexBuffer::operator=(VertexBuffer&& rhs) noexcept {
    std::swap(id, rhs.id);
    return *this;
}

VertexBuffer::~VertexBuffer() {
    GLCALL(glDeleteBuffers(1, &id));
}

void VertexBuffer::bind() const {
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, id));
}

void VertexBuffer::unbind() const {
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
