#pragma once

namespace glw {

class VertexArray;
class IndexBufferHandler;
class Shader;

} // namespace glw

namespace glw {

class Renderer {
public:
    const unsigned char* getOpenGlVersion() const;
    void clear() const;
    void draw(const VertexArray& va,
              const IndexBufferHandler& ib,
              const Shader& shader) const;
private:
};

} // namespace glw
