#pragma once

#include "../Include/OGLGraphicDriver.h"
#include "DisplayDeviceInfo.h"
#include <Collection_Dictionary.h>
#include <Manage_Object.h>
#include <Logger.h>
#include <Math_Rectangle.h>

namespace CB{
	class COGLAdapter;

	class COGLManager :
		public Graphic::IManager,
		public Manage::IObjectManager<COGLAdapter>
	{
	private:
		CRefPtr<Window::IManager>	m_pWindowManager;
		CRefPtr<Graphic::IDriver>	m_pDriver;

		Collection::CDictionary<CString, CDisplayDeviceInfo>	m_AdapterList;
		Collection::CDictionary<CString, Math::CRectangle>		m_Monitors;

	public:
		COGLManager(CRefPtr<Graphic::IDriver> pDriver, CRefPtr<Window::IManager> pWindowManager);
		~COGLManager();

		const uint32	GetApiId() const override;

		const uint32				GetNumberOfAdapters() const override;
		CRefPtr<Graphic::IAdapter>	GetAdapter(const uint32 uIndex) override;
		CRefPtr<Graphic::IAdapter>	GetDefaultAdapter() override;

		CRefPtr<Window::IManager>	GetWindowManager() const;
	};

	extern const uint32	g_uApiID;
}