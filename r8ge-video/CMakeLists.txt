set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_library(r8ge-video
        Window.cpp
        Window.h
        platform/Win32Window.h
        platform/Win32Window.cpp)

target_include_directories(r8ge-video PRIVATE ../vendor/glew-cmake/include)
target_link_libraries(r8ge-video PRIVATE glfw)
target_link_libraries(r8ge-video PRIVATE opengl32)