cmake_minimum_required(VERSION 3.15)
project(Engine)

file(GLOB Engine_SRC
    "src/*.hpp"
    "src/*.cpp"
)

add_library(Engine SHARED ${Engine_SRC})
