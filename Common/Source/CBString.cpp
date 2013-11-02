#include "../Include/CBString.h"
#include "../Include/Exception.h"
#include <sstream>
#include <exception>

namespace CB{
	namespace String{
		const CString	ToString(const Encoding uEncoding){
			switch (uEncoding)
			{
			case Encoding::UTF16:	return L"UTF16";
			case Encoding::UTF8:	return L"UTF8";
			case Encoding::ANSI:	return L"ANSI";
			default:
				return ToString((uint32)uEncoding);
			}
		}

		const CString	Fromint3232(const int32 iValue){
			try{
				std::wstringstream ss;

				ss << iValue;

				return ss.str().c_str();
			}
			catch(std::exception& Exception){
				throw CB::Exception::CException(
					FromANSI((int8*)Exception.what()), CR_INFO());
			}
		}

		const int32	Toint3232(const CString& strText){
			if(strText.IsEmpty()){
				throw CB::Exception::CZeroLengthArgumentException(L"strText", 
					L"Cannot convert empty string.", CR_INFO());
			}

			std::wstringstream ss;
			int32 iValue = 0;
			try{
				ss << strText.GetPointer();
				ss >> iValue;
			}
			catch(std::exception& Exception){
				throw CB::Exception::CException(
					FromANSI((int8*)Exception.what()), CR_INFO());
			}

			if(ss.fail()){
				throw CB::Exception::CInvalidArgumentException(L"strText", strText, 
					L"Invalid string for conversion.", CR_INFO());
			}

			return iValue;
		}

		const CString	FromUint3232(const uint32 uValue){
			try{
			std::wstringstream ss;

			ss << uValue;

			return ss.str().c_str();
			}
			catch(std::exception& Exception){
				throw CB::Exception::CException(
					FromANSI((int8*)Exception.what()), CR_INFO());
			}
		}

		const uint32	ToUint3232(const CString& strText){
			if(strText.IsEmpty()){
				throw CB::Exception::CZeroLengthArgumentException(L"strText", 
					L"Cannot convert empty string.", CR_INFO());
			}

			std::wstringstream ss;
			uint32 uValue = 0;

			try{
				ss << strText.GetPointer();
				ss >> uValue;
			}
			catch(std::exception& Exception){
				throw CB::Exception::CException(
					FromANSI((int8*)Exception.what()), CR_INFO());
			}

			if(ss.fail()){
				throw CB::Exception::CInvalidArgumentException(L"strText", strText, 
					L"Invalid string for conversion.", CR_INFO());
			}

			return uValue;
		}

		const CString	FromFloat(const float32 fValue){
			try{
				std::wstringstream ss;

				ss << fValue;

				return ss.str().c_str();
			}
			catch(std::exception& Exception){
				throw CB::Exception::CException(
					FromANSI((int8*)Exception.what()), CR_INFO());
			}
		}

		const float32	ToFloat(const CString& strText){
			if(strText.IsEmpty()){
				throw CB::Exception::CZeroLengthArgumentException(L"strText", 
					L"Cannot convert empty string.", CR_INFO());
			}

			std::wstringstream ss;
			float32 fValue = 0.0f;

			try{
				ss << strText.GetPointer();
				ss >> fValue;
			}
			catch(std::exception& Exception){
				throw CB::Exception::CException(
					FromANSI((int8*)Exception.what()), CR_INFO());
			}

			if(ss.fail()){
				throw CB::Exception::CInvalidArgumentException(L"strText", strText, 
					L"Invalid string for conversion.", CR_INFO());
			}

			return fValue;
		}

		const CString	FromBool(const bool bValue){
			if(bValue){
				return L"true";
			}
			return L"false";
		}

		const bool	ToBool(const CString& strText){
			if(strText == L"true" || strText == L"True" || strText == L"TRUE"){
				return true;
			}
			return false;
		}

		const bool	ToBool(const CString& strText, bool& bOutValue){
			if(strText == L"true" || strText == L"True" || strText == L"TRUE"){
				bOutValue = true;
				return true;
			}
			if(strText == L"false" || strText == L"False" || strText == L"FALSE"){
				bOutValue = false;
				return true;
			}
			return false;
		}

		const bool		Toint3232(const CString& strText, int32& iOutValue){
			try{
				std::wstringstream ss;

				ss << strText.GetPointer();
				ss >> iOutValue;

				return !ss.fail();
			}
			catch(std::exception& Exception){
				throw CB::Exception::CException(
					FromANSI((int8*)Exception.what()), CR_INFO());
			}
		}

		const bool		ToUint3232(const CString& strText, uint32& uOutValue){
			try{
				std::wstringstream ss;

				ss << strText.GetPointer();
				ss >> uOutValue;

				return !ss.fail();
			}
			catch(std::exception& Exception){
				throw CB::Exception::CException(
					FromANSI((int8*)Exception.what()), CR_INFO());
			}
		}

		const bool		ToFloat(const CString& strText, float32& fOutValue){
			try{
				std::wstringstream ss;

				ss << strText.GetPointer();
				ss >> fOutValue;

				return !ss.fail();
			}
			catch(std::exception& Exception){
				throw CB::Exception::CException(
					FromANSI((int8*)Exception.what()), CR_INFO());
			}
		}

		const CString	ToHexString(const uint32 uValue){
			try{
				std::wstringstream ss;

				ss << std::hex << uValue;

				return ss.str().c_str();
			}
			catch(std::exception& Exception){
				throw CB::Exception::CException(
					FromANSI((int8*)Exception.what()), CR_INFO());
			}
		}
	}
}