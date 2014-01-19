#pragma once

#include <GraphicDriver.h>
#include "VertexShaderConfig.h"

namespace GraphicTest{
	class CCubeModel{
	private:
		const CB::Math::CVector3D	m_vSize;
		uint32	m_uNumberOfPolygons;
		float	m_fValue;

	public:
		CB::Math::CMatrix	mModelMatrix;
		CB::CRefPtr<CB::Graphic::IVertexDeclaration>	pVertexDecl;
		CB::CRefPtr<CB::Graphic::IBuffer>				pBuffer;
		CB::CRefPtr<CB::Graphic::IBuffer>				pIndices;

		CCubeModel(CB::CRefPtr<CB::Graphic::IDevice> pDevice, const CB::Math::CVector3D& vSize, const CVertexShaderConfig& config);

		void	Update(const float32 fTimeDelta);
		void	Render(CB::CRefPtr<CB::Graphic::IDevice> pDevice);
	};
}