#include "../Include/Module.h"

namespace CB{
	CModuleManager::CModuleManager(){
	}

	CModuleManager::CModuleManager(const CModuleManager& Manager){
	}

	CModuleManager::~CModuleManager(){
	}

	void	CModuleManager::LoadModule(const CString& strModuleName){
		try{
			if(this->m_ModuleDictionary.Contains(strModuleName)){
				return;
			}
			CModule module(strModuleName);
			module.Load();
			this->m_ModuleDictionary.Add(strModuleName, module);
		}
		catch(Exception::CModuleNotFoundException& Exception){
			throw Exception::CModuleNotFoundException(strModuleName, __FUNCTIONW__, __FILEW__, __LINE__, Exception);
		}
		catch(Exception::CModuleLoadException& Exception){
			throw Exception::CModuleLoadException(strModuleName, L"Internal loading error.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
		}
		catch(Exception::CException& Exception){
			throw Exception::CModuleException(strModuleName, L"Unknown internal error.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
		}
	}

	void	CModuleManager::UnloadModule(const CString& strModuleName){
		try{
			this->m_ModuleDictionary.DeleteByKey(strModuleName);
		}
		catch(Exception::CException& Exception){
			throw Exception::CModuleException(strModuleName, L"Failed to unload module.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
		}
	}

	void*	CModuleManager::GetFunction(const CString& strModuleName, const CString& strFunctionName){
		try{
			this->LoadModule(strModuleName);
			return this->m_ModuleDictionary[strModuleName].GetFunction(strFunctionName);
		}
		catch(Exception::CModuleFunctionNotFoundException& Exception){
			throw Exception::CModuleFunctionNotFoundException(strModuleName, strFunctionName, __FUNCTIONW__, __FILEW__, __LINE__, Exception);
		}
		catch(Exception::CModuleFunctionLoadException& Exception){
			throw Exception::CModuleFunctionLoadException(strModuleName, strFunctionName, L"Unknown loading error.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
		}
		catch(Exception::CModuleNotFoundException& Exception){
			throw Exception::CModuleNotFoundException(strModuleName, __FUNCTIONW__, __FILEW__, __LINE__, Exception);
		}
		catch(Exception::CModuleLoadException& Exception){
			throw Exception::CModuleLoadException(strModuleName, L"Failed loading module for function loading.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
		}
		catch(Exception::CException& Exception){
			throw Exception::CModuleException(strModuleName, L"Error while loading function " + strFunctionName + L".", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
		}
	}
}