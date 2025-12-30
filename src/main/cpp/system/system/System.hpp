#pragma once

#if defined(_WIN32)

#include "WindowsSystem.h"
using System = cpp_smith::WindowsSystem;

#else

#include "PosixSystem.hpp"
using System = cpp_smith::PosixSystem;

#endif
