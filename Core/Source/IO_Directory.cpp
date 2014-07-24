#include "stdafx.h"
#include "../Include/IO_Directory.h"
#include "../Include/CBStringEx.h"
#include "../Internal/IO_DirectoryWIN.h"
#include "../Include/IO_Directory_Exceptions.h"
#include "../Include/WindowsErrors.h"

namespace CB{
	namespace IO{
		namespace Directory{
			CDirectory::CDirectory(const CString& strDirectory) : 
				m_strDirectory(strDirectory)
			{
				this->m_pData.Set(new CDirectoryWIN(strDirectory));
			}

			CDirectory::CDirectory(const CDirectory& Directory) : 
				m_strDirectory(Directory.m_strDirectory)
			{
				this->m_pData.Set(new CDirectoryWIN(Directory.m_strDirectory));
			}

			CDirectory::~CDirectory(){
				this->m_pData.Delete<CDirectoryWIN>();
			}

			const CString& CDirectory::GetDirectory() const{
				return this->m_strDirectory;
			}

			void		CDirectory::ToFirstEntry(){
				this->m_pData.Get<CDirectoryWIN>()->ToFirstEntry();
			}

			void		CDirectory::NextEntry(){
				this->m_pData.Get<CDirectoryWIN>()->NextEntry();
			}

			const bool	CDirectory::IsEndOfEntries() const{
				return this->m_pData.Get<CDirectoryWIN>()->IsEndOfEntries();
			}

			const CString	CDirectory::GetCurrentName() const{
				return this->m_pData.Get<CDirectoryWIN>()->GetCurrentName();
			}

			const CString	CDirectory::GetCurrentPath() const{
				return this->m_pData.Get<CDirectoryWIN>()->GetCurrentPath();
			}

			const bool	CDirectory::IsCurrentAnFile() const{
				return this->m_pData.Get<CDirectoryWIN>()->IsCurrentAnFile();
			}

			const bool	CDirectory::IsCurrentAnDirectory() const{
				return this->m_pData.Get<CDirectoryWIN>()->IsCurrentAnDirectory();
			}

			const CDirectory& CDirectory::operator=(const CDirectory& Directory){
				CDirectoryWIN* pDir = new CDirectoryWIN(Directory.m_strDirectory);

				this->m_pData.Delete<CDirectoryWIN>();
				this->m_pData.Set(pDir);

				return *this;
			}

			//	Implementation of creation functions

			const CDirectory	Open(const CString& strPath){
				return CDirectory(strPath);
			}

			//	Other functions

			void	Create(const CString& strPath){
				Create(strPath, false);
			}

			void	Create(const CString& strPath, const bool bThrowIfExists){
				if(Exists(strPath)){
					if(bThrowIfExists){
						throw Exception::CDirectoryException(strPath,
							L"Directory already exists.", CR_INFO());
					}
					else return;
				}

				if(!CreateDirectoryW(strPath.GetPointer(), 0)){
					throw Exception::CDirectoryException(strPath,
						L"Failed to create directory. " + CWindowsError(GetLastError()).GetMessage(), CR_INFO());
				}
			}

			const bool	Exists(const CString& strPath){
				DWORD dwAttrib = GetFileAttributesW(strPath.GetPointer());

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
					CDirectory  Dir(strPath);

					for(Dir.ToFirstEntry(); !Dir.IsEndOfEntries(); Dir.NextEntry()){
						if(Dir.IsCurrentAnFile()){
							List.Add(Dir.GetCurrentName());
						}
					}

					return List;
				}
				catch(Exception::CException& Exception){
					throw Exception::CDirectoryException(strPath, 
						L"Error while scanning directory for file entries.", CR_INFO(), Exception);
				}
			}
		}
	}
}