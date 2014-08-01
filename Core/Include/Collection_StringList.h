#pragma once

#include "Collection_List.h"

namespace CB{
	class CString;

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
}