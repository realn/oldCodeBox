#pragma once

#include <GraphicDriver.h>

namespace GraphicTest{
	class CRectOrthoModel{
	private:
		const uint32	m_uNumberOfPolygons;
		const float32	m_fWidth;
		const float32	m_fHeight;
		float32			m_fValue;

	public:
		CB::Math::CMatrix					mModelMatrix;
		CB::CRefPtr<CB::Graphic::IVertexDeclaration>	pVertexDecl;
		CB::CRefPtr<CB::Graphic::IBuffer>	pVertexBuffer;

		CRectOrthoModel(CB::CRefPtr<CB::Graphic::IDevice> pDevice, CB::CRefPtr<CB::Graphic::IShader> pVertexShader, const float32 fWidth, const float32 fHeight);

		void	SetInputVertex(CB::CRefPtr<CB::Graphic::IShader> pVertexShader);

		void	Update(const float32 fTimeDelta);
		void	Render(CB::CRefPtr<CB::Graphic::IDevice> pDevice);
	};
}