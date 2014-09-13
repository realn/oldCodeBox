#pragma once

#include <Types.h>

namespace CB{
	class CString;

	namespace Graphic{
		enum class BufferFormat;
		enum class Style;
		enum class VirtualKey;
	}

	namespace String{
		extern const CString	ToString( const Graphic::BufferFormat uFormat );
		extern const CString	ToString( const Graphic::Style uStyle );
		extern const CString	ToString( const Graphic::VirtualKey uKey);
		extern const Graphic::VirtualKey	FromString(const CString& strKey);
	}
}