add_library(r8ge-instance
        "Instance.cpp"
        "Instance.h"
        "GameInstance.cpp"
        "GameInstance.h"
)

add_subdirectory(layers)
target_link_libraries(r8ge-instance PUBLIC r8ge-layers)