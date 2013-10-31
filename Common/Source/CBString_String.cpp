#include "../Include/CBString.h"
#include "../Include/Exception.h"
#include "../Include/Memory.h"

#include <wchar.h>

const bool MultiCompare(const CB::CString& strText, const unsigned uPos, const CB::CString& strCharList){
	for(unsigned uIndex = 0; uIndex < strCharList.GetLength(); uIndex++){
		if(strText[uPos] == strCharList[uIndex]){
			return true;
		}
	}
	return false;
}

const wchar_t*	szWhiteSpace = L" \n\r\t";
const unsigned	uWhiteSpaceNumber = 4;

const bool	IsCharWhiteSpace(const wchar_t uChar){
	for(unsigned uIndex = 0; uIndex < uWhiteSpaceNumber; uIndex++){
		if(uChar == szWhiteSpace[uIndex]){
			return true;
		}
	}
	return false;
}

namespace CB{
	CString::CString() : m_pStr(0), m_uLength(0){
	}

	CString::CString(const CString& strText) : m_pStr(0), m_uLength(0){
		this->Assign(strText);
	}

	CString::CString(const wchar_t* pStr) : m_pStr(0), m_uLength(0){
		if(pStr == 0){
			throw Exception::CNullArgumentException(L"pStr",
				L"Cannot create string from null pointer", __FUNCTIONW__, __FILEW__, __LINE__);
		}
		if(pStr[0] == 0){
			return;
		}

		this->m_uLength = wcslen(pStr);

		this->m_pStr = new wchar_t[this->m_uLength + 1];

		Memory::SetZeroArray<wchar_t>(this->m_pStr, this->m_uLength + 1);
		Memory::CopyArray<wchar_t>(pStr, this->m_pStr, this->m_uLength);
	}

	CString::CString(const wchar_t* pStr, const unsigned uLength) : m_pStr(0), m_uLength(0){
		if(pStr == NULL){
			throw Exception::CNullArgumentException(L"pStr",
				L"Cannot create string from null pointer.", __FUNCTIONW__, __FILEW__, __LINE__);
		}
		if(uLength == 0){
			throw Exception::CZeroLengthArgumentException(L"uLength",
				L"Cannot create string from zero length one.", __FUNCTIONW__, __FILEW__, __LINE__);
		}

		for(;this->m_uLength < uLength; this->m_uLength++){
			if(pStr[this->m_uLength] == 0){
				break;
			}
		}

		if(this->m_uLength == 0){
			return;
		}

		this->m_pStr = new wchar_t[this->m_uLength + 1];

		Memory::SetZeroArray<wchar_t>(this->m_pStr, this->m_uLength);
		Memory::CopyArray<wchar_t>(pStr, this->m_pStr, this->m_uLength);
	}

	CString::CString(const wchar_t chStr) : m_pStr(0), m_uLength(0){
		if(chStr == 0){
			return;
		}

		this->m_pStr = new wchar_t[2];
		this->m_uLength = 1;

		this->m_pStr[0] = chStr;
		this->m_pStr[1] = 0;
	}

	CString::~CString(){
		this->Clear();
	}

	void	CString::Resize(){
		if(this->m_uLength == 0){
			return;
		}

		unsigned uLength = 0;
		for(;uLength < this->m_uLength; uLength++){
			if(this->m_pStr[uLength] == 0){
				break;
			}
		}

		if(this->m_uLength == uLength){
			return;
		}

		wchar_t* pStr = new wchar_t[uLength+1];
		Memory::SetZeroArray<wchar_t>(pStr, uLength + 1);
		Memory::CopyArray<wchar_t>(this->m_pStr, pStr, uLength);

		this->Clear();

		this->m_pStr	= pStr;
		this->m_uLength	= uLength;
	}

	void	CString::Resize(const unsigned uLength){
		if(uLength == 0){
			this->Clear();
			return;
		}

		if(this->m_uLength == 0){
			this->m_uLength = uLength;
			this->m_pStr = new wchar_t[this->m_uLength + 1];

			Memory::SetZeroArray<wchar_t>(this->m_pStr, this->m_uLength + 1);
		
			return;
		}

		wchar_t* pStr = new wchar_t[uLength + 1];

		Memory::SetZeroArray(pStr, uLength + 1);
		Memory::CopyArray<wchar_t>(this->m_pStr, pStr, uLength < this->m_uLength ? uLength : this->m_uLength);

		this->Clear();

		this->m_pStr	= pStr;
		this->m_uLength = uLength;
	}

