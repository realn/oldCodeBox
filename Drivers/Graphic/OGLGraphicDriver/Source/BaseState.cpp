#include "../Internal/BaseState.h"

namespace CB{
	IOGLBaseState::IOGLBaseState(CRefPtr<COGLDevice> pDevice, const Graphic::DeviceStateType uType) :
		Manage::IManagedObject<COGLDevice, IOGLBaseState>(pDevice),
		m_uType(uType)
	{

	}

	const uint32	IOGLBaseState::GetApiId() const{
		return g_uApiID;
	}

	CRefPtr<Graphic::IDevice>	IOGLBaseState::GetDevice() const{
		return this->m_pParent.Cast<Graphic::IDevice>();
	}

	const Graphic::DeviceStateType	IOGLBaseState::GetType() const{
		return this->m_uType;
	}
}