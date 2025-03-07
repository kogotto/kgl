
add_library(
    ui

    KeyboardListener.cpp
    mouse_listener.cpp
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
