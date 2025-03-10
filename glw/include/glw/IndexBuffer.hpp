#pragma once

#include <vector>

#include <glw/IndexBufferHandler.hpp>

#include <utils/SizeInBytes.hpp>

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

    storage_t& storage() { return storage_; }
    const storage_t& storage() const { return storage_; }

    const IndexBufferHandler& handler() const { return ib_; }

    void update() {
        ib_.update(storage_.data(), ut::sizeInBytes(storage_));
    }

    auto getCount() const { return storage_.size(); }

private:
    storage_t storage_;
    IndexBufferHandler ib_;
};

} // namespace glw
