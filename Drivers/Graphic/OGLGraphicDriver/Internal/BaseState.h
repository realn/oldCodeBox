#pragma once

#include "Device.h"

namespace CB{
	class IOGLBaseState :
		public virtual Graphic::IDeviceState,
		public Manage::IManagedObject<COGLDevice, IOGLBaseState>
	{
	protected:
		const Graphic::DeviceStateType	m_uType;

	protected:
		IOGLBaseState(CRefPtr<COGLDevice> pDevice, const Graphic::DeviceStateType uType);

	public:
		const uint32	GetApiId() const override;

		CRefPtr<Graphic::IDevice>		GetDevice() const override;

		const Graphic::DeviceStateType	GetType() const override;	
	};
}