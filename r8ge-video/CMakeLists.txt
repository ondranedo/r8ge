set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED true)

hunter_add_package(glfw)
find_package(glfw3 REQUIRED)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

hunter_add_package(glew)
find_package(glew CONFIG REQUIRED)

add_library(r8ge-video
        Window.cpp
        Window.h
        platform/UniversalWindow.h
        platform/UniversalWindow.cpp
        platform/UniversalWindowManager.hpp)


target_link_libraries(r8ge-video INTERFACE glfw)
target_link_libraries(r8ge-video PUBLIC glew::glew)

#TODO Replace for R8GE variable
if(WIN32)
target_link_libraries(r8ge-video PRIVATE opengl32)
endif()