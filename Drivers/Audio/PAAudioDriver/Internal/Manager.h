#pragma once

#include <AudioDriver.h>
#include <Collection_List.h>
#include <Manage_Object.h>

#include <portaudio\portaudio.h>

namespace CB{
	extern const uint32	g_uApiId;

	class CPAAdapter;

	class CPAManager : 
		public Audio::IManager,
		public Manage::IObjectManager<CPAManager, CPAAdapter>
	{
	private:
		CRefPtr<Audio::IDriver>	m_pDriver;
		
		Collection::CList<CString>	m_strAdapterList;
		uint32						m_uDefaultIndex;

	public:
		CPAManager(CRefPtr<Audio::IDriver> pDriver);
		~CPAManager();

		const uint32	GetApiId() const override;

		const uint32		GetNumberOfAdapters() const override;
		CRefPtr<Audio::IAdapter>	GetAdapter(const uint32 uIndex) override;
		CRefPtr<Audio::IAdapter>	GetDefaultAdapter() override;
	};
}