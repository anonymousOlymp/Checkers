cmake_minimum_required(VERSION 3.5)
project(checkers)

include_directories("include", "test/include")
set(SOURCES )
set(TESTS )

add_executable(checkers ${SOURCES} src/main.cpp)
add_executable(checkersTest ${SOURCES} test/src/test.cpp)