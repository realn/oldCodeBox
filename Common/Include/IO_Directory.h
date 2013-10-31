#pragma once

#include "Macros.h"
#include "../../Common/Include/CBString.h"
#include "../../Common/Include/CBStringEx.h"
#include "../../Common/Include/Ref.h"
#include "../../Common/Include/SmartPointers.h"

namespace CB{
	namespace IO{
		namespace Directory{
			class IDirectory : public IRef{
			public:
				virtual const CString& GetDirectory() const = 0;

				virtual void		ToFirstEntry() = 0;
				virtual void		NextEntry() = 0;
				virtual const bool	IsEndOfEntries() const = 0;

				virtual const CString	GetCurrentName() const = 0;
				virtual const CString	GetCurrentPath() const = 0;

				virtual const bool	IsCurrentAnFile() const = 0;
				virtual const bool	IsCurrentAnDirectory() const = 0;
			};

			extern COMMON_API CRefPtr<IDirectory>	Open(const CString& strPath);
			extern COMMON_API void	Create(const CString& strPath);
			extern COMMON_API void	Create(const CString& strPath, const bool bThrowIfExists);
			extern COMMON_API const bool	Exists(const CString& strPath);
			extern COMMON_API const Collection::CStringList GetFileList(const CString& strPath);
		}
	}

	namespace Exception{
		class COMMON_API CDirectoryException : public CException{
		protected:
			CString	m_strPath;

		public:
			CDirectoryException(const CDirectoryException& Exception);
			CDirectoryException(const CString& strPath, const CString& strMessage, const CString& strFunction, const CString& strFile, const unsigned uLine);
			CDirectoryException(const CString& strPath, const CString& strMessage, const CString& strFunction, const CString& strFile, const unsigned uLine, const CException& InnerException);

			virtual const CString	GetMessage() const;

			virtual CException*	CreateCopy() const;
		};
	}
}