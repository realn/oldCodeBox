#pragma once

#include "Types.h"
#include "CBString.h"

#pragma pack(1)

namespace CB{
	namespace Math{
		class COMMON_API CPoint{
		public:
			int32	X;
			int32	Y;

			CPoint();
			CPoint(const CPoint& Point);
			CPoint(const int32 iValue);
			CPoint(const int32 iX, const int32 iY);

			void		SetZero();
			void		Set(const CPoint& Point);
			void		Set(const int32 iValue);
			void		Set(const int32 iX, const int32 iY);

			const bool	IsZero() const;
			const bool	IsPartialZero() const;
			const bool	IsEqual(const CPoint& Point) const;

			const CPoint	Add(const CPoint& Point) const;
			const CPoint	Sub(const CPoint& Point) const;
			const CPoint	Mul(const CPoint& Point) const;
			const CPoint	Div(const CPoint& Point) const;
			const CPoint	Mod(const CPoint& Point) const;

			const CPoint	Mul(const int32 iValue) const;
			const CPoint	Div(const int32 iValue) const;
			const CPoint	Mod(const int32 iValue) const;

			const CString	ToString() const;

			const CPoint&	operator=(const CPoint& Point);

			const CPoint	operator+() const;
			const CPoint	operator-()	const;

			const CPoint	operator+(const CPoint& Point) const;
			const CPoint	operator-(const CPoint& Point) const;
			const CPoint	operator*(const CPoint& Point) const;
			const CPoint	operator/(const CPoint& Point) const;
			const CPoint	operator%(const CPoint& Point) const;

			const CPoint	operator*(const int32 iValue) const;
			const CPoint	operator/(const int32 iValue) const;
			const CPoint	operator%(const int32 iValue) const;

			const CPoint&	operator+=(const CPoint& Point);
			const CPoint&	operator-=(const CPoint& Point);
			const CPoint&	operator*=(const CPoint& Point);
			const CPoint&	operator/=(const CPoint& Point);
			const CPoint&	operator%=(const CPoint& Point);

			const CPoint&	operator*=(const int32 iValue);
			const CPoint&	operator/=(const int32 iValue);
			const CPoint&	operator%=(const int32 iValue);

			const bool	operator==(const CPoint& Point) const;
			const bool	operator!=(const CPoint& Point) const;

			const int32&	operator[](const uint32 uIndex) const;
			int32&			operator[](const uint32 uIndex);
		};

		class COMMON_API CPoint3D : 
			public CPoint
		{
		public:
			int32	Z;

			CPoint3D();
			CPoint3D(const CPoint3D& Point);
			CPoint3D(const CPoint& Point);
			CPoint3D(const CPoint& Point, const int32 Z);
			CPoint3D(const int32 iValue);
			CPoint3D(const int32 iX, const int32 iY);
			CPoint3D(const int32 iX, const int32 iY, const int32 iZ);

			void		SetZero();
			void		Set(const CPoint3D& Point);
			void		Set(const CPoint& Point);
			void		Set(const CPoint& Point, const int32 iZ);
			void		Set(const int32 iValue);
			void		Set(const int32 iX, const int32 iY);
			void		Set(const int32 iX, const int32 iY, const int32 iZ);

			const bool	IsZero() const;
			const bool	IsPartialZero() const;
			const bool	IsEqual(const CPoint3D& Point) const;

			const CPoint3D	Add(const CPoint3D& Point) const;
			const CPoint3D	Sub(const CPoint3D& Point) const;
			const CPoint3D	Mul(const CPoint3D& Point) const;
			const CPoint3D	Div(const CPoint3D& Point) const;
			const CPoint3D	Mod(const CPoint3D& Point) const;

			const CPoint3D	Mul(const int32 iValue) const;
			const CPoint3D	Div(const int32 iValue) const;
			const CPoint3D	Mod(const int32 iValue) const;

			const CString	ToString() const;

			const CPoint3D& operator=(const CPoint3D& Point);

			const CPoint3D	operator+() const;
			const CPoint3D	operator-() const;

			const CPoint3D	operator+(const CPoint3D& Point) const;
			const CPoint3D	operator-(const CPoint3D& Point) const;
			const CPoint3D	operator*(const CPoint3D& Point) const;
			const CPoint3D	operator/(const CPoint3D& Point) const;
			const CPoint3D	operator%(const CPoint3D& Point) const;

			const CPoint3D	operator*(const int32 iValue) const;
			const CPoint3D	operator/(const int32 iValue) const;
			const CPoint3D	operator%(const int32 iValue) const;

			const CPoint3D&	operator+=(const CPoint3D& Point);
			const CPoint3D&	operator-=(const CPoint3D& Point);
			const CPoint3D&	operator*=(const CPoint3D& Point);
			const CPoint3D&	operator/=(const CPoint3D& Point);
			const CPoint3D&	operator%=(const CPoint3D& Point);

			const CPoint3D&	operator*=(const int32 iValue);
			const CPoint3D&	operator/=(const int32 iValue);
			const CPoint3D&	operator%=(const int32 iValue);

			const bool	operator==(const CPoint3D& Point) const;
			const bool	operator!=(const CPoint3D& Point) const;

			const int32&	operator[](const uint32 uIndex) const;
			int32&			operator[](const uint32 uIndex);
		};
	}
}

#pragma pack()