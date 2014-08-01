#include "stdafx.h"
#include "../Include/CBString_Funcs.h"
#include "../Include/Collection_StringList.h"
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

		const CString	FromInt32(const int32 iValue){
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

		const int32	ToInt32(const CString& strText){
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

		const CString	FromUInt32(const uint32 uValue){
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

		const CString	ToString(const int32 iValue){ 
			return FromInt32(iValue); 
		}

		const CString	ToString(const uint32 uValue){ 
			return FromUInt32(uValue); 
		}

		const CString ToString(const float32 fValue){ 
			return FromFloat(fValue); 
		}

		const CString ToString(const bool bValue){ 
			return FromBool(bValue); 
		}


		const uint32	ToUInt32(const CString& strText){
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

		const bool		ToInt32(const CString& strText, int32& iOutValue){
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

		const bool		ToUInt32(const CString& strText, uint32& uOutValue){
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

		const CString	VarReplace(const CString& strText, const Collection::ICountable<CB::CString>& VarList){
			return VarReplace(strText, VarList, false);
		}

		const CString	VarReplace(const CString& strText, const Collection::ICountable<CB::CString>& VarList, const bool bIgnoreMissing){
			if(strText.IsEmpty()){
				throw CB::Exception::CZeroLengthArgumentException(L"strText",
					L"Cannot replace in empty string.", CR_INFO());
			}
			if(VarList.IsEmpty()){
				throw CB::Exception::CZeroLengthArgumentException(L"VarList",
					L"Cannot replace with empty var list.", CR_INFO());
			}

			try{
				uint32 uPos = 0, uNextPos = 0, uIndex = 0;
				CString strReturn;

				while(strText.Find(L"{", uPos, uNextPos)){
					if(uNextPos - uPos > 0){
						strReturn += strText.SubString(uPos, uNextPos - uPos);
					}

					if(!strText.Find(L"}", uNextPos, uPos)){
						return strReturn + strText.SubString(uNextPos);
					}

					if(uNextPos+1 == uPos){
						uPos = uNextPos + 1;
						strReturn += L"{";
						continue;
					}
			
					if(bIgnoreMissing){
						if(!ToUInt32(strText.SubStringIndexed(uNextPos+1, uPos), uIndex) || uIndex >= VarList.GetLength()){
							uPos = uNextPos + 1;
							strReturn += L"{";
							continue;
						}
					}
					else{
						uIndex = ToUInt32(strText.SubStringIndexed(uNextPos+1, uPos));
					}

					strReturn += VarList[uIndex];
					uPos = uPos + 1;
				}

				return strReturn + strText.SubString(uPos);
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while replacing vars in string.", CR_INFO(), Exception);
			}
		}

		const CString	Format(const CString& strFormat, const CString& strOp1){
			CB::Collection::CStringList argList;
			argList.Add(strOp1);
			return VarReplace(strFormat, argList, false);
		}

		const CString	Format(const CString& strFormat, const CString& strOp1, const CString& strOp2){
			CB::Collection::CStringList argList;
			argList.Add(strOp1);
			argList.Add(strOp2);
			return VarReplace(strFormat, argList, false);
		}

		const CString	Format(const CString& strFormat, const CString& strOp1, const CString& strOp2, const CString& strOp3){
			CB::Collection::CStringList argList;
			argList.Add(strOp1);
			argList.Add(strOp2);
			argList.Add(strOp3);
			return VarReplace(strFormat, argList, false);
		}

		const CString	Format(const CString& strFormat, const CString& strOp1, const CString& strOp2, const CString& strOp3, const CString& strOp4){
			CB::Collection::CStringList argList;
			argList.Add(strOp1);
			argList.Add(strOp2);
			argList.Add(strOp3);
			argList.Add(strOp4);
			return VarReplace(strFormat, argList, false);
		}

		const CString	Format(const CString& strFormat, const CString& strOp1, const CString& strOp2, const CString& strOp3, const CString& strOp4, const CString& strOp5){
			CB::Collection::CStringList argList;
			argList.Add(strOp1);
			argList.Add(strOp2);
			argList.Add(strOp3);
			argList.Add(strOp4);
			argList.Add(strOp5);
			return VarReplace(strFormat, argList, false);
		}

		const CString	FromANSI(const CB::Collection::IPacked<int8>& Array){
			if(Array.IsEmpty()){
				throw CB::Exception::CZeroLengthArgumentException(L"Array",
					L"Cannot create string from empty array.", CR_INFO());
			}

			try{
				return FromANSI(&Array[0], Array.GetLength());
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while converting int8 array to string.", CR_INFO(), Exception);
			}
		}

		const CString	FromUTF8(const Collection::IPacked<int8>& Array){
			if(Array.IsEmpty()){
				throw CB::Exception::CZeroLengthArgumentException(L"Array",
					L"Cannot create string from empty array.", CR_INFO());
			}

			try{
				return FromUTF8(&Array[0], Array.GetLength());
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while converting int8 array to string.", CR_INFO(), Exception);
			}
		}

		const CString	ToString(const Collection::IPacked<wchar>&	Array){
			if(Array.IsEmpty()){
				throw CB::Exception::CZeroLengthArgumentException(L"Array",
					L"Cannot create string from empty array.", CR_INFO());
			}

			try{
				CB::CString strReturn;

				uint32 uRange = 0;
				for(; uRange < Array.GetLength(); uRange++){
					if(Array[uRange] == 0){
						break;
					}
				}
				if(uRange == 0){
					return L"";
				}

				return CString(&Array[0], uRange);
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while converting int8 array to string.", CR_INFO(), Exception);
			}
		}

		void	ToANSI(const CString& strText, Collection::CList<int8>& Array){
			if(strText.IsEmpty()){
				throw CB::Exception::CZeroLengthArgumentException(L"strText", 
					L"Cannot convert empty string to array.", CR_INFO());
			}
			try{
				uint32 uLength = ToANSICount(strText);
				if(Array.GetLength() < uLength){
					Array.Resize(uLength);
				}
				ToANSI(strText, &Array[0], Array.GetLength());
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while converting string to array.", CR_INFO(), Exception);
			}
		}

		void	ToUTF8(const CString& strText, Collection::CList<int8>& Array){
			if(strText.IsEmpty()){
				throw CB::Exception::CZeroLengthArgumentException(L"strText", 
					L"Cannot convert empty string to array.", CR_INFO());
			}

			try{
				Array.Resize(ToUTF8Count(strText));
				ToUTF8(strText, &Array[0], Array.GetLength());
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while converting string to array.", CR_INFO(), Exception);
			}
		}

		const Collection::CList<int8>		ToANSI(const CB::CString& strText){
			Collection::CList<int8>	Array(ToANSICount(strText) + 1);
			Memory::SetZeroArray(Array);
			ToANSI(strText, Array);
			return Array;
		}

		const Collection::CList<int8>		ToUTF8(const CB::CString& strText){
			Collection::CList<int8>	Array(ToUTF8Count(strText) + 1);
			Memory::SetZeroArray(Array);
			ToUTF8(strText, Array);
			return Array;
		}

		void	ToArray(const CString& strText, Collection::CList<wchar>& Array){
			if(strText.IsEmpty()){
				throw CB::Exception::CZeroLengthArgumentException(L"strText", 
					L"Cannot convert empty string to array.", CR_INFO());
			}

			try{
				if(Array.GetLength() < strText.GetLength()){
					Array.Resize(strText.GetLength());
				}
				Memory::SetZeroArray<wchar>(Array);
				Memory::CopyArray<wchar>(&strText[0], &Array.First(), strText.GetLength());
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while converting string to array.", CR_INFO(), Exception);
			}
		}

		const Collection::CList<wchar>	ToArray(const CString& strText){
			Collection::CList<wchar>	Array(strText.GetLength());
			Memory::SetZeroArray(Array);
			ToArray(strText, Array);
			return Array;
		}

		const bool	SubCompare(const CString& strText, const uint32 uPos, const Collection::ICountable<CString>& strCompare){
			uint32 uEndPos = 0;
			return SubCompare(strText, uPos, strCompare, uEndPos);
		}

		const bool	SubCompare(const CString& strText, const uint32 uPos, const Collection::ICountable<CString>& strCompare, uint32& uEndPos){
			if(strText.IsEmpty()){
				return false;
			}
			if(strCompare.IsEmpty()){
				return false;
			}
			if(uPos >= strText.GetLength()){
				return false;
			}

			try{
				for(uint32 uIndex = 0; uIndex < strCompare.GetLength(); uIndex++){
					if(strText.SubCompare(uPos, strCompare[uIndex])){
						uEndPos = uPos + strCompare[uIndex].GetLength();
						return true;
					}
				}

				return false;
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while comparing sub strings from list.", CR_INFO(), Exception);
			}
		}

		const bool	MultiCompare(const CString& strText, const uint32 uPos, const Collection::ICountable<wchar>& CharList){
			const wchar& toCompare = strText[uPos];
			for(uint32 uIndex = 0; uIndex < CharList.GetLength(); uIndex++){
				if(toCompare == CharList[uIndex]){
					return true;
				}
			}
			return false;
		}

		const bool	Find(const CString& strText, const Collection::ICountable<CString>& strFind){
			uint32 uPos = 0;
			return Find(strText, strFind, 0, uPos);
		}

		const bool	Find(const CString& strText, const Collection::ICountable<CString>& strFind, uint32& uOutPos){
			return Find(strText, strFind, 0, uOutPos);
		}

		const bool	Find(const CString& strText, const Collection::ICountable<CString>& strFind, const uint32 uStartPos, uint32& uOutPos){
			if(strText.IsEmpty()){
				return false;
			}
			if(strFind.IsEmpty()){
				return false;
			}
			if(uStartPos >= strText.GetLength()){
				return false;
			}
	
			try{
				for(uint32 uPos = uStartPos; uPos < strText.GetLength(); uPos++){
					for(uint32 uIndex = 0; uIndex < strFind.GetLength(); uIndex++){
						if(strText.SubCompare(uPos, strFind[uIndex])){
							uOutPos = uPos;
							return true;
						}
					}
				}

				return false;
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while searching for strings from list.", CR_INFO(), Exception);
			}
		}

		const bool	FindNot(const CString& strText, const Collection::ICountable<CString>& strSkip){
			uint32 uPos;
			return FindNot(strText, strSkip, 0, uPos);
		}

		const bool	FindNot(const CString& strText, const Collection::ICountable<CString>& strSkip, uint32& uOutPos){
			return FindNot(strText, strSkip, 0, uOutPos);
		}

		const bool	FindNot(const CString& strText, const Collection::ICountable<CString>& strSkip, const uint32 uStartPos, uint32& uOutPos){
			if(strText.IsEmpty() || strSkip.IsEmpty()){
				uOutPos = 0;
				return true;
			}

			try{
				for(uint32 uPos = uStartPos; uPos < strText.GetLength(); uPos++){
					if(!SubCompare(strText, uPos, strSkip)){
						uOutPos = uPos;
						return true;
					}
				}

				return false;
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while skiping strings from list.", CR_INFO(), Exception);
			}
		}
	}
}