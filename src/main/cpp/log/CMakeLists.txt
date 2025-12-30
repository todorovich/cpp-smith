add_library(cpp-log INTERFACE)

target_sources(cpp-log
    PUBLIC
        log/Logger.hpp
        log/LogMessage.hpp
        log/LogMessageFormatter.hpp
        log/Sink.hpp
)

target_include_directories(cpp-log INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
