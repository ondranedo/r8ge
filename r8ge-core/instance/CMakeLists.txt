add_library(instance
        "Instance.cpp"
        "Instance.h"
        "GameInstance.cpp"
        "GameInstance.h"
)

add_subdirectory(layers)
target_link_libraries(instance PUBLIC layers)