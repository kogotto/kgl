#pragma once

class VertexBuffer;
class VertexBufferLayout;

class VertexArray {
public:
    VertexArray();

    VertexArray(const VertexArray&) = delete;
    VertexArray(VertexArray&& rhs) noexcept;

    VertexArray& operator=(const VertexArray&) = delete;
    VertexArray& operator=(VertexArray&& rhs) noexcept;

    ~VertexArray();

    void addBuffer(const VertexBuffer& buffer, const VertexBufferLayout& layout);

    void bind() const;
    void unbind() const;

private:
    unsigned int id;
};
