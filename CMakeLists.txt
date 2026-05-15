cmake_minimum_required(VERSION 3.10.0)

project(game VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
find_package(OpenGL REQUIRED)

add_executable(game)

target_sources(game PRIVATE 
                dependencies/lib/imgui/imgui.cpp dependencies/lib/imgui/imgui_tables.cpp
                dependencies/lib/imgui/imgui_impl_glfw.cpp dependencies/lib/imgui/imgui_widgets.cpp
                dependencies/lib/imgui/imgui_draw.cpp dependencies/lib/imgui/imgui_demo.cpp
                dependencies/lib/imgui/imgui_impl_opengl3.cpp
                dependencies/lib/glad.c src/debugger.cpp
                src/main.cpp
                src/IndexBuffer.cpp src/VertexBuffer.cpp src/VertexArray.cpp src/Shader.cpp
                src/Renderer.cpp src/Texture.cpp
                src/Camera.cpp)

target_include_directories(game PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/include")
target_include_directories(game PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/includes")

target_link_libraries(game PRIVATE 
    "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/lib/libglfw3.a"
    OpenGL::GL
)
