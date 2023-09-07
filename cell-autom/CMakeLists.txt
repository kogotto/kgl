
add_library(
    cell-autom
    cell.cpp
    field.cpp
    rule.cpp
)

target_include_directories(
    cell-autom
    PUBLIC .
)
