
add_library(
    glw

    debug.cpp
    index_buffer.cpp
    renderer.cpp
    shader.cpp
    uniform_location.cpp
    vertex_array.cpp
    vertex_buffer.cpp
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

    GLEW::glew_s
    OpenGL::GL
)
