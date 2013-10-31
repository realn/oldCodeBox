#include "../Include/CBStringEx.h"
#include "../Include/Exception.h"

using namespace CB::Collection;

CStringList::CStringList(){}

CStringList::CStringList(const CStringList& List) : CLinkList<CString>(List){}

CStringList::CStringList(const CLinkList<CB::CString>& List) : CLinkList<CString>(List){}

const bool	CStringList::Contains(const CB::CString& strText) const{
	if(strText.IsEmpty()){
		throw CB::Exception::CZeroLengthArgumentException(L"strText",
			L"Cannot search with empty find text.", __FUNCTIONW__, __FILEW__, __LINE__);
	}

	try{
		CEnumerator Enumerator = this->GetEnumerator();

		for(Enumerator.ToFirst(); Enumerator.IsValid(); Enumerator.Next()){
			if(Enumerator.Get() == strText){
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

const unsigned	CStringList::IndexOf(const CB::CString& strText) const{
	if(strText.IsEmpty()){
		throw CB::Exception::CZeroLengthArgumentException(L"strText",
			L"Cannot search with empty find text.", __FUNCTIONW__, __FILEW__, __LINE__);
	}

	try{
		CEnumerator Enumerator = this->GetEnumerator();

		unsigned uIndex = 0;
		for(Enumerator.ToFirst(); Enumerator.IsValid(); Enumerator.Next()){
			if(Enumerator.Get() == strText){
				return uIndex;
			}
			uIndex++;
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
		CEnumerator Enumerator = this->GetEnumerator();
		unsigned uLength = 0;

		for(Enumerator.ToFirst(); Enumerator.IsValid(); Enumerator.Next()){
			uLength += Enumerator.Get().GetLength();
		}

		strReturn.Resize(uLength);

		unsigned uIndex = 0;
		for(Enumerator.ToFirst(); Enumerator.IsValid(); Enumerator.Next()){
			if(Enumerator.Get().IsEmpty()){
				continue;
			}
			Memory::CopyArray<wchar_t>(&Enumerator.Get().GetChar(0), &strReturn.GetChar(uIndex), Enumerator.Get().GetLength());
			uIndex += Enumerator.Get().GetLength();
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
		unsigned uLength = 0;

		for(Enumerator.ToFirst(); Enumerator.IsValid(); Enumerator.Next()){
			uLength += Enumerator.Get().GetLength();
			if(Enumerator.HasNext()){
				uLength += strGlue.GetLength();
			}	
		}

		strReturn.Resize(uLength);

		unsigned uIndex = 0;
		for(Enumerator.ToFirst(); Enumerator.IsValid(); Enumerator.Next()){
			if(Enumerator.Get().IsEmpty()){
				continue;
			}
			Memory::CopyArray<wchar_t>(&Enumerator.Get().GetChar(0), &strReturn[uIndex], Enumerator.Get().GetLength());
			uIndex += Enumerator.Get().GetLength();
			if(Enumerator.HasNext() && !strGlue.IsEmpty()){
				Memory::CopyArray<wchar_t>(&strGlue[0], &strReturn[uIndex], strGlue.GetLength());
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