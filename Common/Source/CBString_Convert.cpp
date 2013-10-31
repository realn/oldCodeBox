#include "../Include/CBString.h"
#include "../Include/Exception.h"

#include <sstream>
#ifdef WIN32
#include <Windows.h>
#endif

#undef GetMessage

const CB::CString	CB::String::FromANSI(const int8* szText){
	uint32 uLength = strlen(reinterpret_cast<const char*>(szText));
	return CB::String::FromANSI(szText, uLength);
}

const CB::CString	CB::String::FromANSI(const int8* szText, const uint32 uLength){
	if(szText == 0){
		throw CB::Exception::CNullPointerException(L"szText", 
			L"Cannot convert from null pointer.", CR_INFO());
	}
	if(uLength == 0){
		throw CB::Exception::CZeroLengthException(L"szText",
			L"Connot convert from zero length string.", CR_INFO());
	}

	try{
		CB::CString	strReturn;

#ifdef WIN32
		uint32 uLen = MultiByteToWideChar(CP_ACP, 0, reinterpret_cast<const char*>(szText), uLength, 0, 0);

		strReturn.Resize(uLen);

		if(!MultiByteToWideChar(CP_ACP, 0, reinterpret_cast<const char*>(szText), uLength, &strReturn[0], uLen)){
			DWORD dwError = GetLastError();
			throw CB::Exception::CInvalidVarValueException(L"dwError", CB::String::FromUInt32(dwError),
				L"Error while converting from ANSI to UTF-16.", CR_INFO());
		}
#else
#error ANSI - UNICODE only on win32 platform implemented.
#endif

		return strReturn;
	}
	catch(CB::Exception::CException& Exception){
		throw CB::Exception::CException(
			L"Error while converting from ANSI to UTF-16 string.", CR_INFO(), Exception);
	}
}

const CB::CString	CB::String::FromUTF8(const int8* szText){
	//	TODO: proper utf8 length impelmentation
	CR_THROWNOTIMPLEMENTED();
	//return CB::String::FromANSI(szText, uLength);
}

const CB::CString	CB::String::FromUTF8(const int8* szText, const uint32 uLength){
	if(szText == 0){
		throw CB::Exception::CNullPointerException(L"szText", 
			L"Cannot convert from null pointer.", CR_INFO());
	}
	if(uLength == 0){
		throw CB::Exception::CZeroLengthException(L"szText",
			L"Connot convert from zero length string.", CR_INFO());
	}

	try{
		CB::CString	strReturn;
#ifdef WIN32
		uint32 uLen = MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<const char*>(szText), uLength, 0, 0);

		strReturn.Resize(uLen);

		if(!MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<const char*>(szText), uLength, &strReturn[0], uLen)){
			DWORD dwError = GetLastError();
			throw CB::Exception::CInvalidVarValueException(L"dwError", CB::String::FromUInt32(dwError),
				L"Error while converting from UTF-8 to UTF-16.", CR_INFO());
		}
#else
#error ANSI - UNICODE only on win32 platform implemented.
#endif

		return strReturn;
	}
	catch(CB::Exception::CException& Exception){
		throw CB::Exception::CException(
			L"Error while converting from UTF-8 to UTF-16 string.", CR_INFO(), Exception);
	}
}

const uint32	CB::String::ToANSICount(const CB::CString& strText){
	return strText.GetLength();
}

void	CB::String::ToANSI(const CB::CString& strText, int8* szOutText, const uint32 uBufferLen){
	if(strText.IsEmpty()){
		throw CB::Exception::CZeroLengthException(L"strText",
			L"Cannot convert from zero length string.", CR_INFO());
	}
	if(szOutText == 0){
		throw CB::Exception::CNullPointerException(L"szOutText",
			L"Cannot convert to buffer with null pointer.", CR_INFO());
	}
	if(uBufferLen < strText.GetLength()){
		throw CB::Exception::CInvalidArgumentException(L"uLength", CB::String::FromUInt32(uBufferLen),
			L"Output buffer must have length at least equal as input string.", CR_INFO());
	}

	try{
#ifdef WIN32
		if(!WideCharToMultiByte(CP_ACP, 0, &strText[0], strText.GetLength(), reinterpret_cast<char*>(szOutText), uBufferLen, 0, 0)){
			DWORD dwError = GetLastError();
			throw CB::Exception::CInvalidVarValueException(L"dwError", CB::String::FromUInt32(dwError),
				L"Error while converting from UTF16 to ANSI.", CR_INFO());
		}
#else
#error ANSI - UNICODE only on win32 platform implemented.
#endif
	}
	catch(CB::Exception::CException& Exception){
		throw CB::Exception::CException(
			L"Error while converting form UTF-16 to ANSII string.", CR_INFO(), Exception);
	}
}

const uint32	CB::String::ToUTF8Count(const CB::CString& strText){
	if(strText.IsEmpty()){
		return 0;
	}

#ifdef WIN32
	return WideCharToMultiByte(CP_UTF8, 0, &strText[0], strText.GetLength(), 0, 0, 0, 0);
#else
#error ANSI - UNICODE only on win32 platform implemented.
#endif
}

void	CB::String::ToUTF8(const CB::CString& strText, int8* szOutText, const uint32 uBufferLen){
	if(strText.IsEmpty()){
		throw CB::Exception::CZeroLengthException(L"strText",
			L"Cannot convert from zero length string.", CR_INFO());
	}
	if(szOutText == 0){
		throw CB::Exception::CNullPointerException(L"szOutText",
			L"Cannot convert to buffer with null pointer.", CR_INFO());
	}
	if(uBufferLen < strText.GetLength() + 1){
		throw CB::Exception::CInvalidArgumentException(L"uLength", CB::String::FromUInt32(uBufferLen),
			L"Output buffer must have length at least equal as input string.", CR_INFO());
	}

	try{
#ifdef WIN32
		BOOL bUsed = FALSE;
		CHAR cChar = '?';
		if(!WideCharToMultiByte(CP_UTF8, 0, &strText[0], strText.GetLength(), reinterpret_cast<char*>(szOutText), uBufferLen, 0, 0)){
			DWORD dwError = GetLastError();
			throw CB::Exception::CInvalidVarValueException(L"dwError", CB::String::FromUInt32(dwError),
				L"Error while converting from UTF16 to ANSI.", CR_INFO());
		}
#else
#error ANSI - UNICODE only on win32 platform implemented.
#endif
	}
	catch(CB::Exception::CException& Exception){
		throw CB::Exception::CException(
			L"Error while converting form UTF-16 to ANSII string.", CR_INFO(), Exception);
	}
}