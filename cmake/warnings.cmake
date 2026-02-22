# cmake/warnings.cmake
# Usage:
#   include(cmake/warnings.cmake)
#   target_set_warnings(<target>)

function(target_set_warnings target)
    if(MSVC)
        target_compile_options(${target} PRIVATE
            /W4
            /permissive-
            /wd4100  # unreferenced formal parameter (optional)
        )
        # Uncomment if you want warnings as errors:
        # target_compile_options(${target} PRIVATE /WX)
    else()
        target_compile_options(${target} PRIVATE
            -Wall
            -Wextra
            -Wpedantic
            -Wconversion
            -Wsign-conversion
        )
        # Uncomment if you want warnings as errors:
        # target_compile_options(${target} PRIVATE -Werror)
    endif()
endfunction()