	void	CString::Clear(){
		if(this->m_pStr){
			delete[] this->m_pStr;

			this->m_pStr	= 0;
			this->m_uLength = 0;
		}
	}

	const unsigned	CString::GetLength() const{
		return this->m_uLength;
	}

	const wchar_t*		CString::ToConst() const{
		if(this->m_pStr){
			return this->m_pStr;
		}
		return L"";
	}

	const bool		CString::IsEmpty() const{
		if(this->m_pStr == 0 || this->m_uLength == 0){
			return true;
		}

		if(this->m_pStr[0] == 0){
			return true;
		}

		return false;
	}

	const bool		CString::IsEmptyOrWhiteSpace() const{
		if(this->IsEmpty()){
			return true;
		}

		bool haveChars = false;
		for(unsigned uIndex = 0; uIndex < this->GetLength(); uIndex++){
			if(!IsCharWhiteSpace(this->m_pStr[uIndex])){
				return false;
			}
		}

		return true;
	}

	const CString	CString::SubStringIndexed(const unsigned uStartPos, const unsigned uEndPos) const{
		return this->SubString(uStartPos, uEndPos - uStartPos);
	}

	const CString	CString::SubString(const unsigned uIndex) const{
		return this->SubString(uIndex, this->m_uLength - uIndex);
	}

	const CString	CString::SubString(const unsigned uIndex, const unsigned uLength) const{
		if(this->IsEmpty()){
			throw Exception::CZeroLengthException(L"CString",
				L"Source string is empty.", __FUNCTIONW__, __FILEW__, __LINE__);
		}
		if(uIndex >= this->m_uLength){
			throw Exception::CInvalidArgumentException(L"uIndex", String::FromUInt32(uIndex),
				L"Sub string index is greather then source string length.", __FUNCTIONW__, __FILEW__, __LINE__);
		}
		if(uLength == 0){
			throw Exception::CZeroLengthException(L"uLength",
				L"Cannot crate zero length sub string.", __FUNCTIONW__, __FILEW__, __LINE__);
		}

		unsigned uRealLength = (uIndex + uLength < this->m_uLength ? uLength : this->m_uLength - uIndex);

		CString strReturn;
		strReturn.Resize(uRealLength);

		Memory::CopyArray<wchar_t>(this->m_pStr + uIndex, &strReturn[0], uRealLength); 

		return strReturn;
	}

	const bool	CString::SubCompare(const unsigned uIndex, const CString& strCompare) const{
		if(uIndex + strCompare.GetLength() > this->m_uLength){
			return false;
		}
		return this->SubString(uIndex, strCompare.GetLength()) == strCompare;
	}

	const CString	CString::Trim() const{
		return this->Trim(L" \t\n\r");
	}

	const CString	CString::Trim(const CString& strCharList) const{
		if(this->IsEmpty()){
			return CString();
		}

		unsigned uPos = 0;
		for(; uPos < this->m_uLength; uPos++){
			if(MultiCompare(*this, uPos, strCharList)){
				continue;
			}
			break;
		}

		if(uPos == this->m_uLength){
			return CString();
		}
		if(uPos == this->m_uLength - 1){
			return this->SubString(uPos);
		}

		unsigned uEndPos = this->m_uLength;
		for(; uEndPos > 0; uEndPos--){
			if(MultiCompare(*this, uEndPos - 1, strCharList)){
				continue;
			}
			break;
		}

		return this->SubStringIndexed(uPos, uEndPos);
	}

	const bool	CString::Find(const CString& strFind) const{
		unsigned uPos = 0;
		return this->Find(strFind, 0, uPos);
	}

	const bool	CString::Find(const CString& strFind, unsigned& uPos) const{
		return this->Find(strFind, 0, uPos);
	}

	const bool	CString::Find(const CString& strFind, const unsigned uStartPos, unsigned& uPos) const{
		if(this->IsEmpty() || strFind.IsEmpty()){
			return false;
		}

		for(unsigned uIndex = uStartPos; uIndex < this->m_uLength; uIndex++){
			if(this->SubCompare(uIndex, strFind)){
				uPos = uIndex;
				return true;
			}
		}

		return false;
	}

