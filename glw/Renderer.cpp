#include <glw/Renderer.hpp>

#define GLEW_NO_GLU
#include <GL/glew.h>

#include <glw/Debug.hpp>
#include <glw/VertexArray.hpp>
#include <glw/IndexBuffer.hpp>
#include <glw/Shader.hpp>

namespace glw {

const unsigned char* Renderer::getOpenGlVersion() const {
    return GLCALL(glGetString(GL_VERSION));
}

void Renderer::clear() const {
    GLCALL(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::draw(const VertexArray& va,
                    const IndexBuffer& ib,
                    const Shader& shader) const {
    va.bind();
    ib.handler().bind();
    shader.bind();

    GLCALL(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, 0));
}

} // namespace glw
