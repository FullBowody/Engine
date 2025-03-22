cmake_minimum_required(VERSION 3.18)
project(Engine)

add_subdirectory(dependencies/glm)

# Engine interface

file(GLOB_RECURSE EngineInterface_SRC "src/public/*.cpp")
add_library(EngineInterface INTERFACE)
target_include_directories(EngineInterface INTERFACE include/public)
target_include_directories(EngineInterface INTERFACE dependencies/glm)
set_property(TARGET EngineInterface PROPERTY CXX_STANDARD 17)

# Engine library

file(GLOB_RECURSE Engine_SRC "src/private/*.cpp")

add_library(Engine SHARED ${Engine_SRC})
target_link_libraries(Engine EngineInterface)
target_include_directories(Engine PRIVATE include/private)
target_compile_definitions(Engine PRIVATE EXPORT_ENGINE)
set_property(TARGET Engine PROPERTY CXX_STANDARD 17)

# Test executable

file(GLOB_RECURSE EngineTest_SRC "src/test/*.cpp")

add_executable(EngineTest ${EngineTest_SRC})
target_link_libraries(EngineTest EngineInterface)
target_include_directories(EngineTest PRIVATE include/test)
set_property(TARGET EngineTest PROPERTY CXX_STANDARD 17)
