#pragma once

#include <cstdint>

class IndexBuffer {
public:
    IndexBuffer(const unsigned int* data, std::ptrdiff_t count);
    ~IndexBuffer();

    void bind() const;
    void unbind() const;

    auto getCount() const { return count; }
private:
    unsigned int id;
    std::ptrdiff_t count;
};
