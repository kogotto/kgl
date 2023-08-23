#pragma once

#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"

class VertexArray {
public:
    VertexArray();
    ~VertexArray();

    void addBuffer(const VertexBuffer& buffer, const VertexBufferLayout& layout);

    void bind() const;
    void unbind() const;

private:
    unsigned int id;
};
