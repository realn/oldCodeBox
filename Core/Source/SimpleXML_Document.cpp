#include "stdafx.h"
#include "../Include/SimpleXML.h"
#include "../Include/SimpleXML_Exceptions.h"
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

		CDocument::~CDocument(){
			Clear();
		}

		void	CDocument::Clear(){
			this->Nodes.Clear();
		}

		void	CDocument::Parse(const CString& strText){
			uint32 uIndex;
			this->Nodes.Parse( strText, 0, uIndex );
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

				return RetList.ToString(CreateNewLines(bWithNewLines));
			}
			catch(Exception::CException& Exception){
				throw Exception::CSXMLException( 
					L"Error while converting SXML Root to string.", CR_INFO(), Exception);
			}
		}
	}
}