#pragma once

#include "artifacts/Artifact.hpp"

namespace cpp_smith
{
    class SourceGraph
    {
    public:
        SourceGraph(const Artifact* artifact, const Configuration& configuration)
        {
            // TODO: implement me or replace me with whatever dag
            /*const GccProbe probe{};
            for (const auto& path : artifact->sources())
            {
                SourceFile sourceFile = SourceFile::from(path, &probe);

                std::println("Translation Unit: {}", sourceFile.path().string());

                for (const auto& dependency : sourceFile.directDependencies())
                {
                    std::println("Dependency: {}", dependency.string());
                }

                for (const auto& dependency : sourceFile.systemDependencies())
                {
                    std::println("System Dependency: {}", dependency.string());
                }
            }*/
        }
    };
}
