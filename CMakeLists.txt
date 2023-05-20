cmake_minimum_required(VERSION 3.8)
project("The sandbox game")

set(CXX_STANDARD C++17)

set(SOURCE
    src/main.cpp)

add_executable(app ${SOURCE})