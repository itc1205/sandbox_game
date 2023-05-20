cmake_minimum_required(VERSION 3.2)

project(glad)

include_directories("include")

add_library(glad "src/glad.c")

target_include_directories(glad INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")