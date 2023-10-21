add_library(r8ge-video-rendering-service-context
        "X11/XContext.h"
        "X11/XContext.cpp"
        "X11/GLX/GLXContext.h"
        "X11/GLX/GLXContext.cpp"
)

target_include_directories(
        r8ge-video-rendering-service-context PRIVATE ${CMAKE_SOURCE_DIR}/include)