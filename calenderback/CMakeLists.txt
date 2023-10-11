cmake_minimum_required(VERSION 3.15)

project(calenderback)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(vendor/server)
add_subdirectory(vendor/libpqxx)
add_subdirectory(vendor/server/vendor/json)

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(calenderback ${SOURCES})
target_link_libraries(calenderback server pqxx nlohmann_json::nlohmann_json)
target_include_directories(calenderback PUBLIC src vendor/server/src vendor/libpqxx/include vendor/server/vendor/json/include)