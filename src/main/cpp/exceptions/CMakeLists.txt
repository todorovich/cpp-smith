add_library(exceptions INTERFACE)

target_link_libraries(exceptions INTERFACE :libstdc++exp.a)

target_include_directories(exceptions INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
