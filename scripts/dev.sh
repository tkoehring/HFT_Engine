#!/usr/bin/env bash

COMMAND="$1"
PLATFORM="linux"
CONFIG="debug"

run_build() {
    cmake --build --preset "${PLATFORM}-${CONFIG}"
}

run_test() {
    ctest --preset "${PLATFORM}-${CONFIG}"
}

case "$COMMAND" in
    build)
        run_build
        ;;
    build-verbose)
        cmake --build --preset "${PLATFORM}-${CONFIG}-verbose"
        ;;
    test)
        run_test
        ;;
    test-fast)
        ctest --preset "${PLATFORM}-${CONFIG}-fast"
        ;;
    test-verbose)
        ctest --preset "${PLATFORM}-${CONFIG}-verbose"
        ;;
    asan)
        ctest --preset "linux-debug-asan"
        ;;
    *)
        echo "Unknown command: $COMMAND"
        exit 1
        ;;
esac