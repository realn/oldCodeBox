#include "../Include/Tools_Mesh.h"

namespace CB{
	namespace Tools{
		CMeshRawV::CMeshRawV() :
			uNumberOfPolygons(0)
		{}

		CMeshRawV::CMeshRawV(const CMeshRawV& Mesh) :
			Vertices(Mesh.Vertices),
			uNumberOfPolygons(Mesh.uNumberOfPolygons)
		{}

		void	CMeshRawV::AddVertex(const Math::CVector3D& vPosition){
			this->Vertices.Add(vPosition);
		}
	}
}