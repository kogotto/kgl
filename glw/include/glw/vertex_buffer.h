#pragma once

#include <cstdint>

namespace glw {

class VertexBuffer {
public:
    VertexBuffer(const void* data, std::ptrdiff_t size);

    VertexBuffer(const VertexBuffer&) = delete;
    VertexBuffer(VertexBuffer&& rhs) noexcept;

    VertexBuffer& operator=(const VertexBuffer&) = delete;
    VertexBuffer& operator=(VertexBuffer&& rhs) noexcept;

    ~VertexBuffer();

    void bind() const;
    void unbind() const;
private:
    unsigned int id;
};

} // namespace glw
