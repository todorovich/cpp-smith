add_library(cpp-log INTERFACE)

target_sources(cpp-log
    PUBLIC
        log.hpp
        logger/Logger.hpp
        logger/LogMessage.hpp
        logger/LogMessageFormatter.hpp
        logger/Sink.hpp
)

target_include_directories(cpp-log INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
