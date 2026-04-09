add_executable(matching_tests
    #test_main.cpp
    test_order.cpp
    test_order_book.cpp
    test_order_id.cpp
    test_price.cpp
    test_qty.cpp
    test_side.cpp
    test_traits.cpp
    
    $<$<CONFIG:Debug>:test_order_debug.cpp>
    $<$<CONFIG:Debug>:test_order_book_debug.cpp>
)

find_package(GTest CONFIG REQUIRED)

target_link_libraries(matching_tests
    PRIVATE
        matching
        GTest::gtest_main
)

if(ENABLE_WARNINGS)
    target_set_warnings(matching_tests)
endif()

target_enable_sanitizers(matching_tests)

include(GoogleTest)
gtest_discover_tests(matching_tests
    DISCOVERY_MODE PRE_TEST
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)