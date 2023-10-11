cmake_minimum_required(VERSION 3.15)

project(calenderback)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(vendor/server)

add_executable(calenderback src/main.cpp)
target_link_libraries(calenderback server)
target_include_directories(calenderback PUBLIC vendor/server/src)