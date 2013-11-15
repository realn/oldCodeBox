#include "../Internal/RasterizerState.h"

namespace CB{
	COGLRasterizerState::COGLRasterizerState(CRefPtr<COGLDevice> pDevice, const Graphic::CRasterizerStateDesc& Desc) :
		IOGLBaseState(pDevice, Graphic::DeviceStateType::Rasterizer),
		m_Desc(Desc)
	{}

	const Graphic::CRasterizerStateDesc	COGLRasterizerState::GetDesc() const{
		return this->m_Desc;
	}
}