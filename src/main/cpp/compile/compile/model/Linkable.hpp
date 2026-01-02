#pragma once

#include <filesystem>

#include "system/System.hpp"

namespace cpp_smith
{
	class  Linkable
	{
		// TODO: these should be associated with compilation unit somehow

		std::filesystem::path _linkableFile {};
		std::filesystem::file_time_type _lastWriteTimeBuild {};

	  public:
		virtual ~Linkable()                  = default;
		Linkable(const Linkable&)            = default;
		Linkable& operator=(const Linkable&) = default;
		Linkable(Linkable&&)                 = default;
		Linkable& operator=(Linkable&&)      = default;

		explicit Linkable(const std::filesystem::path& path)
			: _linkableFile(path)
			, _lastWriteTimeBuild(System::getLastWriteTime(_linkableFile))
		{}

		[[nodiscard]] const std::filesystem::file_time_type& getLastWriteTimeBuild() const
		{
			return _lastWriteTimeBuild;
		}

		[[nodiscard]] virtual const std::filesystem::path& getLinkable() const
		{
			return _linkableFile;
		};

		void updateLastBuiltTime()
		{
			_lastWriteTimeBuild = System::getLastWriteTime(_linkableFile);
		}
	};

	class ObjectFile : public Linkable
	{
		std::filesystem::path _dependencyFile{};

	public:
		~ObjectFile() override                   = default;
		ObjectFile(const ObjectFile&)            = default;
		ObjectFile& operator=(const ObjectFile&) = default;
		ObjectFile(ObjectFile&&)                 = default;
		ObjectFile& operator=(ObjectFile&&)      = default;

		ObjectFile(
			const std::filesystem::path& objectFile,
			const std::filesystem::path& dependencyFile
		)
			: Linkable(objectFile)
			, _dependencyFile(dependencyFile)
		{}

		const std::filesystem::path& getDependencyFile() const { return _dependencyFile; }
	};

	class SharedLibraryFile : public Linkable
	{
	public:
		~SharedLibraryFile() override                          = default;
		SharedLibraryFile(const SharedLibraryFile&)            = default;
		SharedLibraryFile& operator=(const SharedLibraryFile&) = default;
		SharedLibraryFile(SharedLibraryFile&&)                 = default;
		SharedLibraryFile& operator=(SharedLibraryFile&&)      = default;

		explicit SharedLibraryFile(const std::filesystem::path& sharedLibraryFile)
			: Linkable(sharedLibraryFile)
		{}
	};

	class StaticLibraryFile : public Linkable
	{
	public:
		~StaticLibraryFile() override                          = default;
		StaticLibraryFile(const StaticLibraryFile&)            = default;
		StaticLibraryFile& operator=(const StaticLibraryFile&) = default;
		StaticLibraryFile(StaticLibraryFile&&)                 = default;
		StaticLibraryFile& operator=(StaticLibraryFile&&)      = default;

		explicit StaticLibraryFile(const std::filesystem::path& staticLibraryFile)
			: Linkable(staticLibraryFile)
		{}
	};
}
