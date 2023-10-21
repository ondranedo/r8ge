add_executable(plain-video "Plain.cpp")

target_link_libraries(plain-video PRIVATE r8ge-core)
target_link_libraries(plain-video PRIVATE r8ge-video)

target_include_directories(plain-video PRIVATE ${CMAKE_SOURCE_DIR}/include)