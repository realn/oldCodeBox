#pragma once

#include "DeviceContextInterface.h"
#include "WinPlatform.h"
#include <Collection_Interface.h>

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
		const bool	IsBinded() const;

		HGLRC&	Get() const;

		void		CreateContext(const IDeviceContext& DC);
		const bool	CreateContext(const IDeviceContext& DC, const Collection::ICountable<int32>& Attribs);

	private:

	};

	class CRCBindGuard{
	private:
		HDC		m_hDC;
		HGLRC	m_hRC;

	public:
		CRCBindGuard();
		~CRCBindGuard();
	};
}