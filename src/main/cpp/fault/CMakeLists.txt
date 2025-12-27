add_library(cpp-fault INTERFACE)

target_link_libraries(cpp-fault INTERFACE :libstdc++exp.a)

target_include_directories(cpp-fault INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
