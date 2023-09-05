#include "renderer.h"

#define GLEW_NO_GLU
#include <GL/glew.h>

#include "debug.h"
#include "vertex_array.h"
#include "index_buffer.h"
#include "shader.h"

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
