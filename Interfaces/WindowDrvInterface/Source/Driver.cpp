#include "../Internal/Driver.h"

namespace CB{
	const CString	g_strCreateFuncName = L"CreateManager";

	CDriver::CDriver(const CString& strModule) :
		m_Module(strModule, false)
	{
		try{
			m_Module.Load();

			m_pCreate = m_Module.Get<CreateManagerProc>(g_strCreateFuncName);
		}
		catch(Exception::CException& Exception){
			CR_RETHROW(L"Error while loading driver " + strModule + L".", Exception);
		}
	}

	CRefPtr<Window::IManager>	CDriver::CreateManager(){
		return this->m_pCreate(this);
	}

	namespace Window{
		CRefPtr<IDriver>	LoadDriver(const CString& strDriverName){
			return new CDriver(strDriverName);
		}
	}
}