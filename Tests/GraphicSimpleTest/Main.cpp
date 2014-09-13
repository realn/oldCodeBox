#include <iostream>

#include <Graphic_Adapter.h>
#include <Graphic_Display.h>
#include <Graphic_DisplayMode.h>
#include <Graphic_Window.h>

#include <Collection_List.h>

#include <Math_Rectangle.h>

#include <Signals_Func.h>

bool	bRun = true;

const bool	CloseEvent( CB::Graphic::CWindow& window ){
	bRun = false;
	return true;
}

int main( int argc, char* argv[] ){

	std::wcout << L"Count: " << CB::Graphic::CAdapter::Count() << std::endl << std::endl;

	CB::Graphic::CAdapter adapter;

	std::wcout << L"ID: " << adapter.GetId().GetPointer() << std::endl;
	std::wcout << L"Name: " << adapter.GetName().GetPointer() << std::endl;

	std::wcout << std::endl;

	std::wcout << L"Display Count: " << adapter.CountDisplays() << std::endl << std::endl;

	CB::Graphic::CDisplay display( adapter );

	std::wcout << L"ID: " << display.GetId().GetPointer() << std::endl;
	std::wcout << L"Name: " << display.GetName().GetPointer() << std::endl;
	std::wcout << L"Rect: " << display.GetRect().ToString().GetPointer() << std::endl;
	std::wcout << L"CRect: " << display.GetClientRect().ToString().GetPointer() << std::endl;
	std::wcout << L"Primary: " << CB::String::ToString( display.IsPrimary() ).GetPointer() << std::endl;

	std::wcout << std::endl;

	auto list = display.GetModes();
	std::wcout << L"Modes Count: " << list.GetLength() << std::endl;
	for( uint32 i = 0; i < list.GetLength(); i++ ){
		std::wcout << list[i].ToString().GetPointer() << std::endl;
	}

	std::wcout << std::endl;

	{
		CB::Graphic::CWindow window( L"Test Window", CB::Graphic::Style::Single, CB::Math::CSize2D( 300, 200 ) );
		window.OnClose += CB::Signals::CFunc<const bool, CB::Graphic::CWindow&>( CloseEvent );
		window.SetVisible( true );

		while( bRun ){
			CB::Graphic::CWindow::ProcessEvents();
		}
	}

	std::wcin.get();

	return 0;
}