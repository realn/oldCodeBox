#include "../Include/GraphicDriver_Structs.h"
#include "../../Common/Include/StringEx.h"
#include "../Include/GraphicDriver_Strings.h"

namespace CB{
	namespace Graphic{
		CDepthStencilStateDesc::CDepthStencilStateDesc() :
			uDepthFunction(CompareFunc::Less),
			uStencilReadMask(0xFFFFFFFF),
			uStencilWriteMask(0xFFFFFFFF),
			bDepthTestEnabled(true),
			bDepthWrite(true),
			bStencilTestEnabled(false)
		{
		}

		CDepthStencilStateDesc::CDepthStencilStateDesc(const CDepthStencilStateDesc& Desc) :
			bDepthTestEnabled(Desc.bDepthTestEnabled),
			bDepthWrite(Desc.bDepthWrite),
			uDepthFunction(Desc.uDepthFunction),
			bStencilTestEnabled(Desc.bStencilTestEnabled),
			uStencilReadMask(Desc.uStencilReadMask),
			uStencilWriteMask(Desc.uStencilWriteMask),
			StencilFront(Desc.StencilFront),
			StencilBack(Desc.StencilBack)
		{
		}

		CDepthStencilStateDesc::CDepthStencilStateDesc(const bool bDepthEnabled, const bool bDepthWrite, const CompareFunc uDepthFunc, const bool bStencilEnabled, const unsigned uStencilWrite, const unsigned uStencilRead, const CStencilInstDesc& Front, const CStencilInstDesc& Back):
			bDepthTestEnabled(bDepthEnabled),
			bDepthWrite(bDepthWrite),
			uDepthFunction(uDepthFunc),
			bStencilTestEnabled(bStencilEnabled),
			uStencilReadMask(uStencilRead),
			uStencilWriteMask(uStencilWrite),
			StencilFront(Front),
			StencilBack(Back)
		{
		}

		void	CDepthStencilStateDesc::SetDepth(const bool bEnabled, const CompareFunc uFunction){
			this->bDepthTestEnabled = bEnabled;
			this->uDepthFunction = uFunction;
		}

		void	CDepthStencilStateDesc::SetDepth(const bool bEnabled, const bool bDepthWrite, const CompareFunc uFunction){
			this->bDepthTestEnabled = bEnabled;
			this->bDepthWrite = bDepthWrite;
			this->uDepthFunction = uFunction;
		}

		void	CDepthStencilStateDesc::SetStencil(const bool bEnabled, const CStencilInstDesc& FrontDesc){
			this->bStencilTestEnabled = bEnabled;
			this->StencilFront = FrontDesc;
		}

		void	CDepthStencilStateDesc::SetStencil(const bool bEnabled, const CStencilInstDesc& FrontDesc, const CStencilInstDesc& BackDesc){
			this->bStencilTestEnabled = bEnabled;
			this->StencilFront = FrontDesc;
			this->StencilBack = BackDesc;
		}

		void	CDepthStencilStateDesc::SetStencil(const bool bEnabled, const unsigned uWriteMask, const unsigned uReadMask, const CStencilInstDesc& FrontDesc){
			this->bStencilTestEnabled = bEnabled;
			this->uStencilWriteMask = uWriteMask;
			this->uStencilReadMask = uReadMask;
			this->StencilFront = FrontDesc;
		}

		void	CDepthStencilStateDesc::SetStencil(const bool bEnabled, const unsigned uWriteMask, const unsigned uReadMask, const CStencilInstDesc& FrontDesc, const CStencilInstDesc& BackDesc){
			this->bStencilTestEnabled = bEnabled;
			this->uStencilWriteMask = uWriteMask;
			this->uStencilReadMask = uReadMask;
			this->StencilFront = FrontDesc;
			this->StencilBack = BackDesc;
		}

		const CDepthStencilStateDesc&	CDepthStencilStateDesc::operator=(const CDepthStencilStateDesc& Desc){
			this->bDepthTestEnabled = Desc.bDepthTestEnabled;
			this->bDepthWrite = Desc.bDepthWrite;
			this->uDepthFunction = Desc.uDepthFunction;
			this->bStencilTestEnabled = Desc.bStencilTestEnabled;
			this->uStencilWriteMask = Desc.uStencilWriteMask;
			this->uStencilReadMask = Desc.uStencilReadMask;
			this->StencilFront = Desc.StencilFront;
			this->StencilBack = Desc.StencilBack;

			return *this;
		}

		const CString	CDepthStencilStateDesc::ToString() const{
			Collection::CStringList list;

			list.Add(L"Depth Test Enabled: " + String::FromBool(this->bDepthTestEnabled));
			list.Add(L"Depth Write: " + String::FromBool(this->bDepthWrite));
			list.Add(L"Depth Function: " + String::ToString(this->uDepthFunction));
			list.Add(L"Stencil Test Enabled: " + String::FromBool(this->bStencilTestEnabled));
			list.Add(L"Stencil Write Mask: " + String::ToHexString(this->uStencilWriteMask));
			list.Add(L"Stencil Read Mask: " + String::ToHexString(this->uStencilReadMask));
			list.Add(L"Stencil Front: (" + this->StencilFront.ToString() + L")");
			list.Add(L"Stencil Back: (" + this->StencilBack.ToString() + L")");

			return list.ToString(L", ");
		}
	}
}