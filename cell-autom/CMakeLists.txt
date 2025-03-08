
add_library(
    cell-autom

    Cell.cpp
    FieldModel.cpp
    Rule.cpp
)

target_include_directories(
    cell-autom
    PUBLIC include
)

target_link_libraries(
    cell-autom

    ut
)
