#include "vertex_buffer.h"

#define GLEW_NO_GLU
#include <GL/glew.h>

#include "debug.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
    GLCALL(glGenBuffers(1, &id));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, id));
    GLCALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));

}

VertexBuffer::~VertexBuffer() {
    GLCALL(glDeleteBuffers(1, &id));
}

void VertexBuffer::bind() {
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, id));
}

void VertexBuffer::unbind() {
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}