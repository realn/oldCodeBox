#pragma once

#include "CBString.h"
#include "Collection.h"

namespace CB{
	namespace Collection{
		class COMMON_API CStringList : public CLinkList<CString>{
		public:
			CStringList();
			CStringList(const CStringList& List);
			CStringList(const CLinkList<CString>& List);

			const bool		Contains(const CString& strText) const;
			const unsigned	IndexOf(const CString& strFind) const;

			const CString	ToString() const;
			const CString	ToString(const CString& strGlue) const;
		};
	}

	namespace String{
		extern COMMON_API const CString	VarReplace(const CString& strText, const Collection::CLinkList<CString>& VarList);
		extern COMMON_API const CString	VarReplace(const CString& strText, const Collection::CLinkList<CString>& VarList, const bool bIgnoreMissng);

		extern COMMON_API const CString	FromANSI(const Collection::CList<char>& Array);
		extern COMMON_API const CString	FromUTF8(const Collection::CList<char>& Array);

		extern COMMON_API void	ToANSI(const CString& strText, Collection::CList<char>& Array);
		extern COMMON_API void	ToUTF8(const CString& strText, Collection::CList<char>& Array);
		extern COMMON_API void	ToArray(const CString& strText, Collection::CList<wchar_t>& Array);

		extern COMMON_API const Collection::CList<char>		ToANSI(const CString& strText);
		extern COMMON_API const Collection::CList<char>		ToUTF8(const CString& strText);
		extern COMMON_API const Collection::CList<wchar_t>		ToArray(const CString& strText);

		//! Converts to array wihout char 0 ending.
		extern COMMON_API const CString	ToString(const Collection::CList<wchar_t>& Array);

		extern COMMON_API const bool	SubCompare(const CString& strText, const unsigned uPos, const Collection::CLinkList<CString>& strCompare);
		extern COMMON_API const bool	SubCompare(const CString& strText, const unsigned uPos, const Collection::CLinkList<CString>& strCompare, unsigned& uEndPos);

		extern COMMON_API const bool	MultiCompare(const CString& strText, const unsigned uPos, const Collection::CList<wchar_t>& CharList);
		extern COMMON_API const bool	MultiCompare(const CString& strText, const unsigned uPos, const CString& strCharList);

		extern COMMON_API const bool	Find(const CString& strText, const Collection::CLinkList<CString>& strFind);
		extern COMMON_API const bool	Find(const CString& strText, const Collection::CLinkList<CString>& strFind, unsigned& uOutPos);
		extern COMMON_API const bool	Find(const CString& strText, const Collection::CLinkList<CString>& strFind, const unsigned uStartPos, unsigned& uOutPos);

		extern COMMON_API const bool	FindNot(const CString& strText, const Collection::CLinkList<CString>& strSkip);
		extern COMMON_API const bool	FindNot(const CString& strText, const Collection::CLinkList<CString>& strSkip, unsigned& uOutPos);
		extern COMMON_API const bool	FindNot(const CString& strText, const Collection::CLinkList<CString>& strSkip, const unsigned uStartPos, unsigned& uOutPos);
	}
}