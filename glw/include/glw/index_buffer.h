#pragma once

#include <vector>

#include <glw/index_buffer_handler.h>

namespace glw {

class IndexBuffer {
public:
    using storage_t = std::vector<unsigned int>;

    IndexBuffer(storage_t storage)
        : storage_(std::move(storage))
        , ib_{storage_.data(), static_cast<std::ptrdiff_t>(storage_.size())}
    {}

    IndexBuffer(const IndexBuffer&) = delete;
    IndexBuffer(IndexBuffer&&) noexcept = default;

    IndexBuffer& operator=(const IndexBuffer&) = delete;
    IndexBuffer& operator=(IndexBuffer&&) noexcept = default;

    const IndexBufferHandler& handler() const { return ib_; }

    auto getCount() const { return ib_.getCount(); }

private:
    storage_t storage_;
    IndexBufferHandler ib_;
};

} // namespace glw
