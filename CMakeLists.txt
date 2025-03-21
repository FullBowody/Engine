cmake_minimum_required(VERSION 3.18)
project(Engine)

add_subdirectory(dependencies/glm)

file(GLOB_RECURSE Engine_SRC "src/private/*.cpp" "src/public/*.cpp")

include_directories(include/public include/private)
include_directories(dependencies/glm)

add_library(Engine SHARED ${Engine_SRC})
add_compile_definitions(EXPORT_ENGINE)
set_property(TARGET Engine PROPERTY CXX_STANDARD 17)
