#pragma once

namespace glw {

class VertexArray;
class IndexBuffer;
class Shader;

} // namespace glw

namespace glw {

class Renderer {
public:
    const unsigned char* getOpenGlVersion() const;
    void clear() const;
    void draw(const VertexArray& va, const IndexBuffer& ib,
              const Shader& shader) const;

private:
};

} // namespace glw
