# tools/replay/CMakeLists.txt

add_executable(replay
    main.cpp
)

target_link_libraries(replay
    PRIVATE matching
)