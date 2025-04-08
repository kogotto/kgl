#pragma once

#include <cstdint>

namespace glw {

class VertexBufferHandler {
  public:
    VertexBufferHandler(const void* data, std::ptrdiff_t size);

    VertexBufferHandler(const VertexBufferHandler&) = delete;
    VertexBufferHandler(VertexBufferHandler&& rhs) noexcept;

    VertexBufferHandler& operator=(const VertexBufferHandler&) = delete;
    VertexBufferHandler& operator=(VertexBufferHandler&& rhs) noexcept;

    ~VertexBufferHandler();

    void update(const void* data, std::ptrdiff_t size) const;

    void bind() const;
    void unbind() const;

  private:
    unsigned int id;
};

} // namespace glw
