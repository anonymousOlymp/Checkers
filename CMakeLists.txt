set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)

cmake_minimum_required(VERSION 3.5)
project(checkers)

include_directories("include", "test/include")
set(SOURCES src/board.cpp src/checker.cpp src/game.cpp src/player.cpp src/position.cpp)
set(TESTS test/src/test_board.cpp test/src/test_checker.cpp test/src/test_game.cpp test/src/test_player.cpp test/src/test_position.cpp)

add_executable(checkers ${SOURCES} src/main.cpp)
add_executable(checkersTest ${SOURCES} ${TESTS} test/src/test.cpp)