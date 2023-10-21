add_library(r8ge-video-rendering-service
        "RenderingService.cpp"
        "RenderingService.h"
        "buffers/Buffer.cpp"
        "buffers/Buffer.h"
)

target_include_directories(r8ge-video-rendering-service PRIVATE ${CMAKE_SOURCE_DIR}/include)

add_subdirectory(openGL)
target_link_libraries(r8ge-video-rendering-service PRIVATE r8ge-video-rendering-service-gl)

add_subdirectory(context)
target_link_libraries(r8ge-video-rendering-service PRIVATE r8ge-video-rendering-service-context)