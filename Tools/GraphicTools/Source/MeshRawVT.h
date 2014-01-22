#include "../Include/Tools_Mesh.h"

namespace CB{
	namespace Tools{
		CMeshRawVT::CMeshRawVT() :
			uNumberOfPolygons(0)
		{}

		CMeshRawVT::CMeshRawVT(const CMeshRawVT& Mesh) :
			Vertices(Mesh.Vertices),
			TexCoords(Mesh.TexCoords),
			uNumberOfPolygons(Mesh.uNumberOfPolygons)
		{}

		void	CMeshRawVT::AddVertex(const Math::CVector3D& vPosition, const Math::CVector2D& vTexCoord){
			this->Vertices.Add(vPosition);
			this->TexCoords.Add(vTexCoord);
		}
	}
}