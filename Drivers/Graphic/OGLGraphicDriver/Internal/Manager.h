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
		CRefPtr<Graphic::IDriver>	m_pDriver;

		Collection::CDictionary<CString, CDisplayDeviceInfo>	m_AdapterList;
		Collection::CDictionary<CString, Math::CRectangle>		m_Monitors;

	public:
		COGLManager(CRefPtr<Graphic::IDriver> pDriver);
		~COGLManager();

		const uint32	GetApiId() const override;

		const uint32				GetNumberOfAdapters() const override;
		CRefPtr<Graphic::IAdapter>	GetAdapter(const uint32 uIndex) override;
		CRefPtr<Graphic::IAdapter>	GetDefaultAdapter() override;

		void	AddMonitor(const CString& strDisplay, const Math::CRectangle& Rect, const bool bPrimary);
	};

	extern const uint32	g_uApiID;
}