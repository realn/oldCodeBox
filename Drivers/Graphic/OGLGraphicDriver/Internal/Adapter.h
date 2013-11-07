#pragma once

#include "Manager.h"

namespace CB{
	class COGLOutput;
	class COGLDevice;

	class COGLAdapter : 
		public Graphic::IAdapter,
		public Manage::IManagedObject<COGLManager, COGLAdapter>,
		public Manage::IObjectManager<COGLOutput>,
		public Manage::IObjectManager<COGLDevice>
	{
	private:
		const uint32	m_uIndex;
		const CString	m_strDeviceID;
		DISPLAY_DEVICEW	m_DeviceInfo;
		Collection::CList<DISPLAY_DEVICEW> m_Outputs;

	public:
		COGLAdapter(CRefPtr<COGLManager> pManager, const uint32 uIndex, const CString& strDeviceID, const DISPLAY_DEVICEW& DeviceInfo);
		~COGLAdapter();

		const uint32 GetApiId() const override;

		CRefPtr<Graphic::IManager>	GetManager() const override;

		const uint32	GetIndex() const override;
		const CString	GetName() const override;

		virtual const uint32				GetNumberOfOutputs() const override;
		virtual CRefPtr<Graphic::IOutput>	GetOutput(const uint32 uIndex) override;
		virtual CRefPtr<Graphic::IOutput>	GetDefaultOutput() override;

		CRefPtr<Graphic::IDevice>	CreateDevice(CRefPtr<Window::IWindow> pWindow, const Graphic::CDeviceDesc& Desc) override;
		CRefPtr<Graphic::IDevice>	CreateDevice(CRefPtr<Window::IWindow> pWindow, const Graphic::CDeviceDesc& Desc, CRefPtr<Graphic::IOutput> pOutput) override;
	};
}