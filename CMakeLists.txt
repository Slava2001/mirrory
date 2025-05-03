cmake_minimum_required(VERSION 3.24.0)
project(mirrory VERSION 0.1.0 LANGUAGES C CXX)

include(FetchContent)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(RAYLIB_VERSION 5.0)
FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    FIND_PACKAGE_ARGS
)
FetchContent_MakeAvailable(raylib)

set(SRC ./src/main.cpp)

if ("${PLATFORM}" STREQUAL "Web")
    SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -sASYNCIFY")
endif()

add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} raylib)

if ("${PLATFORM}" STREQUAL "Web")
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
    target_link_options(${PROJECT_NAME} PUBLIC -sUSE_GLFW=3 PUBLIC)
endif()
