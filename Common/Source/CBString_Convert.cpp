#include "../Include/CBString.h"
#include "../Include/Exception.h"

#include <sstream>
#ifdef WIN32
#include <Windows.h>
#endif

#undef GetMessage

const CB::CString	CB::String::FromANSI(const char* szText){
	unsigned uLength = strlen(szText);
	return CB::String::FromANSI(szText, uLength);
}

const CB::CString	CB::String::FromANSI(const char* szText, const unsigned uLength){
	if(szText == 0){
		throw CB::Exception::CNullPointerException(L"szText", 
			L"Cannot convert from null pointer.", __FUNCTIONW__, __FILEW__, __LINE__);
	}
	if(uLength == 0){
		throw CB::Exception::CZeroLengthException(L"szText",
			L"Connot convert from zero length string.", __FUNCTIONW__, __FILEW__, __LINE__);
	}

	try{
		CB::CString	strReturn;
		unsigned uLen = MultiByteToWideChar(CP_ACP, 0, szText, uLength, 0, 0);

		strReturn.Resize(uLen);

		if(!MultiByteToWideChar(CP_ACP, 0, szText, uLength, &strReturn[0], uLen)){
			DWORD dwError = GetLastError();
			throw CB::Exception::CInvalidVarValueException(L"dwError", CB::String::FromUInt32(dwError),
				L"Error while converting from ANSI to UTF-16.", __FUNCTIONW__, __FILEW__, __LINE__);
		}

		return strReturn;
	}
	catch(CB::Exception::CException& Exception){
		throw CB::Exception::CException(
			L"Error while converting from ANSI to UTF-16 string.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
	}
}

const CB::CString	CB::String::FromUTF8(const char* szText){
	//	TODO: proper utf8 length impelmentation
	throw CB::Exception::CException(L"Not implemented.", __FUNCTIONW__, __FILEW__, __LINE__);
	//return CB::String::FromANSI(szText, uLength);
}

const CB::CString	CB::String::FromUTF8(const char* szText, const unsigned uLength){
	if(szText == 0){
		throw CB::Exception::CNullPointerException(L"szText", 
			L"Cannot convert from null pointer.", __FUNCTIONW__, __FILEW__, __LINE__);
	}
	if(uLength == 0){
		throw CB::Exception::CZeroLengthException(L"szText",
			L"Connot convert from zero length string.", __FUNCTIONW__, __FILEW__, __LINE__);
	}

	try{
		CB::CString	strReturn;
		unsigned uLen = MultiByteToWideChar(CP_UTF8, 0, szText, uLength, 0, 0);

		strReturn.Resize(uLen);

		if(!MultiByteToWideChar(CP_UTF8, 0, szText, uLength, &strReturn[0], uLen)){
			DWORD dwError = GetLastError();
			throw CB::Exception::CInvalidVarValueException(L"dwError", CB::String::FromUInt32(dwError),
				L"Error while converting from UTF-8 to UTF-16.", __FUNCTIONW__, __FILEW__, __LINE__);
		}

		return strReturn;
	}
	catch(CB::Exception::CException& Exception){
		throw CB::Exception::CException(
			L"Error while converting from UTF-8 to UTF-16 string.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
	}
}

const unsigned	CB::String::ToANSICount(const CB::CString& strText){
	return strText.GetLength();
}

void	CB::String::ToANSI(const CB::CString& strText, char* szOutText, const unsigned uBufferLen){
	if(strText.IsEmpty()){
		throw CB::Exception::CZeroLengthException(L"strText",
			L"Cannot convert from zero length string.", __FUNCTIONW__, __FILEW__, __LINE__);
	}
	if(szOutText == 0){
		throw CB::Exception::CNullPointerException(L"szOutText",
			L"Cannot convert to buffer with null pointer.", __FUNCTIONW__, __FILEW__, __LINE__);
	}
	if(uBufferLen < strText.GetLength()){
		throw CB::Exception::CInvalidArgumentException(L"uLength", CB::String::FromUInt32(uBufferLen),
			L"Output buffer must have length at least equal as input string.", __FUNCTIONW__, __FILEW__, __LINE__);
	}

	try{
		
		if(!WideCharToMultiByte(CP_ACP, 0, &strText[0], strText.GetLength(), szOutText, uBufferLen, 0, 0)){
			DWORD dwError = GetLastError();
			throw CB::Exception::CInvalidVarValueException(L"dwError", CB::String::FromUInt32(dwError),
				L"Error while converting from UTF16 to ANSI.", __FUNCTIONW__, __FILEW__, __LINE__);
		}
	}
	catch(CB::Exception::CException& Exception){
		throw CB::Exception::CException(
			L"Error while converting form UTF-16 to ANSII string.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
	}
}

const unsigned	CB::String::ToUTF8Count(const CB::CString& strText){
	if(strText.IsEmpty()){
		return 0;
	}

	return WideCharToMultiByte(CP_UTF8, 0, &strText[0], strText.GetLength(), 0, 0, 0, 0);
}

void	CB::String::ToUTF8(const CB::CString& strText, char* szOutText, const unsigned uBufferLen){
	if(strText.IsEmpty()){
		throw CB::Exception::CZeroLengthException(L"strText",
			L"Cannot convert from zero length string.", __FUNCTIONW__, __FILEW__, __LINE__);
	}
	if(szOutText == 0){
		throw CB::Exception::CNullPointerException(L"szOutText",
			L"Cannot convert to buffer with null pointer.", __FUNCTIONW__, __FILEW__, __LINE__);
	}
	if(uBufferLen < strText.GetLength() + 1){
		throw CB::Exception::CInvalidArgumentException(L"uLength", CB::String::FromUInt32(uBufferLen),
			L"Output buffer must have length at least equal as input string.", __FUNCTIONW__, __FILEW__, __LINE__);
	}

	try{
		BOOL bUsed = FALSE;
		CHAR cChar = '?';
		if(!WideCharToMultiByte(CP_UTF8, 0, &strText[0], strText.GetLength(), szOutText, uBufferLen, 0, 0)){
			DWORD dwError = GetLastError();
			throw CB::Exception::CInvalidVarValueException(L"dwError", CB::String::FromUInt32(dwError),
				L"Error while converting from UTF16 to ANSI.", __FUNCTIONW__, __FILEW__, __LINE__);
		}
	}
	catch(CB::Exception::CException& Exception){
		throw CB::Exception::CException(
			L"Error while converting form UTF-16 to ANSII string.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
	}
}