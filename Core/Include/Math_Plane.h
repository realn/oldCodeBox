#pragma once

#include "Macros.h"
#include "Types.h"
#include "Math_Vector3D.h"

namespace CB{
	namespace Math{
		enum class PlaneSide;

		class CPlane{
		public:
			CVector3D	Normal;
			float32		D;

			CPlane();
			CPlane(const CPlane& plane);
			CPlane(const CPlane& plane, const float32	 dist);
			CPlane(const float32 a, const float32 b, const float32 c, const float32 d);
			CPlane(const CVector3D& normal, const float32 dist);
			CPlane(const CVector3D& normal, const CVector3D& point);
			explicit CPlane(const CVector3D& normal);
			explicit CPlane(const CVector4D& plane);
			explicit CPlane(const Collection::ICountable<float32>& array);

			void	Set(const CPlane& plane);
			void	Set(const CVector3D& normal, const float32 dist);
			void	Set(const float32 a, const float32 b, const float32 c, const float32 d);

			const float32	Solve(const CVector3D& point) const;
			const PlaneSide	GetSide( const CVector3D& point ) const;
			const float32	GetDistance( const CVector3D& point) const;

			const bool	IsEqual( const CPlane& plane ) const;
			const bool	IsParallel( const CPlane& plane ) const;

			const CString	ToString() const;

			const CPlane&	operator=(const CPlane& plane);

			const CPlane	operator+() const;
			const CPlane	operator-() const;

			const bool	operator==(const CPlane& plane) const;
			const bool	operator!=(const CPlane& plane) const;

			const Collection::CArray<float32, 4>	ToArray() const;
		};

		extern const CPlane	ComputePlane( const CVector3D& v1, const CVector3D& v2, const CVector3D& v3 );
		extern const CPlane	ComputeEdgePlane( const CVector3D& edgeV1, const CVector3D& edgeV2, const CVector3D& surfacePoint );
	}
}