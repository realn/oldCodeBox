#include "stdafx.h"
#include "../Include/SimpleXML.h"

namespace CB{
	namespace SXML{
		extern const CString	CreateNewLines(const bool bWithNewLines);
		extern const CString	CreateTabs(const bool bNested, const uint32 uNestLevel);

		CNode::CNode(CNodeList* pParent, const CString& strName) :
			m_pParent(pParent),
			m_strName(strName),
			Attributes(this),
			Nodes(this)
		{}

		CNode::CNode(const CNode& Node) :
			m_pParent(Node.m_pParent),
			m_strName(Node.m_strName),
			m_strValue(Node.m_strValue),
			Attributes(Node.Attributes),
			Nodes(Node.Nodes)
		{
			this->Attributes.m_pParent = this;
			this->Nodes.m_pParent = this;
		}

		const CString	CNode::GetName() const{
			return this->m_strName;
		}

		const CString	CNode::GetValue() const{
			return this->m_strValue;
		}

		void	CNode::Set(const CString& strValue){
			this->m_strValue = strValue;
		}

		const bool	CNode::HasAttributes() const{
			return !this->Attributes.IsEmpty();
		}

		const bool	CNode::HasNodes() const{
			return !this->Nodes.IsEmpty();
		}

		const uint32	CNode::Parse(const CString& strText, const uint32 uStartIndex){
			try{
				const Collection::CList<wchar_t> whiteList = String::ToArray(L" \t\n\r");

				uint32 uIndex = uStartIndex;
				for(; uIndex < strText.GetLength(); uIndex++){
					if(String::MultiCompare(strText, uIndex, whiteList)){
						continue;
					}

					if(strText.SubCompare(uIndex, L"</")){
						return this->ParseEndTag(strText, uStartIndex, uIndex);
					}

					if(strText.SubCompare(uIndex, L"<")){
						uIndex = this->ParseStartTag(strText, uIndex);
					}								
				}
			}
			catch(Exception::CException& Exception){
				throw Exception::CSXMLNodeException(this->m_strName, 
					CR_INFO(), Exception);
			}
			throw Exception::CSXMLException(
				L"No ending tag for SXML node: " + this->m_strName + L".", CR_INFO());
		}

		const uint32	CNode::ParseStartTag(const CString& strText, const uint32 uIndex){
			uint32 uEndPos = uIndex;
			bool bEnded = false;
			if(!strText.Find(L">", uIndex, uEndPos)){
				throw Exception::CSXMLException(L"Failed to find ending bracet.", CR_INFO());
			}
			if(uIndex + 1 == uEndPos){
				throw Exception::CSXMLException(L"No endging tag found.", CR_INFO());
			}
			if(strText.SubCompare(uEndPos - 1, L"/")){
				bEnded = true;
				uEndPos--;
			}

			try{
				//CNode& Node = this->Add(strText.SubStringIndexed(uIndex+1, uEndPos).Trim());
				//if(!bEnded){
				//	return Node.Parse(strText, uEndPos + 1);
				//}
				return uEndPos + 1;
			}
			catch(Exception::CException& Exception){
				throw Exception::CSXMLException(L"Error while adding new node to " + this->m_strName + L" node.", 
					CR_INFO(), Exception);
			}
		}

		const uint32	CNode::ParseEndTag(const CString& strText, const uint32 uStartIndex, const uint32 uIndex){
			uint32 uEndPos = uIndex;
			if(!strText.Find(L">", uIndex, uEndPos)){
				throw Exception::CSXMLException(
					L"Didn't found ending bracet for tag.", CR_INFO());
			}
			if(uIndex + 2 == uEndPos){
				throw Exception::CSXMLException(
					L"Invalid ending tag bracet position.", CR_INFO());
			}

			if(this->m_strName != strText.SubStringIndexed(uIndex + 2, uEndPos).Trim()){
				throw Exception::CSXMLException(
					L"Inalid ending tag for node: " + this->m_strName + L".", CR_INFO());
			}

			try{
				if(!this->HasNodes()){
					this->Set(strText.SubStringIndexed(uStartIndex, uIndex).Trim());
				}
				return uIndex + 1;
			}
			catch(Exception::CException& Exception){
				throw Exception::CSXMLException(L"Error while concluding end tag parsing for node " + this->m_strName + L".",
					CR_INFO(), Exception);
			}
		}

		const CString	CNode::ToString(const bool bWithNewLines, const bool bNested, const uint32 uNestLevel) const{
			try{
				Collection::CStringList RetList;
				RetList.Add(CreateTabs(bNested, uNestLevel));
				RetList.Add(L"<" + this->m_strName);

				if(this->HasAttributes()){
					RetList.Add(L" " + this->Attributes.ToString());
				}

				if(!this->HasNodes() && this->m_strValue.IsEmptyOrWhiteSpace()){
					RetList.Add(L" />");
					RetList.Add(CreateNewLines(bWithNewLines));
				}
				else{
					RetList.Add(L">");
					if(this->HasNodes()){
						RetList.Add(CreateNewLines(bWithNewLines));
						RetList.Add(this->Nodes.ToString(bWithNewLines, bNested, uNestLevel + 1));
						RetList.Add(CreateTabs(bNested, uNestLevel));
					}
					else{
						RetList.Add(this->m_strValue);
					}
					RetList.Add(L"</" + this->m_strName + L">");
					RetList.Add(CreateNewLines(bWithNewLines));
				}

				return RetList.ToString();
			}
			catch(Exception::CException& Exception){
				throw Exception::CSXMLException(L"Error while converting node " + this->m_strName + L" to string.", CR_INFO(), Exception);
			}
		}
	}
}