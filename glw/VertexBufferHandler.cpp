#include <glw/VertexBufferHandler.hpp>

#include <utility>

#define GLEW_NO_GLU
#include <GL/glew.h>

#include <glw/Debug.hpp>

namespace glw {

VertexBufferHandler::VertexBufferHandler(const void* data,
                                         std::ptrdiff_t size) {
    GLCALL(glGenBuffers(1, &id));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, id));
    GLCALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));
}

VertexBufferHandler::VertexBufferHandler(VertexBufferHandler&& rhs) noexcept
    : id{std::exchange(rhs.id, 0)} {}

VertexBufferHandler&
VertexBufferHandler::operator=(VertexBufferHandler&& rhs) noexcept {
    std::swap(id, rhs.id);
    return *this;
}

VertexBufferHandler::~VertexBufferHandler() { GLCALL(glDeleteBuffers(1, &id)); }

void VertexBufferHandler::update(const void* data, std::ptrdiff_t size) const {
    bind();
    GLCALL(glBufferSubData(GL_ARRAY_BUFFER, 0, size, data));
}

void VertexBufferHandler::bind() const {
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, id));
}

void VertexBufferHandler::unbind() const {
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

} // namespace glw
