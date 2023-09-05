#pragma once

class VertexBuffer;
class VertexBufferLayout;

class VertexArray {
public:
    VertexArray();
    ~VertexArray();

    void addBuffer(const VertexBuffer& buffer, const VertexBufferLayout& layout);

    void bind() const;
    void unbind() const;

private:
    unsigned int id;
};
