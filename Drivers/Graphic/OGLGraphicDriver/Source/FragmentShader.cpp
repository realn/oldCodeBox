#include "../Internal/FragmentShader.h"

namespace CB{
	COGLFragmentShader::COGLFragmentShader(CRefPtr<COGLDevice> pDevice, const Graphic::ShaderVersion uVersion, const CString& strSource, const CString& strEntryPoint) :
		IOGLBaseShader(pDevice, Graphic::ShaderType::Fragment, uVersion, CG_SOURCE, pDevice->GetCGProfile(uVersion, Graphic::ShaderType::Fragment), strSource, strEntryPoint)
	{

	}
}