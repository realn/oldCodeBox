#include "../Include/CBStringEx.h"
#include "../Include/Exception.h"

namespace CB{
	namespace String{
		const CString	VarReplace(const CString& strText, const Collection::CLinkList<CB::CString>& VarList){
			return VarReplace(strText, VarList, false);
		}

		const CString	VarReplace(const CString& strText, const Collection::CLinkList<CB::CString>& VarList, const bool bIgnoreMissing){
			if(strText.IsEmpty()){
				throw CB::Exception::CZeroLengthArgumentException(L"strText",
					L"Cannot replace in empty string.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
			if(VarList.IsEmpty()){
				throw CB::Exception::CZeroLengthArgumentException(L"VarList",
					L"Cannot replace with empty var list.", __FUNCTIONW__, __FILEW__, __LINE__);
			}

			try{
				Collection::CLinkList<CB::CString>::CEnumerator Enumerator = VarList.GetEnumerator();
				unsigned uPos = 0, uNextPos = 0, uIndex = 0;
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
					L"Error while replacing vars in string.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
			}
		}

		const CString	FromANSI(const CB::Collection::CList<char>& Array){
			if(Array.IsEmpty()){
				throw CB::Exception::CZeroLengthArgumentException(L"Array",
					L"Cannot create string from empty array.", __FUNCTIONW__, __FILEW__, __LINE__);
			}

			try{
				return FromANSI(&Array[0], Array.GetLength());
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while converting char array to string.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
			}
		}

		const CString	FromUTF8(const Collection::CList<char>& Array){
			if(Array.IsEmpty()){
				throw CB::Exception::CZeroLengthArgumentException(L"Array",
					L"Cannot create string from empty array.", __FUNCTIONW__, __FILEW__, __LINE__);
			}

			try{
				return FromUTF8(&Array[0], Array.GetLength());
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while converting char array to string.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
			}
		}

		const CString	ToString(const Collection::CList<wchar_t>&	Array){
			if(Array.IsEmpty()){
				throw CB::Exception::CZeroLengthArgumentException(L"Array",
					L"Cannot create string from empty array.", __FUNCTIONW__, __FILEW__, __LINE__);
			}

			try{
				CB::CString strReturn;

				unsigned uRange = 0;
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
					L"Error while converting char array to string.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
			}
		}

		void	ToANSI(const CString& strText, Collection::CList<char>& Array){
			if(strText.IsEmpty()){
				throw CB::Exception::CZeroLengthArgumentException(L"strText", 
					L"Cannot convert empty string to array.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
			try{
				unsigned uLength = ToANSICount(strText);
				if(Array.GetLength() < uLength){
					Array.Resize(uLength);
				}
				ToANSI(strText, &Array[0], Array.GetLength());
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while converting string to array.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
			}
		}

		void	ToUTF8(const CString& strText, Collection::CList<char>& Array){
			if(strText.IsEmpty()){
				throw CB::Exception::CZeroLengthArgumentException(L"strText", 
					L"Cannot convert empty string to array.", __FUNCTIONW__, __FILEW__, __LINE__);
			}

			try{
				Array.Resize(ToUTF8Count(strText));
				ToUTF8(strText, &Array[0], Array.GetLength());
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while converting string to array.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
			}
		}

		const Collection::CList<char>		ToANSI(const CB::CString& strText){
			Collection::CList<char>	Array(ToANSICount(strText) + 1);
			Memory::SetZeroArray(Array);
			ToANSI(strText, Array);
			return Array;
		}

		const Collection::CList<char>		ToUTF8(const CB::CString& strText){
			Collection::CList<char>	Array(ToUTF8Count(strText) + 1);
			Memory::SetZeroArray(Array);
			ToUTF8(strText, Array);
			return Array;
		}

		void	ToArray(const CString& strText, Collection::CList<wchar_t>& Array){
			if(strText.IsEmpty()){
				throw CB::Exception::CZeroLengthArgumentException(L"strText", 
					L"Cannot convert empty string to array.", __FUNCTIONW__, __FILEW__, __LINE__);
			}

			try{
				Array.Resize(strText.GetLength());
				Memory::SetZeroArray<wchar_t>(Array);
				Memory::CopyArray<wchar_t>(&strText[0], &Array.First(), strText.GetLength());
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while converting string to array.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
			}
		}

		const Collection::CList<wchar_t>	ToArray(const CString& strText){
			Collection::CList<wchar_t>	Array(strText.GetLength());
			Memory::SetZeroArray(Array);
			ToArray(strText, Array);
			return Array;
		}

		const bool	SubCompare(const CString& strText, const unsigned uPos, const Collection::CLinkList<CString>& strCompare){
			unsigned uEndPos = 0;
			return SubCompare(strText, uPos, strCompare, uEndPos);
		}

		const bool	SubCompare(const CString& strText, const unsigned uPos, const Collection::CLinkList<CString>& strCompare, unsigned& uEndPos){
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
				Collection::CLinkList<CB::CString>::CEnumerator Enum = strCompare.GetEnumerator();

				for(Enum.ToFirst(); !Enum.IsValid(); Enum.Next()){
					if(strText.SubCompare(uPos, Enum.Get())){
						uEndPos = uPos + Enum.Get().GetLength();
						return true;
					}
				}

				return false;
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while comparing sub strings from list.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
			}
		}

		const bool	MultiCompare(const CString& strText, const unsigned uPos, const CString& strCharList){
			return MultiCompare(strText, uPos, ToArray(strCharList));
		}

		const bool	MultiCompare(const CString& strText, const unsigned uPos, const Collection::CList<wchar_t>& CharList){
			const wchar_t& toCompare = strText[uPos];
			for(unsigned uIndex = 0; uIndex < CharList.GetLength(); uIndex++){
				if(toCompare == CharList[uIndex]){
					return true;
				}
			}
			return false;
		}

		const bool	Find(const CString& strText, const Collection::CLinkList<CString>& strFind){
			unsigned uPos = 0;
			return Find(strText, strFind, 0, uPos);
		}

		const bool	Find(const CString& strText, const Collection::CLinkList<CString>& strFind, unsigned& uOutPos){
			return Find(strText, strFind, 0, uOutPos);
		}

		const bool	Find(const CString& strText, const Collection::CLinkList<CString>& strFind, const unsigned uStartPos, unsigned& uOutPos){
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
				Collection::CLinkList<CString>::CEnumerator Enum = strFind.GetEnumerator();

				for(unsigned uPos = uStartPos; uPos < strText.GetLength(); uPos++){
					for(Enum.ToFirst(); !Enum.IsValid(); Enum.Next()){
						if(strText.SubCompare(uPos, Enum.Get())){
							uOutPos = uPos;
							return true;
						}
					}
				}

				return false;
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while searching for strings from list.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
			}
		}

		const bool	FindNot(const CString& strText, const Collection::CLinkList<CString>& strSkip){
			unsigned uPos;
			return FindNot(strText, strSkip, 0, uPos);
		}

		const bool	FindNot(const CString& strText, const Collection::CLinkList<CString>& strSkip, unsigned& uOutPos){
			return FindNot(strText, strSkip, 0, uOutPos);
		}

		const bool	FindNot(const CString& strText, const Collection::CLinkList<CString>& strSkip, const unsigned uStartPos, unsigned& uOutPos){
			if(strText.IsEmpty() || strSkip.IsEmpty()){
				uOutPos = 0;
				return true;
			}

			try{
				for(unsigned uPos = uStartPos; uPos < strText.GetLength(); uPos++){
					if(!SubCompare(strText, uPos, strSkip)){
						uOutPos = uPos;
						return true;
					}
				}

				return false;
			}
			catch(CB::Exception::CException& Exception){
				throw CB::Exception::CException(
					L"Error while skiping strings from list.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
			}
		}

	}
}