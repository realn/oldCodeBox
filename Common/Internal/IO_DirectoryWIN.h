#pragma once

#include "../Include/IO_Directory.h"
#include "WinPlatform.h"

namespace CB{
	class CDirectoryWIN{
	protected:
		const CString		m_strPath;
		HANDLE				m_hFindHandle;
		WIN32_FIND_DATAW	m_FindData;
		bool				m_bEndOfEntries;

	public:
		CDirectoryWIN(const CString& strPath);
		~CDirectoryWIN();

		void		ToFirstEntry();
		void		Close();

		void		NextEntry();
		const bool	IsEndOfEntries() const;

		const CString	GetCurrentName() const;
		const CString	GetCurrentPath() const;

		const bool	IsCurrentAnFile() const;
		const bool	IsCurrentAnDirectory() const;
	};
}