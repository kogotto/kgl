#include <glw/renderer.h>

#define GLEW_NO_GLU
#include <GL/glew.h>

#include <glw/debug.h>
#include <glw/vertex_array.h>
#include <glw/index_buffer_handler.h>
#include <glw/shader.h>

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
    ib.bind();
    shader.bind();

    GLCALL(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, 0));
}

} // namespace glw
