#include "../Include/GraphicDriver_Structs.h"
#include "../Include/GraphicDriver_Strings.h"
#include "../../Common/Include/StringEx.h"

namespace CB{
	namespace Graphic{
		CBlendStateDesc::CBlendStateDesc()
		{
			Memory::SetZeroArray(this->bEnabled, 8);
			Memory::SetZeroArray(this->uWriteMask, 8);
		}

		CBlendStateDesc::CBlendStateDesc(const CBlendStateDesc& Desc) :
			AlphaBlend(Desc.AlphaBlend),
			ColorBlend(Desc.ColorBlend)
		{
			Memory::CopyArray(Desc.bEnabled, this->bEnabled, 8);
			Memory::CopyArray(Desc.uWriteMask, this->uWriteMask, 8);
		}

		CBlendStateDesc::CBlendStateDesc(const bool bEnabled, const CBlendInstDesc& ColorBlend, const CBlendInstDesc& AlphaBlend, const unsigned char uWriteMask) :
			ColorBlend(ColorBlend),
			AlphaBlend(AlphaBlend)
		{
			for(unsigned i = 0; i < 8; i++){
				this->bEnabled[i] = bEnabled;
				this->uWriteMask[i] = uWriteMask;
			}
		}

		void	CBlendStateDesc::Set(const bool bEnabled, const CBlendInstDesc& ColorBlend, const CBlendInstDesc& AlphaBlend, const unsigned char uWriteMask){
			this->AlphaBlend = AlphaBlend;
			this->ColorBlend = ColorBlend;
			for(unsigned i = 0; i < 8; i++){
				this->bEnabled[i] = bEnabled;
				this->uWriteMask[i] = uWriteMask;
			}			
		}

		const CBlendStateDesc&	CBlendStateDesc::operator=(const CBlendStateDesc& Desc){
			this->ColorBlend = Desc.ColorBlend;
			this->AlphaBlend = Desc.AlphaBlend;
			for(unsigned i = 0; i < 8; i++){
				this->bEnabled[i] = Desc.bEnabled[i];
				this->uWriteMask[i] = Desc.uWriteMask[i];
			}

			return *this;
		}

		const CString	CBlendStateDesc::ToString() const{
			Collection::CStringList list;

			for(unsigned i = 0; i < 8; i++){
				list.Add(L"Enabled[" + String::FromUInt32(i) + L"]: " + String::FromBool(this->bEnabled[i]));
				list.Add(L"Write Mask[" + String::FromUInt32(i) + L"]: " + String::ToHexString(this->uWriteMask[i]));
			}
			list.Add(L"Color Blend: (" + this->ColorBlend.ToString() + L")");
			list.Add(L"Alpha Blend: (" + this->AlphaBlend.ToString() + L")");

			return list.ToString(L", ");
		}
	}
}