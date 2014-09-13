#pragma once

#include <Types.h>
#include <Signals_Slots.h>
#include <SmartPointers_AutoPtr.h>

#include "Graphic_OutputWindow.h"

namespace CB{
	namespace Math{
		class CPoint2D;
		class CSize2D;
	}

	namespace Graphic{
		enum class Style{
			Pure,
			Single,
			Sizeable,
			ToolWindow,
			SizeableToolWindow
		};

		enum class VirtualKey{
			Undefined = 0,
			#define CR_DEFVK(A,B)	A = B,
			#include "VirtualKeys.incl"
			#undef CR_DEFVK
			LastReserved = 0xFF,
		};

		class CWindow;

		typedef Signals::CSlot<const bool, CWindow&, const bool, const bool>	SlotVisibilityChange;
		typedef Signals::CSlot<const bool, CWindow&, const Math::CSize2D&, const Math::CSize2D&>	SlotSizeChange;
		typedef Signals::CSlot<const bool, CWindow&, const Math::CPoint2D&, const Math::CPoint2D&>	SlotPositionChange;
		typedef Signals::CSlot<const bool, CWindow&, const bool>	SlotFocusChange;
		typedef Signals::CSlot<const bool, CWindow&, const uint32, const uint32, const uint32>	SlotEvent;
		typedef Signals::CSlot<const bool, CWindow&>						SlotWindow;
		typedef Signals::CSlot<const bool, CWindow&, const wchar>			SlotChar;
		typedef Signals::CSlot<const bool, CWindow&, const Math::CPoint2D&>	SlotMouseMove;
		typedef Signals::CSlot<const bool, CWindow&, const VirtualKey>		SlotKey;

		class CWindow : 
			public IOutputWindow
		{
		private:
			class CWindowImpl;

			CWindowImpl*	m_pImpl;

		public:
			CWindow(const CString& strTitle, const Style uStyle);
			CWindow(const CString& strTitle, const Style uStyle, const Math::CSize2D& Size);
			CWindow(const CString& strTitle, const Style uStyle, const Math::CSize2D& Size, const Math::CPoint2D& Position);
			virtual ~CWindow();

			void	SetPosition(const Math::CPoint2D& Position);
			void	SetSize(const Math::CSize2D& Size);
			void	SetRect( const Math::CRectangle& Rect ) override;
			void	SetVisible(const bool bVisible);
			void	SetTitle(const CString& strTitle);
			void	SetStyle(const Style uStyle);

			const Math::CPoint2D	GetPosition() const;
			const Math::CSize2D		GetSize() const;
			const Math::CRectangle	GetRect() const override;
			const bool				IsVisible() const;
			const CString			GetTitle() const;
			const Style				GetStyle() const;
			void*					GetHandle() const override;

			SlotVisibilityChange	OnVisibilityChange;
			SlotSizeChange			OnSizeChange;
			SlotPositionChange		OnPositionChange;
			SlotWindow				OnCreate;
			SlotWindow				OnClose;
			SlotEvent				OnEvent;
			SlotWindow				OnFocusGain;
			SlotWindow				OnFocusLost;
			SlotFocusChange			OnFocusChange;
			SlotMouseMove			OnMouseMove;
			SlotChar				OnChar;
			SlotKey					OnKeyDown;
			SlotKey					OnKeyUp;
			SlotKey					OnMouseButtonUp;
			SlotKey					OnMouseButtonDown;

			static	void	ProcessEvents();
			static	void	ProcessEvents(uint32 uMaxEvents);

		private:
			void	Init( const CString& strTitle, const Style style, const Math::CSize2D& size, const Math::CPoint2D& pos );
		};
	}
}