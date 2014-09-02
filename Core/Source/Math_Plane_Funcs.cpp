#include "stdafx.h"
#include "../Include/Math_Plane.h"

namespace CB{
	namespace Math{
		const CPlane	ComputePlane( const CVector3D& v1, const CVector3D& v2, const CVector3D& v3 ) {
			const CVector3D normal = ComputeNormal( v1, v2, v3 );
			return CPlane( normal, v3 );
		}

		const CPlane	ComputeEdgePlane( const CVector3D& edgeV1, const CVector3D& edgeV2, const CVector3D& surfacePoint ) {
			const CVector3D edgeVector = edgeV2 - edgeV1;
			const CVector3D surfVector = edgeV2 - surfacePoint;
			const CVector3D surfNormal = edgeVector.Cross( surfVector );
			const CVector3D edgeNormal = surfNormal.Cross( edgeVector ).Normalize();

			return CPlane( edgeNormal, edgeV1 );
		}
	}
}