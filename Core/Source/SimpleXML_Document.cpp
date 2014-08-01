#include "stdafx.h"
#include "../Include/SimpleXML.h"
#include "../Include/CBString.h"
#include "../Include/Collection_StringList.h"

namespace CB{
	namespace SXML{

		const CString	CreateNewLines(const bool bWithNewLines){
			if(bWithNewLines){
				return L"\n";
			}
			return L"";
		}

		const CString	CreateTabs(const bool bNested, const uint32 uNestLevel){
			if(!bNested){
				return L"";
			}
			CString strReturn;
			for(uint32 uIndex = 0; uIndex < uNestLevel; uIndex++){
				strReturn += L"\t";
			}
			return strReturn;
		}

		//=================================================================
		//	Root DEFINITION
		//=================================================================

		CDocument::CDocument() :
			Nodes( nullptr )
		{
		}

		void	CDocument::Parse(const CString& strText){
			static const Collection::CList<wchar_t> whiteList = String::ToArray(L" \n\t\r");

			for(uint32 uIndex = 0; uIndex < strText.GetLength(); uIndex++){
				if(String::MultiCompare(strText, uIndex, whiteList)){
					continue;
				}

				if(strText.SubCompare(uIndex, L"<")){
					//uIndex = this->m_Root.ParseStartTag(strText, uIndex);
				}
			}
		}

		const CString	CDocument::ToString() const{
			return this->ToString(false, false);
		}

		const CString	CDocument::ToString(const bool bWithNewLines) const{
			return this->ToString(bWithNewLines, false);
		}

		const CString	CDocument::ToString(const bool bWithNewLines, const bool bNested) const{
			try{
				Collection::CStringList RetList;

				for(uint32 i = 0; i < this->Nodes.GetLength(); i++)
				{
					RetList.Add(this->Nodes[i].ToString(bWithNewLines, bNested, 0));
				}
				if(bWithNewLines){
					RetList.Add(CreateNewLines(bWithNewLines));
				}

				return RetList.ToString();
			}
			catch(Exception::CException& Exception){
				throw Exception::CSXMLException( 
					L"Error while converting SXML Root to string.", CR_INFO(), Exception);
			}
		}
	}

	namespace Exception{
		//	====SXML Exception Class====

		CSXMLException::CSXMLException(const CSXMLException& Exception) : 
			CException(Exception)
		{
		}

		CSXMLException::CSXMLException(const CString& strMessage, const CString& strFunction, const CString& strFile, const uint32 uLine) :
			CException(strMessage, strFunction, strFile, uLine)
		{
		}

		CSXMLException::CSXMLException(const CString& strMessage, const CString& strFunction, const CString& strFile, const uint32 uLine, const CException& Exception) :
			CException(strMessage, strFunction, strFile, uLine, Exception)
		{
		}

		CException*	CSXMLException::CreateCopy() const{
			return new CSXMLException(*this);
		}

		//	====SXML Node Exception Class====
		CSXMLNodeException::CSXMLNodeException(const CSXMLNodeException& Exception) :
			CSXMLException(Exception),
			m_strNodeName(Exception.m_strNodeName)
		{
		}

		CSXMLNodeException::CSXMLNodeException(const CString& strName, const CString& strFunction, const CString& strFile, const uint32 uLine) :
			CSXMLException(L"Error in Simple XML Node.", strFunction, strFile, uLine),
			m_strNodeName(strName)
		{
		}

		CSXMLNodeException::CSXMLNodeException(const CString& strName, const CString& strFunction, const CString& strFile, const uint32 uLine, const CException& InnerException) :
			CSXMLException(L"Error in Simple XML Node {0}.", strFunction, strFile, uLine, InnerException),
			m_strNodeName(strName)
		{
		}

		const CString	CSXMLNodeException::GetMessage() const{
			Collection::CStringList varList;

			varList.Add(this->m_strNodeName);

			return String::VarReplace(this->m_strMessage, varList, true);
		}

		CException*	CSXMLNodeException::CreateCopy() const{
			return new CSXMLNodeException(*this);
		}

		//	====SXML Node Missing Exception Class====
		const CString	g_strNodeMissingError = L"Missing node {1} in Simple XML parent {0}.";

