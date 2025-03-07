cmake_minimum_required(VERSION 3.16.3)

project(kgl)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_CXX_STANDARD 23)

add_executable(
    ${PROJECT_NAME}
    main.cpp

    cell_view.cpp
    field_view.cpp
    prepare_views.cpp
    FieldViewMouseAdapter.cpp
    TimeController.cpp
)

find_package(
    glfw3 3.3 REQUIRED
)

include_directories(
    ${GLFW3_INCLUDE_DIR}
)

add_subdirectory(utils)
add_subdirectory(cell-autom)
add_subdirectory(glw)
add_subdirectory(ui)

target_link_libraries(
    kgl

    cell-autom
    glw
    ui

    glfw
)

# TODO Reconsider mechanics for using resources in build
add_custom_command(
    TARGET ${PROJECT_NAME} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink
        ${CMAKE_CURRENT_SOURCE_DIR}/res
        ${CMAKE_CURRENT_BINARY_DIR}/res
)
