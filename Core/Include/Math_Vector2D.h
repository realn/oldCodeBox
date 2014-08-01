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
		class CVector3D;
		class CVector4D;
		class CPoint2D;

		class COMMON_API CVector2D{
		public:
			float32	X;
			float32	Y;

			CVector2D();
			CVector2D(const CVector2D& Vector);
			CVector2D(const float32 fValue);
			CVector2D(const float32 fX, const float32 fY);
			explicit CVector2D(const CPoint2D& Point);
			explicit CVector2D(const CVector3D& Vector);
			explicit CVector2D(const CVector4D& Vector);
			explicit CVector2D(const Collection::ICountable<float32>& array);

			void	SetZero();
			void	Set(const CVector2D& Vector);
			void	Set(const float32 fValue);
			void	Set(const float32 fX, const float32 fY);

			const bool	IsZero() const;
			const bool	IsPartialZero() const;
			const bool	IsNearZero() const;
			const bool	IsEqual(const CVector2D& Vector) const;
			const bool	IsNearEqual(const CVector2D& Vector) const;

			const bool		IsEmpty() const ;
			const uint32	GetLength() const ;
			const uint32	GetSizeInBytes() const ;

			const float32&	Get(const uint32 uIndex) const ;
			float32&		Get(const uint32 uIndex) ;

			const float32*	GetPointer() const ;
			float32*		GetPointer() ;

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

			const float32&	operator[](const uint32 uIndex) const ;
			float32&		operator[](const uint32 uIndex) ;

			operator const Collection::CArray<float32, 2>() const;
		};

		//	Vector 2D operations

		extern COMMON_API void				Swap(CVector2D& vVecA, CVector2D& vVecB);
		extern COMMON_API const CVector2D	RotatePoint(const CVector2D& vCenter, const float32 fAngle, const CVector2D& vPoint);
		extern COMMON_API const CVector2D	RotatePoint(const float32 fAngle, const CVector2D& vPoint);
		extern COMMON_API const CVector2D	RotatePoint(const float32 fAngle, const float32 fDistance);
		extern COMMON_API const float32		RotateAngle(const CVector2D& vPosition);
		extern COMMON_API const float32		RotateAngle(const float32 fX, const float32 fY);
		extern COMMON_API const float32		RotateAngle(const CVector2D& vCenter, const CVector2D& vPoint1, const CVector2D& vPoint2);
		extern COMMON_API const float32		MidPoint(const CVector2D& vPoint1, const CVector2D& vPoint2, const float32 fPX);
		extern COMMON_API const bool		IsInsideTriangle(const CVector2D& vA, const CVector2D& vB, const CVector2D& vC, const CVector2D& vPoint);
		extern COMMON_API const float32		Distance(const CVector2D& vA, const CVector2D& vB);		
		extern COMMON_API const bool		LineFunction(const CVector2D& vLineStart, const CVector2D& vLineEnd, float32 &fOutA, float32 &fOutB);
		extern COMMON_API const CVector2D	Lerp(const CVector2D& vA, const CVector2D& vB, const float32 fX);
	}
}