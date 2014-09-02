#pragma once

#include "Macros.h"
#include "Types.h"
#include "Math_Vector4D.h"

namespace CB{
	class CString;

	namespace Math{
		class CMatrix3D;

		class COMMON_API CMatrix4D{
		public:
			CVector4D	Row1;
			CVector4D	Row2;
			CVector4D	Row3;
			CVector4D	Row4;

			CMatrix4D();
			CMatrix4D(const CMatrix4D& Matrix);
			CMatrix4D(const CVector4D& vRow1, const CVector4D& vRow2, const CVector4D& vRow3, const CVector4D& vRow4);
			CMatrix4D(
				const float32 m11, const float32 m12, const float32 m13, const float32 m14,
				const float32 m21, const float32 m22, const float32 m23, const float32 m24,
				const float32 m31, const float32 m32, const float32 m33, const float32 m34,
				const float32 m41, const float32 m42, const float32 m43, const float32 m44
				);
			explicit CMatrix4D( const float32 value );
			explicit CMatrix4D( const CMatrix3D& matrix );
			explicit CMatrix4D( const CMatrix3D& matrix, const float32 value );
			explicit CMatrix4D( const CMatrix3D& matrix, const CVector4D& trans );
			explicit CMatrix4D( const Collection::ICountable<CVector4D>& array );
			explicit CMatrix4D( const Collection::ICountable<float32>& array );

			void	Set( const CMatrix4D& Matrix );
			void	Set( const CVector4D& vRow1, const CVector4D& vRow2,const CVector4D& vRow3, const CVector4D& vRow4 );

			const float32	Determinant() const;
			const CVector4D	Transform( const CVector4D& vector ) const;
			const CVector3D Transform( const CVector3D& vector ) const;

			const uint32	GetSize() const;
			const uint32	GetSizeInBytes() const;
			const bool		IsEmpty() const;

			const float32*	GetPointer() const;
			float32*		GetPointer();

			const CVector4D&	Get(const uint32 uIndex) const;
			CVector4D&			Get(const uint32 uIndex);
			const CVector4D		GetColumn(const uint32 uIndex) const;
			const CMatrix3D		GetMinor(const uint32 uRow, const uint32 uColumn) const;
			
			const CMatrix4D	Add(const CMatrix4D& Matrix) const;
			const CMatrix4D	Sub(const CMatrix4D& Matrix) const;
			const CMatrix4D	Mul(const CMatrix4D& Matrix) const;

			const CMatrix4D Add(const float32 value) const;
			const CMatrix4D Sub(const float32 value) const;
			const CMatrix4D	Mul(const float32 fValue) const;
			const CMatrix4D	Div(const float32 fValue) const;

			const CMatrix4D&	operator=(const CMatrix4D& Matrix);

			const CMatrix4D	operator+(const CMatrix4D& Matrix) const;
			const CMatrix4D	operator-(const CMatrix4D& Matrix) const;
			const CMatrix4D	operator*(const CMatrix4D& Matrix) const;
			const CMatrix4D operator+(const float32 value) const;
			const CMatrix4D operator-(const float32 value) const;
			const CMatrix4D	operator*(const float32 value) const;
			const CMatrix4D	operator/(const float32 value) const;
			const CVector3D	operator*(const CVector3D& vector) const;
			const CVector4D operator*(const CVector4D& vector) const;

			const CMatrix4D&	operator+=(const CMatrix4D& Matrix);
			const CMatrix4D&	operator-=(const CMatrix4D& Matrix);
			const CMatrix4D&	operator*=(const CMatrix4D& Matrix);
			const CMatrix4D&	operator+=(const float32 value);
			const CMatrix4D&	operator-=(const float32 value);
			const CMatrix4D&	operator*=(const float32 value);
			const CMatrix4D&	operator/=(const float32 value);

			const CVector4D&	operator[](const uint32 uIndex) const;
			CVector4D&			operator[](const uint32 uIndex);

			const CString	ToString() const; 
			const Collection::CArray<float32, 16> ToArray() const;

			static const CMatrix4D Identity();
			static const CMatrix4D Transpose( const CMatrix4D& matrix );
			static const CMatrix4D Inverse( const CMatrix4D& matrix );
			static const CMatrix4D Rotation( const CVector3D& vector, const float radAngle );
			static const CMatrix4D Translation( const CVector3D& pos );
			static const CMatrix4D Ortho( const CVector2D& size );
			static const CMatrix4D Ortho( const CVector2D& size, const float32 zNear, const float32 zFar );
			static const CMatrix4D Ortho( const float32 left, const float32 right, const float32 bottom, const float32 top );
			static const CMatrix4D Ortho( const float32 left, const float32 right, const float32 bottom, const float32 top, const float32 zNear, const float32 zFar );
			static const CMatrix4D Frustrum( const float32 left, const float32 right, const float32 bottom, const float32 top, const float32 zNear, const float32 zFar );
			static const CMatrix4D Perspective( const float32 fov, const float32 aspectRatio, const float32 zNear );
			static const CMatrix4D Perspective( const float32 fov, const float32 aspectRatio, const float32 zNear, const float32 zFar );
		};

		extern const CVector3D	Project( const CVector3D& obj, const CMatrix4D& model, const CMatrix4D& proj, const CVector4D& viewport );
		extern const CVector3D Unproject( const CVector3D& win, const CMatrix4D& model, const CMatrix4D& proj, const CVector4D& viewport );
	}
}