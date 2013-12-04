#pragma once

#include <AudioDriver.h>
#include <Collection_List.h>
#include <Manage_Object.h>

namespace CB{
	extern const uint32	g_uApiId;

	class COALAdapter;

	class COALManager : 
		public Audio::IManager,
		public Manage::IObjectManager<COALManager, COALAdapter>
	{
	private:
		CRefPtr<Audio::IDriver>	m_pDriver;
		
		Collection::CList<CString>	m_strAdapterList;

	public:
		COALManager(CRefPtr<Audio::IDriver> pDriver);
		~COALManager();

		const uint32	GetApiId() const override;

		const uint32		GetNumberOfAdapters() const override;
		CRefPtr<Audio::IAdapter>	GetAdapter(const uint32 uIndex) override;
		CRefPtr<Audio::IAdapter>	GetDefaultAdapter() override;
	};
}