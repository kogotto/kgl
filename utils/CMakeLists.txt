
add_library(
    ut

    field_indices.cpp
    field.cpp
)

target_include_directories(
    ut

    PUBLIC .
)

find_package(GTest)
if (GTest_FOUND)
    add_executable(
        tests

        field_test.cpp
    )
    target_link_libraries(
        tests
        ut
        GTest::gtest
        GTest::gtest_main
    )
else()
    message(WARNING "Google test framework not found. Install it to build tests")
endif()
