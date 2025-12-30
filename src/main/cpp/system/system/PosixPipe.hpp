#pragma once

#include <string>
#include <cstdio>

namespace cpp_smith
{
	class Pipe
	{
		using handle = std::unique_ptr<FILE, int(*)(FILE*)>;

		handle _file{nullptr, pclose};
		int _status = 0;

	  public:
		explicit Pipe(const std::string_view cmd)
			: _file(
				popen(std::format("{} 2>&1", cmd).c_str(), "r"),
				pclose
			)
		{}

		Pipe(const Pipe&) = delete;
		Pipe& operator=(const Pipe&) = delete;

		FILE* get() const { return _file.get(); }

		int close()
		{
			if (!_file)
				return _status;

			FILE* f = _file.release();   // prevent destructor close
			_status = pclose(f);
			return _status;
		}

		~Pipe() = default;
	};

}