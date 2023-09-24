cmake_minimum_required(VERSION 3.2)

project(r8ge LANGUAGES C CXX)

# Variables
set(INSTALL_DIR ${CMAKE_SOURCE_DIR}/install/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE})


# Libraries
add_subdirectory(r8ge-core)


# Executables
# add_subdirectory(testbed) # Testing executable, may use different name


# Installation
install(TARGETS r8ge-core
        RUNTIME DESTINATION ${INSTALL_DIR}
        LIBRARY DESTINATION ${INSTALL_DIR}/slib
        ARCHIVE DESTINATION ${INSTALL_DIR}/lib
)
