#include "../Include/CBStringEx.h"
#include "../Include/Exception.h"

using namespace CB::Collection;

CStringList::CStringList(){}

CStringList::CStringList(const CStringList& List) : CList<CString>(List){}

CStringList::CStringList(const ICountable<CB::CString>& List) : CList<CString>(List){}

const bool	CStringList::Contains(const CB::CString& strText) const{
	if(strText.IsEmpty()){
		throw CB::Exception::CZeroLengthArgumentException(L"strText",
			L"Cannot search with empty find text.", __FUNCTIONW__, __FILEW__, __LINE__);
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
			L"Error while searching for matching string.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
	}
}

const uint32	CStringList::IndexOf(const CB::CString& strText) const{
	if(strText.IsEmpty()){
		throw CB::Exception::CZeroLengthArgumentException(L"strText",
			L"Cannot search with empty find text.", __FUNCTIONW__, __FILEW__, __LINE__);
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
		throw CB::Exception::CException(
			L"Error while searching for matching string.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
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
		throw CB::Exception::CException(
			L"Error while merging strings.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
	}
}

const CB::CString	CStringList::ToString(const CB::CString& strGlue) const{
	if(this->IsEmpty()){
		return L"";
	}

	try{
		CB::CString strReturn;
		CEnumerator Enumerator = this->GetEnumerator();
		uint32 uLength = 0;

		for(uint32 uIndex = 0; uIndex < this->GetLength(); uIndex++){
		}
		for(Enumerator.ToFirst(); Enumerator.IsValid(); Enumerator.Next()){
			uLength += Enumerator.Get().GetLength();
			if(Enumerator.HasNext()){
				uLength += strGlue.GetLength();
			}	
		}

		strReturn.Resize(uLength);

		uint32 uIndex = 0;
		for(Enumerator.ToFirst(); Enumerator.IsValid(); Enumerator.Next()){
			if(Enumerator.Get().IsEmpty()){
				continue;
			}
			Memory::CopyArray<wchar>(&Enumerator.Get().GetChar(0), &strReturn[uIndex], Enumerator.Get().GetLength());
			uIndex += Enumerator.Get().GetLength();
			if(Enumerator.HasNext() && !strGlue.IsEmpty()){
				Memory::CopyArray<wchar>(&strGlue[0], &strReturn[uIndex], strGlue.GetLength());
				uIndex += strGlue.GetLength();
			}
		}

		return strReturn;
	}
	catch(CB::Exception::CException& Exception){
		throw CB::Exception::CException(
			L"Error while gluing strings.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
	}
}