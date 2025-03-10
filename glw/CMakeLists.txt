
add_library(
    glw

    Debug.cpp
    IndexBuffer.cpp
    IndexBufferHandler.cpp
    Renderer.cpp
    Shader.cpp
    UniformLocation.cpp
    VertexArray.cpp
    VertexBuffer.cpp
    VertexBufferHandler.cpp
)

target_include_directories(
    glw
    PUBLIC include
)


find_package(
    OpenGL REQUIRED
)

set(GLEW_USE_STATIC_LIBS TRUE)
find_package(
    GLEW REQUIRED
)

target_link_libraries(
    glw

    ut

    GLEW::glew_s
    OpenGL::GL
)
