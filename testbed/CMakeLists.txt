add_executable(testbed "piano.cpp")

target_link_libraries(testbed PRIVATE r8ge-core)
target_link_libraries(testbed PRIVATE r8ge-video)

target_link_libraries(testbed PRIVATE r8ge-sound)

target_include_directories(testbed PRIVATE ${CMAKE_SOURCE_DIR}/include)