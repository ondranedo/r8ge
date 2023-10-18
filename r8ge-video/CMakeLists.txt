set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED true)

set(OpenGL_GL_PREFERENCE "GLVND")

add_library(r8ge-video
        WindowClass.h
        platform/LinuxWindow.cpp
        )

if (UNIX)
    find_package(GLEW REQUIRED)
    find_package(OpenGL REQUIRED)
    find_package(X11 REQUIRED)
    include_directories(${X11_INCLUDE_DIR})
    include_directories(${GLEW_INCLUDE_DIRS})
    target_link_libraries(r8ge-video INTERFACE ${X11_LIBRARIES} ${OPENGL_LIBRARIES} GLEW::GLEW)
endif ()