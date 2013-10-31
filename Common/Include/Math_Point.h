#pragma once

#include "../Include/CBString.h"

#pragma pack(1)

namespace CB{
	namespace Math{
		class COMMON_API CPoint{
		public:
			int	X;
			int Y;

			CPoint();
			CPoint(const CPoint& Point);
			CPoint(const int iValue);
			CPoint(const int iX, const int iY);

			void		SetZero();
			void		Set(const CPoint& Point);
			void		Set(const int iValue);
			void		Set(const int iX, const int iY);

			const bool	IsZero() const;
			const bool	IsPartialZero() const;
			const bool	IsEqual(const CPoint& Point) const;

			const CPoint	Add(const CPoint& Point) const;
			const CPoint	Sub(const CPoint& Point) const;
			const CPoint	Mul(const CPoint& Point) const;
			const CPoint	Div(const CPoint& Point) const;
			const CPoint	Mod(const CPoint& Point) const;

			const CPoint	Mul(const int iValue) const;
			const CPoint	Div(const int iValue) const;
			const CPoint	Mod(const int iValue) const;

			const CString	ToString() const;

			const CPoint& operator=(const CPoint& Point);

			const CPoint	operator+() const;
			const CPoint	operator-()	const;

			const CPoint	operator+(const CPoint& Point) const;
			const CPoint	operator-(const CPoint& Point) const;
			const CPoint	operator*(const CPoint& Point) const;
			const CPoint	operator/(const CPoint& Point) const;
			const CPoint	operator%(const CPoint& Point) const;

			const CPoint	operator*(const int iValue) const;
			const CPoint	operator/(const int iValue) const;
			const CPoint	operator%(const int iValue) const;

			const CPoint&	operator+=(const CPoint& Point);
			const CPoint&	operator-=(const CPoint& Point);
			const CPoint&	operator*=(const CPoint& Point);
			const CPoint&	operator/=(const CPoint& Point);
			const CPoint&	operator%=(const CPoint& Point);

			const CPoint&	operator*=(const int iValue);
			const CPoint&	operator/=(const int iValue);
			const CPoint&	operator%=(const int iValue);

			const bool	operator==(const CPoint& Point) const;
			const bool	operator!=(const CPoint& Point) const;

			const int&	operator[](const unsigned uIndex) const;
			int&		operator[](const unsigned uIndex);
		};

		class COMMON_API CPoint3D : public CPoint{
		public:
			int	Z;

			CPoint3D();
			CPoint3D(const CPoint3D& Point);
			CPoint3D(const CPoint& Point);
			CPoint3D(const CPoint& Point, const int Z);
			CPoint3D(const int iValue);
			CPoint3D(const int iX, const int iY);
			CPoint3D(const int iX, const int iY, const int iZ);

			void		SetZero();
			void		Set(const CPoint3D& Point);
			void		Set(const CPoint& Point);
			void		Set(const CPoint& Point, const int iZ);
			void		Set(const int iValue);
			void		Set(const int iX, const int iY);
			void		Set(const int iX, const int iY, const int iZ);

			const bool	IsZero() const;
			const bool	IsPartialZero() const;
			const bool	IsEqual(const CPoint3D& Point) const;

			const CPoint3D	Add(const CPoint3D& Point) const;
			const CPoint3D	Sub(const CPoint3D& Point) const;
			const CPoint3D	Mul(const CPoint3D& Point) const;
			const CPoint3D	Div(const CPoint3D& Point) const;
			const CPoint3D	Mod(const CPoint3D& Point) const;

			const CPoint3D	Mul(const int iValue) const;
			const CPoint3D	Div(const int iValue) const;
			const CPoint3D	Mod(const int iValue) const;

			const CString	ToString() const;

			const CPoint3D& operator=(const CPoint3D& Point);

			const CPoint3D	operator+() const;
			const CPoint3D	operator-() const;

			const CPoint3D	operator+(const CPoint3D& Point) const;
			const CPoint3D	operator-(const CPoint3D& Point) const;
			const CPoint3D	operator*(const CPoint3D& Point) const;
			const CPoint3D	operator/(const CPoint3D& Point) const;
			const CPoint3D	operator%(const CPoint3D& Point) const;

			const CPoint3D	operator*(const int iValue) const;
			const CPoint3D	operator/(const int iValue) const;
			const CPoint3D	operator%(const int iValue) const;

			const CPoint3D&	operator+=(const CPoint3D& Point);
			const CPoint3D&	operator-=(const CPoint3D& Point);
			const CPoint3D&	operator*=(const CPoint3D& Point);
			const CPoint3D&	operator/=(const CPoint3D& Point);
			const CPoint3D&	operator%=(const CPoint3D& Point);

			const CPoint3D&	operator*=(const int iValue);
			const CPoint3D&	operator/=(const int iValue);
			const CPoint3D&	operator%=(const int iValue);

			const bool	operator==(const CPoint3D& Point) const;
			const bool	operator!=(const CPoint3D& Point) const;

			const int&	operator[](const unsigned uIndex) const;
			int&		operator[](const unsigned uIndex);
		};
	}
}

#pragma pack()