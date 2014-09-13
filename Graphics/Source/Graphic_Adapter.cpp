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

			//	Then we obtain the name of this specific adapter
			//	by finding in on the list.
			{
				DISPLAY_DEVICEW devInfo = { 0 };
				devInfo.cb = sizeof( DISPLAY_DEVICEW );

				for( uint32 i = 0; EnumDisplayDevicesW( nullptr, i, &devInfo, 0 ); i++ ){
					if( this->m_strId == devInfo.DeviceID ){
						this->m_strName = devInfo.DeviceString;	//	Contains human readable name of adapter
						// We found the needed information, so we can quit the loop.
						break;
					}
				}
			}
		}

		CAdapter::~CAdapter(){
			//	No work needed.
		}

		//	Return Index of the adapter when encountered on enumeration.
		const uint32	CAdapter::GetIndex() const{
			return this->m_uIndex;
		}

		//	Returns specific ID for adapter
		const CString	CAdapter::GetId() const{
			return this->m_strId;
		}

		//	Returns system address for adapter
		const CString	CAdapter::GetName() const{
			return this->m_strName;
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
			for( uint32 i = 0; EnumDisplayDevicesW( nullptr, i, &devInfo, 0 ); i++ ){ 
				if( (devInfo.StateFlags & DISPLAY_DEVICE_ACTIVE) && this->m_strId == devInfo.DeviceID )
					uNumber++;
			}

			return uNumber;
		}
	}
}