cmake_policy(SET CMP0048 NEW)
project(LibraryChecker)

cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 14)

add_compile_options(-Wall -Wextra -Wshadow -Wconversion -Wno-sign-conversion -Werror)
add_compile_options(-fsanitize=undefined,address -fno-sanitize-recover=all)
add_link_options(-fsanitize=undefined,address)

enable_testing()

add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include(GoogleTest)

include_directories(.)
include_directories(../../common)


add_executable(FastIOTest fastio_test.cpp)
target_link_libraries(FastIOTest gtest gtest_main)
gtest_discover_tests(FastIOTest)
