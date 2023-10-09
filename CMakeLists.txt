cmake_minimum_required(VERSION 3.2)

#Package manager
include(vendor/gate/cmake/HunterGate.cmake)
HunterGate(
    URL "https://github.com/cpp-pm/hunter/archive/v0.25.0.tar.gz"
    SHA1 "a1296b351dbfaf036c92d85c1bdb461f615849fa"
)

project(r8ge LANGUAGES C CXX)

# Variables
set(INSTALL_DIR ${CMAKE_SOURCE_DIR}/install/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${INSTALL_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${INSTALL_DIR}/slib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${INSTALL_DIR}")



#add_subdirectory(r8ge-core)
add_subdirectory(r8ge-video)

# Executables
add_subdirectory(testbed)

# Installation
install(TARGETS testbed r8ge-video
        RUNTIME DESTINATION ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}
        LIBRARY DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
        ARCHIVE DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)
