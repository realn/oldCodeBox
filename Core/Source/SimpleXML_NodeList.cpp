#include "stdafx.h"
#include "../Include/SimpleXML.h"
#include "../Include/SimpleXML_Exceptions.h"
#include "../Include/Collection_StringList.h"
#include "../Include/Collection_Funcs.h"

namespace CB{
	namespace SXML{
		extern const CString	CreateNewLines(const bool bWithNewLines);
		extern const CString	CreateTabs(const bool bNested, const uint32 uNestLevel);

		CNodeList::CNodeList(CNode* pParent) :
			m_pParent(pParent)
		{
		}

		CNodeList::CNodeList(const CNodeList& List) :
			m_pParent(List.m_pParent),
			m_List(List.m_List)
		{
		}

		CNodeList::~CNodeList(){
			this->Clear();
		}

		CNode&	CNodeList::Add(const CString& strName){
			try{
				this->m_List.Add(new CNode(this, strName));
				return *this->m_List.Last();
			}
			catch(Exception::CException& Exception){
				throw Exception::CSXMLNodeException(strName, 
					CR_INFO(), Exception);
			}
		}

		CNode&	CNodeList::Add(const CString& strName, const CString& strValue){
			try{
				CNode& Node = this->Add(strName);
				Node.Set(strValue);
				return Node;
			}
			catch(Exception::CException& Exception){
				throw Exception::CSXMLNodeException(strName, CR_INFO(), Exception);
			}
		}

		const bool CompareNodeName(const CPtr<CNode>& Node, const CString& strName){
			return Node->GetName() == strName;
		}

		CNode&	CNodeList::Get(const CString& strName){
			try{
				uint32 uIndex = Collection::Find(this->m_List, CompareNodeName, strName);
				return this->Get(uIndex);
			}
			catch(Exception::CException& Exception){
				throw Exception::CInvalidArgumentException(L"strName", strName, 
					L"Node name not found.", CR_INFO(), Exception);
			}
		}

		const CNode&	CNodeList::Get(const CString& strName) const{
			try{
				uint32 uIndex = Collection::Find(this->m_List, CompareNodeName, strName);
				return this->Get(uIndex);
			}
			catch(Exception::CException& Exception){
				throw Exception::CInvalidArgumentException(L"strName", strName, 
					L"Node name not found.", CR_INFO(), Exception);
			}
		}

		const uint32	CNodeList::GetLength() const{
			return this->m_List.GetLength();
		}

		const bool	CNodeList::IsEmpty() const{
			return this->m_List.IsEmpty();
		}

		CNode&	CNodeList::Get(const uint32 uIndex){
			return *this->m_List.Get(uIndex);
		}

		const CNode&	CNodeList::Get(const uint32 uIndex) const {
			return *this->m_List.Get(uIndex);
		}

		const bool	CNodeList::Contains(const CString& strName) const{
			try{
				return Collection::Contains(this->m_List, CompareNodeName, strName);
			}
			catch(Exception::CException& Exception){
				throw Exception::CSXMLException(
					L"Error while checking for node " + strName + L" existance.", CR_INFO(), Exception);
			}
		}

		void	CNodeList::Remove(const CString& strName){
			try{
				uint32 uIndex = 0;
				if(Collection::TryFind(this->m_List, CompareNodeName, strName, uIndex)){
					delete this->m_List[uIndex].Reset();
					this->m_List.Remove(uIndex);
				}
			}
			catch(Exception::CException& Exception){
				throw Exception::CSXMLNodeMissingException(strName, strName,
					CR_INFO(), Exception);
			}
		}

		void	CNodeList::Clear(){
			for(uint32 i = 0; i < this->m_List.GetLength(); i++){
				delete this->m_List[i].Reset();
			}
			this->m_List.Clear();
		}

		const CString	CNodeList::ToString() const{
			return this->ToString(false, false, 0);
		}
		
		const CString	CNodeList::ToString(const bool bWithNewLines) const{
			return this->ToString(bWithNewLines, false, 0);
		}

		const CString	CNodeList::ToString(const bool bWithNewString, const bool bNested) const{
			return this->ToString(bWithNewString, bNested, 0);
		}

		CNode&	CNodeList::operator[](const CString& strName){
			return this->Get(strName);
		}

		const CNode&	CNodeList::operator[](const CString& strName) const{
			return this->Get(strName);
		}

		CNode&	CNodeList::operator[](const uint32 uIndex){
			return this->Get(uIndex);
		}

		const CNode&	CNodeList::operator[](const uint32 uIndex) const{
			return this->Get(uIndex);
		}

		const CString	CNodeList::ToString(const bool bWithNewLines, const bool bNested, const uint32 uNestLevel) const{
			try{
				Collection::CStringList RetList;
				
				if(!this->IsEmpty()){
					for(uint32 i = 0; i < this->m_List.GetLength(); i++){
						RetList.Add(this->m_List[i]->ToString(bWithNewLines, bNested, uNestLevel));
					}
				}

				return RetList.ToString();
			}
			catch(Exception::CException& Exception){
				throw Exception::CSXMLException(L"Error while converting node list to string.", CR_INFO(), Exception);
			}
		}

		const bool	CNodeList::Parse( const CString& strText, const uint32 uStartIndex, uint32& uOutIndex ){
			uint32 uIndex;
			if( !String::SkipWhiteSpace( strText, uStartIndex, uIndex ) ){
				return false;
			}

			if( strText.SubCompare( uIndex, L"</" ) ) {
				return false;
			}

			if( strText[uIndex] != L'<' ){
				if( !strText.Find(L"</", uIndex, uOutIndex ) ) {
					uOutIndex = uIndex;
				}
				return false;
			}

			while( !strText.SubCompare( uIndex, L"</" ) ) {
				if( strText[uIndex] != L'<') {
					CR_THROW(L"NodeList: Invalid Value inside node list.");
				}

				CNode* pNode = CNode::Parse( this, strText, uIndex, uIndex );
				this->m_List.Add( pNode );

				if( !String::SkipWhiteSpace( strText, uIndex, uIndex ) ){
					uOutIndex = strText.GetLength();
					return true;
				}
			}

			uOutIndex = uIndex;
			return true;
		}
	}
}