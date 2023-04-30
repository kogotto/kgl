#pragma once

namespace debug
{

struct GLErrorHandler {
    GLErrorHandler(const char* function, const char* file, int line);
    ~GLErrorHandler();
private:
    const char* function;
    const char* file;
    int line;
};

} // namespace debug

#ifdef NDEBUG

#define GLCALL(x) (x)

#else // #ifdef NDEBUG

#define GLCALL(x)                                               \
    [&] {                                                       \
        debug::GLErrorHandler handler{#x, __FILE__, __LINE__};  \
        return (x);                                             \
    } ()

#endif


