#pragma once

#include <Types.h>

namespace CB{
	class CString;

	namespace Graphic{
		enum class BufferFormat;
	}

	namespace String{
		extern const CString	ToString( const Graphic::BufferFormat uFormat );
	}
}