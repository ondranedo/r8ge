set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_library(r8ge-sound
        "Sound.hpp"
        "Sound.cpp"
        "Generators.cpp"
        "Generators.hpp"
        "Sequencer.cpp"
        "Sequencer.hpp"
        "Visualiser.cpp"
        "Visualiser.h"
        "Instruments.h"
)

find_package(ALSA REQUIRED)
if(ALSA_FOUND)
    include_directories(${ALSA_INCLUDE_DIRS})
    target_link_libraries(r8ge-sound ${ALSA_LIBRARIES})
endif(ALSA_FOUND)

target_include_directories(r8ge-sound PRIVATE ${CMAKE_SOURCE_DIR}/include)