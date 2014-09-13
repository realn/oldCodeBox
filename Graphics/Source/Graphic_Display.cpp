#include "stdafx.h"
#include "../Include/Graphic_Display.h"
#include "../Include/Graphic_Adapter.h"
#include "../Include/Graphic_DisplayMode.h"

#include <Collection_Dictionary.h>
#include <Collection_List.h>
#include <Collection_Funcs.h>

#include <Math_Rectangle.h>

namespace CB{
	namespace Graphic{
		const uint32	DEFAULT_DISPLAY = 0;

		BOOL CALLBACK MonitorEnum( HMONITOR hMonitor, HDC hDC, LPRECT lpRect, LPARAM lParam){
			CDisplay* pDisplay = reinterpret_cast<CDisplay*>( lParam );

			MONITORINFOEXW monitorInfo;
			monitorInfo.cbSize = sizeof( MONITORINFOEXW );

			if( GetMonitorInfoW( hMonitor, &monitorInfo ) ){
				if( pDisplay->GetName() == monitorInfo.szDevice ){
					pDisplay->SetHandle( hMonitor );

					return false;
				}
			}
			return true;
		}

		CDisplay::CDisplay( const uint32 uIndex ) :
			m_uIndex( uIndex ),
			m_Handle( nullptr )
		{
			//	We create a default adapter for this case.
			CAdapter adapter;
			this->Init( adapter );
		}

		CDisplay::CDisplay( const CAdapter& adapter, const uint32 uIndex ) :
			m_uIndex( uIndex )
		{
			this->Init( adapter );
		}

		CDisplay::~CDisplay(){

		}

		const CString&	CDisplay::GetId() const{
			return this->m_strId;
		}

		const CString&	CDisplay::GetName() const{
			return this->m_strName;
		}

		const CAdapter	CDisplay::GetAdapter() const{
			return CAdapter( this->m_uAdapterIndex );
		}

		const Math::CRectangle	CDisplay::GetRect() const{
			MONITORINFO info = { 0 };
			info.cbSize = sizeof( MONITORINFO );

			if( GetMonitorInfoW( reinterpret_cast<HMONITOR>(this->m_Handle), &info ) ){
				const RECT& rect = info.rcMonitor;
				return Math::CRectangle(
					rect.left, rect.top,
					rect.right - rect.left, rect.bottom - rect.top
					);
			}

			return Math::CRectangle();
		}

		const Math::CRectangle	CDisplay::GetClientRect() const{
			MONITORINFO info = { 0 };
			info.cbSize = sizeof( MONITORINFO );

			if( GetMonitorInfoW( reinterpret_cast<HMONITOR>(this->m_Handle), &info ) ){
				const RECT& rect = info.rcWork;
				return Math::CRectangle(
					rect.left, rect.top,
					rect.right - rect.left, rect.bottom - rect.top
					);
			}

			return Math::CRectangle();
		}

		const bool	CDisplay::IsPrimary() const{
			MONITORINFO info = { 0 };
			info.cbSize = sizeof( MONITORINFO );

			if( GetMonitorInfoW( reinterpret_cast<HMONITOR>(this->m_Handle), &info ) ){
				return (info.dwFlags & MONITORINFOF_PRIMARY) > 0;
			}

			return false;
		}

		const uint32	CDisplay::Count(){
			//	For this case we use the default adapter.
			CAdapter adapter;
			return CDisplay::Count( adapter );
		}

		const uint32	CDisplay::Count( const CAdapter& adapter ){

			//	Adapter class already has a method of counting displays.
			return adapter.CountDisplays();
		}

		const Collection::CList<CDisplayMode>	CDisplay::GetModes() const{
			Collection::CList<CDisplayMode> list;
			DEVMODEW devMode = { 0 };
			devMode.dmSize = sizeof( DEVMODEW );

			for(uint32 uIndex = 0; EnumDisplaySettingsExW( this->m_strName.GetPointer(), uIndex, &devMode, 0 ); uIndex++ ){

				//	We make sure to count only display settings that matter.
				if( ( devMode.dmFields & DM_PELSWIDTH ) &&
					( devMode.dmFields & DM_PELSHEIGHT ) &&
					( devMode.dmFields & DM_BITSPERPEL ) &&
					( devMode.dmFields & DM_DISPLAYFREQUENCY ) &&
					( devMode.dmFields & DM_DISPLAYFLAGS ) )
				{
					//	Convert to uour display mode struct
					CDisplayMode mode( 
						Math::CSize2D( devMode.dmPelsWidth, devMode.dmPelsHeight ), 
						devMode.dmBitsPerPel, 
						devMode.dmDisplayFrequency > 1 ? devMode.dmDisplayFrequency : 0
						);

					//	Check if mode already exists on the list.
					if( !Collection::Contains( list, mode ) ){
						list.Add( mode );
					}
				}
			}

			return list;
		}

