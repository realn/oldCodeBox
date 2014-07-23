#include "../Include/CBString.h"
#include "../Include/Exception.h"
#include "../Include/Memory.h"

#include <wchar.h>

const bool MultiCompare(const CB::CString& strText, const uint32 uPos, const CB::CString& strCharList){
	for(uint32 uIndex = 0; uIndex < strCharList.GetLength(); uIndex++){
		if(strText[uPos] == strCharList[uIndex]){
			return true;
		}
	}
	return false;
}

const wchar*	g_szWhiteSpace = L" \n\r\t";
const uint32	g_uWhiteSpaceNumber = 4;

const bool	IsCharWhiteSpace(const wchar uChar){
	for(uint32 uIndex = 0; uIndex < g_uWhiteSpaceNumber; uIndex++){
		if(uChar == g_szWhiteSpace[uIndex]){
			return true;
		}
	}
	return false;
}

namespace CB{
	CString::CString() : 
		m_pStr(0), 
		m_uLength(0)
	{
	}

	CString::CString(const CString& strText) : 
		m_pStr(0), 
		m_uLength(0)
	{
		this->Assign(strText);
	}

	CString::CString(const Collection::IPacked<wchar>& Data) :
		m_pStr(0),
		m_uLength(0)
	{
		if(Data.IsEmpty()){
			return;
		}
		if(Data[0] == 0){
			return;
		}

		for(; this->m_uLength < Data.GetLength(); this->m_uLength++){
			if(Data[this->m_uLength] == 0){
				break;
			}
		}

		this->m_pStr = new wchar[this->m_uLength + 1];

		Memory::SetZero(*(this->m_pStr + this->m_uLength));
		Memory::CopyArray(Data.GetPointer(), this->m_pStr, this->m_uLength);
	}

	CString::CString(const wchar* pStr) : 
		m_pStr(0), 
		m_uLength(0)
	{
		if(pStr == 0){
			throw Exception::CNullArgumentException(L"pStr",
				L"Cannot create string from null pointer", __FUNCTIONW__, __FILEW__, __LINE__);
		}
		if(pStr[0] == 0){
			return;
		}

		this->m_uLength = wcslen(pStr);
		this->m_pStr = new wchar[this->m_uLength + 1];

		Memory::SetZero(*(this->m_pStr + this->m_uLength));
		Memory::CopyArray(pStr, this->m_pStr, this->m_uLength);
	}

	CString::CString(const wchar* pStr, const uint32 uLength) : 
		m_pStr(0), 
		m_uLength(0)
	{
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

		this->m_pStr = new wchar[this->m_uLength + 1];

		Memory::SetZeroArray<wchar>(this->m_pStr, this->m_uLength);
		Memory::CopyArray<wchar>(pStr, this->m_pStr, this->m_uLength);
	}

	CString::CString(const wchar chStr) : 
		m_pStr(0), 
		m_uLength(0)
	{
		if(chStr == 0){
			return;
		}

		this->m_pStr = new wchar[2];
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

		uint32 uLength = 0;
		for(;uLength < this->m_uLength; uLength++){
			if(this->m_pStr[uLength] == 0){
				break;
			}
		}

		if(this->m_uLength == uLength){
			return;
		}

		wchar* pStr = new wchar[uLength+1];
		Memory::SetZero(*(this->m_pStr + this->m_uLength));
		Memory::CopyArray(this->m_pStr, pStr, uLength);

		this->Clear();

		this->m_pStr	= pStr;
		this->m_uLength	= uLength;
	}

