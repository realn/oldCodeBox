#include "../Include/Tools_Mesh.h"

namespace CB{
	namespace Tools{
		CMeshRawIVTN::CMeshRawIVTN() :
			uNumberOfPolygons(0)
		{}

		CMeshRawIVTN::CMeshRawIVTN(const CMeshRawIVTN& Mesh) :
			Vertices(Mesh.Vertices),
			TexCoords(Mesh.TexCoords),
			Normals(Mesh.Normals),
			Indices(Mesh.Indices),
			uNumberOfPolygons(Mesh.uNumberOfPolygons)
		{}

		void		CMeshRawIVTN::Clear(){
			this->Vertices.Clear();
			this->TexCoords.Clear();
			this->Normals.Clear();
			this->Indices.Clear();
			this->uNumberOfPolygons = 0;
		}

		const bool	CMeshRawIVTN::FindVertex(const Math::CVector3D& vPos, const Math::CVector2D& vTexCoord, const Math::CVector3D& vNormal, uint16& uOutIndex) const{
			for(uint16 i = 0; i < this->Vertices.GetLength(); i++){
				if(this->Vertices[i] == vPos && this->TexCoords[i] == vTexCoord && this->Normals[i] == vNormal){
					uOutIndex = i;
					return true;
				}
			}
			return false;
		}
		void		CMeshRawIVTN::AddVertex(const Math::CVector3D& vPos, const Math::CVector2D& vTexCoord, const Math::CVector3D& vNormal){
			uint16 uIndex = 0;
			if(!this->FindVertex(vPos, vTexCoord, vNormal, uIndex)){
				uIndex = (uint16)this->Vertices.GetLength();
				this->Vertices.Add(vPos);
				this->TexCoords.Add(vTexCoord);
				this->Normals.Add(vNormal);
			}
			this->Indices.Add(uIndex);
		}
	}
}