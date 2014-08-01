#pragma once

#include "Macros.h"
#include "Types.h"

namespace CB{
	class CString;

	namespace Collection{
		template<typename _Type> class ICountable;
		template<typename _Type, uint32 _Len> class CArray;
	}

	namespace Math{
		class CPoint2D;
		class CSize3D;

		class COMMON_API CPoint3D {
		public:
			int32	X;
			int32	Y;
			int32	Z;

			CPoint3D();
			CPoint3D(const CPoint3D& Point);
			CPoint3D(const int32 iValue);
			CPoint3D(const int32 iX, const int32 iY);
			CPoint3D(const int32 iX, const int32 iY, const int32 iZ);
			explicit CPoint3D(const CPoint2D& Point);
			explicit CPoint3D(const CPoint2D& Point, const int32 Z);
			explicit CPoint3D(const CSize3D& Size);
			explicit CPoint3D(const Collection::ICountable<int32>& array);

			void		SetZero();
			void		Set(const CPoint3D& Point);
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

			const Collection::CArray<int32, 3>	ToArray() const;
		};
	}
}