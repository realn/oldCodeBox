#include "RectOrthoModel.h"
#include <CBMath.h>

namespace GraphicTest{
	class CVertex{
	public:
		CB::Math::CVector3D	vPosition;
		CB::Math::CVector4D vColor;
	};

	CRectOrthoModel::CRectOrthoModel(CB::CRefPtr<CB::Graphic::IDevice> pDevice, CB::CRefPtr<CB::Graphic::IShader> pVertexShader, const float32 fWidth, const float32 fHeight) :
		m_fWidth(fWidth), m_fHeight(fHeight), m_uNumberOfPolygons(2), m_fValue(0.0f)
	{
		CB::Collection::CArray<CVertex, 6> verts;

		auto halfW = this->m_fWidth / 2.0f;
		auto halfH = this->m_fHeight / 2.0f;

		verts[0].vPosition.Set(-halfW,	-halfH, 0.0f);
		verts[1].vPosition.Set(halfW,	halfH,	0.0f);
		verts[2].vPosition.Set(halfW,	-halfH,	0.0f);

		verts[3].vPosition.Set(-halfW,	-halfH,	0.0f);
		verts[4].vPosition.Set(-halfW,	halfH,	0.0f);
		verts[5].vPosition.Set(halfW,	halfH,	0.0f);

		for(uint32 i = 0; i < verts.GetLength(); i++){
			verts[i].vColor.Set(
				CB::Math::Clamp01(verts[i].vPosition.X / halfW), 
				CB::Math::Clamp01(verts[i].vPosition.Y / halfH),
				verts[i].vColor.X * verts[i].vColor.Y,
				1.0f
				);
		}

		this->pVertexBuffer = pDevice->CreateBuffer(CB::Graphic::BufferType::Vertex, 
			CB::Graphic::BufferUsage::Static, CB::Graphic::BufferAccess::Write, verts);

		CB::Collection::CList<CB::Graphic::CVertexElement> vEls;
		vEls.Add(CB::Graphic::CVertexElement(0, L"vinput.vPosition", 0, CB::Graphic::VertexType::Float, 3));
		vEls.Add(CB::Graphic::CVertexElement(0, L"vinput.vColor", sizeof(float32) * 3, CB::Graphic::VertexType::Float, 4));

		this->pVertexDecl = pDevice->CreateVertexDeclaration(pVertexShader, vEls);

		this->mModelMatrix = CB::Math::CMatrix::GetIdentity();
	}

	void	CRectOrthoModel::SetInputVertex(CB::CRefPtr<CB::Graphic::IShader> pVertexShader){
	}

	void	CRectOrthoModel::Update(const float32 fTimeDelta){
		this->m_fValue += fTimeDelta * 30.0f;
		this->mModelMatrix = CB::Math::CMatrix::GetRotation(CB::Math::AxisOrientation::AxisY, this->m_fValue);
	}

	void	CRectOrthoModel::Render(CB::CRefPtr<CB::Graphic::IDevice> pDevice){
		pDevice->Render(this->m_uNumberOfPolygons, 0);
	}
}