		//	Returns current display mode.
		const CDisplayMode	CDisplay::GetCurrentMode() const{
			DEVMODEW devMode = { 0 };
			devMode.dmSize = sizeof(DEVMODEW);

			if( EnumDisplaySettingsExW( this->m_strName.GetPointer(), ENUM_CURRENT_SETTINGS, &devMode, 0 ) ){
				return CDisplayMode(
					Math::CSize2D( devMode.dmPelsWidth, devMode.dmPelsHeight ),
					devMode.dmBitsPerPel,
					devMode.dmDisplayFrequency > 1 ? devMode.dmDisplayFrequency : 0 
					);
			}

			//	TODO: ERROR
			return CDisplayMode();
		}

		void	CDisplay::SetMode( const CDisplayMode& mode ){
			DEVMODEW devMode = { 0 };
			devMode.dmSize = sizeof(DEVMODEW);

			devMode.dmPelsWidth = mode.Size.Width;
			devMode.dmPelsHeight = mode.Size.Height;
			devMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;

			if( mode.uBitsPerPixel != DMODE_DEFAULT_BPP ){
				devMode.dmBitsPerPel = mode.uBitsPerPixel;
				devMode.dmFields |= DM_BITSPERPEL;
			}

			if( mode.uRefreshRate != DMODE_DEFAULT_FREQENCY ){
				devMode.dmDisplayFrequency = mode.uRefreshRate;
				devMode.dmFields |= DM_DISPLAYFREQUENCY;
			}

			//	We fill basic infomration defining given mode.
			if(devMode.dmDisplayFrequency != 0){
				devMode.dmFields |= DM_DISPLAYFREQUENCY;
			}

			//	If mode has only zeroes in ih it - it means there
			//	is a need for reset monitor to original mode.
			if( mode == CDisplayMode() ){
				ChangeDisplaySettingsExW(this->m_strName.GetPointer(), 0, 0, CDS_RESET, 0);

				// we don't need to check for success.
				return;
			}

			//	We change mode to desired using the FULLSCREEN flag,
			//	to indicate that this is a temporary change.
			if( ChangeDisplaySettingsExW(this->m_strName.GetPointer(), &devMode, 0, CDS_FULLSCREEN, 0) != DISP_CHANGE_SUCCESSFUL){
				CR_THROWWIN(GetLastError(), L"Failed to change display mode to: " + mode.ToString());
			}
		}

		void	CDisplay::SetHandle( void* pHandle ){
			this->m_Handle = pHandle;
		}

		//	Initializes information about display of given adapter.
		void	CDisplay::Init( const CAdapter& adapter ){
			Collection::CDictionary<CString, DISPLAY_DEVICEW>	list;

			DISPLAY_DEVICEW devInfo = { 0 };
			devInfo.cb = sizeof( DISPLAY_DEVICEW );

			//	We collect each output display info, that has correct criteria.
			for( uint32 uIndex = 0; EnumDisplayDevicesW( nullptr, uIndex, &devInfo, 0 ); uIndex++ ){
				//	display must be active
				if( !(devInfo.StateFlags & DISPLAY_DEVICE_ACTIVE ) )
					continue;

				//	There can be duplicates of this display.
				if( list.Contains( devInfo.DeviceName ) )
					continue;

				//	If the current display is primary, we move it to the beggining
				if( devInfo.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE )
					list.Insert( 0, devInfo.DeviceID, devInfo );
				else
					list.Add( devInfo.DeviceID, devInfo );
			}

			//	With list completed - we can select the proper information.
			devInfo = list.GetValue( this->m_uIndex );

			this->m_strId = devInfo.DeviceID;
			this->m_strName = devInfo.DeviceName;
			this->m_uAdapterIndex = adapter.GetIndex();

			//	We want the monitor handle for this display,
			//	so we need to enumarate every monitor and,
			//	find one matching this device.
			EnumDisplayMonitors( 
				nullptr, nullptr, 
				reinterpret_cast<MONITORENUMPROC>( MonitorEnum ), 
				reinterpret_cast<LPARAM>( this ) );
		}
	}
}
