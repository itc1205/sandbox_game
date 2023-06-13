cmake_minimum_required(VERSION 3.8)
project("The sandbox game")



include_directories(headers)
add_subdirectory(libs)

set(CXX_STANDARD C++17)

set(SOURCE
    src/main.cpp
    src/logger/logger.cpp
    src/core/engine.cpp
    src/core/window.cpp
    src/core/input.cpp
    src/draw/shader.cpp
    src/draw/texture.cpp
    src/core/mouse.cpp
    src/core/font.cpp
    src/draw/primitives.cpp
    )

add_executable(app ${SOURCE})


target_compile_features(app PRIVATE cxx_std_17)

target_link_libraries(app glfw glad glm freetype)

file(COPY assets DESTINATION .)