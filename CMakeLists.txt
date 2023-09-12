cmake_minimum_required(VERSION 3.16.3)

project(kgl)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_CXX_STANDARD 20)

add_executable(
    ${PROJECT_NAME}
    main.cpp
    debug.cpp
    vertex_array.cpp
    vertex_buffer.cpp
    index_buffer.cpp
    shader.cpp
    uniform_location.cpp
    renderer.cpp

    cell_view.cpp
    field_view.cpp
    prepare_views.cpp
)

find_package(
    glfw3 3.3 REQUIRED
)

include_directories(
    ${GLFW3_INCLUDE_DIR}
)

find_package(
    OpenGL REQUIRED
)

set(GLEW_USE_STATIC_LIBS TRUE)
find_package(
    GLEW REQUIRED
)

add_subdirectory(cell-autom)

target_link_libraries(
    kgl
    cell-autom
    OpenGL::GL
    glfw
    GLEW::glew_s
)

# TODO Reconsider mechanics for using resources in build
add_custom_command(
    TARGET ${PROJECT_NAME} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink
        ${CMAKE_CURRENT_SOURCE_DIR}/res
        ${CMAKE_CURRENT_BINARY_DIR}/res
)
