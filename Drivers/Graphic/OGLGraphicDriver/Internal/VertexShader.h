#pragma once

#include "BaseShader.h"

namespace CB{
	class COGLVertexShader :
		public IOGLBaseShader
	{
	public:
		COGLVertexShader(CRefPtr<COGLDevice> pDevice, const Graphic::ShaderVersion uVersion, const CString& strSource, const CString& strEntryPoint);
	};
}