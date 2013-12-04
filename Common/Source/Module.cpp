#include "../Include/Module.h"
#include "../Internal/WinPlatform.h"
#include "../Include/WindowsErrors.h"
#include "../../Common/Include/CBStringEx.h"

namespace CB{
	CModule::CModule(const CString& strName) : 
		m_strName(strName)
	{
		this->Load();
	}

	CModule::CModule(const CString& strName, const bool bLoad) :
		m_strName(strName)
	{
		if(bLoad){
			this->Load();
		}
	}

	CModule::CModule(const CModule& Module) : 
		m_strName(Module.m_strName), 
		m_pHandle(Module.m_pHandle)
	{
		if(this->m_pHandle.IsValid()){
			// raising module reference count for proper handling
			this->m_pHandle.SetCast<HMODULE>(LoadLibraryW(this->m_strName.GetPointer()));
		}
	}

	CModule::~CModule(){
		try{
			this->Unload();
		}
		catch(Exception::CException&){}
	}

	void	CModule::Load(){
		if(this->m_pHandle.IsValid())
			return;

		this->m_pHandle.SetCast<HMODULE>(LoadLibraryW(this->m_strName.GetPointer()));
		if(this->m_pHandle.IsNull()){
			DWORD dwError = GetLastError();
			if(dwError == ERROR_MOD_NOT_FOUND){
				throw Exception::CModuleNotFoundException(this->m_strName, CR_INFO());
			}
			else{
				throw Exception::CModuleLoadException(this->m_strName,
					CWindowsError(GetLastError()).GetMessage(), CR_INFO());
			}
		}
	}

	void	CModule::Unload(){
		if(this->m_pHandle.IsValid()){
			if(!FreeLibrary(this->m_pHandle.GetCast<HMODULE>())){
				throw Exception::CModuleException(this->m_strName,
					L"Failed to unload module: " + CWindowsError(GetLastError()).GetMessage(), CR_INFO());
			}
		}
	}

	void*	CModule::GetFunction(const CString& strFunctionName){
		if(this->m_pHandle.IsNull()){
			throw Exception::CModuleException(this->m_strName,
				L"Module not loaded.", CR_INFO());
		}

		if(strFunctionName.IsEmpty()){
			throw Exception::CModuleException(this->m_strName,
				L"Cannot load function with empty name string.", CR_INFO());
		}

		Collection::CList<int8> szFuncName = String::ToANSI(strFunctionName);
		HMODULE hModule = this->m_pHandle.GetCast<HMODULE>();
		const char* szProcName = reinterpret_cast<const char*>(szFuncName.GetPointer());

		FARPROC pFunc = GetProcAddress(hModule, szProcName);
		if(pFunc == 0){
			DWORD dwError = GetLastError();

			if(dwError == ERROR_PROC_NOT_FOUND){
				throw Exception::CModuleFunctionNotFoundException(this->m_strName, strFunctionName, CR_INFO());
			}
			else{
				throw Exception::CModuleFunctionLoadException(this->m_strName, strFunctionName,
					CWindowsError(dwError).GetMessage(), CR_INFO());
			}
		}

		return (void*)pFunc;
	}

	const bool	CModule::operator==(const CModule& Module) const{
		return this->m_pHandle.GetCast<HANDLE>() == Module.m_pHandle.GetCast<HANDLE>();
	}

	const bool	CModule::operator!=(const CModule& Module) const{
		return this->m_pHandle.GetCast<HANDLE>() != Module.m_pHandle.GetCast<HANDLE>();
	}

	CModuleRef::CModuleRef(const CModuleRef& Module) :
		CModule(Module)
	{}

	CModuleRef::CModuleRef(const CString& strModule) :
		CModule(strModule)
	{}

	CModuleRef::CModuleRef(const CString& strModule, const bool bLoad) :
		CModule(strModule, bLoad)
	{}
}