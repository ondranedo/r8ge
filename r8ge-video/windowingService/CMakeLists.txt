if(LINUX)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set(platform-code
                linux-impl/glfw/GLFW.cpp
                linux-impl/glfw/GLFW.h
                linux-impl/glfw/Convertor.cpp
                linux-impl/glfw/Convertor.h
        )
    endif()
endif()

add_library(r8ge-video-platform
        "WindowingService.cpp"
        "WindowingService.h"
        ${platform-code}
)

target_include_directories(r8ge-video-platform PUBLIC "${CMAKE_SOURCE_DIR}/include")

if (LINUX)
    find_package(GLEW REQUIRED)
    include_directories(${GLEW_INCLUDE_DIRS})

    target_link_libraries(r8ge-video-platform
            INTERFACE
            ${OPENGL_LIBRARIES}
            GLEW::GLEW
    )
endif ()