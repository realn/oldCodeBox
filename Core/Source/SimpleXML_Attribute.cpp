#include "stdafx.h"
#include "../Include/SimpleXML.h"
#include "../Include/Collection_StringList.h"
#include "../Include/CBString_Funcs.h"

namespace CB{
	namespace SXML{
		CAttribute::CAttribute(CAttributeList* pParent, const CString& strName) :
			m_pParent(pParent),
			m_strName(strName)
		{
		}

		CAttribute::CAttribute(CAttributeList* pParent, const CString& strName, const CString& strValue) :
			m_pParent(pParent),
			m_strName(strName),
			m_strValue(strValue)
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

		CAttribute*	CAttribute::Parse( CAttributeList* pParent, const CString& strText, const uint32 uStartIndex, uint32& uOutIndex){
			uint32 uIndex = uStartIndex;
			
			uint32 uNameStart;
			if(!String::SkipWhiteSpace( strText, uIndex, uNameStart )) {
				CR_THROW(L"Attribute: Skip Whitespace Failed.");
			}

			uint32 uNameEnd;
			if(!strText.Find(L"=", uNameStart, uNameEnd)){
				CR_THROW(L"Attribute: Find Name End Failed.");
			}

			uint32 uValueStart;
			if(!String::SkipWhiteSpace( strText, uNameEnd + 1, uValueStart ) ) {
				CR_THROW(L"Attribute: Find Value Start Failed." );
			}

			wchar quoteChar = L'"';
			bool bQuote = strText[uValueStart] == quoteChar;
			if( !bQuote ) {
				quoteChar = L'\'';
				bQuote = strText[uValueStart] == quoteChar;
			}

			uint32 uValueEnd;
			if( bQuote ) {
				uValueStart++;
				if(! strText.Find( quoteChar, uValueStart, uValueEnd ) ) {
					CR_THROW(L"Attribute: Find Quoted Value End Failed.");
				}
			}
			else{
				Collection::CList<CString> endChars = String::GetWhiteSpace();
				endChars.Add(L"/");
				endChars.Add(L">");

				if( !String::Find( strText, endChars, uValueStart, uValueEnd ) ){
					CR_THROW(L"Attribute: Find Value End Failed.");
				}
			}

			CString name = strText.SubStringIndexed( uNameStart, uNameEnd ).Trim();
			CString value;
			if( uValueEnd - uValueStart > 0 )
				value = strText.SubStringIndexed( uValueStart, uValueEnd );

			uOutIndex = uValueEnd;
			if( bQuote )
				uOutIndex++;

			return new CAttribute( pParent, name, value );
		}
	}
}