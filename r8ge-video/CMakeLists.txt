set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED true)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

add_library(r8ge-video
        Video.cpp
        Video.h
        EntrytPoint.cpp
        EntrytPoint.h
)

target_include_directories(r8ge-video PUBLIC "${CMAKE_SOURCE_DIR}/include")

add_subdirectory(windowingService)
target_link_libraries(r8ge-video PUBLIC r8ge-video-platform)

add_subdirectory(renderingService)
target_link_libraries(r8ge-video PUBLIC r8ge-video-rendering-service)

add_subdirectory(renderer)
target_link_libraries(r8ge-video PUBLIC r8ge-video-renderer)