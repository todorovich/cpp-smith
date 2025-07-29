add_library(source-graph-lib STATIC)

target_sources(source-graph-lib
    PRIVATE
        SourceFile.cpp
        SourceGraph.cpp
    PUBLIC
        SourceFile.hpp
        SourceGraph.hpp
)

target_link_libraries(source-graph-lib
    PUBLIC
        compiler-probe-lib
)