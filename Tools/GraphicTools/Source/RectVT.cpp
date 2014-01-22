#include "../Include/GraphicTools.h"

namespace CB{
	namespace Tools{
		CRectVT::CRectVT(CRefPtr<Graphic::IDevice> pDevice, const Math::CVector2D& vSize, CRefPtr<Graphic::IShader> pVertexShader, const CString& strVertexName, const CString& strTexCoordName){
			{
				Collection::CList<Graphic::CVertexElement> elems;

				elems.Add(Graphic::CVertexElement(0, strVertexName, 0, Graphic::VertexType::Float, 3));
				elems.Add(Graphic::CVertexElement(0, strTexCoordName, sizeof(Math::CVector3D), Graphic::VertexType::Float, 2));

				this->m_pVertexDeclaration = pDevice->CreateVertexDeclaration(pVertexShader, elems);
			}

			class CVert{
			public:
				Math::CVector3D	vPosition;
				Math::CVector2D	vTexCoord;
			};

			Collection::CArray<CVert, 4>	verts;

			auto vHalfSize = vSize / 2.0f;

			verts[0].vPosition.Set(-vHalfSize.X, -vHalfSize.Y, 0.0f);
			verts[1].vPosition.Set(vHalfSize.X, -vHalfSize.Y, 0.0f);
			verts[2].vPosition.Set(vHalfSize.X, vHalfSize.Y, 0.0f);
			verts[3].vPosition.Set(-vHalfSize.X, vHalfSize.Y, 0.0f);

			verts[0].vTexCoord.Set(0.0f, 0.0f);
			verts[1].vTexCoord.Set(1.0f, 0.0f);
			verts[2].vTexCoord.Set(1.0f, 1.0f);
			verts[3].vTexCoord.Set(0.0f, 1.0f);

			Collection::CArray<uint16, 6>	indices;

			indices[0] = 0;
			indices[1] = 2;
			indices[2] = 3;
			indices[3] = 0;
			indices[4] = 1;
			indices[5] = 2;

			this->m_pVertexBuffer = pDevice->CreateBuffer(Graphic::BufferType::Vertex, Graphic::BufferUsage::Static, Graphic::BufferAccess::Write, verts);
			this->m_pIndexBuffer = pDevice->CreateBuffer(Graphic::BufferType::Index, Graphic::BufferUsage::Static, Graphic::BufferAccess::Write, indices);
			this->m_uNumberOfPolygons = indices.GetLength() / 3;
		}

		CRefPtr<Graphic::IVertexDeclaration>	CRectVT::GetDeclaration() const{
			return this->m_pVertexDeclaration;
		}

		CRefPtr<Graphic::IBuffer>	CRectVT::GetVertexBuffer() const{
			return this->m_pVertexBuffer;
		}

		CRefPtr<Graphic::IBuffer>	CRectVT::GetIndexBuffer() const{
			return this->m_pIndexBuffer;
		}

		const uint32	CRectVT::GetNumberOfPolygons() const{
			return this->m_uNumberOfPolygons;
		}
	}
}