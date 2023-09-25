#pragma once

#include <cstdint>

namespace glw {

class IndexBuffer {
public:
    IndexBuffer(const unsigned int* data, std::ptrdiff_t count);

    IndexBuffer(const IndexBuffer&) = delete;
    IndexBuffer(IndexBuffer&& rhs) noexcept;

    IndexBuffer& operator=(const IndexBuffer&) = delete;
    IndexBuffer& operator=(IndexBuffer&& rhs) noexcept;

    ~IndexBuffer();

    void bind() const;
    void unbind() const;

    auto getCount() const { return count; }
private:
    unsigned int id;
    std::ptrdiff_t count;
};

} // namespace glw
