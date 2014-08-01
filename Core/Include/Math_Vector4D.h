#pragma once

#include "Macros.h"
#include "Types.h"

namespace CB{
	class CString;

	namespace Collection{
		template<typename _Type, uint32 _Len> class CArray;
		template<typename _Type> class ICountable;
	}

	namespace Math{
		class CVector2D;
		class CVector3D;
		class CPoint3D;

		class COMMON_API CVector4D{
		public:
			float32 X;
			float32 Y;
			float32 Z;
			float32	W;

			CVector4D();
			CVector4D(const CVector4D& Vector);
			CVector4D(const float32 fValue);
			CVector4D(const float32 fValue, const float32 fW);
			CVector4D(const float32 fX, const float32 fY, const float32 fZ);
			CVector4D(const float32 fX, const float32 fY, const float32 fZ, const float32 fW);
			explicit CVector4D(const CPoint3D& Point);
			explicit CVector4D(const CPoint3D& Point, const float32 fW);
			explicit CVector4D(const CVector2D& Vector);
			explicit CVector4D(const CVector2D& Vector, const float32 fZ);
			explicit CVector4D(const CVector2D& Vector, const float32 fZ, const float32 fW);
			explicit CVector4D(const CVector3D& Vector);
			explicit CVector4D(const CVector3D& Vector, const float32 fW);
			explicit CVector4D(const Collection::ICountable<float32>& array);

			void		SetZero();
			void		Set(const CVector4D& Vector);
			void		Set(const float32 fValue);
			void		Set(const float32 fValue, const float32 fW);
			void		Set(const float32 fX, const float32 fY, const float32 fZ);
			void		Set(const float32 fX, const float32 fY, const float32 fZ, const float32 fW);

			const bool	IsZero() const;
			const bool	IsPartialZero() const;
			const bool	IsNearZero() const;
			const bool	IsEqual(const CVector4D& Vector) const;
			const bool	IsNearEqual(const CVector4D& Vector) const;

			const bool		IsEmpty() const ;
			const uint32	GetLength() const ;
			const uint32	GetSizeInBytes() const ;

			const float32&	Get(const uint32 uIndex) const ;
			float32&		Get(const uint32 uIndex) ;

			const float32*	GetPointer() const ;
			float32*		GetPointer() ;

			const float32	GetVectorLength() const;
			const float32	GetVectorLengthSq() const;

			const CVector4D	GetNormalized() const;
			void			Normalize();

			const CVector4D	Add(const CVector4D& Vector) const;
			const CVector4D	Sub(const CVector4D& Vector) const;
			const CVector4D	Mul(const CVector4D& Vector) const;
			const CVector4D	Div(const CVector4D& Vector) const;

			const CVector4D	Mul(const float32 fValue) const;
			const CVector4D	Div(const float32 fValue) const;

			const float32		Dot(const CVector4D& Vector) const;

			const CString		ToString() const;
			const CPoint3D		ToPoint() const;

			const CVector4D&	operator=(const CVector4D& Vector);

			const CVector4D operator+() const;
			const CVector4D operator-() const;

			const CVector4D	operator+(const CVector4D& Vector) const;
			const CVector4D	operator-(const CVector4D& Vector) const;
			const CVector4D	operator*(const CVector4D& Vector) const;
			const CVector4D	operator/(const CVector4D& Vector) const;

			const CVector4D	operator*(const float32 fValue) const;
			const CVector4D	operator/(const float32 fValue) const;

			const CVector4D&	operator+=(const CVector4D& Vector);
			const CVector4D&	operator-=(const CVector4D& Vector);
			const CVector4D&	operator*=(const CVector4D& Vector);
			const CVector4D&	operator/=(const CVector4D& Vector);

			const CVector4D&	operator*=(const float32 fValue);
			const CVector4D&	operator/=(const float32 fValue);

			const bool	operator==(const CVector4D& Vector) const;
			const bool	operator!=(const CVector4D& Vector) const;

			const float32&	operator[](const uint32 uIndex) const;
			float32&		operator[](const uint32 uIndex);

			const Collection::CArray<float32, 4> ToArray() const;
		};
	}
}