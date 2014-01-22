#include "../Include/Tools_Mesh.h"

namespace CB{
	namespace Tools{
		CMeshRawIVT::CMeshRawIVT() :
			uNumberOfPolygons(0)
		{}

		CMeshRawIVT::CMeshRawIVT(const CMeshRawIVT& Mesh) : 
			Vertices(Mesh.Vertices),
			TexCoords(Mesh.TexCoords),
			Indices(Mesh.Indices),
			uNumberOfPolygons(Mesh.uNumberOfPolygons)
		{
		}

		const bool	CMeshRawIVT::FindVertex(const Math::CVector3D& vPosition, const Math::CVector2D& vTexCoord, uint16& uOutIndex) const{
			for(uint16 i = 0; i < this->Vertices.GetLength() && i < this->TexCoords.GetLength(); i++){
				if(this->Vertices[i] == vPosition && this->TexCoords[i] == vTexCoord){
					uOutIndex = i;
					return true;
				}
			}
			return false;
		}

		void	CMeshRawIVT::AddVertex(const Math::CVector3D& vPosition, const Math::CVector2D& vTexCoord){
			uint16 uIndex = 0;
			if(!this->FindVertex(vPosition, vTexCoord, uIndex)){
				uIndex = (uint16)this->Vertices.GetLength();
				this->Vertices.Add(vPosition);
				this->TexCoords.Add(vTexCoord);
			}
			this->Indices.Add(uIndex);
		}

		void	CMeshRawIVT::Clear(){
			this->Vertices.Clear();
			this->TexCoords.Clear();
			this->Indices.Clear();
			this->uNumberOfPolygons = 0;
		}
	}
}