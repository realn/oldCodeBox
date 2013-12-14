#include "../Include/GraphicDriver_Structs.h"
#include "../Include/GraphicDriver_Strings.h"
#include <CBStringEx.h>

namespace CB{
	namespace Graphic{
		CDisplayMode::CDisplayMode() : 
			uRefreshRate(60), 
			uFormat(Graphic::BufferFormat::R8G8B8A8)
		{
		}

		CDisplayMode::CDisplayMode(const CDisplayMode& Mode) : 
			Size(Mode.Size), 
			uRefreshRate(Mode.uRefreshRate), 
			uFormat(Mode.uFormat)
		{
		}

		CDisplayMode::CDisplayMode(const Math::CSize& Size, const uint32 uRefreshRate, const BufferFormat uFormat) : 
			Size(Size), 
			uRefreshRate(uRefreshRate), 
			uFormat(uFormat)
		{
		}

		void CDisplayMode::Set(const Math::CSize& Size, const uint32 uRefreshRate, const BufferFormat uFormat){
			this->Size = Size;
			this->uRefreshRate = uRefreshRate;
			this->uFormat = uFormat;
		}

		const CDisplayMode&	CDisplayMode::operator=(const CDisplayMode& Mode){
			this->Size = Mode.Size;
			this->uRefreshRate = Mode.uRefreshRate;
			this->uFormat = Mode.uFormat;

			return *this;
		}

		const bool	CDisplayMode::operator==(const CDisplayMode& Mode) const{
			return this->Size == Mode.Size && this->uRefreshRate == Mode.uRefreshRate && this->uFormat == Mode.uFormat;
		}

		const bool	CDisplayMode::operator!=(const CDisplayMode& Mode) const{
			return !(this->Size == Mode.Size && this->uRefreshRate == Mode.uRefreshRate && this->uFormat == Mode.uFormat);
		}

		const CString	CDisplayMode::ToString() const{
			Collection::CStringList list;

			list.Add(L"Size: (" + this->Size.ToString() + L")");
			list.Add(L"Refresh Rate: " + String::FromUInt32(uRefreshRate));
			list.Add(L"Format: " + String::ToString(this->uFormat));

			return list.ToString(L", ");
		}
	}
}