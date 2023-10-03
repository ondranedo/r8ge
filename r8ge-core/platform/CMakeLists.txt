set(include-headers
        "Time.h"
)

if(LINUX)
    set(platform-code
        "linux-impl/Time.cpp"
    )
endif()

add_library(platform
        ${include-headers}
        ${platform-code}
)

target_include_directories(platform PRIVATE "include")