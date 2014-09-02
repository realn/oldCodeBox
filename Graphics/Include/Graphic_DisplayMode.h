#pragma once

#include <Types.h>
#include <Math_Size2D.h>

namespace CB{
	class CString;

	namespace Graphic{
		class CDisplay;

		extern const uint32 DMODE_DEFAULT_FREQENCY;
		extern const uint32 DMODE_DEFAULT_BPP;

		//==================================================================
		//	Class representing outputs display modes. Can be used to define 
		//	a device back buffer.
		//==================================================================
		class CDisplayMode{
		public:
			Math::CSize2D	Size;
			uint32			uRefreshRate;
			uint32			uBitsPerPixel;

			CDisplayMode();
			CDisplayMode(const CDisplayMode& Mode);
			CDisplayMode(const Math::CSize2D& Size, const uint32 uBitsPerPixel = DMODE_DEFAULT_BPP, const uint32 uRefreshRate = DMODE_DEFAULT_FREQENCY);

			void Set(const Math::CSize2D& Size, const uint32 uBitsPerPixel = DMODE_DEFAULT_BPP, const uint32 uRefreshRate = DMODE_DEFAULT_FREQENCY);

			const CDisplayMode& operator=(const CDisplayMode& Mode);

			const bool operator==(const CDisplayMode& mode) const;
			const bool operator!=(const CDisplayMode& mode) const;

			const CString	ToString() const;
		};
	}
}