#pragma once

#include "CBString.h"
#include "Math_Point.h"
#include "Math_Size.h"

namespace CB{
	namespace Math{
		class COMMON_API CVector2D{
		public:
			float	X;
			float	Y;

			CVector2D();
			CVector2D(const CVector2D& Vector);
			CVector2D(const CPoint& Point);
			CVector2D(const float fValue);
			CVector2D(const float fX, const float fY);

			void		SetZero();
			void		Set(const CVector2D& Vector);
			void		Set(const float fValue);
			void		Set(const float fX, const float fY);

			const bool	IsZero() const;
			const bool	IsPartialZero() const;
			const bool	IsNearZero() const;
			const bool	IsEqual(const CVector2D& Vector) const;
			const bool	IsNearEqual(const CVector2D& Vector) const;

			const float	GetLength() const;
			const float GetLengthSq() const;

			const CVector2D	GetNormalized() const;
			void			Normalize();

			const CVector2D	Add(const CVector2D& Vector) const;
			const CVector2D	Sub(const CVector2D& Vector) const;
			const CVector2D	Mul(const CVector2D& Vector) const;
			const CVector2D	Div(const CVector2D& Vector) const;

			const CVector2D	Mul(const float fValue) const;
			const CVector2D	Div(const float fValue) const;

			const float		Dot(const CVector2D& Vector) const;

			const CString		ToString() const;
			const CPoint		ToPoint() const;
			const float*		ToFloat() const;
			void				ToFloat(float* pFloat) const;

			const CVector2D&	operator=(const CVector2D& Vector);

			const CVector2D operator+() const;
			const CVector2D operator-() const;

			const CVector2D	operator+(const CVector2D& Vector) const;
			const CVector2D	operator-(const CVector2D& Vector) const;
			const CVector2D	operator*(const CVector2D& Vector) const;
			const CVector2D	operator/(const CVector2D& Vector) const;

			const CVector2D	operator*(const float fValue) const;
			const CVector2D	operator/(const float fValue) const;

			const CVector2D&	operator+=(const CVector2D& Vector);
			const CVector2D&	operator-=(const CVector2D& Vector);
			const CVector2D&	operator*=(const CVector2D& Vector);
			const CVector2D&	operator/=(const CVector2D& Vector);

			const CVector2D&	operator*=(const float fValue);
			const CVector2D&	operator/=(const float fValue);

			const bool	operator==(const CVector2D& Vector) const;
			const bool	operator!=(const CVector2D& Vector) const;

			const float&	operator[](const unsigned uIndex) const;
			float&			operator[](const unsigned uIndex);
		};

		class COMMON_API CVector3D : public CVector2D{
		public:
			float	Z;

			CVector3D();
			CVector3D(const CVector3D& Vector);
			CVector3D(const CVector2D& Vector);
			CVector3D(const CVector2D& Vector, const float fZ);
			CVector3D(const CPoint3D& Point);
			CVector3D(const float fValue);
			CVector3D(const float fX, const float fY);
			CVector3D(const float fX, const float fY, const float fZ);

			void		SetZero();
			void		Set(const CVector3D& Vector);
			void		Set(const float fValue);
			void		Set(const float fX, const float fY);
			void		Set(const float fX, const float fY, const float fZ);

			const bool	IsZero() const;
			const bool	IsPartialZero() const;
			const bool	IsNearZero() const;
			const bool	IsEqual(const CVector3D& Vector) const;
			const bool	IsNearEqual(const CVector3D& Vector) const;

			const float	GetLength() const;
			const float GetLengthSq() const;

			const CVector3D	GetNormalized() const;
			void			Normalize();

			const CVector3D	Add(const CVector3D& Vector) const;
			const CVector3D	Sub(const CVector3D& Vector) const;
			const CVector3D	Mul(const CVector3D& Vector) const;
			const CVector3D	Div(const CVector3D& Vector) const;

			const CVector3D	Mul(const float fValue) const;
			const CVector3D	Div(const float fValue) const;

			const float		Dot(const CVector3D& Vector) const;
			const CVector3D	Cross(const CVector3D& Vector) const;

			const CString		ToString() const;
			const CPoint3D		ToPoint() const;
			const float*		ToFloat() const;
			void				ToFloat(float* pFloat) const;

