set(include-headers
        "WindowingService.h"
)

set(source-code
        "WindowingService.cpp"
)


if(LINUX)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set(platform-code
                "linux-impl/x11/X11.cpp"
                "linux-impl/x11/X11.h"
        )
    endif()
endif()

add_library(r8ge-video-platform
        ${include-headers}
        ${source-code}
        ${platform-code}
)

target_include_directories(r8ge-video-platform PRIVATE "${CMAKE_SOURCE_DIR}/include")

if (LINUX)
    find_package(GLEW REQUIRED)
    find_package(OpenGL REQUIRED)
    find_package(X11 REQUIRED)
    include_directories(${X11_INCLUDE_DIR})
    include_directories(${GLEW_INCLUDE_DIRS})

    target_link_libraries(r8ge-video-platform
            INTERFACE
            ${X11_LIBRARIES}
            ${OPENGL_LIBRARIES}
            GLEW::GLEW
            OpenGL::GL
            X11::X11
    )
endif ()