set(include-headers
       "Console.h"
)

if(LINUX)
    set(platform-code
            "linux-impl/Console.cpp"
    )
endif()

add_library(r8ge-platform
        ${include-headers}
        ${platform-code}
)