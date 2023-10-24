add_library(r8ge-core-instance
        "Instance.cpp"
        "Instance.h"
        "GameInstance.cpp"
        "GameInstance.h"
        "ConsoleAppInstance.cpp"
        "ConsoleAppInstance.h"
)

add_subdirectory(layers)
target_link_libraries(r8ge-core-instance PUBLIC r8ge-core-layers)