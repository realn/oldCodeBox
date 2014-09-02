#pragma once

#include "Macros.h"
#include "Types.h"
#include "CBString_Consts.h"

namespace CB{
	class CString;

	namespace Collection{
		template<typename _Type> class IPacked;
		template<typename _Type> class ICountable;
		template<typename _Type> class CList;
	}

	namespace String{
		extern COMMON_API const CString ToString(const Encoding uEncoding);

		extern COMMON_API const CString	FromInt32(const int32 iValue);
		extern COMMON_API const CString	FromUInt32(const uint32 uValue);
		extern COMMON_API const CString	FromFloat(const float32 fValue);
		extern COMMON_API const CString	FromBool(const bool bValue);

		extern COMMON_API const CString	ToString(const int32 iValue);
		extern COMMON_API const CString	ToString(const uint32 uValue);
		extern COMMON_API const CString ToString(const float32 fValue);
		extern COMMON_API const CString ToString(const bool bValue);
		
		extern COMMON_API const int32		ToInt32(const CString& strText);
		extern COMMON_API const uint32		ToUInt32(const CString& strText);
		extern COMMON_API const float32		ToFloat(const CString& strText);
		extern COMMON_API const bool		ToBool(const CString& strText);

		extern COMMON_API const bool		ToInt32(const CString& strText, int& iOutValue);
		extern COMMON_API const bool		ToUInt32(const CString& strText, uint32& uOutValue);
		extern COMMON_API const bool		ToFloat(const CString& strText, float& fOutValue);
		extern COMMON_API const bool		ToBool(const CString& strText, bool& bOutValue);
			
		extern COMMON_API const CString		ToHexString(const uint32 uValue);

		extern COMMON_API const CString		FromANSI(const int8* szText); // with zero
		extern COMMON_API const CString		FromANSI(const int8* szText, const uint32 uLength);	// without zero
		extern COMMON_API const CString		FromUTF8(const int8* szText); // with zero
		extern COMMON_API const CString		FromUTF8(const int8* szText, const uint32 uLength);	// wirhout zero

		extern COMMON_API const uint32		ToANSICount(const CString& strText); // returns count without zero
		extern COMMON_API void				ToANSI(const CString& strText, int8* szOutText, const uint32 uBufferLen); // buffer len with zero
		extern COMMON_API const uint32		ToUTF8Count(const CString& strText); // returns count without zero
		extern COMMON_API void				ToUTF8(const CString& strText, int8* szOutText, const uint32 uBufferLen);	// buffer len with zero

		extern COMMON_API const CString	VarReplace(const CString& strText, const Collection::ICountable<CString>& VarList);
		extern COMMON_API const CString	VarReplace(const CString& strText, const Collection::ICountable<CString>& VarList, const bool bIgnoreMissng);

		extern COMMON_API const CString	Format(const CString& strFormat, const CString& strOp1);
		extern COMMON_API const CString	Format(const CString& strFormat, const CString& strOp1, const CString& strOp2);
		extern COMMON_API const CString	Format(const CString& strFormat, const CString& strOp1, const CString& strOp2, const CString& strOp3);
		extern COMMON_API const CString	Format(const CString& strFormat, const CString& strOp1, const CString& strOp2, const CString& strOp3, const CString& strOp4);
		extern COMMON_API const CString	Format(const CString& strFormat, const CString& strOp1, const CString& strOp2, const CString& strOp3, const CString& strOp4, const CString& strOp5);

		extern COMMON_API const CString	FromANSI(const Collection::IPacked<int8>& Array);
		extern COMMON_API const CString	FromUTF8(const Collection::IPacked<int8>& Array);

		extern COMMON_API void	ToANSI(const CString& strText, Collection::CList<int8>& Array);		// convert to buffer without zero
		extern COMMON_API void	ToUTF8(const CString& strText, Collection::CList<int8>& Array);		// convert to buffer without zero
		extern COMMON_API void	ToArray(const CString& strText, Collection::CList<wchar>& Array);	// convert to buffer without zero

		extern COMMON_API const Collection::CList<int8>		ToANSI(const CString& strText);		// return buffer with zero
		extern COMMON_API const Collection::CList<int8>		ToUTF8(const CString& strText);		// return buffer with zero
		extern COMMON_API const Collection::CList<wchar>	ToArray(const CString& strText);	// return buffer with zero

		extern COMMON_API const CString	ToString(const Collection::IPacked<wchar>& Array);

		extern COMMON_API const bool	SubCompare(const CString& strText, const uint32 uPos, const Collection::ICountable<CString>& strCompare);
		extern COMMON_API const bool	SubCompare(const CString& strText, const uint32 uPos, const Collection::ICountable<CString>& strCompare, uint32& uEndPos);

		extern COMMON_API const bool	MultiCompare(const CString& strText, const uint32 uPos, const Collection::ICountable<wchar>& CharList);

		extern COMMON_API const bool	Find(const CString& strText, const Collection::ICountable<CString>& strFind);
		extern COMMON_API const bool	Find(const CString& strText, const Collection::ICountable<CString>& strFind, uint32& uOutPos);
		extern COMMON_API const bool	Find(const CString& strText, const Collection::ICountable<CString>& strFind, const uint32 uStartPos, uint32& uOutPos);

		extern COMMON_API const bool	FindNot(const CString& strText, const Collection::ICountable<CString>& strSkip);
		extern COMMON_API const bool	FindNot(const CString& strText, const Collection::ICountable<CString>& strSkip, uint32& uOutPos);
		extern COMMON_API const bool	FindNot(const CString& strText, const Collection::ICountable<CString>& strSkip, const uint32 uStartPos, uint32& uOutPos);

		extern COMMON_API const Collection::CList<CString>	Split( const CString& strText );
		extern COMMON_API const Collection::CList<CString>	Split( const CString& strText, const CString& strSeparator );
		extern COMMON_API const Collection::CList<CString>	Split( const CString& strText, const CString& strSeparator, const bool bIgnoreEmpty );

		extern COMMON_API const CString	Join( const Collection::ICountable<CString>& list );
		extern COMMON_API const CString Join( const Collection::ICountable<CString>& list, const CString& strGlue );

		extern COMMON_API const bool	IsWhiteSpace( const wchar chElem );
		extern COMMON_API const bool	IsWhiteSpace( const CString& strText );

		extern COMMON_API const bool	SkipWhiteSpace( const CString& strText, const uint32 uStartPos, uint32& uOutPos );
		extern COMMON_API const bool	FindWhiteSpace( const CString& strText, const uint32 uStartPos, uint32& uOutPot );

		extern COMMON_API const Collection::CList<CString>	GetWhiteSpace();
		extern COMMON_API void	GetWhiteSpace( Collection::CList<CString>& list );
	}
}