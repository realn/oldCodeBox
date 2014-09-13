#pragma once

#include <Types.h>
#include <Ref.h>
#include <CBString.h>
#include <SmartPointers_Ptr.h>
#include <Manage_Singleton.h>
#include <Collection_List.h>
#include <Collection_Dictionary.h>
#include <Signals_Method.h>

#include <Windows.h>
#undef GetClassName

namespace CB{
	namespace Graphic{
		enum class VirtualKey;

		class CWindow;
	}

	namespace Internal{
		class CWindowClass :
			public IRef,
			public Manage::CRefSingleton<CWindowClass>
		{
		private:
			typedef Signals::CMethod<CWindowClass, int32, Graphic::CWindow&, UINT, WPARAM, LPARAM>	MessageMethod;
			typedef uint32	MessageID;

			CString	m_strClassName;
			Collection::CList<CPtr<Graphic::CWindow>>	m_WindowList;
			Collection::CDictionary<MessageID, MessageMethod>	m_MessageMap;

		public:
			CWindowClass();
			virtual ~CWindowClass();

			void	AddWindow( CPtr<Graphic::CWindow> pWindow );
			void	RemoveWindow( CPtr<Graphic::CWindow> pWindow );

			const CString	GetClassName() const;

		private:
			void	InitMessageMap();

			static LRESULT CALLBACK staticWindowCallback( HWND hWindow, UINT uMsg, WPARAM wParam, LPARAM lParam );
			int	WindowCallback( HWND hWindow, UINT uMsg, WPARAM wParam, LPARAM lParam );

			const bool TryGetVirtualKey(const uint32 uKeyCode, Graphic::VirtualKey& uKeyOut);
			const bool TryGetMouseVirtualButton(const uint32 uMsg, const WPARAM wParam, Graphic::VirtualKey& uKeyOut);

			int32	MessageCreate( Graphic::CWindow& window, UINT uMsg, WPARAM wParam, LPARAM lParam );
			int32	MessageClose( Graphic::CWindow& window, UINT uMsg, WPARAM wParam, LPARAM lParam );
			int32	MessageSize( Graphic::CWindow& window, UINT uMsg, WPARAM wParam, LPARAM lParam );
			int32	MessageMove( Graphic::CWindow& window, UINT uMsg, WPARAM wParam, LPARAM lParam );
			int32	MessageShowWindow( Graphic::CWindow& window, UINT uMsg, WPARAM wParam, LPARAM lParam );
			int32	MessageActivate( Graphic::CWindow& window, UINT uMsg, WPARAM wParam, LPARAM lParam );
			int32	MessageKey( Graphic::CWindow& window, UINT uMsg, WPARAM wParam, LPARAM lParam );
			int32	MessageChar( Graphic::CWindow& window, UINT uMsg, WPARAM wParam, LPARAM lParam );
			int32	MessageMouseMove( Graphic::CWindow& window, UINT uMsg, WPARAM wParam, LPARAM lParam );
			int32	MessageMouseKey( Graphic::CWindow& window, UINT uMsg, WPARAM wParam, LPARAM lParam );			
		};
	}
}