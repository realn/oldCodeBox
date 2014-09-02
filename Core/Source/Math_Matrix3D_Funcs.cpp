#include "stdafx.h"
#include "../Include/Math_Matrix3D.h"
#include "../Include/Math_Funcs.h"

namespace CB{
	namespace Math{
		const CMatrix3D	CMatrix3D::Identity() {
			return CMatrix3D( 1.0f );
		}

		const CMatrix3D	CMatrix3D::Transpose( const CMatrix3D& matrix ){
			return CMatrix3D(
				matrix.GetColumn( 0 ),
				matrix.GetColumn( 1 ),
				matrix.GetColumn( 2 )
				);
		}

		const CMatrix3D	CMatrix3D::Inverse( const CMatrix3D& matrix ){

			float32 Determinant = matrix.Determinant();
			if( Determinant == 0.0f )
				return CMatrix3D( 1.0f );


			float32 S00 = matrix[0][0];
			float32 S01 = matrix[0][1];
			float32 S02 = matrix[0][2];

			float32 S10 = matrix[1][0];
			float32 S11 = matrix[1][1];
			float32 S12 = matrix[1][2];

			float32 S20 = matrix[2][0];
			float32 S21 = matrix[2][1];
			float32 S22 = matrix[2][2];

			CMatrix3D Inverse(
				CVector3D( +(S11 * S22 - S12 * S21), -(S10 * S22 - S12 * S20), +(S10 * S21 - S11 * S20) ),
				CVector3D( -(S01 * S22 - S02 * S21), +(S00 * S22 - S02 * S20), -(S00 * S21 - S01 * S20) ),
				CVector3D( +(S01 * S12 - S02 * S11), -(S00 * S12 - S02 * S10), +(S00 * S11 - S01 * S10) )
				);

			Inverse /= Determinant;
			return Inverse;
		}

		const CMatrix3D	CMatrix3D::Rotation( const CVector3D& vector, const float32 radAngle ){
			float32 c = Math::Cos( radAngle );
			float32 s = Math::Sin( radAngle );

			CVector3D axis = vector.Normalize();

			CVector3D temp = axis * (1.0f - c);

			CMatrix3D Rotate;

			Rotate[0][0] = c + temp[0] * axis[0];
			Rotate[0][1] = 0 + temp[0] * axis[1] + s * axis[2];
			Rotate[0][2] = 0 + temp[0] * axis[2] - s * axis[1];

			Rotate[1][0] = 0 + temp[1] * axis[0] - s * axis[2];
			Rotate[1][1] = c + temp[1] * axis[1];
			Rotate[1][2] = 0 + temp[1] * axis[2] + s * axis[0];

			Rotate[2][0] = 0 + temp[2] * axis[0] + s * axis[1];
			Rotate[2][1] = 0 + temp[2] * axis[1] - s * axis[0];
			Rotate[2][2] = c + temp[2] * axis[2];

			return Rotate;
		}

	}
}