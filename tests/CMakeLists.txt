# tests/CMakeLists.txt

file(GLOB TEST_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

add_executable(matching_tests ${TEST_SOURCES})

target_sources(matching_tests PRIVATE
    test_traits.cpp
    $<$<CONFIG:Debug>:test_order_debug.cpp>
)

find_package(GTest CONFIG REQUIRED)

target_link_libraries(matching_tests
    PRIVATE
        matching
        GTest::gtest
)

if(ENABLE_WARNINGS)
    target_set_warnings(matching_tests)
endif()

target_enable_sanitizers(matching_tests)

include(GoogleTest)
gtest_discover_tests(matching_tests)