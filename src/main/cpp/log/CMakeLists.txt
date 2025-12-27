add_library(cpp-log INTERFACE)

target_sources(cpp-log
    PUBLIC
        Logger.hpp
        LogMessage.hpp
        LogMessageFormatter.hpp
        Sink.hpp
)

target_include_directories(cpp-log INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
