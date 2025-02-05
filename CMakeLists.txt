cmake_minimum_required(VERSION 3.10)
project(os_lab1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(main
        src/main.cpp
        src/shell.cpp
        include/shell.h
)
add_executable(dedup
        src/dedup.cpp
        include/dedup.h)
add_executable(io_lat_write
        src/io_lat_write.cpp
        include/io_lat_write.h)

set_target_properties(main PROPERTIES OUTPUT_NAME "main")
set_target_properties(dedup PROPERTIES OUTPUT_NAME "dedup")
set_target_properties(io_lat_write PROPERTIES OUTPUT_NAME "io-lat-write")

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest
        GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)

add_executable(tests
        src/tests/test_dedup.cpp
        src/dedup.cpp
        src/tests/test_io_lat_write.cpp
        src/io_lat_write.cpp
        src/tests/test_shell.cpp
        src/shell.cpp
)
target_link_libraries(tests gtest gtest_main)
target_compile_definitions(tests PRIVATE TESTING)

include_directories(${googletest_SOURCE_DIR}/googletest/include)


