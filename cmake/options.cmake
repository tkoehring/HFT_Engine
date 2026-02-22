# cmake/options.cmake
option(ENABLE_TOOLS "Build command-line tools (replay, etc.)" OFF)
option(ENABLE_TESTS "Build tests" ON)
option(ENABLE_WARNINGS "Enable strict compiler warnings" ON)
option(ENABLE_SANITIZERS "Enable ASan/UBSan (Clang/GCC)" OFF)