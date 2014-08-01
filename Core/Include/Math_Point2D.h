#pragma once

#include "Macros.h"
#include "Types.h"

#pragma pack(1)

namespace CB{
	class CString;

	namespace Collection{
		template<typename _Type> class ICountable;
		template<typename _Type, uint32 _Len> class CArray;
	}

	namespace Math{
		class CSize2D;

		class COMMON_API CPoint2D{
		public:
			int32	X;
			int32	Y;

			CPoint2D();
			CPoint2D(const CPoint2D& Point);
			CPoint2D(const int32 iValue);
			CPoint2D(const int32 iX, const int32 iY);
			explicit CPoint2D( const CSize2D& Size );
			explicit CPoint2D( const Collection::ICountable<int32>& array );

			void		SetZero();
			void		Set(const CPoint2D& Point);
			void		Set(const int32 iValue);
			void		Set(const int32 iX, const int32 iY);

			const bool	IsZero() const;
			const bool	IsPartialZero() const;
			const bool	IsEqual(const CPoint2D& Point) const;

			const CPoint2D	Add(const CPoint2D& Point) const;
			const CPoint2D	Sub(const CPoint2D& Point) const;
			const CPoint2D	Mul(const CPoint2D& Point) const;
			const CPoint2D	Div(const CPoint2D& Point) const;
			const CPoint2D	Mod(const CPoint2D& Point) const;

			const CPoint2D	Mul(const int32 iValue) const;
			const CPoint2D	Div(const int32 iValue) const;
			const CPoint2D	Mod(const int32 iValue) const;

			const CString	ToString() const;

			const CPoint2D&	operator=(const CPoint2D& Point);

			const CPoint2D	operator+() const;
			const CPoint2D	operator-()	const;

			const CPoint2D	operator+(const CPoint2D& Point) const;
			const CPoint2D	operator-(const CPoint2D& Point) const;
			const CPoint2D	operator*(const CPoint2D& Point) const;
			const CPoint2D	operator/(const CPoint2D& Point) const;
			const CPoint2D	operator%(const CPoint2D& Point) const;

			const CPoint2D	operator*(const int32 iValue) const;
			const CPoint2D	operator/(const int32 iValue) const;
			const CPoint2D	operator%(const int32 iValue) const;

			const CPoint2D&	operator+=(const CPoint2D& Point);
			const CPoint2D&	operator-=(const CPoint2D& Point);
			const CPoint2D&	operator*=(const CPoint2D& Point);
			const CPoint2D&	operator/=(const CPoint2D& Point);
			const CPoint2D&	operator%=(const CPoint2D& Point);

			const CPoint2D&	operator*=(const int32 iValue);
			const CPoint2D&	operator/=(const int32 iValue);
			const CPoint2D&	operator%=(const int32 iValue);

			const bool	operator==(const CPoint2D& Point) const;
			const bool	operator!=(const CPoint2D& Point) const;

			const int32&	operator[](const uint32 uIndex) const;
			int32&			operator[](const uint32 uIndex);

			const Collection::CArray<int32, 2>	ToArray() const;
		};
	}
}

#pragma pack()