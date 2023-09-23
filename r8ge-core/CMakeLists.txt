set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_library(r8ge-core
        "src/Core.h"
        "src/Core.cpp"
        )

target_compile_definitions(r8ge-core PRIVATE R8GE_CORE_BUILD)

if(BUILD_SHARED_LIBS)
        add_compile_definitions(R8GE_SHARED)
elseif()
        add_compile_definitions(R8GE_STATIC)
endif()

set(BUILD_SHARED_LIBS true) # option for user