#pragma once

#include "BaseState.h"

namespace CB{
	class COGLRasterizerState :
		public Graphic::IRasterizerState,
		public IOGLBaseState
	{
	private:
		Graphic::CRasterizerStateDesc	m_Desc;

	public:
		COGLRasterizerState(CRefPtr<COGLDevice> pDevice, const Graphic::CRasterizerStateDesc& Desc);

		const Graphic::CRasterizerStateDesc	GetDesc() const override;
	};
}