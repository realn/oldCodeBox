#include "stdafx.h"
#include "../Include/Math_Plane.h"
#include "../Include/Math_Vector4D.h"
#include "../Include/Math_Funcs.h"
#include "../Include/Math_Consts.h"
#include "../Include/Collection_Array.h"
#include "../Include/CBString_Funcs.h"

namespace CB{
	namespace Math{
		CPlane::CPlane() :
			Normal(1.0f, 0.0f, 0.0f),
			D(0.0f)
		{}

		CPlane::CPlane( const CPlane& plane ) :
			Normal( plane.Normal ),
			D( plane.D )
		{}

		CPlane::CPlane( const CPlane& plane, const float32 dist ) :
			Normal( plane.Normal ),
			D( dist )
		{}

		CPlane::CPlane( const float32 a, const float32 b, const float32 c, const float32 d ) :
			Normal( a, b, c ),
			D( d )
		{}

		CPlane::CPlane( const CVector3D& normal, const float32 dist ) :
			Normal(normal),
			D( dist )
		{}

		CPlane::CPlane( const CVector3D& normal, const CVector3D& point ) :
			Normal( normal ),
			D( -normal.Dot( point ) )
		{}

		CPlane::CPlane( const CVector3D& normal ) :
			Normal( normal ),
			D( 0.0f )
		{}

		CPlane::CPlane( const CVector4D& plane ) :
			Normal( plane ),
			D( plane.W )
		{}

		CPlane::CPlane( const Collection::ICountable<float32>& array ) :
			Normal( 1.0f, 0.0f, 0.0f ),
			D( 0.0f )
		{
			if( array.GetLength() >= 4 ){
				Normal.Set( array[0], array[1], array[2] );
				D = array[3];
			}
		}

		void	CPlane::Set( const CPlane& plane ){
			Normal = plane.Normal;
			D = plane.D;
		}

		void	CPlane::Set( const CVector3D& normal, const float32 dist ){
			Normal = normal;
			D = dist;
		}

		void	CPlane::Set( const float32 a, const float32 b, const float32 c, const float32 d ){
			Normal.Set( a, b, c);
			D = d;
		}

		const float32	CPlane::Solve( const CVector3D& point ) const{
			return Normal.Dot( point ) + D;
		}

		const PlaneSide	CPlane::GetSide( const CVector3D& point ) const{
			float32 res = Solve( point );
			if( res > 0.0f )
				return PlaneSide::Front;
			if( res < 0.0f )
				return PlaneSide::Back;

			return PlaneSide::OnPlane;
		}

		const float32	CPlane::GetDistance( const CVector3D& point ) const{
			return Math::Absolute( Solve( point ) );
		}

		const bool	CPlane::IsEqual( const CPlane& plane ) const{
			return 
				( Normal == plane.Normal && D == plane.D ) ||
				( Normal == -plane.Normal && D == -plane.D );
		}

		const bool	CPlane::IsParallel( const CPlane& plane ) const{
			return Normal == plane.Normal || Normal == -plane.Normal;
		}

		const CString	CPlane::ToString() const {
			return L"Normal: (" + Normal.ToString() + L"), D: " + String::ToString( D );
		}

		const CPlane&	CPlane::operator=( const CPlane& plane ) {
			this->Set( plane );
			return *this;
		}

		const CPlane	CPlane::operator+() const{
			return *this;
		}

		const CPlane	CPlane::operator-()	const{
			return CPlane( -Normal, -D );
		}

		const bool	CPlane::operator==(const CPlane& plane) const{
			return this->IsEqual( plane );
		}

		const bool	CPlane::operator!=(const CPlane& plane) const{
			return !this->IsEqual( plane );
		}

		const Collection::CArray<float32, 4>	CPlane::ToArray() const{
			return Collection::CArray<float32, 4>( Normal.GetPointer(), 4 );
		}
	}
}