add_library(r8ge-video-renderer
        "../types/Color.cpp"
        "../types/Color.h"
        "../types/Primitives.cpp"
        "../types/Primitives.h"
        ../types/Texture.h
        Camera.cpp
        Camera.h
        #"Mesh.cpp"
        #"Mesh.h"
        #"MeshTrinagle.cpp"
        #"MeshTrinagle.h"
        #"Rectangle.cpp"
        #"Rectangle.h"
)

target_include_directories(r8ge-video-renderer PRIVATE "${CMAKE_SOURCE_DIR}/include")