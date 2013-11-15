#include "../Internal/DepthStencilState.h"

namespace CB{
	COGLDepthStencilState::COGLDepthStencilState(CRefPtr<COGLDevice> pDevice, const Graphic::CDepthStencilStateDesc& Desc) :
		IOGLBaseState(pDevice, Graphic::DeviceStateType::DepthStencil),
		m_Desc(Desc)
	{}

	const Graphic::CDepthStencilStateDesc	COGLDepthStencilState::GetDesc() const{
		return this->m_Desc;
	}
}