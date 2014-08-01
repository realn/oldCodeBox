#pragma once

#include "Macros.h"
#include "Types.h"

namespace CB{
	class CString;

	namespace Log{
		enum class LogLevel{
			Debug,
			Info,
			Warning,
			Error,
			Fatal
		};
	}
	namespace String{
		extern COMMON_API const CString	ToString(const Log::LogLevel uLevel);
	}
}