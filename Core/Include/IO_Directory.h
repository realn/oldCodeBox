#pragma once

#include "Macros.h"
#include "CBString.h"
#include "CBStringEx.h"
#include "SmartPointers_Hidden.h"

namespace CB{
	namespace IO{
		namespace Directory{
			class COMMON_API CDirectory {
			private:
				CString		m_strDirectory;
				CHiddenPtr	m_pData;

			public:
				CDirectory(const CString& strDirectory);
				CDirectory(const CDirectory& Directory);
				~CDirectory();

				const CString& GetDirectory() const;

				void		ToFirstEntry();
				void		NextEntry();
				const bool	IsEndOfEntries() const;

				const CString	GetCurrentName() const;
				const CString	GetCurrentPath() const;

				const bool	IsCurrentAnFile() const;
				const bool	IsCurrentAnDirectory() const;

				const CDirectory& operator=(const CDirectory& Directory);
			};

			extern COMMON_API const CDirectory	Open(const CString& strPath);
			extern COMMON_API void				Create(const CString& strPath); // does not throw
			extern COMMON_API void				Create(const CString& strPath, const bool bThrowIfExists);
			extern COMMON_API const bool		Exists(const CString& strPath);
			extern COMMON_API const Collection::CStringList GetFileList(const CString& strPath);
		}
	}
}