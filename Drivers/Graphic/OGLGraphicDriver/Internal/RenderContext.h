#pragma once

#include "DeviceContextInterface.h"
#include "WinPlatform.h"

namespace CB{
	class CRenderContext{
	private:
		mutable HGLRC	m_GLContext;

	public:
		CRenderContext();
		CRenderContext(const IDeviceContext& DC);
		~CRenderContext();

		void	Free();

		void	Bind(const IDeviceContext& DC);
		void	Unbind();

		HGLRC&	Get() const;

		void	CreateContext(const IDeviceContext& DC);
	};
}