#include "../Include/CBString.h"
#include "../Include/Exception.h"
#include <sstream>
#include <exception>

namespace CB{
	namespace String{
		const CString	FromInt32(const int iValue){
			try{
				std::wstringstream ss;

				ss << iValue;

				return ss.str().c_str();
			}
			catch(std::exception& Exception){
				throw CB::Exception::CException(
					FromANSI(Exception.what()), __FUNCTIONW__, __FILEW__, __LINE__);
			}
		}

		const int	ToInt32(const CString& strText){
			if(strText.IsEmpty()){
				throw CB::Exception::CZeroLengthArgumentException(L"strText", 
					L"Cannot convert empty string.", __FUNCTIONW__, __FILEW__, __LINE__);
			}

			std::wstringstream ss;
			int iValue = 0;
			try{
				ss << strText.ToConst();
				ss >> iValue;
			}
			catch(std::exception& Exception){
				throw CB::Exception::CException(
					FromANSI(Exception.what()), __FUNCTIONW__, __FILEW__, __LINE__);
			}

			if(ss.fail()){
				throw CB::Exception::CInvalidArgumentException(L"strText", strText, 
					L"Invalid string for conversion.", __FUNCTIONW__, __FILEW__, __LINE__);
			}

			return iValue;
		}

		const CString	FromUInt32(const unsigned uValue){
			try{
			std::wstringstream ss;

			ss << uValue;

			return ss.str().c_str();
			}
			catch(std::exception& Exception){
				throw CB::Exception::CException(
					FromANSI(Exception.what()), __FUNCTIONW__, __FILEW__, __LINE__);
			}
		}

		const unsigned	ToUInt32(const CString& strText){
			if(strText.IsEmpty()){
				throw CB::Exception::CZeroLengthArgumentException(L"strText", 
					L"Cannot convert empty string.", __FUNCTIONW__, __FILEW__, __LINE__);
			}

			std::wstringstream ss;
			unsigned uValue = 0;

			try{
				ss << strText.ToConst();
				ss >> uValue;
			}
			catch(std::exception& Exception){
				throw CB::Exception::CException(
					FromANSI(Exception.what()), __FUNCTIONW__, __FILEW__, __LINE__);
			}

			if(ss.fail()){
				throw CB::Exception::CInvalidArgumentException(L"strText", strText, 
					L"Invalid string for conversion.", __FUNCTIONW__, __FILEW__, __LINE__);
			}

			return uValue;
		}

		const CString	FromFloat(const float fValue){
			try{
				std::wstringstream ss;

				ss << fValue;

				return ss.str().c_str();
			}
			catch(std::exception& Exception){
				throw CB::Exception::CException(
					FromANSI(Exception.what()), __FUNCTIONW__, __FILEW__, __LINE__);
			}
		}

		const float	ToFloat(const CString& strText){
			if(strText.IsEmpty()){
				throw CB::Exception::CZeroLengthArgumentException(L"strText", 
					L"Cannot convert empty string.", __FUNCTIONW__, __FILEW__, __LINE__);
			}

			std::wstringstream ss;
			float fValue = 0.0f;

			try{
				ss << strText.ToConst();
				ss >> fValue;
			}
			catch(std::exception& Exception){
				throw CB::Exception::CException(
					FromANSI(Exception.what()), __FUNCTIONW__, __FILEW__, __LINE__);
			}

			if(ss.fail()){
				throw CB::Exception::CInvalidArgumentException(L"strText", strText, 
					L"Invalid string for conversion.", __FUNCTIONW__, __FILEW__, __LINE__);
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

		const bool		ToInt32(const CString& strText, int& iOutValue){
			try{
				std::wstringstream ss;

				ss << strText.ToConst();
				ss >> iOutValue;

				return !ss.fail();
			}
			catch(std::exception& Exception){
				throw CB::Exception::CException(
					FromANSI(Exception.what()), __FUNCTIONW__, __FILEW__, __LINE__);
			}
		}

		const bool		ToUInt32(const CString& strText, unsigned& uOutValue){
			try{
				std::wstringstream ss;

				ss << strText.ToConst();
				ss >> uOutValue;

				return !ss.fail();
			}
			catch(std::exception& Exception){
				throw CB::Exception::CException(
					FromANSI(Exception.what()), __FUNCTIONW__, __FILEW__, __LINE__);
			}
		}

		const bool		ToFloat(const CString& strText, float& fOutValue){
			try{
				std::wstringstream ss;

				ss << strText.ToConst();
				ss >> fOutValue;

				return !ss.fail();
			}
			catch(std::exception& Exception){
				throw CB::Exception::CException(
					FromANSI(Exception.what()), __FUNCTIONW__, __FILEW__, __LINE__);
			}
		}

		const CString	ToHexString(const unsigned uValue){
			try{
				std::wstringstream ss;

				ss << std::hex << uValue;

				return ss.str().c_str();
			}
			catch(std::exception& Exception){
				throw CB::Exception::CException(
					FromANSI(Exception.what()), __FUNCTIONW__, __FILEW__, __LINE__);
			}
		}
	}
}