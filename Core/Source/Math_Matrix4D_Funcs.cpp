#include "stdafx.h"
#include "../Include/Math_Matrix4D.h"
#include "../Include/Math_Matrix3D.h"
#include "../Include/Math_Vector2D.h"
#include "../Include/Math_Funcs.h"

namespace CB{
	namespace Math{
		const CMatrix4D	CMatrix4D::Identity(){
			return CMatrix4D( 1.0f );
		}

		const CMatrix4D CMatrix4D::Transpose( const CMatrix4D& matrix ){
			return CMatrix4D(
				matrix.GetColumn(0),
				matrix.GetColumn(1),
				matrix.GetColumn(2),
				matrix.GetColumn(3)
				);
		}

		const CMatrix4D CMatrix4D::Inverse( const CMatrix4D& matrix ){
			float32 det = matrix.Determinant();
			if( det == 0.0f )
				return CMatrix4D( 1.0f );

			CMatrix4D out;
			float32 signY = 1.0f;
			for( uint32 y = 0; y < 4; y++ ){
				float32 signX = 1.0f;
				for( uint32 x = 0; x < 4; x++ ){
					out[y][x] = matrix.GetMinor( y, x ).Determinant() * signY * signX;
					signX = -signX;
				}
				signY = -signY;
			}

			return out / det;
		}

		const CMatrix4D CMatrix4D::Rotation( const CVector3D& vector, const float radAngle ){
			return CMatrix4D( CMatrix3D::Rotation( vector, radAngle ), 1.0f );
		}

		const CMatrix4D Translation( const CVector3D& pos ){
			CMatrix4D out(1.0f);
			out[4] = CVector4D( pos, 1.0f );
			return out;
		}

		const CMatrix4D CMatrix4D::Ortho( const CVector2D& size ){
			return Ortho( size, -1.0f, 1.0f );
		}

		const CMatrix4D CMatrix4D::Ortho( const CVector2D& size, const float32 zNear, const float32 zFar ){
			CVector2D halfSize = size / 1.0f;
			return Ortho( -halfSize.X, halfSize.X, -halfSize.Y, -halfSize.Y, zNear, zFar ); 
		}

		const CMatrix4D CMatrix4D::Ortho( const float32 left, const float32 right, const float32 bottom, const float32 top ) {
			return Ortho( left, right, top, bottom, -1.0f, 1.0f);
		}

		const CMatrix4D CMatrix4D::Ortho( const float32 left, const float32 right, const float32 bottom, const float32 top, const float32 zNear, const float32 zFar ) {
			CMatrix4D result( 1.0f );
			
			result[0][0] = 2.0f / (right - left);
			result[1][1] = 2.0f / (top - bottom);
			result[2][2] = - 2.0f / (zFar - zNear);
			result[0][3] = - (right + left) / (right - left);
			result[1][3] = - (top + bottom) / (top - bottom);
			result[2][3] = - (zFar + zNear) / (zFar - zNear);

			return result;
		}

		const CMatrix4D CMatrix4D::Frustrum( const float32 left, const float32 right, const float32 bottom, const float32 top, const float32 zNear, const float32 zFar ) {
			CMatrix4D	result( 0.0f );

			result[0][0] = (2.0f * zNear) / (right - left);
			result[1][1] = (2.0f * zNear) / (top - bottom);
			result[0][2] = (right + left) / (right - left);
			result[1][2] = (top + bottom) / (top - bottom);
			result[2][2] = -(zFar + zNear) / (zFar - zNear);
			result[3][2] = -1.0f;
			result[2][3] = -(2.0f * zFar * zNear) / (zFar - zNear);

			return result;
		}

		const CMatrix4D CMatrix4D::Perspective( const float32 fov, const float32 aspectRatio, const float32 zNear ) {

			float32 range = Math::Tan(fov / 2.0f) * zNear;	
			float32 left = -range * aspectRatio;
			float32 right = range * aspectRatio;
			float32 bottom = -range;
			float32 top = range;

			CMatrix4D Result( 0.0f );

			Result[0][0] = (2.0f * zNear) / (right - left);
			Result[1][1] = (2.0f * zNear) / (top - bottom);
			Result[2][2] = - 1.0f;
			Result[3][2] = - 1.0f;
			Result[2][3] = - 2.0f * zNear;

			return Result;
		}

		const CMatrix4D CMatrix4D::Perspective( const float32 fov, const float32 aspectRatio, const float32 zNear, const float32 zFar ) {
		
			float32 range = Math::Tan(fov / 2.0f) * zNear;	
			float32 left = -range * aspectRatio;
			float32 right = range * aspectRatio;
			float32 bottom = -range;
			float32 top = range;

			return Frustrum( left, right, bottom, top, zNear, zFar );
		}

		const CVector3D	Project( const CVector3D& obj, const CMatrix4D& model, const CMatrix4D& proj, const CVector4D& viewport ) {
			CVector4D tmp( obj, 1.0f );

			tmp = model * tmp;
			tmp = proj * tmp;

			tmp /= tmp.W;
			tmp = tmp * 0.5f + 0.5f;
			tmp[0] = tmp[0] * viewport[2] + viewport[0];
			tmp[1] = tmp[1] * viewport[3] + viewport[1];

			return CVector3D(tmp);
		}
		const CVector3D Unproject( const CVector3D& win, const CMatrix4D& model, const CMatrix4D& proj, const CVector4D& viewport ) {
			CMatrix4D inverse = CMatrix4D::Inverse( proj * model );
			CVector4D tmp( win, 1.0f );

			tmp.X = (tmp.X - viewport[0]) / viewport[2];
			tmp.Y = (tmp.Y - viewport[1]) / viewport[3];
			tmp = tmp * 2.0f - 1.0f;

			CVector4D obj = inverse * tmp;
			obj /= obj.W;

			return CVector3D(obj);
		}
	}
}