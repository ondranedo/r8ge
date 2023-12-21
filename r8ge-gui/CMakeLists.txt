set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_library(r8ge-gui
        test.cpp
)

target_include_directories(r8ge-gui PUBLIC "${CMAKE_SOURCE_DIR}/include")

add_subdirectory(vendor)
target_link_libraries(r8ge-gui PUBLIC r8ge-gui-imgui)