add_library(r8ge-video-program-manager
        "Program.cpp"
        "Program.h"
        ProgramData.cpp
        ProgramData.h
)

target_include_directories(r8ge-video-program-manager
        PRIVATE
        "${CMAKE_SOURCE_DIR}/include")