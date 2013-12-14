#include "../Internal/IO_DirectoryWIN.h"
#include "../Include/WindowsErrors.h"
#include "../../Common/Include/IO_Path.h"

namespace CB{
	CDirectoryWIN::CDirectoryWIN(const CString& strPath) : 
		m_strPath(strPath), 
		m_hFindHandle(0), 
		m_bEndOfEntries(true)
	{
		Memory::SetZero(this->m_FindData);
	}

	CDirectoryWIN::~CDirectoryWIN(){
		try{
			this->Close();
		}
		catch(Exception::CException&){}
	}

	void	CDirectoryWIN::ToFirstEntry(){
		this->Close();

		this->m_hFindHandle = FindFirstFileW(this->m_strPath.GetPointer(), &this->m_FindData);
		if(this->m_hFindHandle == INVALID_HANDLE_VALUE || this->m_hFindHandle == 0){
			DWORD dwError = GetLastError();
			throw Exception::CDirectoryException(this->m_strPath, 
				CWindowsError(dwError).GetMessage(), CR_INFO());
		}
		this->m_bEndOfEntries = false;
	}

	void	CDirectoryWIN::Close(){
		if(this->m_hFindHandle){
			if(!FindClose(this->m_hFindHandle)){
				DWORD dwError = GetLastError();
				throw Exception::CDirectoryException(this->m_strPath,
					CWindowsError(dwError).GetMessage(), CR_INFO());
			}
			this->m_hFindHandle	= 0;
			this->m_bEndOfEntries = true;
		}
	}

	void	CDirectoryWIN::NextEntry(){
		if(this->m_bEndOfEntries){
			return;
		}

		if(!this->m_hFindHandle){
			throw Exception::CDirectoryException(this->m_strPath,
				L"Search already closed.", CR_INFO());
		}

		if(!FindNextFileW(this->m_hFindHandle, &this->m_FindData)){
			DWORD dwError = GetLastError();
			if(dwError == ERROR_NO_MORE_FILES){
				this->m_bEndOfEntries = true;
			}
			else{
				throw Exception::CDirectoryException(this->m_strPath,
					CWindowsError(dwError).GetMessage(), CR_INFO());
			}
		}
	}

	const bool	CDirectoryWIN::IsEndOfEntries() const{
		return this->m_bEndOfEntries;
	}

	const CString	CDirectoryWIN::GetCurrentName() const{
		if(!this->m_hFindHandle || this->m_bEndOfEntries){
			return L"";
		}
		return this->m_FindData.cFileName;
	}

	const CString	CDirectoryWIN::GetCurrentPath() const{
		if(!this->m_hFindHandle || this->m_bEndOfEntries){
			return L"";
		}

		return IO::Path::Combine(this->m_strPath, this->m_FindData.cFileName);
	}

	const bool	CDirectoryWIN::IsCurrentAnFile() const{
		if(!this->m_hFindHandle || this->m_bEndOfEntries){
			return false;
		}
		return (this->m_FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) > 0 ? false : true;
	}

	const bool	CDirectoryWIN::IsCurrentAnDirectory() const{
		if(!this->m_hFindHandle || this->m_bEndOfEntries){
			return false;
		}
		return (this->m_FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) > 0 ? true : false;
	}
}