
add_library(
    ui

    mouse_listener.cpp
)

target_link_libraries(
    ui

    ut
)

target_include_directories(
    ui

    PUBLIC include
)
