    add_library(r8ge-video-rendering-service
            "RenderingService.cpp"
            "RenderingService.h"
            "buffers/Buffer.cpp"
            "buffers/Buffer.h"
            "buffers/VertexBuffer.cpp"
            "buffers/VertexBuffer.h"
            "../types/Vertex.cpp"
            "../types/Vertex.h"
            "buffers/VertexBufferLayout.cpp"
            "buffers/VertexBufferLayout.h"
            "buffers/IndexBuffer.cpp"
            "buffers/IndexBuffer.h"
    )

    target_include_directories(r8ge-video-rendering-service PRIVATE ${CMAKE_SOURCE_DIR}/include)

    add_subdirectory(openGL)
    target_link_libraries(r8ge-video-rendering-service PRIVATE r8ge-video-rendering-service-gl)

    add_subdirectory(programManager)
    target_link_libraries(r8ge-video-rendering-service PUBLIC r8ge-video-program-manager)

    add_subdirectory(textures)
    target_link_libraries(r8ge-video-rendering-service PUBLIC r8ge-video-textures)