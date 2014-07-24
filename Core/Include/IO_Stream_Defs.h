#pragma once

#include "Types.h"

namespace CB{
	namespace IO{
		enum class StreamPos{
			Current = 0,
			Begin,
			End,
		};

		enum class Direction{
			Forward,
			Back
		};
	}
}