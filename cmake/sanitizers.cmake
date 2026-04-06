# cmake/sanitizers.cmake
# Usage:
#   include(cmake/sanitizers.cmake)
#   target_enable_sanitizers(<target>)

option(ENABLE_SANITIZERS "Enable ASan/UBSan (Clang/GCC)" OFF)

function(target_enable_sanitizers target)
    if(NOT ENABLE_SANITIZERS)
        return()
    endif()

    if(MSVC)
        message(WARNING "Sanitizers requested, but MSVC sanitizer flags are not enabled by this helper.")
        return()
    endif()

    # Only enable on Debug-ish configs by default (optional)
    # You can remove this if you want sanitizers in Release too.
    if(CMAKE_BUILD_TYPE AND NOT CMAKE_BUILD_TYPE MATCHES "Debug|RelWithDebInfo")
        message(STATUS "ENABLE_SANITIZERS is ON but build type is ${CMAKE_BUILD_TYPE}; enabling anyway.")
    endif()

    target_compile_options(${target} PRIVATE
        -fsanitize=address,undefined
        -fno-omit-frame-pointer
        -fno-optimize-sibling-calls
        -fsanitize-address-use-after-scope
    )
    target_link_options(${target} PRIVATE
        -fsanitize=address,undefined
    )
endfunction()