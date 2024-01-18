add_library(r8ge-video-rendering-service-gl
        "GLService.h"
        "GLService.cpp"
        "GLConvertor.cpp"
        "GLConvertor.h"
        GLTexture.cpp
        GLTexture.h
        GLFrameBuffer.cpp
        GLFrameBuffer.h
)

target_include_directories(r8ge-video-rendering-service-gl PRIVATE ${CMAKE_SOURCE_DIR}/include)
