# Variables
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED true)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

# Platform dependant code & entry point
if(LINUX)
        #add_subdirectory(platform/linux)
        #target_link_libraries(r8ge-core PRIVATE r8ge-core-linux)
        set(entryPointFile "platform/linux/EntryPoint.cpp")
        set(BUILD_SHARED_LIBS OFF) # TODO: fix this: error while loading shared libraries: libr8ge-core.so: cannot open shared object file: No such file or directory
elseif(WIN32)
        #add_subdirectory(platform/windows)
        #target_link_libraries(r8ge-core PRIVATE r8ge-core-windows)
elseif()
        message(FATAL_ERROR "Unsupported platform")
endif()


# Build
add_library(r8ge-core
        "Core.h"
        "Core.cpp"
        EntryPoint.cpp
        EntryPoint.h
        ${entryPointFile}
)

# Compile definitions
target_compile_definitions(r8ge-core PRIVATE R8GE_CORE_BUILD)

if(BUILD_SHARED_LIBS)
        add_compile_definitions(R8GE_SHARED)
elseif()
        add_compile_definitions(R8GE_STATIC)
endif()