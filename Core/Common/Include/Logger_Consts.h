#pragma once

#include "CBString.h"

namespace CB{
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