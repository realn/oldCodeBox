#include "stdafx.h"
#include "../Include/IO_File.h"
#include "../Internal/IO_FileStreamWIN.h"
#include "../Internal/WinPlatform.h"

namespace CB{
	namespace IO{
		namespace File{
			//	Implementation of file stream creation functions

			CRefPtr<IFileStream>	Open(const CString& strFilename){
				return Open(strFilename, AccessType::ReadOnly, OpenAction::Open, ShareType::ReadOnly);
			}

			CRefPtr<IFileStream>	Open(const CString& strFilename, const AccessType uType){
				return Open(strFilename, uType, OpenAction::AlwaysOpen, ShareType::ReadOnly);
			}

			CRefPtr<IFileStream>	Open(const CString& strFilename, const AccessType uType, const OpenAction uAction){
				return Open(strFilename, uType, uAction, ShareType::ReadOnly);
			}

			CRefPtr<IFileStream>	Open(const CString& strFilename, const AccessType uType, const OpenAction uAction, const ShareType uShare){
				return new CFileStreamWIN(strFilename, uType, uAction, uShare);
			}

			const bool	Exists(const CString& strFilename){
				DWORD dwAttr = GetFileAttributesW(strFilename.GetPointer());
				if(dwAttr != INVALID_FILE_ATTRIBUTES && !(dwAttr & FILE_ATTRIBUTE_DIRECTORY)){
					return true;
				}
				return false;
			}

			const bool	Delete(const CString& strFilename){
				if(::DeleteFileW(strFilename.GetPointer())){
					return true;
				}
				return false;
			}
		}
	}

	namespace String{
		const CString	ToString(const IO::File::AccessType uType){
			switch (uType)
			{
			case IO::File::AccessType::ReadOnly:		return L"ReadOnly";
			case IO::File::AccessType::WriteOnly:		return L"WriteOnly";
			case IO::File::AccessType::ReadAndWrite:	return L"ReadAndWrite";
			default:
				return L"Unknown Value: " + ToString((unsigned)uType);
			}
		}

		const CString	ToString(const IO::File::OpenAction uAction){
			switch (uAction)
			{
			case IO::File::OpenAction::Open:		return L"Open";
			case IO::File::OpenAction::Create:		return L"Create";
			case IO::File::OpenAction::AlwaysOpen:	return L"AlwaysOpen";
			case IO::File::OpenAction::AlwaysCreate:	return L"AlwaysCreate";
			default:
				return L"Unknown Value: " + ToString((unsigned)uAction);
			}
		}

		const CString	ToString(const IO::File::ShareType uShare){
			switch (uShare)
			{
			case IO::File::ShareType::None:		return L"None";
			case IO::File::ShareType::WriteOnly:	return L"WriteOnly";
			case IO::File::ShareType::ReadOnly:		return L"ReadOnly";
			case IO::File::ShareType::ReadAndWrite:	return L"ReadAndWrite";
			default:
				return L"Unknown Value: " + ToString((unsigned)uShare);
			}
		}
	}
}