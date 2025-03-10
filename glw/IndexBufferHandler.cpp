#include <glw/IndexBufferHandler.hpp>

#include <utility>

#define GLEW_NO_GLU
#include <GL/glew.h>

#include <glw/Debug.hpp>

namespace glw {

IndexBufferHandler::IndexBufferHandler(const unsigned int* data, std::ptrdiff_t count)
{
    GLCALL(glGenBuffers(1, &id));
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id));
    GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));

}

IndexBufferHandler::IndexBufferHandler(IndexBufferHandler&& rhs) noexcept
    : id{std::exchange(rhs.id, 0)}
{}

IndexBufferHandler& IndexBufferHandler::operator=(IndexBufferHandler&& rhs) noexcept {
    std::swap(id, rhs.id);
    return *this;
}

IndexBufferHandler::~IndexBufferHandler() {
    GLCALL(glDeleteBuffers(1, &id));
}

void IndexBufferHandler::update(const unsigned int* data, std::ptrdiff_t size) {
    bind();
    GLCALL(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, size, data));
}

void IndexBufferHandler::bind() const {
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id));
}

void IndexBufferHandler::unbind() const {
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

} // namespace glw
