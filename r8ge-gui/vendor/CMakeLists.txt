set(IMGUI_PATH ${CMAKE_SOURCE_DIR}/r8ge-gui/vendor/imgui)

add_library(r8ge-gui-imgui
        ${IMGUI_PATH}/imgui.cpp
        ${IMGUI_PATH}/imgui_demo.cpp
        ${IMGUI_PATH}/imgui_draw.cpp
        ${IMGUI_PATH}/imgui_widgets.cpp
        ${IMGUI_PATH}/imgui_tables.cpp
        ${IMGUI_PATH}/backends/imgui_impl_opengl3.cpp

)


target_include_directories(r8ge-gui-imgui
        PUBLIC
        $<BUILD_INTERFACE:${IMGUI_PATH}>
        $<BUILD_INTERFACE:${IMGUI_PATH}/backends>  # Include the entire "backends" directory during build
        $<INSTALL_INTERFACE:include>  # Use 'include' as the install interface base directory
)