	const bool	CString::FindLast(const CString& strFind, unsigned& uPos) const{
		return this->FindLast(strFind, this->m_uLength, uPos);
	}

	const bool	CString::FindLast(const CString& strFind, const unsigned uReverseStartPos, unsigned& uPos) const{
		if(this->IsEmpty() || strFind.IsEmpty() || this->m_uLength < strFind.GetLength()){
			return false;
		}

		unsigned uStartPos = uReverseStartPos;
		if(uStartPos + strFind.GetLength() > this->m_uLength){
			uStartPos = this->m_uLength - strFind.GetLength();
		}

		for(unsigned uIndex = uStartPos + 1; uIndex > 0; uIndex--){
			if(this->SubCompare(uIndex - 1, strFind)){
				uPos = uIndex - 1;
				return true;
			}
		}

		return false;
	}

	const CString	CString::Replace(const CString& strFind, const CString& strReplace) const{
		unsigned uOut = 0;
		return this->Replace(strFind, strReplace, uOut); 
	}

	const CString	CString::Replace(const CString& strFind, const CString& strReplace, unsigned& uNumberOfReplaced) const{
		if(strFind.IsEmpty()){
			throw Exception::CZeroLengthException(L"strFind",
				L"Cannot replace empty string.", __FUNCTIONW__, __FILEW__, __LINE__);
		}

		unsigned uPos = 0;
		unsigned uNextPos = 0;
		CString	strReturn;

		while(this->Find(strFind, uPos, uNextPos)){
			strReturn += this->SubString(uPos, uNextPos - uPos) + strReplace;
			uPos = uNextPos + strFind.GetLength();
		}

		if(uPos < this->m_uLength){
			strReturn += this->SubString(uPos);
		}

		return strReturn;
	}

	wchar_t&	CString::GetChar(const unsigned uIndex){
		return this->m_pStr[uIndex];
	}

	const wchar_t&	CString::GetChar(const unsigned uIndex) const{
		return this->m_pStr[uIndex];
	}

	void	CString::Assign(const CString& strText){
		this->Clear();
	
		if(strText.IsEmpty()){
			return;
		}

		this->Resize(strText.GetLength());

		Memory::CopyArray<wchar_t>(strText.ToConst(), this->m_pStr, this->m_uLength);
	}

	const CString	CString::Add(const CString& strText) const{
		if(strText.IsEmpty()){
			return *this;
		}
		if(this->IsEmpty()){
			return strText;
		}

		CString strRet;

		strRet.Resize(this->m_uLength + strText.GetLength());

		Memory::CopyArray<wchar_t>(this->m_pStr, &strRet[0], this->m_uLength);
		Memory::CopyArray<wchar_t>(strText.ToConst(), &strRet[this->m_uLength], strText.GetLength());

		return strRet;
	}

	const bool	CString::IsEqual(const CString& strText) const{
		if(this->m_uLength != strText.GetLength()){
			return false;
		}
		if(Memory::CompareArray<wchar_t>(this->m_pStr, strText.ToConst(), this->m_uLength) == 0){
			return true;
		}
		return false;
	}

	const bool	CString::IsNotEqual(const CString& strText) const{
		return !this->IsEqual(strText);
	}

	const wchar_t&	CString::operator[](const unsigned uIndex) const{
		return this->GetChar(uIndex);
	}

	wchar_t& CString::operator[](const unsigned uIndex){
		return this->GetChar(uIndex);
	}

	const CString&	CString::operator=(const CString& strText){
		this->Assign(strText);
		return *this;
	}

	const CString	CString::operator+(const CString& strText) const{
		return this->Add(strText);
	}

	const bool	CString::operator==(const CString& strText) const{
		return this->IsEqual(strText);
	}

	const bool	CString::operator!=(const CString& strText) const{
		return this->IsNotEqual(strText);
	}

	const CString&	CString::operator+=(const CString& strText){
		this->Assign(this->Add(strText));
		return *this;
	}
}

//	Functions
const CB::CString	operator+(const wchar_t* pStr, const CB::CString& strText){
	return CB::CString(pStr) + strText;
}

const bool	operator==(const wchar_t* pStr, const CB::CString& strText){
	return CB::CString(pStr) == strText;
}

const bool	operator!=(const wchar_t* pStr, const CB::CString& strText){
	return CB::CString(pStr) != strText;
}