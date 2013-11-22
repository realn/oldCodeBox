#pragma once

#include "BaseState.h"
#pragma warning(disable : 4250)

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