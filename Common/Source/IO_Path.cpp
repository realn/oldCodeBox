#include "../Include/IO_Path.h"

namespace CB{
	namespace IO{
		namespace Path{
			const CString	RepairDirectorySlashes(const CString& strPath){
				CString strNewPath = strPath.Replace(L"\\", L"/");
				return strNewPath.Replace(L"//", L"/");
			}

			const CString	Combine(const CString& strPath1, const CString& strPath2){
				CString strNewPath1 = RepairDirectorySlashes(strPath1);
				CString	strNewPath2 = RepairDirectorySlashes(strPath2);

				if(strNewPath1.IsEmpty()){
					return strNewPath2;
				}
				if(strNewPath2.IsEmpty()){
					return strNewPath1;
				}

				if(strNewPath1[strNewPath1.GetLength()-1] == L'/'){
					if(strNewPath1.GetLength() == 1){
						strNewPath1.Clear();
					}
					else{
						strNewPath1 = strNewPath1.SubString(0, strNewPath1.GetLength()-1);
					}
				}
				if(strNewPath2[0] == L'/'){
					if(strNewPath2.GetLength() == 1){
						strNewPath2.Clear();
					}
					else{
						strNewPath2 = strNewPath2.SubString(1, strNewPath2.GetLength()-1);
					}
				}
				return strNewPath1 + L"/" + strNewPath2;
			}

			const CString	GetDirectory(const CString& strPath){
				if(strPath.IsEmpty()){
					return L"";
				}
				CString strNewPath = RepairDirectorySlashes(strPath);

				if(strNewPath[strNewPath.GetLength()-1] == L'/'){
					if(strNewPath.GetLength() == 1){
						return L"/";
					}
					else{
						return strNewPath;
					}
				}

				unsigned uPos = 0;
				if(!strNewPath.FindLast(L"/", uPos)){
					return L"";
				}

				if(uPos == 0){
					return L"/";
				}

				return strNewPath.SubString(0, uPos) + L"/";
			}

			const CString	GetFilename(const CString& strPath){
				if(strPath.IsEmpty()){
					return L"";
				}
				CString strNewPath = RepairDirectorySlashes(strPath);

				unsigned uPos = 0;
				if(!strNewPath.FindLast(L"/", uPos)){
					return strNewPath;
				}

				if(uPos == 0 && strNewPath.GetLength() == 1){
					return L"";
				}

				if(uPos + 1 == strNewPath.GetLength()){
					return L"";
				}

				return strNewPath.SubString(uPos + 1);
			}

			const CString	GetFilenameBase(const CString& strPath){
				CString strFilename = GetFilename(strPath);

				unsigned uDotPos = 0;
				if(!strFilename.FindLast(L".", uDotPos)){
					return strFilename;
				}

				if(uDotPos == 0){
					return L"";
				}

				return strFilename.SubString(0, uDotPos);
			}

			const CString	GetFilenameExt(const CString& strPath){
				CString strFilename = GetFilename(strPath);

				unsigned uDotPos = 0;
				if(!strFilename.FindLast(L".", uDotPos)){
					return L"";
				}

				if(uDotPos + 1 == strFilename.GetLength()){
					return L"";
				}

				return strFilename.SubString(uDotPos + 1);
			}

			const CString	GetDirectoryBase(const CString& strPath){
				CString strDirectory = GetDirectory(strPath);
				if(strDirectory.IsEmpty() || strDirectory == L"/"){
					return L"";
				}

				unsigned uPos = 0;
				if(!strDirectory.FindLast(L"/", strDirectory.GetLength() - 2, uPos)){
					return strDirectory.SubString(0, strDirectory.GetLength() - 1);
				}

				return strDirectory.SubStringIndexed(uPos + 1, strDirectory.GetLength() - 1);
			}

			const CString	CombineFilename(const CString& strName, const CString& strExt){
				if(strName.IsEmpty() || strExt.IsEmpty()){
					return L"";
				}
				CString strFilename = strName;
				if(strFilename[strFilename.GetLength() - 1] == L'.'){
					if(strFilename.GetLength() == 1){
						strFilename = L"";
					}
					else{
						strFilename = strFilename.SubString(0, strFilename.GetLength() - 1);
					}
				}

				if(strExt[0] == L'.'){
					return strFilename + strExt;
				}
				else{
					return strFilename + L'.' + strExt;
				}
			}
		}
	}
}