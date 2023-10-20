add_executable(plain "Plain.cpp")

target_link_libraries(plain PRIVATE r8ge-core)

target_include_directories(plain PRIVATE ${CMAKE_SOURCE_DIR}/include)