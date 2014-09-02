#include "stdafx.h"
#include "../Include/Graphic_DisplayMode.h"

#include <CBString.h>
#include <Collection_StringList.h>

namespace CB{
	namespace Graphic{
		const uint32	DMODE_DEFAULT_FREQENCY = 0;
		const uint32	DMODE_DEFAULT_BPP = 0;

		CDisplayMode::CDisplayMode() : 
			uRefreshRate(DMODE_DEFAULT_FREQENCY), 
			uBitsPerPixel(DMODE_DEFAULT_BPP)
		{
		}

		CDisplayMode::CDisplayMode(const CDisplayMode& Mode) : 
			Size(Mode.Size), 
			uRefreshRate(Mode.uRefreshRate), 
			uBitsPerPixel(Mode.uBitsPerPixel)
		{
		}

		CDisplayMode::CDisplayMode(const Math::CSize2D& Size, const uint32 uBitsPerPixel, const uint32 uRefreshRate) : 
			Size(Size), 
			uRefreshRate(uRefreshRate), 
			uBitsPerPixel(uBitsPerPixel)
		{
		}

		void CDisplayMode::Set(const Math::CSize2D& Size, const uint32 uBitsPerPixel, const uint32 uRefreshRate){
			this->Size = Size;
			this->uRefreshRate = uRefreshRate;
			this->uBitsPerPixel = uBitsPerPixel;
		}

		const CDisplayMode&	CDisplayMode::operator=(const CDisplayMode& Mode){
			this->Size = Mode.Size;
			this->uRefreshRate = Mode.uRefreshRate;
			this->uBitsPerPixel = Mode.uBitsPerPixel;

			return *this;
		}

		const bool	CDisplayMode::operator==(const CDisplayMode& Mode) const{
			return this->Size == Mode.Size && this->uRefreshRate == Mode.uRefreshRate && this->uBitsPerPixel == Mode.uBitsPerPixel;
		}

		const bool	CDisplayMode::operator!=(const CDisplayMode& Mode) const{
			return !(this->Size == Mode.Size && this->uRefreshRate == Mode.uRefreshRate && this->uBitsPerPixel == Mode.uBitsPerPixel);
		}

		const CString	CDisplayMode::ToString() const{
			Collection::CStringList list;

			list.Add(L"Size: (" + this->Size.ToString() + L")");
			list.Add(L"Refresh Rate: " + String::ToString(this->uRefreshRate));
			list.Add(L"Bits Per Pixel: " + String::ToString(this->uBitsPerPixel));

			return list.ToString(L", ");
		}
	}
}