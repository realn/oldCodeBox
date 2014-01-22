#include "../Include/Tools_Mesh.h"
#include <Collection_Funcs.h>

namespace CB{
	namespace Tools{
		CMeshRawIV::CMeshRawIV() : 
			uNumberOfPolygons(0)
		{}

		CMeshRawIV::CMeshRawIV(const CMeshRawIV& Mesh) :
			Vertices(Mesh.Vertices),
			Indices(Mesh.Indices),
			uNumberOfPolygons(0)
		{}

		void	CMeshRawIV::Clear(){
			this->Vertices.Clear();
			this->Indices.Clear();
			this->uNumberOfPolygons = 0;
		}

		const bool	CMeshRawIV::FindVertex(const Math::CVector3D& vPosition, uint16& uOutIndex) const{
			uint32 uIndex = 0;
			if(Collection::TryFind(this->Vertices, vPosition, uIndex)){
				uOutIndex = (uint16)uIndex;
				return true;
			}
			return false;
		}

		void	CMeshRawIV::AddVertex(const Math::CVector3D& vPosition){
			uint16 uIndex = 0;
			if(!this->FindVertex(vPosition, uIndex)){
				uIndex = (uint16)this->Vertices.GetLength();
				this->Vertices.Add(vPosition);
			}
			this->Indices.Add(uIndex);
		}
	}
}