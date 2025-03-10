
add_library(
    ui

    KeyboardListener.cpp
    MouseListener.cpp
)

target_link_libraries(
    ui

    ut
    glw
)

target_include_directories(
    ui

    PUBLIC include
)
