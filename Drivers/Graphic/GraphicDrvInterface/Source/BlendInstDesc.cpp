#include "../Include/GraphicDriver_Structs.h"
#include "../Include/GraphicDriver_Strings.h"
#include "../../Common/Include/StringEx.h"

namespace CB{
	namespace Graphic{
		CBlendInstDesc::CBlendInstDesc() : 
			uSourceOperand(Graphic::BlendOption::One),
			uDestOperand(Graphic::BlendOption::Zero),
			uOperation(Graphic::BlendOperation::Add)
		{
		}

		CBlendInstDesc::CBlendInstDesc(const CBlendInstDesc& Desc) :
			uSourceOperand(Desc.uSourceOperand),
			uDestOperand(Desc.uDestOperand),
			uOperation(Desc.uOperation)
		{
		}

		CBlendInstDesc::CBlendInstDesc(const BlendOption uSource, const BlendOperation uOperation, const BlendOption uDest) :
			uSourceOperand(uSource),
			uDestOperand(uDest),
			uOperation(uOperation)
		{
		}

		void	CBlendInstDesc::Set(const BlendOption uSource, const BlendOperation uOperation, const BlendOption uDest){
			this->uSourceOperand = uSource;
			this->uOperation = uOperation;
			this->uDestOperand = uDest;
		}

		const CBlendInstDesc&	CBlendInstDesc::operator=(const CBlendInstDesc& Desc){
			this->uDestOperand = Desc.uDestOperand;
			this->uOperation = Desc.uOperation;
			this->uSourceOperand = Desc.uSourceOperand;

			return *this;
		}

		const CString	CBlendInstDesc::ToString() const{
			Collection::CStringList list;

			list.Add(L"Source Operand: " + String::ToString(this->uSourceOperand));
			list.Add(L"Operation: " + String::ToString(this->uOperation));
			list.Add(L"Dest Operand: " + String::ToString(this->uDestOperand));

			return list.ToString(L", ");
		}
	}
}