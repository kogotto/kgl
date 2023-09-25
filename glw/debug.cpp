#include <glw/debug.h>

#include <iostream>

#define GLEW_NO_GLU
#include <GL/glew.h>

namespace {

void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

struct GLErrorCode {
    GLenum code;
};

std::ostream& operator<<(std::ostream& stream, GLErrorCode code) {
    return stream <<
        std::hex << std::showbase <<
        code.code <<
        std::noshowbase << std::dec;
}

void GLLogError(GLErrorCode code, const char* function, const char* file, int line) {
    std::cout <<
        "[OpenGl] error, code = " << code <<
        " in call " << function <<
        " on " << file << ":" << line <<
        std::endl;
}

bool GLCheckErrors(const char* function, const char* file, int line) {
    int errorsCount = 0;
    for (auto errorCode = glGetError(); errorCode != GL_NO_ERROR; errorCode = glGetError()) {
        ++errorsCount;
        GLLogError({errorCode}, function, file, line);
    }

    return errorsCount == 0;
}

} // namespace

#define GLASSERT(x) { if (!(x)) std::abort(); }

namespace glw::debug {

GLErrorHandler::GLErrorHandler(const char* function, const char* file, int line)
    : function{function}
    , file{file}
    , line{line} {
        GLClearError();
}

GLErrorHandler::~GLErrorHandler() {
    GLASSERT(GLCheckErrors(function, file, line));
}

} // namespace glw::debug

