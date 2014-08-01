#include "stdafx.h"
#include "../Include/Collection_StringList.h"
#include "../Include/Exception.h"

namespace CB{
	namespace Collection{
		CStringList::CStringList(){
		}

		CStringList::CStringList(const CStringList& List) : CList<CString>(List){
		}

		CStringList::CStringList(const ICountable<CB::CString>& List) : CList<CString>(List){
		}

		const bool	CStringList::Contains(const CB::CString& strText) const{
			if(strText.IsEmpty()){
				throw CB::Exception::CZeroLengthArgumentException(L"strText",
					L"Cannot search with empty find text.", CR_INFO());
			}

			try{
				for(uint32 uIndex = 0; uIndex < this->GetLength(); uIndex++){
					if(this->Get(uIndex) == strText){
						return true;
					}
				}

				return false;
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while searching for matching string.", CR_INFO(), Exception);
			}
		}

		const uint32	CStringList::IndexOf(const CB::CString& strText) const{
			if(strText.IsEmpty()){
				throw CB::Exception::CZeroLengthArgumentException(L"strText",
					L"Cannot search with empty find text.", CR_INFO());
			}

			try{
				for(uint32 uIndex = 0; uIndex < this->GetLength(); uIndex++){
					if(this->Get(uIndex) == strText){
						return uIndex;
					}
				}

				return false;
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(L"Error while searching for matching string.", CR_INFO(), Exception);
			}

		}

		const CB::CString	CStringList::ToString() const{
			if(this->IsEmpty()){
				return L"";
			}
			try{
				CB::CString strReturn;
				uint32 uLength = 0;

				for(uint32 uIndex = 0; uIndex < this->GetLength(); uIndex++){
					uLength += this->Get(uIndex).GetLength();
				}

				strReturn.Resize(uLength);

				uint32 uIndex = 0;
				for(uint32 uListIndex = 0; uListIndex < this->GetLength(); uListIndex++){
					if(this->Get(uListIndex).IsEmpty()){
						continue;
					}
					Memory::CopyArray<wchar>(&this->Get(uListIndex).Get(0), &strReturn.Get(uIndex), this->Get(uListIndex).GetLength());
					uIndex += this->Get(uListIndex).GetLength();
				}

				return strReturn;
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(L"Error while merging strings.", CR_INFO(), Exception);
			}
		}

		const CB::CString	CStringList::ToString(const CB::CString& strGlue) const{
			if(this->IsEmpty()){
				return L"";
			}

			try{
				CB::CString strReturn;
				uint32 uLength = 0;

				for(uint32 uIndex = 0; uIndex < this->GetLength(); uIndex++){
					uLength += this->Get(uIndex).GetLength();
				}
				uLength += strGlue.GetLength() * (this->GetLength() - 1);

				strReturn.Resize(uLength);

				uint32 uIndex = 0;
				for(uint32 uListIndex = 0; uListIndex < this->GetLength(); uListIndex++){
					if(!this->Get(uListIndex).IsEmpty()){
						Memory::CopyArray(this->Get(uListIndex).GetPointer(), &strReturn[uIndex], this->Get(uListIndex).GetLength());
						uIndex += this->Get(uListIndex).GetLength();
					}
					if(uListIndex != this->GetLength() - 1 && !strGlue.IsEmpty()){
						Memory::CopyArray(strGlue.GetPointer(), &strReturn[uIndex], strGlue.GetLength());
						uIndex += strGlue.GetLength();
					}
				}

				return strReturn;
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(L"Error while gluing strings.", CR_INFO(), Exception);
			}
		}

	}
}