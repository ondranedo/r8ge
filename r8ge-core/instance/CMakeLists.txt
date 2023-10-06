add_library(instance
        "Instance.cpp"
        "Instance.h"
)

add_subdirectory(layers)
target_link_libraries(instance PUBLIC layers)