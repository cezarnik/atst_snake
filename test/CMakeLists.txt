cmake_minimum_required(VERSION 3.10)
project(test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall  -Wsign-compare")
set (PROJECT_SOURCE_DIR "/home/kolya/repos/atst_snake/")

include_directories(${PROJECT_SOURCE_DIR}/deps ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/src)
file(GLOB_RECURSE files3
        "${PROJECT_SOURCE_DIR}/src/States/*.cpp")
file(GLOB_RECURSE files4
        "${PROJECT_SOURCE_DIR}/src/Config/*.cpp")
file(GLOB_RECURSE files5
        "${PROJECT_SOURCE_DIR}/src/Display/*.cpp")
file(GLOB_RECURSE files6
        "${PROJECT_SOURCE_DIR}/src/Entities/*.cpp")
file(GLOB_RECURSE files7
        "${PROJECT_SOURCE_DIR}/deps/*.cpp"
        "${PROJECT_SOURCE_DIR}/deps/*.c")
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
add_definitions(-DVERSION="1.1.1" -DPACKAGE="nsnake" -DDATE="07.11.2019" -DSYSTEM_LEVEL_DIR="/usr/share/games/nsnake/levels")
add_executable(test test.cpp
        ${files3}
        ${files4}
        ${files5}
        ${files6}
        ${files7})
target_link_libraries(test ${CURSES_LIBRARIES})