#pragma once

#include "BaseState.h"
#pragma warning(disable : 4250)

namespace CB{
	class COGLDepthStencilState : 
		public Graphic::IDepthStencilState,
		public IOGLBaseState
	{
	private:
		Graphic::CDepthStencilStateDesc	m_Desc;

	public:
		COGLDepthStencilState(CRefPtr<COGLDevice> pDevice, const Graphic::CDepthStencilStateDesc& Desc);

		const Graphic::CDepthStencilStateDesc	GetDesc() const override;
	};
}