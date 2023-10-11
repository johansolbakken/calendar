cmake_minimum_required(VERSION 3.15)

project(calenderback)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(vendor/server)

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(calenderback ${SOURCES})
target_link_libraries(calenderback server)
target_include_directories(calenderback PUBLIC src vendor/server/src)