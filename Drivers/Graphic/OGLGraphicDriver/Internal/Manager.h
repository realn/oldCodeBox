#pragma once

#include "../Include/OGLGraphicDriver.h"
#include <Collection_Dictionary.h>
#include <Manage_Object.h>
#include <Logger.h>

#include "WinPlatform.h"

namespace CB{
	class COGLAdapter;

	class COGLManager :
		public Graphic::IManager,
		public Manage::IObjectManager<COGLAdapter>
	{
	private:
		CRefPtr<Graphic::IDriver>	m_pDriver;

		Collection::CDictionary<CString, DISPLAY_DEVICEW>	m_AdapterList;

	public:
		COGLManager(CRefPtr<Graphic::IDriver> pDriver);
		~COGLManager();

		const uint32	GetApiId() const override;

		const uint32				GetNumberOfAdapters() const override;
		CRefPtr<Graphic::IAdapter>	GetAdapter(const uint32 uIndex) override;
		CRefPtr<Graphic::IAdapter>	GetDefaultAdapter() override;
	};

	extern const uint32	g_uApiID;
}