#pragma once

#include <GraphicDriver.h>

namespace GraphicTest{
	enum class VSCFlags : uint32{
		Vertex	= 0x1,
		TCoord	= 0x2,
		Normal	= 0x4,
	};

	class CVertexShaderConfig{
	public:
		uint32		uFlags;
		CB::CString	strVertexName;
		CB::CString strTCoordName;
		CB::CString strNormalName;
		CB::CRefPtr<CB::Graphic::IShader> pVertexShader;

		const bool	CheckFlag(const VSCFlags uFlag) const{
			return (this->uFlags & (uint32)uFlag) > 0;
		}
	};
}