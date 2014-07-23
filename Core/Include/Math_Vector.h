#pragma once

#include "CBString.h"
#include "Math_Point.h"
#include "Math_Size.h"
#include "Collection_Interface.h"
#include "Collection_Array.h"

namespace CB{
	namespace Math{
		class COMMON_API CVector2D{
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

			const float32&	operator[](const uint32 uIndex) const ;
			float32&		operator[](const uint32 uIndex) ;

			operator const Collection::CArray<float32, 2>() const;
		};

		class COMMON_API CVector3D{
		public:
			float32 X;
			float32 Y;
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

			const bool		IsEmpty() const ;
			const uint32	GetLength() const ;
			const uint32	GetSizeInBytes() const ;

			const float32&	Get(const uint32 uIndex) const ;
			float32&		Get(const uint32 uIndex) ;

			const float32*	GetPointer() const ;
			float32*		GetPointer() ;

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
			float32&		operator[](const uint32 uIndex);

			operator const CVector2D() const;
			operator const Collection::CArray<float32, 3>() const;
		};

		class COMMON_API CVector4D{
		public:
			float32 X;
			float32 Y;
			float32 Z;
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

			operator const CVector3D() const;
			operator const Collection::CArray<float32, 4>() const;
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

		//	Vector 3D operations

		extern COMMON_API const bool		Intersect(const CVector3D& vTriA, const CVector3D& vTriB, const CVector3D& vTriC, const CVector3D& vLineStart, const CVector3D& vLineEnd, CVector3D& vOutIntersection);
		extern COMMON_API const bool		IntersectY(const CVector3D& vTriA, const CVector3D& vTriB, const CVector3D& vTriC, CVector3D& vOutIntersection);
		extern COMMON_API void				RotatePoint(const CVector3D& vCenter, const float32 fAngleHorizontal, const float32 fAngleVertical, CVector3D& vPoint);
		extern COMMON_API void				RotatePoint2(const CVector3D& vCenter, const float32 fAngleHorizontal, const float32 fAngleVertical, CVector3D &vPoint);
		//extern COMMON_API const CVector3D	RotateView(const CVector3D& vCenter, const float32 fAngleHorizontal, const float32 fAngleVertival, const float32 fDistance);
		extern COMMON_API const CVector3D	LookAtPoint(const CVector3D& vEye, const float32 fAngleHorizontal, const float32 fAngleVertical, const float32 fLength);
		extern COMMON_API const float32		Distance(const CVector3D& vA, const CVector3D& vB);
		extern COMMON_API const float32		Distance2D(const CVector3D &a, const CVector3D &b);
		extern COMMON_API const float32		Angle(const CVector3D& vU, const CVector3D& vV);
		extern COMMON_API const CVector3D	ComputeNormal(const CVector3D& vTriA, const CVector3D& vTriB, const CVector3D& vTriC);
		extern COMMON_API const CVector3D	Projection(const CVector3D &a, const CVector3D &b, const CVector3D &p);
		extern COMMON_API const float32		DistancePlanPoint(const CVector3D &vTriA, const CVector3D &vTriB, const CVector3D &vTriC, const CVector3D &vPoint);
		extern COMMON_API const bool		IsSamePlane(const CVector3D* pPlan1, const CVector3D* pPlan2);
		extern COMMON_API const CVector3D	SegmentDist(const CVector3D& vA, const CVector3D& vB, const float32 fX);
	}
}