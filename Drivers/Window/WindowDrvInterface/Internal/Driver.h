#pragma once

#include "../Include/WindowDriver.h"
#include <Module.h>

namespace CB{
	typedef Window::IManager*	(*CreateManagerProc)(Window::IDriver* pModule);

	class CDriver : 
		public Window::IDriver
	{
	private:
		CModule	m_Module;
		CreateManagerProc	m_pCreate;

	public:
		CDriver(const CString& strModule);

		CRefPtr<Window::IManager>	CreateManager() override;
	};
}
