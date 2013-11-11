#pragma once

#include "DeviceContextInterface.h"
#include "WinPlatform.h"

namespace CB{
	class CRenderContext{
	private:
		mutable HGLRC	m_GLContext;

	public:
		CRenderContext();
		~CRenderContext();

		void	Free();

		void	Bind(const IDeviceContext& DC);
		void	Unbind();

		HGLRC&	Get() const;

		void	CreateContext(const IDeviceContext& DC);
		void	CreateContext(const IDeviceContext& DC, const Collection::ICountable<int32>& Attribs);

	private:

	};
}