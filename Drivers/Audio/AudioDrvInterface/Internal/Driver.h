#pragma once

#include "../Include/AudioDriver.h"
#include <Module.h>

namespace CB{
	typedef Audio::IManager*	(*CreateManagerProc)(Audio::IDriver* pDriver);

	class CDriver :
		public Audio::IDriver
	{
	private:
		CModule				m_Module;
		CreateManagerProc	m_pCreate;

	public:
		CDriver(const CString& strDriverName);
		~CDriver();

		CRefPtr<Audio::IManager>	CreateManager() override;
	};
}