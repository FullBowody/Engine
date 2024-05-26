cmake_minimum_required(VERSION 3.18)
project(Engine)

find_package(OpenCV REQUIRED)

file(GLOB_RECURSE Engine_SRC "src/*.cpp")

include_directories(include/public include/private)

add_library(Engine SHARED ${Engine_SRC})
set_property(TARGET Engine PROPERTY CXX_STANDARD 17)
include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIB_DIR})
target_link_libraries(Engine ${OpenCV_LIBS})

if (MSVC)
    if (CMAKE_BUILD_TYPE STREQUAL "")
        message(FATAL_ERROR "CMAKE_BUILD_TYPE not set")
    endif (CMAKE_BUILD_TYPE STREQUAL "")

    list(GET OpenCV_INCLUDE_DIRS 0 OpenCV_INSTALL_PREFIX)
    file(GLOB OPENCV_DLLS "${OpenCV_INSTALL_PREFIX}/bin/${CMAKE_BUILD_TYPE}/*.dll")

    if (OpenCV_DLLS STREQUAL "")
        message(FATAL_ERROR "OpenCV DLLs not found, install prefix is [${OpenCV_INSTALL_PREFIX}]")
    endif (OpenCV_DLLS STREQUAL "")

    add_custom_command(TARGET Engine
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${OPENCV_DLLS}
        $<TARGET_FILE_DIR:Engine>)
endif (MSVC)