#pragma once

#include "Macros.h"
#include <Types.h>
#include <Ref.h>
#include <Math_Size.h>
#include <ApiObject.h>
#include <Signals_Slots.h>
#include <SmartPointers_RefPtr.h>

namespace CB{
	namespace Window{
		enum class Style{
			Pure,
			Single,
			Sizeable,
			ToolWindow,
			SizeableToolWindow
		};

		class IManager;
		class IWindow;

		typedef Signals::CSlot<const bool, CRefPtr<IWindow>, const bool, const bool>	SlotVisibilityChange;
		typedef Signals::CSlot<const bool, CRefPtr<IWindow>, const Math::CSize&, const Math::CSize&>	SlotSizeChange;
		typedef Signals::CSlot<const bool, CRefPtr<IWindow>, const Math::CPoint&, const Math::CPoint&>	SlotPositionChange;
		typedef Signals::CSlot<const bool, CRefPtr<IWindow>, const bool>	SlotFocusChange;
		typedef Signals::CSlot<const bool, CRefPtr<IWindow>, const uint32, const uint32, const uint32>	SlotEvent;
		typedef Signals::CSlot<const bool, CRefPtr<IWindow>>	SlotWindow;
				
		class IWindow : 
			public IApiObject
		{
		public:
			virtual CRefPtr<IManager>	GetManager() const = 0;

			virtual void	SetPosition(const Math::CPoint& Position) = 0;
			virtual void	SetSize(const Math::CSize& Size) = 0;
			virtual void	SetVisible(const bool bVisible) = 0;
			virtual void	SetTitle(const CString& strTitle) = 0;
			virtual void	SetStyle(const Style uStyle) = 0;

			virtual const Math::CPoint	GetPosition() const = 0;
			virtual const Math::CSize	GetSize() const = 0;
			virtual const bool			IsVisible() const = 0;
			virtual const CString		GetTitle() const = 0;
			virtual const Style			GetStyle() const = 0;
			virtual void*				GetHandle() const = 0;

			SlotVisibilityChange	OnVisibilityChange;
			SlotSizeChange			OnSizeChange;
			SlotPositionChange		OnPositionChange;
			SlotWindow				OnCreate;
			SlotWindow				OnClose;
			SlotEvent				OnEvent;
			SlotWindow				OnFocusGain;
			SlotWindow				OnFocusLost;
			SlotFocusChange			OnFocusChange;
		};
		
		class IManager : 
			public IApiObject
		{
		public:
			virtual CRefPtr<IWindow>	CreateWindow(const CString& strTitle, const Style uStyle) = 0;
			virtual CRefPtr<IWindow>	CreateWindow(const CString& strTitle, const Style uStyle, const Math::CSize& Size) = 0;
			virtual CRefPtr<IWindow>	CreateWindow(const CString& strTitle, const Style uStyle, const Math::CSize& Size, const Math::CPoint& Position) = 0;

			virtual void	ProcessEvents() = 0;
			virtual void	ProcessEvents(const uint32 uMaxEvents) = 0;

			virtual const bool	SupportsMultiWindow() const = 0;
			virtual const bool	SupportsStyle(const Style uStyle) const = 0;
		};

		class IDriver : 
			public IRef
		{
		public:
			virtual CRefPtr<IManager>	CreateManager() = 0;
		};

		extern WINDOWDRVINTERFACE_API	CRefPtr<IDriver>	LoadDriver(const CString& strDriver);
	}

	namespace String{
		extern WINDOWDRVINTERFACE_API const CString	ToString(const Window::Style uStyle);
	}
}