	void	CString::Resize(const uint32 uLength){
		if(uLength == 0){
			this->Clear();
			return;
		}

		if(this->m_uLength == 0){
			this->m_uLength = uLength;
			this->m_pStr = new wchar[this->m_uLength + 1];

			Memory::SetZeroArray<wchar>(this->m_pStr, this->m_uLength + 1);
		
			return;
		}

		wchar* pStr = new wchar[uLength + 1];

		Memory::SetZeroArray(pStr, uLength + 1);
		Memory::CopyArray<wchar>(this->m_pStr, pStr, uLength < this->m_uLength ? uLength : this->m_uLength);

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

	const uint32	CString::GetLength() const{
		return this->m_uLength;
	}

	const uint32	CString::GetSizeInBytes() const{
		return this->m_uLength * sizeof(wchar);
	}

	const wchar*		CString::GetPointer() const{
		if(this->m_pStr){
			return this->m_pStr;
		}
		return L"";
	}

	wchar*	CString::GetPointer(){
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
		for(uint32 uIndex = 0; uIndex < this->GetLength(); uIndex++){
			if(!IsCharWhiteSpace(this->m_pStr[uIndex])){
				return false;
			}
		}

		return true;
	}

	const CString	CString::SubStringIndexed(const uint32 uStartPos, const uint32 uEndPos) const{
		return this->SubString(uStartPos, uEndPos - uStartPos);
	}

	const CString	CString::SubString(const uint32 uIndex) const{
		return this->SubString(uIndex, this->m_uLength - uIndex);
	}

	const CString	CString::SubString(const uint32 uIndex, const uint32 uLength) const{
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

		uint32 uRealLength = (uIndex + uLength < this->m_uLength ? uLength : this->m_uLength - uIndex);

		CString strReturn;
		strReturn.Resize(uRealLength);

		Memory::CopyArray<wchar>(this->m_pStr + uIndex, &strReturn[0], uRealLength); 

		return strReturn;
	}

	const bool	CString::SubCompare(const uint32 uIndex, const CString& strCompare) const{
		if(uIndex + strCompare.GetLength() > this->m_uLength){
			return false;
		}
		return this->SubString(uIndex, strCompare.GetLength()) == strCompare;
	}

	const CString	CString::Trim() const{
		return this->Trim(g_szWhiteSpace);
	}

	const CString	CString::Trim(const CString& strCharList) const{
		if(this->IsEmpty()){
			return CString();
		}

		uint32 uPos = 0;
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

		uint32 uEndPos = this->m_uLength;
		for(; uEndPos > 0; uEndPos--){
			if(MultiCompare(*this, uEndPos - 1, strCharList)){
				continue;
			}
			break;
		}

		return this->SubStringIndexed(uPos, uEndPos);
	}

	const bool	CString::Find(const CString& strFind) const{
		uint32 uPos = 0;
		return this->Find(strFind, 0, uPos);
	}

	const bool	CString::Find(const CString& strFind, uint32& uPos) const{
		return this->Find(strFind, 0, uPos);
	}

	const bool	CString::Find(const CString& strFind, const uint32 uStartPos, uint32& uPos) const{
		if(this->IsEmpty() || strFind.IsEmpty()){
			return false;
		}

		for(uint32 uIndex = uStartPos; uIndex < this->m_uLength; uIndex++){
			if(this->SubCompare(uIndex, strFind)){
				uPos = uIndex;
				return true;
			}
		}

		return false;
	}

	const bool	CString::FindLast(const CString& strFind, uint32& uPos) const{
		return this->FindLast(strFind, this->m_uLength, uPos);
	}

	const bool	CString::FindLast(const CString& strFind, const uint32 uReverseStartPos, uint32& uPos) const{
		if(this->IsEmpty() || strFind.IsEmpty() || this->m_uLength < strFind.GetLength()){
			return false;
		}

		uint32 uStartPos = uReverseStartPos;
		if(uStartPos + strFind.GetLength() > this->m_uLength){
			uStartPos = this->m_uLength - strFind.GetLength();
		}

		for(uint32 uIndex = uStartPos + 1; uIndex > 0; uIndex--){
			if(this->SubCompare(uIndex - 1, strFind)){
				uPos = uIndex - 1;
				return true;
			}
		}

		return false;
	}

	const CString	CString::Replace(const CString& strFind, const CString& strReplace) const{
		uint32 uOut = 0;
		return this->Replace(strFind, strReplace, uOut); 
	}

	const CString	CString::Replace(const CString& strFind, const CString& strReplace, uint32& uNumberOfReplaced) const{
		if(strFind.IsEmpty()){
			throw Exception::CZeroLengthException(L"strFind",
				L"Cannot replace empty string.", __FUNCTIONW__, __FILEW__, __LINE__);
		}

		uint32 uPos = 0;
		uint32 uNextPos = 0;
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

	wchar&	CString::Get(const uint32 uIndex){
		return this->m_pStr[uIndex];
	}

	const wchar&	CString::Get(const uint32 uIndex) const{
		return this->m_pStr[uIndex];
	}

	void	CString::Assign(const CString& strText){
		this->Clear();
	
		if(strText.IsEmpty()){
			return;
		}

		this->Resize(strText.GetLength());

		Memory::CopyArray(strText.GetPointer(), this->m_pStr, this->m_uLength);
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

		Memory::CopyArray(this->m_pStr, &strRet[0], this->m_uLength);
		Memory::CopyArray(strText.GetPointer(), &strRet[this->m_uLength], strText.GetLength());

		return strRet;
	}

	const bool	CString::IsEqual(const CString& strText) const{
		if(this->m_uLength != strText.GetLength()){
			return false;
		}
		if(Memory::CompareArray<wchar>(this->m_pStr, strText.GetPointer(), this->m_uLength) == 0){
			return true;
		}
		return false;
	}

	const bool	CString::IsNotEqual(const CString& strText) const{
		return !this->IsEqual(strText);
	}

	const wchar&	CString::operator[](const uint32 uIndex) const{
		return this->Get(uIndex);
	}

	wchar& CString::operator[](const uint32 uIndex){
		return this->Get(uIndex);
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
const CB::CString	operator+(const wchar* pStr, const CB::CString& strText){
	return CB::CString(pStr) + strText;
}

const bool	operator==(const wchar* pStr, const CB::CString& strText){
	return CB::CString(pStr) == strText;
}

const bool	operator!=(const wchar* pStr, const CB::CString& strText){
	return CB::CString(pStr) != strText;
}