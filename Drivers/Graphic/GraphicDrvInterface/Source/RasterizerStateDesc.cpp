#include "../Include/GraphicDriver_Strings.h"
#include "../Include/GraphicDriver_Structs.h"
#include <CBStringEx.h>

namespace CB{
	namespace Graphic{
		CRasterizerStateDesc::CRasterizerStateDesc() : 
			uCullMode(CullMode::Back),
			uFillMode(FillMode::Solid),
			bFrontCounterClockWise(false),
			bDepthClipEnabled(true),
			bScissorEnabled(false)
		{
		}

		CRasterizerStateDesc::CRasterizerStateDesc(const CRasterizerStateDesc& Desc) :
			uCullMode(Desc.uCullMode),
			uFillMode(Desc.uFillMode),
			bFrontCounterClockWise(Desc.bFrontCounterClockWise),
			bDepthClipEnabled(Desc.bDepthClipEnabled),
			bScissorEnabled(Desc.bScissorEnabled)
		{
		}

		CRasterizerStateDesc::CRasterizerStateDesc(const CullMode uCull, const FillMode uFill, const bool bFrontCCW, const bool bDepthClip, const bool bScissorTest) :
			uCullMode(uCull),
			uFillMode(uFill),
			bFrontCounterClockWise(bFrontCCW),
			bDepthClipEnabled(bDepthClip),
			bScissorEnabled(bScissorTest)
		{
		}

		void CRasterizerStateDesc::Set(const CullMode uCull, const FillMode uFill, const bool bFrontCCW, const bool bDepthClipEnabled, const bool bScissorEnabled){
			this->uCullMode = uCull;
			this->uFillMode = uFill;
			this->bFrontCounterClockWise = bFrontCCW;
			this->bDepthClipEnabled = bDepthClipEnabled;
			this->bScissorEnabled = bScissorEnabled;
		}

		const CRasterizerStateDesc&	CRasterizerStateDesc::operator=(const CRasterizerStateDesc& Desc){
			this->uCullMode = Desc.uCullMode;
			this->uFillMode = Desc.uFillMode;
			this->bFrontCounterClockWise = Desc.bFrontCounterClockWise;
			this->bDepthClipEnabled = Desc.bDepthClipEnabled;
			this->bScissorEnabled = Desc.bScissorEnabled;
			
			return *this;
		}

		const CString	CRasterizerStateDesc::ToString() const{
			Collection::CStringList list;

			list.Add(L"Cull Mode: " + String::ToString(this->uCullMode));
			list.Add(L"Fill Mode: " + String::ToString(this->uFillMode));
			list.Add(L"Front is CCW: " + String::FromBool(this->bFrontCounterClockWise));
			list.Add(L"Depth Clip: " + String::FromBool(this->bDepthClipEnabled));
			list.Add(L"Scissor Test: " + String::FromBool(this->bScissorEnabled));

			return list.ToString(L", ");
		}
	}
}