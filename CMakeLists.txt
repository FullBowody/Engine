cmake_minimum_required(VERSION 3.18)
project(Engine)

find_package(Torch REQUIRED)
find_package(OpenCV REQUIRED)

file(GLOB_RECURSE Engine_SRC "src/*.cpp")

include_directories(include/public include/private)

add_library(Engine SHARED ${Engine_SRC})
set_property(TARGET Engine PROPERTY CXX_STANDARD 17)
include_directories(${OpenCV_INCLUDE_DIRS} ${TORCH_INCLUDE_DIRS})
link_directories(${OpenCV_LIB_DIR} ${TORCH_LIB_DIR})
target_link_libraries(Engine ${OpenCV_LIBS} ${TORCH_LIBRARIES})

if (MSVC)
    file(GLOB TORCH_DLLS "${TORCH_INSTALL_PREFIX}/lib/*.dll")
    list(GET OpenCV_INCLUDE_DIRS 0 OpenCV_INSTALL_PREFIX)
    file(GLOB OPENCV_DLLS "${OpenCV_INSTALL_PREFIX}/bin/${CMAKE_BUILD_TYPE}/*.dll")

    if (CMAKE_BUILD_TYPE STREQUAL "")
        message(FATAL_ERROR "CMAKE_BUILD_TYPE not set")
    endif (CMAKE_BUILD_TYPE STREQUAL "")
    if (TORCH_DLLS STREQUAL "")
        message(FATAL_ERROR "PyTorch DLLs not found, install prefix is [${TORCH_INSTALL_PREFIX}] with prefix path being [${CMAKE_PREFIX_PATH}]")
    endif (TORCH_DLLS STREQUAL "")
    if (OpenCV_DLLS STREQUAL "")
        message(FATAL_ERROR "OpenCV DLLs not found, install prefix is [${OpenCV_INSTALL_PREFIX}]")
    endif (OpenCV_DLLS STREQUAL "")

    add_custom_command(TARGET Engine
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${TORCH_DLLS}
        $<TARGET_FILE_DIR:Engine>)
    add_custom_command(TARGET Engine
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${OPENCV_DLLS}
        $<TARGET_FILE_DIR:Engine>)
endif (MSVC)