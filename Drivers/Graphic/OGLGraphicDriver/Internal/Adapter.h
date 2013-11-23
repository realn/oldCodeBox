#pragma once

#include "Manager.h"
#include "DisplayOutputInfo.h"

namespace CB{
	class COGLOutput;
	class COGLDevice;

	class COGLAdapter : 
		public Graphic::IAdapter,
		public Manage::IManagedObject<COGLManager, COGLAdapter>,
		public Manage::IObjectManager<COGLAdapter, COGLOutput>,
		public Manage::IObjectManager<COGLAdapter, COGLDevice>
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

		CRefPtr<Graphic::IDevice>	CreateDevice(CRefPtr<Window::IWindow> pWindow, const Graphic::CDeviceDesc& Desc, const Collection::ICountable<Graphic::FeatureLevel>& FeatureLevels) override;
		CRefPtr<Graphic::IDevice>	CreateDevice(CRefPtr<Window::IWindow> pWindow, const Graphic::CDeviceDesc& Desc, const Collection::ICountable<Graphic::FeatureLevel>& FeatureLevels, CRefPtr<Graphic::IOutput> pOutput) override;
	};
}