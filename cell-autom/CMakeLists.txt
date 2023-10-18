
add_library(
    cell-autom
    cell.cpp
    field_model.cpp
    field.cpp
    rule.cpp
)

target_include_directories(
    cell-autom
    PUBLIC .
)

target_link_libraries(
    cell-autom

    ut
)
