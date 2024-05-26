cmake_minimum_required(VERSION 3.18)
project(Engine)

file(GLOB_RECURSE Engine_SRC "src/*.cpp")

include_directories(include/public include/private)

add_library(Engine SHARED ${Engine_SRC})
set_property(TARGET Engine PROPERTY CXX_STANDARD 17)
