add_library(cpp-compile STATIC)

target_link_libraries(cpp-compile
    PUBLIC
        cpp-log
        cpp-system
        cpp-containers
        cpp-build
)

target_sources(cpp-compile
    PRIVATE
        compile/model/CompilationConfiguration.cpp
        compile/model/SourceFile.cpp
        compile/model/Executable.cpp
        compile/model/SharedLibrary.cpp
        compile/model/StaticLibrary.cpp
        compile/model/factory/CompilationConfigurationFactory.cpp
        compile/model/factory/ExecutableFactory.cpp
        compile/model/factory/SharedLibraryFactory.cpp
        compile/model/factory/StaticLibraryFactory.cpp
        compile/compiler-probe/GccProbe.cpp
    PUBLIC
        compile/model/Architecture.hpp
        compile/model/CompilerType.hpp
        compile/model/CompilationUnit.hpp
        compile/model/CompilationConfiguration.hpp
        compile/model/Linkable.hpp
        compile/model/SourceFile.hpp
        compile/model/Platform.hpp
        compile/model/Executable.hpp
        compile/model/SharedLibrary.hpp
        compile/model/StaticLibrary.hpp
        compile/model/factory/CompilationConfigurationFactory.hpp
        compile/model/factory/ExecutableFactory.hpp
        compile/model/factory/SharedLibraryFactory.hpp
        compile/model/factory/StaticLibraryFactory.hpp
        compile/compiler-probe/CompilerProbe.hpp
        compile/compiler-probe/GccProbe.hpp
        compile/compiler-probe/ProbeUtils.hpp
)

target_include_directories(cpp-compile PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
