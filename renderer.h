#pragma once

class VertexArray;
class IndexBuffer;
class Shader;

class Renderer {
public:
    void clear() const;
    void draw(const VertexArray& va,
              const IndexBuffer& ib,
              const Shader& shader) const;
private:
};
