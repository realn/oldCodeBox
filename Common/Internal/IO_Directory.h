#pragma once

#include "../Include/IO_Directory.h"
#include "WinPlatform.h"

namespace CB{
	class CDirectory : public IO::Directory::IDirectory{
	protected:
		CString				m_strPath;
		HANDLE				m_hFindHandle;
		WIN32_FIND_DATAW	m_FindData;
		bool				m_bEndOfEntries;

	public:
		CDirectory(const CString& strPath);
		~CDirectory();

		const CString& GetDirectory() const override;

		void		ToFirstEntry() override;
		void		Close();

		void		NextEntry() override;
		const bool	IsEndOfEntries() const override;

		const CString	GetCurrentName() const override;
		const CString	GetCurrentPath() const override;

		const bool	IsCurrentAnFile() const override;
		const bool	IsCurrentAnDirectory() const override;
	};
}