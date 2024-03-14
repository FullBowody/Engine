cmake_minimum_required(VERSION 3.18)
project(Engine)

find_package(Torch REQUIRED)
find_package(OpenCV REQUIRED)

file(GLOB Engine_SRC
    "src/*.hpp"
    "src/*.cpp"
)

add_library(Engine SHARED ${Engine_SRC})
set_property(TARGET Engine PROPERTY CXX_STANDARD 17)
include_directories(${OpenCV_INCLUDE_DIRS} ${TORCH_INCLUDE_DIRS})
link_directories(${OpenCV_LIB_DIR} ${TORCH_LIB_DIR})
target_link_libraries(Engine ${OpenCV_LIBS} ${TORCH_LIBRARIES})

if (MSVC)
    file (GLOB Engine_bin "bin/*.dll" "lib/*.dll")
    add_custom_target(CopyDlls POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${Engine_bin} $<TARGET_FILE_DIR:Engine>
    )
    file(GLOB TORCH_DLLS "${TORCH_INSTALL_PREFIX}/lib/*.dll")
    add_custom_command(TARGET Engine
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${TORCH_DLLS}
        $<TARGET_FILE_DIR:Engine>)
    list(GET CMAKE_CONFIGURATION_TYPES 0 CMAKE_BUILD_TYPE)
    list(GET OpenCV_INCLUDE_DIRS 0 OpenCV_INSTALL_PREFIX)
    file(GLOB OPENCV_DLLS "${OpenCV_INSTALL_PREFIX}/bin/${CMAKE_BUILD_TYPE}/*.dll")
    add_custom_command(TARGET Engine
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${OPENCV_DLLS}
        $<TARGET_FILE_DIR:Engine>)
endif (MSVC)
