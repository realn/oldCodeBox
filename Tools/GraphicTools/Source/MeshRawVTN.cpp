#include "../Include/Tools_Mesh.h"

namespace CB{
	namespace Tools{
		CMeshRawVTN::CMeshRawVTN() :
			uNumberOfPolygons(0)
		{}

		CMeshRawVTN::CMeshRawVTN(const CMeshRawVTN& Mesh) :
			Vertices(Mesh.Vertices),
			TexCoords(Mesh.TexCoords),
			Normals(Mesh.Normals),
			uNumberOfPolygons(Mesh.uNumberOfPolygons)
		{}

		void	CMeshRawVTN::AddVertex(const Math::CVector3D& vPosition, const Math::CVector2D& vTexCoord, const Math::CVector3D& vNormal){
			this->Vertices.Add(vPosition);
			this->TexCoords.Add(vTexCoord);
			this->Normals.Add(vNormal);
		}
	}
}