cmake_minimum_required(VERSION 3.16.3)

project(kgl)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_CXX_STANDARD 20)

add_executable(
    ${PROJECT_NAME}
    main.cpp
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

target_link_libraries(
    kgl
    OpenGL::GL
    glfw
)
