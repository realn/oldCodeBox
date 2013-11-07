#pragma once

#include "BaseShader.h"

namespace CB{
	class COGLFragmentShader :
		public IOGLBaseShader
	{
	public:
		COGLFragmentShader(CRefPtr<COGLDevice> pDevice, const Graphic::ShaderVersion uVersion, const CString& strSource, const CString& strEntryPoint);
	};
}