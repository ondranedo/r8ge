set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED true)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

add_library(r8ge-video
        Video.cpp
        Video.h
        EntrytPoint.cpp
        EntrytPoint.h
)

include_directories(vendor/assimp/include)
add_subdirectory(vendor/assimp)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_INJECT_DEBUG_POSTFIX OFF CACHE BOOL "" FORCE)
set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)
link_libraries(assimp)

include_directories(vendor/stb)
add_compile_definitions(STB_IMAGE_IMPLEMENTATION)

include_directories(vendor/glfw/include)
add_subdirectory(vendor/glfw)
link_libraries(glfw)

include_directories(vendor/glm/glm)
add_subdirectory(vendor/glm)
link_libraries(glm)

include_directories(vendor/imgui)
add_library(imgui
        vendor/imgui/imgui.cpp
        vendor/imgui/imgui_draw.cpp
        vendor/imgui/imgui_demo.cpp
        vendor/imgui/imgui_widgets.cpp
        vendor/imgui/imgui_tables.cpp
        vendor/imgui/backends/imgui_impl_glfw.cpp
        vendor/imgui/backends/imgui_impl_opengl3.cpp
)
add_compile_definitions(IMGUI_IMPL_OPENGL_LOADER_GLAD)

include_directories(vendor/ImGuizmo)
add_library(ImGuizmo
        vendor/ImGuizmo/ImGuizmo.cpp
        vendor/ImGuizmo/ImCurveEdit.cpp
        vendor/ImGuizmo/ImGradient.cpp
        vendor/ImGuizmo/ImSequencer.cpp
        vendor/ImGuizmo/ImGuizmo.cpp
)
link_libraries(imgui ImGuizmo)

target_include_directories(r8ge-video PUBLIC "${CMAKE_SOURCE_DIR}/include")

add_subdirectory(windowingService)
target_link_libraries(r8ge-video PUBLIC r8ge-video-platform)

add_subdirectory(renderingService)
target_link_libraries(r8ge-video PUBLIC r8ge-video-rendering-service)

add_subdirectory(renderer)
target_link_libraries(r8ge-video PUBLIC r8ge-video-renderer)

add_subdirectory(guiService)
target_link_libraries(r8ge-video PUBLIC r8ge-video-gui-service)