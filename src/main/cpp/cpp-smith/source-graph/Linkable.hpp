#pragma once

#include <filesystem>

#include "system/System.hpp"

namespace cpp_smith
{
	// TODO: these should be associated with compilation unit somehow
	class Linkable
	{
		const std::filesystem::path _linkableFile {};
		const std::filesystem::path _dependencyFile {};
		std::filesystem::file_time_type _lastWriteTimeBuild {};

	public:
		Linkable(
			const std::filesystem::path& linkableFile,
			const std::filesystem::path& dependencyFile
		)
			: _linkableFile(linkableFile)
			, _dependencyFile(dependencyFile)
		{
			_lastWriteTimeBuild = getLastWriteTimeBuild();
		}

		[[nodiscard]] const std::filesystem::path& getDependencyFile() const { return _dependencyFile; }
		[[nodiscard]] const std::filesystem::path& getObjectFile() const { return _linkableFile; }

		[[nodiscard]] const std::filesystem::file_time_type& getLastWriteTimeBuild() const
		{
			return _lastWriteTimeBuild;
		}

		void updateLastBuiltTime()
		{
			const auto obj_time = System::getLastWriteTime(_linkableFile);
			const auto dep_time = System::getLastWriteTime(_dependencyFile);

			_lastWriteTimeBuild = std::max(obj_time, dep_time);
		}
	};
}