			const CVector3D&	operator=(const CVector3D& Vector);

			const CVector3D operator+() const;
			const CVector3D operator-() const;

			const CVector3D	operator+(const CVector3D& Vector) const;
			const CVector3D	operator-(const CVector3D& Vector) const;
			const CVector3D	operator*(const CVector3D& Vector) const;
			const CVector3D	operator/(const CVector3D& Vector) const;

			const CVector3D	operator*(const float fValue) const;
			const CVector3D	operator/(const float fValue) const;

			const CVector3D&	operator+=(const CVector3D& Vector);
			const CVector3D&	operator-=(const CVector3D& Vector);
			const CVector3D&	operator*=(const CVector3D& Vector);
			const CVector3D&	operator/=(const CVector3D& Vector);

			const CVector3D&	operator*=(const float fValue);
			const CVector3D&	operator/=(const float fValue);

			const bool	operator==(const CVector3D& Vector) const;
			const bool	operator!=(const CVector3D& Vector) const;

			const float&	operator[](const unsigned uIndex) const;
			float&			operator[](const unsigned uIndex);
		};

		class COMMON_API CVector4D : public CVector3D{
		public:
			float	W;

			CVector4D();
			CVector4D(const CVector4D& Vector);
			CVector4D(const CVector3D& Vector);
			CVector4D(const CVector3D& Vector, const float fW);
			CVector4D(const CVector2D& Vector);
			CVector4D(const CVector2D& Vector, const float fZ);
			CVector4D(const CVector2D& Vector, const float fZ, const float fW);
			CVector4D(const CPoint3D& Point);
			CVector4D(const CPoint3D& Point, const float fW);
			CVector4D(const float fValue);
			CVector4D(const float fValue, const float fW);
			CVector4D(const float fX, const float fY, const float fZ);
			CVector4D(const float fX, const float fY, const float fZ, const float fW);

			void		SetZero();
			void		Set(const CVector4D& Vector);
			void		Set(const float fValue);
			void		Set(const float fValue, const float fW);
			void		Set(const float fX, const float fY, const float fZ);
			void		Set(const float fX, const float fY, const float fZ, const float fW);

			const bool	IsZero() const;
			const bool	IsPartialZero() const;
			const bool	IsNearZero() const;
			const bool	IsEqual(const CVector4D& Vector) const;
			const bool	IsNearEqual(const CVector4D& Vector) const;

			const float	GetLength() const;
			const float GetLengthSq() const;

			const CVector4D	GetNormalized() const;
			void			Normalize();

			const CVector4D	Add(const CVector4D& Vector) const;
			const CVector4D	Sub(const CVector4D& Vector) const;
			const CVector4D	Mul(const CVector4D& Vector) const;
			const CVector4D	Div(const CVector4D& Vector) const;

			const CVector4D	Mul(const float fValue) const;
			const CVector4D	Div(const float fValue) const;

			const float		Dot(const CVector4D& Vector) const;

			const CString		ToString() const;
			const CPoint3D		ToPoint() const;
			const float*		ToFloat() const;
			void				ToFloat(float* pFloat) const;

			const CVector4D&	operator=(const CVector4D& Vector);

			const CVector4D operator+() const;
			const CVector4D operator-() const;

			const CVector4D	operator+(const CVector4D& Vector) const;
			const CVector4D	operator-(const CVector4D& Vector) const;
			const CVector4D	operator*(const CVector4D& Vector) const;
			const CVector4D	operator/(const CVector4D& Vector) const;

			const CVector4D	operator*(const float fValue) const;
			const CVector4D	operator/(const float fValue) const;

			const CVector4D&	operator+=(const CVector4D& Vector);
			const CVector4D&	operator-=(const CVector4D& Vector);
			const CVector4D&	operator*=(const CVector4D& Vector);
			const CVector4D&	operator/=(const CVector4D& Vector);

			const CVector4D&	operator*=(const float fValue);
			const CVector4D&	operator/=(const float fValue);

			const bool	operator==(const CVector4D& Vector) const;
			const bool	operator!=(const CVector4D& Vector) const;

			const float&	operator[](const unsigned uIndex) const;
			float&			operator[](const unsigned uIndex);
		};
	}
}