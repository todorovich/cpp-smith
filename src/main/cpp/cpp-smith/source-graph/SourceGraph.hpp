// src/main/cpp/cpp-smith/source-graph/SourceGraph.hpp
#pragma once

#include "Configuration.hpp"
#include "GccProbe.hpp"
#include "SourceFile.hpp"
#include "artifacts/Artifact.hpp"
#include <print>

namespace cpp_smith
{
    class SourceGraph
    {
    public:
        SourceGraph(const Artifact* artifact, const Configuration& configuration)
        {
            for (const auto& path : artifact->sourceFiles())
            {
                SourceFile sourceFile = SourceFile::from(path);

                std::println("Translation Unit: {}", sourceFile.path().string());

                for (const auto& dependency : sourceFile.directDependencies())
                {
                    std::println("Dependency: {}", dependency.string());
                }

                for (const auto& dependency : sourceFile.systemDependencies())
                {
                    std::println("System Dependency: {}", dependency.string());
                }
            }
        }
    };
} // namespace cpp_smith
