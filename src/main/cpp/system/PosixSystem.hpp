#pragma once

#include "faults.hpp"
#include "PosixPipe.hpp"

#include <array>
#include <filesystem>

namespace cpp_smith
{
	struct ShellCommandResult
	{
		int exit_code;
		std::string output;
	};

	struct PosixSystem
	{
		PosixSystem() = delete;

		static std::filesystem::file_time_type getLastWriteTime(const std::filesystem::path& file)
		{
			std::error_code error_code;
			if(!std::filesystem::exists(file, error_code))
			{
				if (error_code.value())
				{
					throw faults::FileSystemError(
						std::format(
							"Failed to check if file exists for file: {}, error code {}",
							file.string(),
							error_code.value()
						)
					);
				}

				return {};
			}

			const auto time = std::filesystem::last_write_time(file, error_code);
			if(error_code.value())
			{
				throw faults::FileSystemError(
					std::format(
						"Failed to get last write time for file: {}, error code {}",
						file.string(),
						error_code.value()
					)
				);
			}

			return time;
		}

		static ShellCommandResult ExecuteCommand(const std::string& command_line)
		{
			Pipe pipe(command_line);
			if (!pipe.get())
			{
				return {-1, {}};
			}

			std::array<char, 4096> buffer;
			std::string output;
			while(fgets(buffer.data(), buffer.size(), pipe.get()))
			{
				output += buffer.data();
			}

			const int status = pipe.close();

			int exit_code = -1;
			if (WIFEXITED(status)) {
				exit_code = WEXITSTATUS(status);
			}

			return {exit_code, output};
		}
	};
}
