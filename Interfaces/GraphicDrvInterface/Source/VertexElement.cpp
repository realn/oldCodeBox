#include "../Include/GraphicDriver_Structs.h"
#include "../Include/GraphicDriver_Strings.h"
#include <CBStringEx.h>

namespace CB{
	namespace Graphic{
		CVertexElement::CVertexElement() :
			uStream(0), 
			strParam(L""), 
			uOffset(0), 
			uType(VertexType::Float), 
			uTypeNumber(0),
			uInstanceUsage(InstanceDataType::None)
		{

		}

		CVertexElement::CVertexElement(const CVertexElement& Element) :
			uStream(Element.uStream), 
			strParam(Element.strParam), 
			uOffset(Element.uOffset), 
			uType(Element.uType), 
			uTypeNumber(Element.uTypeNumber),
			uInstanceUsage(Element.uInstanceUsage)
		{

		}

		CVertexElement::CVertexElement(const uint32 uStream, const CString strParam, const uint32 uOffset, const VertexType uType, const uint32 uTypeNumber) :
			uStream(uStream), 
			strParam(strParam), 
			uOffset(uOffset), 
			uType(uType), 
			uTypeNumber(uTypeNumber),
			uInstanceUsage(InstanceDataType::None)
		{

		}

		CVertexElement::CVertexElement(const uint32 uStream, const CString strParam, const uint32 uOffset, const VertexType uType, const uint32 uTypeNumber, const InstanceDataType uInstance) :
			uStream(uStream), 
			strParam(strParam), 
			uOffset(uOffset), 
			uType(uType), 
			uTypeNumber(uTypeNumber),
			uInstanceUsage(uInstance)
		{

		}

		const uint32	CVertexElement::GetSize() const{
			switch (this->uType){
			case VertexType::Float:		return sizeof(float32) * this->uTypeNumber;
			case VertexType::Color32b:	return sizeof(uint32) * this->uTypeNumber;
			default:
				return 0;
			}
		}

		const CVertexElement&	CVertexElement::operator=(const CVertexElement& Element){
			this->uStream = Element.uStream;
			this->uOffset = Element.uOffset;
			this->uType = Element.uType;
			this->strParam = Element.strParam;
			this->uTypeNumber = Element.uTypeNumber;
			this->uInstanceUsage = Element.uInstanceUsage;

			return *this;
		}

		const CString	CVertexElement::ToString() const{
			Collection::CStringList list;

			list.Add(L"Stream: " + String::FromUInt32(this->uStream));
			list.Add(L"Param: " + this->strParam);
			list.Add(L"Offset: " + String::FromUInt32(this->uOffset));
			list.Add(L"Type: " + String::ToString(this->uType));
			list.Add(L"Type Number: " + String::FromUInt32(this->uTypeNumber));
			list.Add(L"Instance Usage: " + String::ToString(this->uInstanceUsage));

			return list.ToString(L", ");
		}
	}
}