add_library(r8ge-video-textures
        "Texture2D.cpp"
        "Texture2D.h"
)

target_include_directories(r8ge-video-textures
        PRIVATE
        "${CMAKE_SOURCE_DIR}/include")