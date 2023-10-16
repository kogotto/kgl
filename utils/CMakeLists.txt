
find_package(Boost REQUIRED)

add_library(
    ut

    cell_index.cpp
    cell_index_iterator.cpp
    field.cpp
)

target_include_directories(
    ut

    PUBLIC .
    PUBLIC ${Boost_INCLUDE_DIRS}
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
