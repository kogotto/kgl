#include <glw/index_buffer.h>

#include <utility>

#define GLEW_NO_GLU
#include <GL/glew.h>

#include <glw/debug.h>

namespace glw {

IndexBuffer::IndexBuffer(const unsigned int* data, std::ptrdiff_t count)
    : count{count}
{
    GLCALL(glGenBuffers(1, &id));
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id));
    GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));

}

IndexBuffer::IndexBuffer(IndexBuffer&& rhs) noexcept
    : id{std::exchange(rhs.id, 0)}
{}

IndexBuffer& IndexBuffer::operator=(IndexBuffer&& rhs) noexcept {
    std::swap(id, rhs.id);
    return *this;
}

IndexBuffer::~IndexBuffer() {
    GLCALL(glDeleteBuffers(1, &id));
}

void IndexBuffer::bind() const {
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id));
}

void IndexBuffer::unbind() const {
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

} // namespace glw