		CSXMLNodeMissingException::CSXMLNodeMissingException(const CSXMLNodeMissingException& Exception) :
			CSXMLNodeException(Exception),
			m_strChildName(Exception.m_strChildName)
		{
			this->m_strMessage = g_strNodeMissingError;
		}

		CSXMLNodeMissingException::CSXMLNodeMissingException(const CString& strName, const CString& strParentName, const CString& strFunction, const CString& strFile, const uint32 uLine) :
			CSXMLNodeException(strParentName, strFunction, strFile, uLine),
			m_strChildName(strName)
		{
			this->m_strMessage = g_strNodeMissingError;
		}

		CSXMLNodeMissingException::CSXMLNodeMissingException(const CString& strName, const CString& strParentName, const CString& strFunction, const CString& strFile, const uint32 uLine, const CException& InnerException) :
			CSXMLNodeException(strParentName, strFunction, strFile, uLine, InnerException),
			m_strChildName(strName)
		{
			this->m_strMessage = g_strNodeMissingError;
		}

		const CString	CSXMLNodeMissingException::GetMessage() const{
			Collection::CStringList varList;

			varList.Add(this->m_strNodeName);
			varList.Add(this->m_strChildName);

			return String::VarReplace(this->m_strMessage, varList, true);
		}

		CException*	CSXMLNodeMissingException::CreateCopy() const{
			return new CSXMLNodeMissingException(*this);
		}

		//	====SXML Value Pocessing Exception====
		const CString g_strValueProcessingError = L"Error while processing value in Simple XML Node {0}.";

		CSXMLValueProcessingException::CSXMLValueProcessingException(const CSXMLValueProcessingException& Exception) :
			CSXMLNodeException(Exception)
		{
			this->m_strMessage = g_strValueProcessingError;
		}

		CSXMLValueProcessingException::CSXMLValueProcessingException(const CString& strName, const CString& strFunction, const CString& strFile, const uint32 uLine) :
			CSXMLNodeException(strName, strFunction, strFile, uLine)
		{
			this->m_strMessage = g_strValueProcessingError;
		}

		CSXMLValueProcessingException::CSXMLValueProcessingException(const CString& strName, const CString& strFunction, const CString& strFile, const uint32 uLine, const CException& Exception) :
			CSXMLNodeException(strName, strFunction, strFile, uLine, Exception)
		{
			this->m_strMessage = g_strValueProcessingError;
		}

		CException*	CSXMLValueProcessingException::CreateCopy() const{
			return new CSXMLValueProcessingException(*this);
		}

		//	====SXML Value Parsing Exception====
		const CString g_strValueParsingError = L"Error while parsing value {1} in Simple XML Node {0}.";

		CSXMLValueParsingException::CSXMLValueParsingException(const CSXMLValueParsingException& Exception) :
			CSXMLValueProcessingException(Exception),
			m_strValue(Exception.m_strValue)
		{
			this->m_strMessage = g_strValueParsingError;
		}

		CSXMLValueParsingException::CSXMLValueParsingException(const CString& strName, const CString& strValue, const CString& strFunction, const CString& strFile, const uint32 uLine) :
			CSXMLValueProcessingException(strName, strFunction, strFile, uLine),
			m_strValue(strValue)
		{
			this->m_strMessage = g_strValueParsingError;
		}

		CSXMLValueParsingException::CSXMLValueParsingException(const CString& strName, const CString& strValue, const CString& strFunction, const CString& strFile, const uint32 uLine, const CException& Exception) :
			CSXMLValueProcessingException(strName, strFunction, strFile, uLine, Exception),
			m_strValue(strValue)
		{
			this->m_strMessage = g_strValueParsingError;
		}

		const CString	CSXMLValueParsingException::GetMessage() const{
			Collection::CStringList varList;

			varList.Add(this->m_strNodeName);
			varList.Add(this->m_strValue);

			return String::VarReplace(this->m_strMessage, varList, true);
		}

		CException*	CSXMLValueParsingException::CreateCopy() const{
			return new CSXMLValueParsingException(*this);
		}
	}
}