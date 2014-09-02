#pragma once

#include "Macros.h"
#include "Types.h"
#include "Math_Vector3D.h"

namespace CB{
	namespace Math{
		class CMatrix4D;

		class CMatrix3D {
		public:
			CVector3D	Row1;
			CVector3D	Row2;
			CVector3D	Row3;

			CMatrix3D();
			CMatrix3D(const CMatrix3D& matrix);
			CMatrix3D(const CVector3D& row1, const CVector3D& row2, const CVector3D& row3);
			CMatrix3D(
				const float32 m11, const float32 m12, const float32 m13, 
				const float32 m21, const float32 m22, const float32 m23, 
				const float32 m31, const float32 m32, const float32 m33
				);
			explicit CMatrix3D(const float32 value);
			explicit CMatrix3D(const CMatrix4D& matrix);
			explicit CMatrix3D(const Collection::ICountable<CVector3D>& array);
			explicit CMatrix3D(const Collection::ICountable<float32>& array);

			void	Set(const CMatrix3D& matrix);
			void	Set(const CVector3D& row1, const CVector3D& row2, const CVector3D& row3);

			const CVector3D	Transform(const CVector3D& vector) const;
			const float32	Determinant() const;

			const CVector3D& Get(const uint32 uIndex) const;
			CVector3D&		Get(const uint32 uIndex);
			const CVector3D	GetColumn(const uint32 uIndex) const;
			
			const float32*	GetPointer() const;
			float32*		GetPointer();

			const uint32	GetSize() const;
			const uint32	GetSizeInBytes() const;

			const CMatrix3D	Add(const CMatrix3D& matrix) const;
			const CMatrix3D Sub(const CMatrix3D& matrix) const;
			const CMatrix3D Mul(const CMatrix3D& matrix) const;

			const CMatrix3D Add(const float32 value) const;
			const CMatrix3D Sub(const float32 value) const;
			const CMatrix3D Mul(const float32 value) const;
			const CMatrix3D Div(const float32 value) const;

			const bool	IsEqual(const CMatrix3D& matrix) const;

			const CMatrix3D&	operator=(const CMatrix3D& matrix);

			const CMatrix3D	operator+() const;
			const CMatrix3D operator-() const;
			
			const CMatrix3D	operator+(const CMatrix3D& matrix) const;
			const CMatrix3D operator-(const CMatrix3D& matrix) const;
			const CMatrix3D operator*(const CMatrix3D& matrix) const;

			const CVector3D operator*(const CVector3D& vector) const;

			const CMatrix3D operator+(const float32 value) const;
			const CMatrix3D operator-(const float32 value) const;
			const CMatrix3D operator*(const float32 value) const;
			const CMatrix3D operator/(const float32 value) const;

			const CMatrix3D&	operator+=(const CMatrix3D& matrix);
			const CMatrix3D&	operator-=(const CMatrix3D& matrix);
			const CMatrix3D&	operator*=(const CMatrix3D& matrix);

			const CMatrix3D&	operator+=(const float32 value);
			const CMatrix3D&	operator-=(const float32 value);
			const CMatrix3D&	operator*=(const float32 value);
			const CMatrix3D&	operator/=(const float32 value);

			const bool	operator==(const CMatrix3D& matrix) const;
			const bool	operator!=(const CMatrix3D& matrix) const;

			const CVector3D&	operator[](const uint32 uIndex) const;
			CVector3D&			operator[](const uint32 uIndex);

			const CString	ToString() const;
			const Collection::CArray<float32, 9>	ToArray() const;

			static const CMatrix3D	Identity();
			static const CMatrix3D	Transpose( const CMatrix3D& matrix );
			static const CMatrix3D	Inverse( const CMatrix3D& matrix );
			static const CMatrix3D	Rotation( const CVector3D& vector, const float32 radAngle );
		};
	}
}