#include "../Internal/BlendState.h"

namespace CB{
	COGLBlendState::COGLBlendState(CRefPtr<COGLDevice> pDevice, const Graphic::CBlendStateDesc& Desc) :
		IOGLBaseState(pDevice, Graphic::DeviceStateType::Blend),
		m_Desc(Desc)
	{}

	const Graphic::CBlendStateDesc	COGLBlendState::GetDesc() const{
		return this->m_Desc;
	}
}