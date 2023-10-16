set(include-headers
       "Console.h"
)

if(LINUX)
    set(platform-code
            "linux-impl/Console.cpp"
    )
endif()

add_library(platform
        ${include-headers}
        ${platform-code}
)