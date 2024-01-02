set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED true)
cmake_minimum_required(VERSION 3.2)

project(r8ge LANGUAGES C CXX)

# Variables
set(INSTALL_DIR ${CMAKE_SOURCE_DIR}/install/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${INSTALL_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${INSTALL_DIR}/slib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${INSTALL_DIR}")

add_subdirectory(r8ge-core)
add_subdirectory(r8ge-sound)
add_subdirectory(r8ge-video)

# Executables
add_subdirectory(testbed)

# Installation
install(TARGETS testbed r8ge-video r8ge-core r8ge-sound
        RUNTIME DESTINATION ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}
        LIBRARY DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
        ARCHIVE DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)
