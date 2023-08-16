#pragma once

class IndexBuffer {
public:
    IndexBuffer(const unsigned int* data, unsigned int count);
    ~IndexBuffer();

    void bind();
    void unbind();

    auto getCount() const { return count; }
private:
    unsigned int id;
    unsigned int count;
};
