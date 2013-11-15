#pragma once

#include "BaseState.h"

namespace CB{
	class COGLBlendState :
		public Graphic::IBlendState,
		public IOGLBaseState
	{
	private:
		Graphic::CBlendStateDesc	m_Desc;

	public:
		COGLBlendState(CRefPtr<COGLDevice> pDevice, const Graphic::CBlendStateDesc& Desc);

		const Graphic::CBlendStateDesc	GetDesc() const override;
	};
}