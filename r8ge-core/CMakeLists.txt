# Variables
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED true)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)


# Build
add_library(r8ge-core
        "Core.h"
        "Core.cpp"
        "EntryPoint.cpp"
        "EntryPoint.h"
        "Logger.cpp"
        "Logger.h"
        "platform/EntryPoint.cpp"  # main() for each platform
        "Ar8ge.cpp"
        "Ar8ge.h"
        "platform/Console.h"
        Input.cpp
        Input.h
        InputStator.cpp
        InputStator.h
)


# Subcomponents of `Core`
add_subdirectory(utility)
target_link_libraries(r8ge-core PUBLIC r8ge-core-utility)

add_subdirectory(platform)
target_link_libraries(r8ge-core PRIVATE r8ge-core-platform)

add_subdirectory(events)
target_link_libraries(r8ge-core PUBLIC r8ge-core-events)

add_subdirectory(instance)
target_link_libraries(r8ge-core PUBLIC r8ge-core-instance)

add_subdirectory(fileio)
target_link_libraries(r8ge-core PUBLIC r8ge-core-fileio)

# Compile definitions
target_compile_definitions(r8ge-core PRIVATE R8GE_CORE_BUILD)

if(BUILD_SHARED_LIBS)
        add_compile_definitions(R8GE_SHARED)
else()
        add_compile_definitions(R8GE_STATIC)
endif()