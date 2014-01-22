#include "../Include/GraphicTools.h"

namespace CB{
	namespace Tools{
		CTextMeshGenerator::CTextMeshGenerator(const Collection::ICountable<CFontCharDesc>& CharDescs) :
			m_FontChars(CharDescs),
			cInvalidCharReplace(L'?')
		{
		}

		void	CTextMeshGenerator::Generate(const CString& strText, CMeshRawIVT& OutMesh){
			this->Generate(strText, Math::CVector2D(1.0f), OutMesh);
		}

		void	CTextMeshGenerator::Generate(const CString& strText, const Math::CVector2D& vSize, CMeshRawIVT& OutMesh){
			Math::CVector2D vTextPos;
			for(uint32 i = 0; i < strText.GetLength(); i++){
				const CFontCharDesc& charDesc = this->GetChar(strText[i]);

				if(!charDesc.vSize.IsZero()){
					Math::CRectangleF32 charQuad;

					charQuad.Position = charDesc.vPosCorrection * vSize + vTextPos;
					charQuad.Size = charDesc.vSize * vSize;

					this->AddQuad(charQuad, charDesc.vTexCoord, OutMesh);
				}

				vTextPos += charDesc.vAdvance * vSize;
			}

			OutMesh.uNumberOfPolygons = OutMesh.Indices.GetLength() / 3;
		}

		const CFontCharDesc&	CTextMeshGenerator::GetChar(const wchar uCode) const{
			for(uint32 i = 0; i < this->m_FontChars.GetLength(); i++){
				if(this->m_FontChars[i].cCharacter == uCode){
					return this->m_FontChars[i];
				}
			}
			if(uCode != this->cInvalidCharReplace){
				return this->GetChar(this->cInvalidCharReplace);
			}
			return this->m_FontChars[0];
		}

		void	CTextMeshGenerator::AddQuad(const Math::CRectangleF32& vQuad, const Math::CRectangleF32& vTexCoords, CMeshRawIVT& Mesh){
			Collection::CArray<Math::CVector3D, 4>	v;
			Collection::CArray<Math::CVector2D, 4>	t;

			v[0] = vQuad.Position;
			v[1] = vQuad.Position + Math::CVector2D(vQuad.Size.X, 0.0f);
			v[2] = vQuad.Position + vQuad.Size;
			v[3] = vQuad.Position + Math::CVector2D(0.0f, vQuad.Size.Y);

			t[0] = vTexCoords.Position;
			t[1] = vTexCoords.Position + Math::CVector2D(vTexCoords.Size.X, 0.0f);
			t[2] = vTexCoords.Position + vTexCoords.Size;
			t[3] = vTexCoords.Position + Math::CVector2D(0.0f, vTexCoords.Size.Y);

			Mesh.AddVertex(v[0], t[0]);
			Mesh.AddVertex(v[2], t[2]);
			Mesh.AddVertex(v[1], t[1]);

			Mesh.AddVertex(v[0], t[0]);
			Mesh.AddVertex(v[3], t[3]);
			Mesh.AddVertex(v[2], t[2]);
		}
	}
}