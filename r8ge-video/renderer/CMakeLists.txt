add_library(r8ge-video-renderer
        "../types/Color.cpp"
        "../types/Color.h"
        "../types/Primitives.cpp"
        "../types/Primitives.h"
        ../types/Texture.h
        Camera.cpp
        Camera.h
        Mesh.cpp
        Mesh.h
        Model.cpp
        Model.h
        Scene.cpp
        Scene.h
        Entity.cpp
        Entity.h
        ../types/SceneHelper.h
)

target_include_directories(r8ge-video-renderer PRIVATE "${CMAKE_SOURCE_DIR}/include")