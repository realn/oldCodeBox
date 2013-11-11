#pragma once

#include "Adapter.h"
#include <Math_Rectangle.h>

namespace CB{
	class COGLOutput : 
		public Graphic::IOutput,
		public Manage::IManagedObject<COGLAdapter, COGLOutput>
	{
	private:
		const uint32			m_uIndex;
		const CString			m_strName;
		Math::CRectangle		m_Bounds;

		Collection::CList<Graphic::BufferFormat> m_SupportedFormats;
		bool	m_bDisplayChanged;

	public:
		COGLOutput(CRefPtr<COGLAdapter> pAdapter, const uint32 uIndex, const CString& strName);
		~COGLOutput();

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

		void	AdjustWindowRect(CRefPtr<Window::IWindow> pWindow) const;

		const bool	SetMonitor(const CString& strDisplay, const Math::CRectangle& Rect);
	private:
		void	ReadOutputBounds();
	};
}