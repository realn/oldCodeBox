#include "../Include/GraphicDriver_Structs.h"
#include "../Include/GraphicDriver_Strings.h"
#include <CBStringEx.h>

namespace CB{
	namespace Graphic{
		CStencilInstDesc::CStencilInstDesc() :
			uStencilPass(StencilOperation::Keep),
			uDepthTestFail(StencilOperation::Keep),
			uStencilFail(StencilOperation::Keep),
			uStencilFunc(CompareFunc::Always)
		{
		}

		CStencilInstDesc::CStencilInstDesc(const CStencilInstDesc& Desc) :
			uStencilPass(Desc.uStencilPass),
			uDepthTestFail(Desc.uDepthTestFail),
			uStencilFail(Desc.uStencilFail),
			uStencilFunc(Desc.uStencilFunc)
		{
		}

		CStencilInstDesc::CStencilInstDesc(const StencilOperation uPass, const StencilOperation uDepthFail, const StencilOperation uFail, const CompareFunc uFunc) :
			uStencilPass(uPass),
			uDepthTestFail(uDepthFail),
			uStencilFail(uFail),
			uStencilFunc(uFunc)
		{
		}

		void	CStencilInstDesc::Set(const StencilOperation uPass, const StencilOperation uDepthFail, const StencilOperation uFail, const CompareFunc uFunc){
			this->uStencilPass = uPass;
			this->uDepthTestFail = uDepthFail;
			this->uStencilFail = uFail;
			this->uStencilFunc = uFunc;
		}

		const CStencilInstDesc&	CStencilInstDesc::operator=(const CStencilInstDesc& desc){
			this->uStencilPass = desc.uStencilPass;
			this->uDepthTestFail = desc.uDepthTestFail;
			this->uStencilFail = desc.uStencilFail;
			this->uStencilFunc = desc.uStencilFunc;

			return *this;
		}

		const CString	CStencilInstDesc::ToString() const{
			Collection::CStringList list;

			list.Add(L"Pass Operation: " + String::ToString(this->uStencilPass));
			list.Add(L"Depth Test Fail Operation: " + String::ToString(this->uDepthTestFail));
			list.Add(L"Fail Operation: " + String::ToString(this->uStencilFail));
			list.Add(L"Compare Function: " + String::ToString(this->uStencilFunc));

			return list.ToString(L", ");
		}
	}
}