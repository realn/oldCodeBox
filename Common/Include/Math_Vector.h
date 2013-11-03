#pragma once

#include "CBString.h"
#include "Math_Point.h"
#include "Math_Size.h"
#include "Collection_Interface.h"

namespace CB{
	namespace Math{
		class COMMON_API CVector2D :
			public Collection::ICountable<float32>,
			public Collection::IPacked<float32>
		{
		public:
			float32	X;
			float32	Y;

			CVector2D();
			CVector2D(const CVector2D& Vector);
			CVector2D(const CPoint& Point);
			CVector2D(const float32 fValue);
			CVector2D(const float32 fX, const float32 fY);

			void	SetZero();
			void	Set(const CVector2D& Vector);
			void	Set(const float32 fValue);
			void	Set(const float32 fX, const float32 fY);

			const bool	IsZero() const;
			const bool	IsPartialZero() const;
			const bool	IsNearZero() const;
			const bool	IsEqual(const CVector2D& Vector) const;
			const bool	IsNearEqual(const CVector2D& Vector) const;

			const bool		IsEmpty() const override;
			const uint32	GetLength() const override;
			const uint32	GetSizeInBytes() const override;

			const float32&	Get(const uint32 uIndex) const override;
			float32&		Get(const uint32 uIndex) override;

			const float32*	GetPointer() const override;
			float32*		GetPointer() override;

			const float32	GetVectorLength() const;
			const float32	GetVectorLengthSq() const;

			const CVector2D	GetNormalized() const;
			void			Normalize();

			const CVector2D	Add(const CVector2D& Vector) const;
			const CVector2D	Sub(const CVector2D& Vector) const;
			const CVector2D	Mul(const CVector2D& Vector) const;
			const CVector2D	Div(const CVector2D& Vector) const;

			const CVector2D	Mul(const float32 fValue) const;
			const CVector2D	Div(const float32 fValue) const;

			const float32		Dot(const CVector2D& Vector) const;

			const CString		ToString() const;
			const CPoint		ToPoint() const;

			const CVector2D&	operator=(const CVector2D& Vector);

			const CVector2D operator+() const;
			const CVector2D operator-() const;

			const CVector2D	operator+(const CVector2D& Vector) const;
			const CVector2D	operator-(const CVector2D& Vector) const;
			const CVector2D	operator*(const CVector2D& Vector) const;
			const CVector2D	operator/(const CVector2D& Vector) const;

			const CVector2D	operator*(const float32 fValue) const;
			const CVector2D	operator/(const float32 fValue) const;

			const CVector2D&	operator+=(const CVector2D& Vector);
			const CVector2D&	operator-=(const CVector2D& Vector);
			const CVector2D&	operator*=(const CVector2D& Vector);
			const CVector2D&	operator/=(const CVector2D& Vector);

			const CVector2D&	operator*=(const float32 fValue);
			const CVector2D&	operator/=(const float32 fValue);

			const bool	operator==(const CVector2D& Vector) const;
			const bool	operator!=(const CVector2D& Vector) const;

			const float32&	operator[](const uint32 uIndex) const;
			float32&			operator[](const uint32 uIndex);
		};

		class COMMON_API CVector3D : 
			public CVector2D
		{
		public:
			float32	Z;

			CVector3D();
			CVector3D(const CVector3D& Vector);
			CVector3D(const CVector2D& Vector);
			CVector3D(const CVector2D& Vector, const float32 fZ);
			CVector3D(const CPoint3D& Point);
			CVector3D(const float32 fValue);
			CVector3D(const float32 fX, const float32 fY);
			CVector3D(const float32 fX, const float32 fY, const float32 fZ);

			void		SetZero();
			void		Set(const CVector3D& Vector);
			void		Set(const float32 fValue);
			void		Set(const float32 fX, const float32 fY);
			void		Set(const float32 fX, const float32 fY, const float32 fZ);

			const bool	IsZero() const;
			const bool	IsPartialZero() const;
			const bool	IsNearZero() const;
			const bool	IsEqual(const CVector3D& Vector) const;
			const bool	IsNearEqual(const CVector3D& Vector) const;

			const bool		IsEmpty() const override;
			const uint32	GetLength() const override;
			const uint32	GetSizeInBytes() const override;

			const float32&	Get(const uint32 uIndex) const override;
			float32&		Get(const uint32 uIndex) override;

			const float32*	GetPointer() const override;
			float32*		GetPointer() override;

			const float32	GetVectorLength() const;
			const float32	GetVectorLengthSq() const;

			const CVector3D	GetNormalized() const;
			void			Normalize();

			const CVector3D	Add(const CVector3D& Vector) const;
			const CVector3D	Sub(const CVector3D& Vector) const;
			const CVector3D	Mul(const CVector3D& Vector) const;
			const CVector3D	Div(const CVector3D& Vector) const;

			const CVector3D	Mul(const float32 fValue) const;
			const CVector3D	Div(const float32 fValue) const;

			const float32		Dot(const CVector3D& Vector) const;
			const CVector3D	Cross(const CVector3D& Vector) const;

			const CString		ToString() const;
			const CPoint3D		ToPoint() const;

			const CVector3D&	operator=(const CVector3D& Vector);

			const CVector3D operator+() const;
			const CVector3D operator-() const;

			const CVector3D	operator+(const CVector3D& Vector) const;
			const CVector3D	operator-(const CVector3D& Vector) const;
			const CVector3D	operator*(const CVector3D& Vector) const;
			const CVector3D	operator/(const CVector3D& Vector) const;

			const CVector3D	operator*(const float32 fValue) const;
			const CVector3D	operator/(const float32 fValue) const;

			const CVector3D&	operator+=(const CVector3D& Vector);
			const CVector3D&	operator-=(const CVector3D& Vector);
			const CVector3D&	operator*=(const CVector3D& Vector);
			const CVector3D&	operator/=(const CVector3D& Vector);

			const CVector3D&	operator*=(const float32 fValue);
			const CVector3D&	operator/=(const float32 fValue);

			const bool	operator==(const CVector3D& Vector) const;
			const bool	operator!=(const CVector3D& Vector) const;

			const float32&	operator[](const uint32 uIndex) const;
			float32&			operator[](const uint32 uIndex);
		};

		class COMMON_API CVector4D : 
			public CVector3D
		{
		public:
			float32	W;

			CVector4D();
			CVector4D(const CVector4D& Vector);
			CVector4D(const CVector3D& Vector);
			CVector4D(const CVector3D& Vector, const float32 fW);
			CVector4D(const CVector2D& Vector);
			CVector4D(const CVector2D& Vector, const float32 fZ);
			CVector4D(const CVector2D& Vector, const float32 fZ, const float32 fW);
			CVector4D(const CPoint3D& Point);
			CVector4D(const CPoint3D& Point, const float32 fW);
			CVector4D(const float32 fValue);
			CVector4D(const float32 fValue, const float32 fW);
			CVector4D(const float32 fX, const float32 fY, const float32 fZ);
			CVector4D(const float32 fX, const float32 fY, const float32 fZ, const float32 fW);

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

			const bool		IsEmpty() const override;
			const uint32	GetLength() const override;
			const uint32	GetSizeInBytes() const override;

			const float32&	Get(const uint32 uIndex) const override;
			float32&		Get(const uint32 uIndex) override;

			const float32*	GetPointer() const override;
			float32*		GetPointer() override;

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
			float32&			operator[](const uint32 uIndex);
		};
	}
}