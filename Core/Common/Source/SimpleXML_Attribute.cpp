#include "../Include/SimpleXML.h"

namespace CB{
	namespace SXML{
		CAttribute::CAttribute(CAttributeList* pParent, const CString& strName) :
			m_pParent(pParent),
			m_strName(strName)
		{
		}

		CAttribute::CAttribute(const CAttribute& Attribute) :
			m_pParent(Attribute.m_pParent),
			m_strName(Attribute.m_strName),
			m_strValue(Attribute.m_strValue)
		{
		}

		const CString	CAttribute::GetName() const{
			return this->m_strName;
		}

		const CString	CAttribute::GetValue() const{
			return this->m_strValue;
		}

		void	CAttribute::Set(const CString& strValue){
			this->m_strValue = strValue;
		}

		const CString	CAttribute::ToString() const{
			return this->m_strName + L"=\"" + this->m_strValue + L"\"";
		}
	}
}