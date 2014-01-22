#pragma once

#include <GraphicDriver.h>

namespace GraphicTest{
	class CShaderLoader{
	public:
		CB::CRefPtr<CB::Graphic::IShader>	pVertexShader;
		CB::CRefPtr<CB::Graphic::IShader>	pFragmentShader;

	public:
		CShaderLoader(CB::CRefPtr<CB::Graphic::IDevice> pDevice, const CB::CString& strShadersFilename);

	private:
		const CB::CString	LoadSource(const CB::CString& strFilename);
	};
}