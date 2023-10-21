add_library(r8ge-video-rendering-service-gl
        "GLService.h"
        "GLService.cpp"
)

target_include_directories(r8ge-video-rendering-service-gl PRIVATE ${CMAKE_SOURCE_DIR}/include)
