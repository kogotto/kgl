#pragma once

#include <cstdint>

namespace glw {

class IndexBufferHandler {
public:
    IndexBufferHandler(const unsigned int* data, std::ptrdiff_t count);

    IndexBufferHandler(const IndexBufferHandler&) = delete;
    IndexBufferHandler(IndexBufferHandler&& rhs) noexcept;

    IndexBufferHandler& operator=(const IndexBufferHandler&) = delete;
    IndexBufferHandler& operator=(IndexBufferHandler&& rhs) noexcept;

    ~IndexBufferHandler();

    void update(const unsigned int* data, std::ptrdiff_t size);

    void bind() const;
    void unbind() const;

private:
    unsigned int id;
};

} // namespace glw
