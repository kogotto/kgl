
find_package(Boost REQUIRED)

add_library(
    ut

    cell_index.cpp
    field.cpp
    index_iterator.cpp
    index_range.cpp
    color.cpp
    point.cpp
    rect.cpp
)

target_include_directories(
    ut

    PUBLIC include
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
