#include "stdafx.h"
#include "../Include/Graphic_Adapter.h"

#include <Collection_StringList.h>
#include <CBString.h>

namespace CB{
	namespace Graphic{
		//	Constant representing default graphic adapter
		const uint32	DEFAULT_ADAPTER = 0;

		//	Returns list of graphic adapter IDs, where first one is the default.
		const Collection::CStringList	GetAdapterIDList(){
			Collection::CStringList list;

			DISPLAY_DEVICEW devInfo = { 0 };
			devInfo.cb = sizeof(DISPLAY_DEVICEW);

			for( uint32 uIndex = 0; EnumDisplayDevicesW( nullptr, uIndex, &devInfo, 0 ); uIndex++ ){

				//	We want only adapters that are currently in use
				if( !(devInfo.StateFlags & DISPLAY_DEVICE_ACTIVE ) )
					continue;

				//	We want only adapters that are attached to this machine
				if( !(devInfo.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP ) )
					continue;

				//	There still can be ducplicates on this list, so we must
				//	first check for them.
				if( list.Contains( devInfo.DeviceID ) ) {
					uint32 idx = list.IndexOf( devInfo.DeviceID );

					//	There is a chance that on some configurations the first 
					//	adapter will not be first - we must correct that.
					if( (devInfo.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE ) && idx != DEFAULT_ADAPTER ){
						list.Remove( idx );
						list.Insert( 0, devInfo.DeviceID );
					}
					continue;
				}
				//	In other cases we add the Id to list.
				else{
					list.Add( devInfo.DeviceID );
				}
			}
			return list;
		}

		//	Constructor for class
		//	uIndex	indicates whitch adapter will be used (DEFAULT_ADATPER for default one).
		CAdapter::CAdapter( const uint32 uIndex ) : 
			m_uIndex( uIndex )
		{
			//	First we must obtaint adapter ID from list generated for GetCount() call.
			{
				Collection::CStringList adapterList = GetAdapterIDList();
				this->m_strId = adapterList[uIndex];
			}

			//	Then we obtain the name and description of this specific adapter
			//	by finding in on the list.
			{
				DISPLAY_DEVICEW devInfo = { 0 };
				devInfo.cb = sizeof( DISPLAY_DEVICEW );

				for( uint32 i = 0; EnumDisplayDevicesW( nullptr, i, &devInfo, 0 ); i++ ){
					if( this->m_strId == devInfo.DeviceID ){
						this->m_strName = devInfo.DeviceName;	//	Contains specific address to adapter
						this->m_strDesc = devInfo.DeviceString;	//	Contains human readable name of adapter
						// We found the information, so we can quit the loop.
						break;
					}
				}
			}
		}

		CAdapter::~CAdapter(){
			//	No work needed.
		}

		//	Returns specific ID for adapter
		const CString	CAdapter::GetId() const{
			return this->m_strId;
		}

		//	Returns system address for adapter
		const CString	CAdapter::GetName() const{
			return this->m_strName;
		}

		//	Returns human readable name for adapter
		const CString	CAdapter::GetDescription() const{
			return this->m_strDesc;
		}

		//	Counts the number of adapter currently active on this system. 
		const uint32	CAdapter::Count() {
			return GetAdapterIDList().GetLength();
		}

		//	Counts the number of displays currently attached to this adapter.
		const uint32	CAdapter::CountDisplays() const {

			DISPLAY_DEVICEW devInfo = { 0 };
			devInfo.cb = sizeof( DISPLAY_DEVICEW );

			//	Count the number of displays (monitors) using adapter address (name)
			uint32 uNumber = 0;
			while( EnumDisplayDevicesW( this->m_strName.GetPointer(), uNumber, &devInfo, 0 ) ){ 
				uNumber++;
			}

			return uNumber;
		}
	}
}