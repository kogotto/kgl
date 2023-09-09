#pragma once

#include <cstdint>

class VertexBuffer {
public:
    VertexBuffer(const void* data, std::ptrdiff_t size);
    ~VertexBuffer();

    void bind() const;
    void unbind() const;
private:
    unsigned int id;
};
