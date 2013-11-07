#include "../Internal/VertexShader.h"

namespace CB{
	COGLVertexShader::COGLVertexShader(CRefPtr<COGLDevice> pDevice, const Graphic::ShaderVersion uVersion, const CString& strSource, const CString& strEntryPoint) :
		IOGLBaseShader(pDevice, CB::Graphic::ShaderType::Vertex, uVersion, CG_SOURCE, pDevice->GetCGProfile(uVersion, Graphic::ShaderType::Vertex), strSource, strEntryPoint)
	{

	}
}