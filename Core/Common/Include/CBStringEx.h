#pragma once

#include "CBString.h"
#include "Collection_List.h"

namespace CB{
	namespace Collection{
		class COMMON_API CStringList : 
			public CList<CString>
		{
		public:
			CStringList();
			CStringList(const CStringList& List);
			CStringList(const ICountable<CString>& List);

			const bool		Contains(const CString& strText) const;
			const uint32	IndexOf(const CString& strFind) const;

			const CString	ToString() const;
			const CString	ToString(const CString& strGlue) const;
		};
	}

	namespace String{
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
	}
}