set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED true)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

add_library(r8ge-video
        Video.cpp
        Video.h
        EntrytPoint.cpp
        EntrytPoint.h
        Input.cpp
        Input.h
)

target_include_directories(r8ge-video PRIVATE "${CMAKE_SOURCE_DIR}/include")

add_subdirectory(platform)
target_link_libraries(r8ge-video PUBLIC r8ge-video-platform)

add_subdirectory(renderingService)
target_link_libraries(r8ge-video PUBLIC r8ge-video-rendering-service)