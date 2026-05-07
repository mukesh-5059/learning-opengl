cmake_minimum_required(VERSION 3.10.0)
project(game VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
find_package(OpenGL REQUIRED)

add_executable(game src/main.cpp dependencies/lib/glad.c src/utils.cpp)
target_include_directories(game PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/include")
target_include_directories(game PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/includes")
target_link_libraries(game PRIVATE 
    "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/lib/libglfw3.a"
    OpenGL::GL
)
