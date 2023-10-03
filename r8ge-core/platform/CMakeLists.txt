set(include-headers
       "foo.h"
)

if(LINUX)
    set(platform-code
        "linux-impl/foo.cpp"
    )
endif()

add_library(platform
        ${include-headers}
        ${platform-code}
)