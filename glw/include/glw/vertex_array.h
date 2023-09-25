#pragma once

namespace glw {

class VertexBuffer;
class VertexBufferLayout;

} // namespace glw

namespace glw {

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

} // namespace glw
