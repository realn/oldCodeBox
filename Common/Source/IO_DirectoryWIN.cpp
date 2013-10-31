#include "../Internal/IO_Directory.h"
#include "../Include/WindowsErrors.h"
#include "../../Common/Include/IO_Path.h"

namespace CB{
	CDirectory::CDirectory(const CString& strPath) : m_strPath(strPath), m_hFindHandle(0), m_bEndOfEntries(true){
		Memory::SetZero(this->m_FindData);
	}

	CDirectory::~CDirectory(){
		this->Close();
	}

	const CString&	CDirectory::GetDirectory() const{
		return this->m_strPath;
	}

	void	CDirectory::ToFirstEntry(){
		this->Close();

		this->m_hFindHandle = FindFirstFileW(this->m_strPath.ToConst(), &this->m_FindData);
		if(this->m_hFindHandle == INVALID_HANDLE_VALUE || this->m_hFindHandle == 0){
			DWORD dwError = GetLastError();
			throw Exception::CDirectoryException(this->m_strPath, 
				CWindowsError(dwError).GetMessage(), __FUNCTIONW__, __FILEW__, __LINE__);
		}
		this->m_bEndOfEntries = false;
	}

	void	CDirectory::Close(){
		if(this->m_hFindHandle){
			if(!FindClose(this->m_hFindHandle)){
				DWORD dwError = GetLastError();
				throw Exception::CDirectoryException(this->m_strPath,
					CWindowsError(dwError).GetMessage(), __FUNCTIONW__, __FILEW__, __LINE__);
			}
			this->m_hFindHandle	= 0;
			this->m_bEndOfEntries = true;
		}
	}

	void	CDirectory::NextEntry(){
		if(this->m_bEndOfEntries){
			return;
		}

		if(!this->m_hFindHandle){
			throw Exception::CDirectoryException(this->m_strPath,
				L"Search already closed.", __FUNCTIONW__, __FILEW__, __LINE__);
		}

		if(!FindNextFileW(this->m_hFindHandle, &this->m_FindData)){
			DWORD dwError = GetLastError();
			if(dwError == ERROR_NO_MORE_FILES){
				this->m_bEndOfEntries = true;
			}
			else{
				throw Exception::CDirectoryException(this->m_strPath,
					CWindowsError(dwError).GetMessage(), __FUNCTIONW__, __FILEW__, __LINE__);
			}
		}
	}

	const bool	CDirectory::IsEndOfEntries() const{
		return this->m_bEndOfEntries;
	}

	const CString	CDirectory::GetCurrentName() const{
		if(!this->m_hFindHandle || this->m_bEndOfEntries){
			return L"";
		}
		return this->m_FindData.cFileName;
	}

	const CString	CDirectory::GetCurrentPath() const{
		if(!this->m_hFindHandle || this->m_bEndOfEntries){
			return L"";
		}

		return IO::Path::Combine(this->m_strPath, this->m_FindData.cFileName);
	}

	const bool	CDirectory::IsCurrentAnFile() const{
		if(!this->m_hFindHandle || this->m_bEndOfEntries){
			return false;
		}
		return (this->m_FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) > 0 ? false : true;
	}

	const bool	CDirectory::IsCurrentAnDirectory() const{
		if(!this->m_hFindHandle || this->m_bEndOfEntries){
			return false;
		}
		return (this->m_FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) > 0 ? true : false;
	}

	namespace IO{
		namespace Directory{
			//	Implementation of creation functions

			CRefPtr<IDirectory>	Open(const CString& strPath){
				return new CDirectory(strPath);
			}

			//	Other functions

			void	Create(const CString& strPath){
				Create(strPath, false);
			}

			void	Create(const CString& strPath, const bool bThrowIfExists){
				if(Exists(strPath)){
					if(bThrowIfExists){
						throw Exception::CDirectoryException(strPath,
							L"Directory already exists.", __FUNCTIONW__, __FILEW__, __LINE__);
					}
					else return;
				}

				if(!CreateDirectoryW(strPath.ToConst(), 0)){
					throw Exception::CDirectoryException(strPath,
						L"Failed to create directory. " + CWindowsError(GetLastError()).GetMessage(), __FUNCTIONW__, __FILEW__, __LINE__);
				}
			}

			const bool	Exists(const CString& strPath){
				DWORD dwAttrib = GetFileAttributesW(strPath.ToConst());

				if(dwAttrib == INVALID_FILE_ATTRIBUTES){
					return false;
				}

				if(dwAttrib & FILE_ATTRIBUTE_DIRECTORY){
					return true;
				}
				return false;
			}

			const Collection::CStringList	GetFileList(const CString& strPath){
				try{
					Collection::CStringList List;
					CRefPtr<IDirectory> pDir = Open(strPath);

					for(pDir->ToFirstEntry(); !pDir->IsEndOfEntries(); pDir->NextEntry()){
						if(pDir->IsCurrentAnFile()){
							List.Add(pDir->GetCurrentName());
						}
					}

					return List;
				}
				catch(Exception::CException& Exception){
					throw Exception::CDirectoryException(strPath, 
						L"Error while scanning directory for file entries.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
				}
			}
		}
	}
}