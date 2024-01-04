set(STB_PATH ${CMAKE_SOURCE_DIR}/r8ge-video/vendor/stb)


add_library(r8ge-video-stb INTERFACE)
target_include_directories(r8ge-video-stb INTERFACE ${STB_PATH})
