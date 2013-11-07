#include "../Include/GraphicDriver_Structs.h"
#include "../Include/GraphicDriver_Strings.h"
#include <CBStringEx.h>

namespace CB{
	namespace Graphic{
		CBlendStateDesc::CBlendStateDesc()
		{
			Memory::SetZeroArray(this->bEnabled);
			Memory::SetZeroArray(this->uWriteMask);
		}

		CBlendStateDesc::CBlendStateDesc(const CBlendStateDesc& Desc) :
			AlphaBlend(Desc.AlphaBlend),
			ColorBlend(Desc.ColorBlend)
		{
			Memory::CopyArray(Desc.bEnabled, this->bEnabled);
			Memory::CopyArray(Desc.uWriteMask, this->uWriteMask);
		}

		CBlendStateDesc::CBlendStateDesc(const bool bEnabled, const CBlendInstDesc& ColorBlend, const CBlendInstDesc& AlphaBlend, const byte uWriteMask) :
			ColorBlend(ColorBlend),
			AlphaBlend(AlphaBlend)
		{
			for(uint32 i = 0; i < this->bEnabled.GetLength(); i++){
				this->bEnabled[i] = bEnabled;
				this->uWriteMask[i] = uWriteMask;
			}
		}

		void	CBlendStateDesc::Set(const bool bEnabled, const CBlendInstDesc& ColorBlend, const CBlendInstDesc& AlphaBlend, const byte uWriteMask){
			this->AlphaBlend = AlphaBlend;
			this->ColorBlend = ColorBlend;
			for(uint32 i = 0; i < this->bEnabled.GetLength(); i++){
				this->bEnabled[i] = bEnabled;
				this->uWriteMask[i] = uWriteMask;
			}			
		}

		const CBlendStateDesc&	CBlendStateDesc::operator=(const CBlendStateDesc& Desc){
			this->ColorBlend = Desc.ColorBlend;
			this->AlphaBlend = Desc.AlphaBlend;
			Memory::CopyArray(Desc.bEnabled, this->bEnabled);
			Memory::CopyArray(Desc.uWriteMask, this->uWriteMask);

			return *this;
		}

		const CString	CBlendStateDesc::ToString() const{
			Collection::CStringList list;

			for(uint32 i = 0; i < this->bEnabled.GetLength(); i++){
				list.Add(L"Enabled[" + String::FromUInt32(i) + L"]: " + String::FromBool(this->bEnabled[i]));
				list.Add(L"Write Mask[" + String::FromUInt32(i) + L"]: " + String::ToHexString(this->uWriteMask[i]));
			}
			list.Add(L"Color Blend: (" + this->ColorBlend.ToString() + L")");
			list.Add(L"Alpha Blend: (" + this->AlphaBlend.ToString() + L")");

			return list.ToString(L", ");
		}
	}
}