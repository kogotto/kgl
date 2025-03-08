#include <glw/UniformLocation.hpp>

#define GLEW_NO_GLU
#include <GL/glew.h>

#include <glw/Debug.hpp>

namespace glw {

void UniformLocation::set(float v0, float v1, float v2, float v3) {
    GLCALL(glUniform4f(id, v0, v1, v2, v3));
}

} // namespace glw
