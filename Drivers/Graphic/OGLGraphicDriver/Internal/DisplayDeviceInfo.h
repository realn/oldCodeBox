#pragma once

#include <CBString.h>
#include <CBStringEx.h>

namespace CB{
	class CDisplayDeviceInfo{
	public:
		CString					strDeviceId;
		CString					strDeviceName;
		Collection::CStringList strDisplayList;

		CDisplayDeviceInfo(){}
		CDisplayDeviceInfo(const CDisplayDeviceInfo& DeviceInfo) :
			strDeviceId(DeviceInfo.strDeviceId),
			strDeviceName(DeviceInfo.strDeviceName),
			strDisplayList(DeviceInfo.strDisplayList)
		{}

		const CDisplayDeviceInfo&	operator=(const CDisplayDeviceInfo& Info){
			this->strDeviceId = Info.strDeviceId;
			this->strDeviceName = Info.strDeviceName;
			this->strDisplayList = Info.strDisplayList;

			return *this;
		}
	};
}