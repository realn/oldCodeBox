#include "CubeModel.h"
#include <Collection_Funcs.h>

class CVertex2{
public:
	CB::Math::CVector3D	vPosition;
	CB::Math::CVector2D	vTexCoord;

	CVertex2(){}
	CVertex2(const float32 x, const float32 y, const float32 z, const float32 s, const float32 t) :
		vPosition(x, y, z), vTexCoord(s, t)
	{}

	static const bool	CompareVertex(const CVertex2& v1, const CVertex2& v2){
		return v1.vPosition == v2.vPosition && v1.vTexCoord == v2.vTexCoord;
	}
};

const float32 fx[4] = {
	-1.0f, 1.0f, 1.0f, -1.0f
};
const float32	fy[4] = {
	-1.0f, -1.0f, 1.0f, 1.0f
};
const float32	f3d[2] = {
	1.0f, -1.0f
};

const float32	fs[4] = {
	0.0f, 1.0f, 1.0f, 0.0f
};
const float32	ft[4] = {
	0.0f, 0.0f, 1.0f, 1.0f
};

const float32	fxw[3][3] = {
	{1.0f, 0.0f, 0.0f},
	{-1.0f, 0.0f, 0.0f},
	{0.0f, 0.0f, -1.0f}
};

const float32	fyw[3][3] = {
	{0.0f, 1.0f, 0.0f},
	{0.0f, 0.0f, 1.0f},
	{0.0f, 1.0f, 0.0f}
};

const float32	fn[3][3] = {
	{ 0.0f, 0.0f, 1.0f },
	{ 0.0f, 1.0f, 0.0f },
	{ 1.0f, 0.0f, 0.0f },
};

class CCubeBuilder2{
private:
	CB::Collection::CArray<CVertex2, 4> m_quad;
	uint32	m_quadIdx;

public:
	CB::Collection::CList<CVertex2>	verts;
	CB::Collection::CList<uint16>	indices;

	CCubeBuilder2() : 
		m_quadIdx(0)
	{}

	void	Build(const CB::Math::CVector3D& vHalfSize){
		for(uint32 s = 0; s < 2; s++){
			for(uint32 w = 0; w < 3; w++){
				for(uint32 i = 0; i < 4; i++){
					this->AddVertex(
						(fx[i] * fxw[w][0] + fy[i] * fyw[w][0] + fn[w][0] * f3d[s]) * vHalfSize.X, 
						(fx[i] * fxw[w][1] + fy[i] * fyw[w][1] + fn[w][1] * f3d[s]) * vHalfSize.Y,
						(fx[i] * fxw[w][2] + fy[i] * fyw[w][2] + fn[w][2] * f3d[s]) * vHalfSize.Z,
						fs[i],
						ft[i],
						s
					);
				}
			}
		}
	};

private:
	void	AddVertex(const float32 x, const float32 y, const float32 z, const float32 s, const float32 t, const uint32 uSide){
		CVertex2 vert(x, y, z, s, t);

		this->m_quad[this->m_quadIdx] = vert;
		this->m_quadIdx++;
		if(this->m_quadIdx == 4){
			if(uSide == 0){
				this->AddTriangle(this->m_quad[0], this->m_quad[2], this->m_quad[1]);
				this->AddTriangle(this->m_quad[0], this->m_quad[3], this->m_quad[2]);
			}
			else{
				this->AddTriangle(this->m_quad[0], this->m_quad[1], this->m_quad[2]);
				this->AddTriangle(this->m_quad[0], this->m_quad[2], this->m_quad[3]);
			}

			this->m_quadIdx = 0;
		}
	}

	void	AddTriangle(const CVertex2& v1, const CVertex2& v2, const CVertex2& v3){
		this->AddVertex(v1);
		this->AddVertex(v2);
		this->AddVertex(v3);
	}

	void	AddVertex(const CVertex2& vert){
		uint32 uIndex = 0;

		if(CB::Collection::TryFind(this->verts, CVertex2::CompareVertex, vert, uIndex)){
			indices.Add((uint16)uIndex);
		}
		else{
			uIndex = verts.GetLength();
			this->verts.Add(vert);
			this->indices.Add(uIndex);
		}
	}
};

namespace GraphicTest{
	CCubeModel::CCubeModel(CB::CRefPtr<CB::Graphic::IDevice> pDevice, const CB::Math::CVector3D& vSize, const CVertexShaderConfig& config) :
		m_vSize(vSize),
		m_fValue(0.0f)
	{
		auto vHalf = vSize / 2.0f;

		if(config.CheckFlag(VSCFlags::Vertex) && config.CheckFlag(VSCFlags::TCoord) && config.CheckFlag(VSCFlags::Normal)){

		}
		else if(config.CheckFlag(VSCFlags::Vertex) && config.CheckFlag(VSCFlags::TCoord)){
			CCubeBuilder2 mesh;

			mesh.Build(vHalf);

			CB::Collection::CList<CB::Graphic::CVertexElement> vertEls;

			vertEls.Add(CB::Graphic::CVertexElement(0, config.strVertexName, CB::Graphic::VertexType::Float, 3, 0));
			vertEls.Add(CB::Graphic::CVertexElement(0, config.strTCoordName, CB::Graphic::VertexType::Float, 2, sizeof(CB::Math::CVector3D)));

			this->pVertexDecl = pDevice->CreateVertexDeclaration(config.pVertexShader, vertEls);

			this->m_uNumberOfPolygons = mesh.indices.GetLength() / 3;
			
			this->pBuffer = pDevice->CreateBuffer(CB::Graphic::BufferType::Vertex, CB::Graphic::BufferUsage::Static, CB::Graphic::BufferAccess::Write, mesh.verts);
			this->pIndices = pDevice->CreateBuffer(CB::Graphic::BufferType::Index, CB::Graphic::BufferUsage::Static, CB::Graphic::BufferAccess::Write, mesh.indices);
		}
		else if(config.CheckFlag(VSCFlags::Vertex)){

		}

		this->mModelMatrix = CB::Math::CMatrix::GetIdentity();
	}

	void	CCubeModel::Update(const float32 fTimeDelta){
		//this->m_fValue += 30.0f * fTimeDelta;
		this->mModelMatrix = CB::Math::CMatrix::GetRotation(CB::Math::AxisOrientation::AxisY, this->m_fValue);
	}

	void	CCubeModel::Render(CB::CRefPtr<CB::Graphic::IDevice> pDevice){
		pDevice->RenderIndexed(this->m_uNumberOfPolygons, 0, 0);
	}
}