#include <iostream>

#include <Graphic_Adapter.h>
#include <Graphic_Display.h>

#include <Windows.h>

BOOL CALLBACK MonitoEnum( HMONITOR hMonitor, HDC hDC, LPRECT pRect, LPARAM lParam){

	MONITORINFOEXW monInfo;
	monInfo.cbSize = sizeof( MONITORINFOEXW );

	if( GetMonitorInfoW( hMonitor, &monInfo ) ) {
		std::wcout << L"Device: " << monInfo.szDevice << std::endl;
		

		std::wcout << std::endl;
	}

	return TRUE;
}

int main( int argc, char* argv[] ){

	std::wcout << L"Count: " << CB::Graphic::CAdapter::Count() << std::endl << std::endl;

	CB::Graphic::CAdapter adapter;

	std::wcout << L"ID: " << adapter.GetId().GetPointer() << std::endl;
	std::wcout << L"Name: " << adapter.GetName().GetPointer() << std::endl;
	std::wcout << L"Desc: " << adapter.GetDescription().GetPointer() << std::endl;	

	std::wcout << std::endl;

	std::wcout << L"Display Count: " << adapter.CountDisplays() << std::endl << std::endl;

	CB::Graphic::CDisplay display( adapter );

	std::wcout << L"ID: " << display.GetId().GetPointer() << std::endl;
	std::wcout << L"Name: " << display.GetName().GetPointer() << std::endl;
	std::wcout << L"Desc: " << display.GetDescription().GetPointer() << std::endl;	

	std::wcout << std::endl;

	std::wcout << L"Modes Count: " << display.CountModes() << std::endl;

	std::wcout << std::endl;

	EnumDisplayMonitors( NULL, NULL, (MONITORENUMPROC)MonitoEnum, NULL );

	std::wcin.get();

	return 0;
}