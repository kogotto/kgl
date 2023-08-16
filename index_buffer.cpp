#include "index_buffer.h"

#define GLEW_NO_GLU
#include <GL/glew.h>

#include "debug.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
    : count{count}
{
    GLCALL(glGenBuffers(1, &id));
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id));
    GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));

}

IndexBuffer::~IndexBuffer() {
    GLCALL(glDeleteBuffers(1, &id));
}

void IndexBuffer::bind() {
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id));
}

void IndexBuffer::unbind() {
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
