# tests/CMakeLists.txt

file(GLOB TEST_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

add_executable(matching_tests ${TEST_SOURCES})

find_package(GTest CONFIG REQUIRED)

target_link_libraries(matching_tests
    PRIVATE
        matching
        GTest::gtest
)

include(GoogleTest)
gtest_discover_tests(matching_tests)