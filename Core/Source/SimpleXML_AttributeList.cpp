#include "stdafx.h"
#include "../Include/SimpleXML.h"
#include "../Include/Collection_Funcs.h"
#include "../Include/Collection_StringList.h"

namespace CB{
	namespace SXML{
		CAttributeList::CAttributeList(CNode* pParent) :
			m_pParent(pParent)
		{
		}

		CAttributeList::CAttributeList(const CAttributeList& List) :
			m_pParent(List.m_pParent),
			m_List(List.m_List)
		{
		}

		CAttributeList::~CAttributeList(){
			this->Clear();
		}

		CAttribute&	CAttributeList::Add(const CString& strName){
			this->m_List.Add(new CAttribute(this, strName));
			return *this->m_List.Last();
		}

		CAttribute&	CAttributeList::Add(const CString& strName, const CString& strValue){
			this->m_List.Add(new CAttribute(this, strName));
			this->m_List.Last()->Set(strValue);
			return *this->m_List.Last();
		}

		const uint32	CAttributeList::GetLength() const{
			return this->m_List.GetLength();
		}

		const bool	CAttributeList::IsEmpty() const{
			return this->m_List.IsEmpty();
		}

		const CAttribute&	CAttributeList::Get(const uint32 uIndex) const{
			return *this->m_List.Get(uIndex);
		}

		CAttribute&	CAttributeList::Get(const uint32 uIndex){
			return *this->m_List.Get(uIndex);
		}

		const bool	CompareAttribute(const CPtr<CAttribute>& item, const CString& strName){
			return item->GetName() == strName;
		}

		const CAttribute&	CAttributeList::Get(const CString& strName) const{
			auto uIndex = Collection::Find(this->m_List, CompareAttribute, strName);
			return this->Get(uIndex);
		}

		CAttribute&	CAttributeList::Get(const CString& strName){
			auto uIndex = Collection::Find(this->m_List, CompareAttribute, strName);
			return this->Get(uIndex);
		}

		const bool	CAttributeList::Contains(const CString& strName) const{
			return Collection::Contains(this->m_List, CompareAttribute, strName);
		}

		const bool	CAttributeList::Remove(const CString& strName){
			uint32 uIndex = 0;
			if(Collection::TryFind(this->m_List, CompareAttribute, strName, uIndex)){
				delete this->m_List[uIndex].Reset();
				this->m_List.Remove(uIndex);
				return true;
			}
			return false;
		}

		void	CAttributeList::Clear(){
			for(uint32 i = 0; i < this->m_List.GetLength(); i++){
				delete this->m_List[i].Reset();
			}
			this->m_List.Clear();
		}

		const CAttribute&	CAttributeList::operator[](const uint32 uIndex) const{
			return this->Get(uIndex);
		}

		CAttribute&		CAttributeList::operator[](const uint32 uIndex){
			return this->Get(uIndex);
		}

		const CAttribute&	CAttributeList::operator[](const CString& strName) const{
			return this->Get(strName);
		}

		CAttribute&	CAttributeList::operator[](const CString& strName){
			return this->Get(strName);
		}

		const CString	CAttributeList::ToString() const{
			Collection::CStringList list;
			for(uint32 i = 0; i < this->m_List.GetLength(); i++){
				list.Add(this->Get(i).ToString());
			}
			return list.ToString(L" ");
		}

		const uint32	CAttributeList::Parse( const CString& strText, const uint32 uStartIndex ) {
			uint32 uIndex = uStartIndex;

			if( !String::SkipWhiteSpace( strText, uStartIndex, uIndex ) ) {
				CR_THROW(L"AttributeList: Unexpected end of tag.");
			}

			Collection::CStringList endTagList;
			endTagList.Add(L">");
			endTagList.Add(L"/>");
			
			while( !String::SubCompare(strText, uIndex, endTagList ) ) {
				CAttribute* attrib = CAttribute::Parse( this, strText, uIndex, uIndex );

				this->m_List.Add( attrib );

				if( !String::SkipWhiteSpace( strText, uIndex, uIndex ) ){
					CR_THROW(L"AttributeList: Unexpected end of list.");
				}
			}

			return uIndex;
		}
	}
}