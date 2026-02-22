cmake_minimum_required(VERSION 3.20)

project(
    hft_matching_engine
    VERSION 0.1.0
    LANGUAGES CXX
)

# ---- Global settings ----
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ---- Includes ----
include(cmake/options.cmake)
include(cmake/warnings.cmake)
include(cmake/sanitizers.cmake)

# ---- Library: matching ----

add_library(matching STATIC)

target_sources(matching
    PRIVATE
        src/order_book.cpp
        
 "include/matching/order.h" "include/matching/order_type.h")

target_include_directories(matching
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

if(ENABLE_WARNINGS)
    target_set_warnings(matching)
endif()

target_enable_sanitizers(matching)

target_compile_features(matching PUBLIC cxx_std_20)

# ---- Replay tool ----

if(ENABLE_TOOLS)
    add_subdirectory(tools/replay)
endif()

# ---- Tests ----

if(ENABLE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

