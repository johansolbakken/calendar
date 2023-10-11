cmake_minimum_required(VERSION 3.15)

project(calenderback)

option(LOCAL_BUILD "Build for local development" OFF)

if(LOCAL_BUILD)
    message(STATUS "Building for local development")
else()
    message(STATUS "Building for docker")
endif()

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(vendor/server)
add_subdirectory(vendor/server/vendor/json)

set(SKIP_BUILD_TEST ON)
set(BUILD_SHARED_LIBS OFF)
set(BUILD_DOC OFF)
set(INSTALL_TEST OFF)
add_subdirectory(vendor/libpqxx)

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(calenderback ${SOURCES})
target_link_libraries(calenderback server pqxx nlohmann_json::nlohmann_json)
target_include_directories(calenderback PUBLIC src vendor/server/src vendor/libpqxx/include vendor/server/vendor/json/include)
if (LOCAL_BUILD)
    target_compile_definitions(calenderback PUBLIC LOCAL_BUILD)
endif()