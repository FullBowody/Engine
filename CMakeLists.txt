cmake_minimum_required(VERSION 3.18)
project(Engine)

add_subdirectory(dependencies/glm)
add_subdirectory(dependencies/zlib)
add_subdirectory(dependencies/libuv)

# libuv

if(WIN32)
    file(GLOB libuv_SRC "dependencies/libuv/src/*.c" "dependencies/libuv/src/win/*.c")
else()
    file(GLOB libuv_SRC "dependencies/libuv/src/*.c" "dependencies/libuv/src/unix/*.c")
endif()
add_library(libuv STATIC ${libuv_SRC})
target_include_directories(libuv PRIVATE dependencies/libuv/include dependencies/libuv/src)
target_compile_definitions(libuv PRIVATE BUILD_TESTING=OFF)
set_property(TARGET libuv PROPERTY CXX_STANDARD 20)

# Engine interface

add_library(EngineInterface INTERFACE)
target_include_directories(EngineInterface INTERFACE include/public)
target_include_directories(EngineInterface INTERFACE dependencies/glm)
set_property(TARGET EngineInterface PROPERTY CXX_STANDARD 20)

# Engine library

file(GLOB_RECURSE Engine_SRC "src/private/*.cpp" "src/public/*.cpp")
file(GLOB_RECURSE uSockets_SRC "dependencies/uWebSockets/uSockets/src/*.c" "dependencies/uWebSockets/uSockets/src/*.cpp" "dependencies/uWebSockets/uSockets/src/*.h")

add_library(Engine SHARED ${Engine_SRC} ${uSockets_SRC})
target_link_libraries(Engine PRIVATE EngineInterface)
target_link_libraries(Engine PRIVATE libuv)
target_link_libraries(Engine PRIVATE zlibstatic)
if(WIN32)
    target_link_libraries(Engine PRIVATE IPHLPAPI Psapi Userenv Dbghelp)
endif()
target_include_directories(Engine PRIVATE include/private)
target_include_directories(Engine PRIVATE dependencies/zlib)
target_include_directories(Engine PRIVATE dependencies/libuv/include)
target_include_directories(Engine PRIVATE dependencies/uWebSockets/src)
target_include_directories(Engine PRIVATE dependencies/uWebSockets/uSockets/src)
target_include_directories(Engine PRIVATE dependencies/libuv/include dependencies/libuv/src)
target_compile_definitions(Engine PRIVATE EXPORT_ENGINE NOMINMAX LIBUS_USE_LIBUV LIBUS_NO_SSL)
target_compile_options(Engine PRIVATE /FIwinsock2.h)
set_property(TARGET Engine PROPERTY CXX_STANDARD 20)

# Test executable

file(GLOB_RECURSE EngineTest_SRC "src/test/*.cpp")

add_executable(EngineTest ${EngineTest_SRC} )
target_link_libraries(EngineTest EngineInterface)
target_include_directories(EngineTest PRIVATE include/test)
set_property(TARGET EngineTest PROPERTY CXX_STANDARD 20)
