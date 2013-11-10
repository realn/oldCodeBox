#pragma once

#include "DeviceContextInterface.h"
#include <SmartPointers_RefPtr.h>
#include <WindowDriver.h>

namespace CB{
	class CWindowDeviceContext :
		public IDeviceContext
	{
	private:
		CRefPtr<CB::Window::IWindow> m_pWindow;
		mutable HDC m_hDC;

	public:
		CWindowDeviceContext();
		CWindowDeviceContext(CRefPtr<Window::IWindow> pWindow);
		~CWindowDeviceContext();

		void	Release();

		void	SetWindow(CRefPtr<Window::IWindow> pWindow);
		CRefPtr<Window::IWindow>	GetWindow() const;

		HDC&	Get() const override;
	};
}