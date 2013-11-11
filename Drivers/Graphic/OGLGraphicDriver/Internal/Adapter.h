#pragma once

#include "Manager.h"
#include "DisplayOutputInfo.h"

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
		const uint32		m_uIndex;
		const CString		m_strDeviceID;
		const CString		m_strName;
		CDisplayDeviceInfo	m_DeviceInfo;

	public:
		COGLAdapter(CRefPtr<COGLManager> pManager, const uint32 uIndex, const CDisplayDeviceInfo& DeviceInfo);
		~COGLAdapter();

		const uint32 GetApiId() const override;

		CRefPtr<Graphic::IManager>	GetManager() const override;

		const uint32	GetIndex() const override;
		const CString	GetName() const override;

		const uint32				GetNumberOfOutputs() const override;
		CRefPtr<Graphic::IOutput>	GetOutput(const uint32 uIndex) override;
		CRefPtr<Graphic::IOutput>	GetDefaultOutput() override;
		CRefPtr<Graphic::IOutput>	GetOutputForWindow(CRefPtr<Window::IWindow> pWindow) override;

		CRefPtr<Graphic::IDevice>	CreateDevice(CRefPtr<Window::IWindow> pWindow, const Graphic::CDeviceDesc& Desc) override;
		CRefPtr<Graphic::IDevice>	CreateDevice(CRefPtr<Window::IWindow> pWindow, const Graphic::CDeviceDesc& Desc, CRefPtr<Graphic::IOutput> pOutput) override;
	private:
		const int32	FindPixelFormat(CRefPtr<Window::IWindow> pWindow, const Graphic::CDeviceDesc& Desc);
	};
}