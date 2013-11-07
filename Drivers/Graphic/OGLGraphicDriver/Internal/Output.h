#pragma once

#include "Adapter.h"

namespace CB{
	class COGLOutput : 
		public Graphic::IOutput,
		public Manage::IManagedObject<COGLAdapter, COGLOutput>
	{
	private:
		const uint32		m_uIndex;
		DISPLAY_DEVICEW		m_DeviceInfo;
		Collection::CList<Graphic::BufferFormat> m_SupportedFormats;
		bool	m_bDisplayChanged;

	public:
		COGLOutput(CRefPtr<COGLAdapter> pAdapter, const uint32 uIndex, const DISPLAY_DEVICEW& deviceInfo);
		~COGLOutput();

		HDC	CreateDeviceContext();

		//	INTERFACE IMPLEMENTATION	====================================

		const uint32 GetApiId() const override;

		CRefPtr<Graphic::IAdapter>	GetAdapter() const override;

		const uint32	GetIndex() const override;
		const CString	GetName() const override;

		const uint32	GetNumberOfDisplayModes(Graphic::BufferFormat uDisplayFormat) const override;
		const Collection::CList<Graphic::CDisplayMode>	GetDisplayModes(const Graphic::BufferFormat uDisplayFormat) const override;

		//	END OF INTERFACE IMPLEMENTATION	================================

		const Graphic::CDisplayMode	GetCurrentMode() const;
		void	SetCurrentMode(const Graphic::CDisplayMode& Mode);
	};
}