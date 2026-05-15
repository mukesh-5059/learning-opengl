cmake_minimum_required(VERSION 3.10.0)
project(game VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenGL REQUIRED)

file(GLOB src src/*.cpp)
file(GLOB imgui dependencies/lib/imgui/*.cpp)

add_executable(game)

target_sources(game PRIVATE ${imgui} dependencies/lib/glad.c ${src})

target_include_directories(game PRIVATE dependencies/include)
target_include_directories(game PRIVATE src/includes)

target_link_libraries(game PRIVATE 
    "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/lib/libglfw3.a"
    OpenGL::GL
)
