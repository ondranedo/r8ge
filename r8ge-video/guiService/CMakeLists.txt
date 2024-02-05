add_library(r8ge-video-gui-service
        "GUIService.cpp"
        "GUIService.h"
        "linux-impl/imgui/ImGUI.cpp"
        "linux-impl/imgui/ImGUI.h"
)

target_include_directories(r8ge-video-gui-service PRIVATE ${CMAKE_SOURCE_DIR}/include)
