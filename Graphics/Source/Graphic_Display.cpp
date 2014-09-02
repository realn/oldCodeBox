#include "stdafx.h"
#include "../Include/Graphic_Display.h"
#include "../Include/Graphic_Adapter.h"

#include <Collection_Dictionary.h>

namespace CB{
	namespace Graphic{
		const uint32	DEFAULT_DISPLAY = 0;

		CDisplay::CDisplay( const uint32 uIndex ) :
			m_uIndex( uIndex )
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

		const CString&	CDisplay::GetDescription() const{
			return this->m_strDesc;
		}

		const CString&	CDisplay::GetDeviceName() const{
			return this->m_strDevName;
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

		const uint32	CDisplay::CountModes() const{
			uint32 uCount = 0;
			DEVMODEW devMode = { 0 };
			devMode.dmSize = sizeof( DEVMODEW );

			for(uint32 uIndex = 0; EnumDisplaySettingsExW( this->GetDeviceName().GetPointer(), uIndex, &devMode, 0 ); uIndex++ ){

				//	We make sure to count only display settings that matter.
				if( ( devMode.dmFields & DM_PELSWIDTH ) &&
					( devMode.dmFields & DM_PELSHEIGHT ) &&
					( devMode.dmFields & DM_BITSPERPEL ) &&
					( devMode.dmFields & DM_DISPLAYFREQUENCY ) &&
					( devMode.dmFields & DM_DISPLAYFLAGS ) )
					uCount ++;
			}

			return uCount;
		}

		void	CDisplay::Init( const CAdapter& adapter ){
			Collection::CDictionary<CString, DISPLAY_DEVICEW>	list;

			DISPLAY_DEVICEW devInfo = { 0 };
			devInfo.cb = sizeof( DISPLAY_DEVICEW );

			//	We collect each output display info, that has correct criteria.
			for( uint32 uIndex = 0; EnumDisplayDevicesW( adapter.GetName().GetPointer(), uIndex, &devInfo, 0 ); uIndex++ ){
				//	display must be active
				if( !(devInfo.StateFlags & DISPLAY_DEVICE_ACTIVE ) )
					continue;

				//	There can be duplicates of this display.
				if( list.Contains( devInfo.DeviceID ) )
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
			this->m_strDesc = devInfo.DeviceString;
			this->m_strDevName = adapter.GetName();
		}
	}
}