#pragma once

#include <vector>

#include <glw/vertex_buffer_handler.h>

namespace glw::detail {

template <typename T>
std::ptrdiff_t sizeInBytes(const std::vector<T>& vec) {
    return vec.size() * sizeof(T);
}

} // namespace glw::detail

namespace glw {

template <typename VRTX>
class VertexBuffer {
public:
    using vertex_t = VRTX;
    using storage_t = std::vector<vertex_t>;

    VertexBuffer(storage_t storage)
        : storage_(std::move(storage))
        , vb_{storage_.data(), detail::sizeInBytes(storage_)}
    {}

    VertexBuffer(const VertexBuffer&) = delete;
    VertexBuffer(VertexBuffer&&) noexcept = default;

    VertexBuffer& operator=(const VertexBuffer&) = delete;
    VertexBuffer& operator=(VertexBuffer&&) noexcept = default;

    storage_t& storage() { return storage_; }
    const storage_t& storage() const { return storage_; }

    const VertexBufferHandler& handler() { return vb_; }

    void update() const {
        vb_.update(storage_.data(), detail::sizeInBytes(storage_));
    }

private:
    storage_t storage_;
    VertexBufferHandler vb_;
};

} // namespace glw
