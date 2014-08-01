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
		class CVector4D;
		class CPoint3D;

		class COMMON_API CVector3D{
		public:
			float32 X;
			float32 Y;
			float32	Z;

			CVector3D();
			CVector3D(const CVector3D& Vector);
			CVector3D(const float32 fValue);
			CVector3D(const float32 fX, const float32 fY);
			CVector3D(const float32 fX, const float32 fY, const float32 fZ);
			explicit CVector3D(const CPoint3D& Point);
			explicit CVector3D(const CVector2D& Vector);
			explicit CVector3D(const CVector2D& Vector, const float32 fZ);
			explicit CVector3D(const CVector4D& Vector);
			explicit CVector3D(const Collection::ICountable<float32>& array);

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

			operator const Collection::CArray<float32, 3>() const;
		};

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