set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_library(r8ge-video
        Window.cpp
        Window.h
        platform/LinuxWindow.cpp
        platform/UniversalWindowManager.hpp)

add_subdirectory(vendor/glew-cmake)
target_include_directories(r8ge-video PRIVATE vendor/glew-cmake/include/)

#TODO Replace for R8GE variable
if(WIN32)
target_link_libraries(r8ge-video PRIVATE opengl32)
endif()

if (UNIX)
    find_package(X11 REQUIRED)
    include_directories(${X11_INCLUDE_DIR})
    link_directories(${X11_LIBRARIES})
    target_link_libraries(r8ge-video PRIVATE ${X11_LIBRARIES})
endif ()