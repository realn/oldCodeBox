#include "stdafx.h"
#include "../Include/SimpleXML.h"
#include "../Include/SimpleXML_Exceptions.h"
#include "../Include/Collection_StringList.h"

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

		void	CNode::SetAttributeValue( const CString& strName, const CString& strValue ){
			CAttribute* attr = nullptr;
			if( this->Attributes.Contains( strName ) )
				attr = &this->Attributes[strName];
			else
				attr = &this->Attributes.Add( strName );

			attr->Set( strValue );
		}

		const CString	CNode::GetAttributeValue( const CString& strName, const CString& strDefault ) const{
			if( !this->Attributes.Contains( strName ) )
				return strDefault;

			return this->Attributes[strName].GetValue();
		}

		CNode*	CNode::Parse( CNodeList* pParent, const CString& strText, const uint32 uStartIndex, uint32& uOutIndex ) {
			uint32 uTagStart;
			if( !String::SkipWhiteSpace( strText, uStartIndex, uTagStart ) ) {
				CR_THROW(L"Node: Failed to Find Tag Start.");
			}

			if( !strText.SubCompare( uTagStart, L"<" ) ){
				CR_THROW(L"Node: Missing Tag Start.");
			}

			uint32 uNameStart;
			if( !String::SkipWhiteSpace( strText, uTagStart + 1, uNameStart ) ){
				CR_THROW(L"Node: Failed to Find Name Start.");
			}

			if( strText[uNameStart] == L'>' || strText[uNameStart] == L'/' ) {
				CR_THROW(L"Node: Missing Name Start.");
			}

			Collection::CList<CString>	nameEnd = String::GetWhiteSpace();
			nameEnd.Add(L"/>");
			nameEnd.Add(L">");

			uint32 uNameEnd;
			if( !String::Find( strText, nameEnd, uNameStart, uNameEnd ) ) {
				CR_THROW(L"Node: Failed to Find Name End.");
			}

			CString name = strText.SubStringIndexed( uNameStart, uNameEnd );

			CAutoPtr<CNode> pNode = new CNode( pParent, name );

			uint32 uTagEnd;
			if( !String::SkipWhiteSpace( strText, uNameEnd, uTagEnd ) ) {
				CR_THROW(L"Node: Failed to Find Tag End.");
			}

			if( strText[uTagEnd] != L'>' && strText[uTagEnd] != L'/' ) {
				uTagEnd = pNode->Attributes.Parse( strText, uTagEnd );
			}

			if( strText.SubCompare( uTagEnd, L"/>" ) ){
				uOutIndex = uTagEnd + 2;
				return pNode.Reset();
			}
			else if( strText.SubCompare( uTagEnd, L">" ) ){
				uTagEnd++;
				uint32 uEndTagStart;
				if( !pNode->Nodes.Parse( strText, uTagEnd, uEndTagStart ) ) {
					CString value = strText.SubStringIndexed( uTagEnd, uEndTagStart ).Trim();

					pNode->m_strValue = value;
				}

				if( !strText.SubCompare( uEndTagStart, L"</" ) ){
					CR_THROW(L"Node: Invalid ending tag start.");
				}

				uint32 uEndNameStart = uEndTagStart + 2;
				uint32 uEndNameEnd;
				if( !strText.Find( L">", uEndNameStart, uEndNameEnd ) ){
					CR_THROW(L"Node: Failed to find ending tag name end.");
				}

				name = strText.SubStringIndexed( uEndNameStart, uEndNameEnd ).Trim();
				if( pNode->m_strName != name ){
					CR_THROW(L"Node: Ending tag name isn't euqal to node name.");
				}

				uOutIndex = uEndNameEnd + 1;
				return pNode.Reset();
			}
			else{
				CR_THROW(L"Node: Missing tag end.");
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