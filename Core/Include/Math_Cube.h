#pragma once

#include "Macros.h"
#include "Types.h"
#include "Math_Point3D.h"
#include "Math_Size3D.h"

namespace CB{
	namespace Math{
		class CRectangle;

		class COMMON_API CCube{
		public:
			CPoint3D	Position;
			CSize3D		Size;

			CCube();
			CCube(const CCube& Cube);
			CCube(const CPoint3D& Position, const CSize3D& Size);
			CCube(const int32 X, const int32 Y, const int32 Z, const uint32 Width, const uint32 Height, const uint32 Depth);
			CCube(const CRectangle& Rect, int32 Z, uint32 Depth);
			explicit CCube( const Collection::ICountable<int32>& array );

			void	SetZero();
			void	Set(const CCube& Cube);
			void	Set(const int32 X, const int32 Y, const int32 Z, const uint32 Width, const uint32 Height, const uint32 Depth);

			const bool	IsZero() const;
			const bool	IsPartialZero() const;
			const bool	IsEqual(const CCube& Cube) const;

			const int32	GetXLower() const;
			const int32	GetXHigher() const;
			const int32	GetYLower() const;
			const int32	GetYHigher() const;
			const int32	GetZLower() const;
			const int32	GetZHigher() const;

			const bool	Contains(const CPoint3D& Point) const;
			const bool	Contains(const CCube& Cube) const;
			const bool	Intersects(const CCube& Cube) const;

			const CString	ToString() const;

			const CCube&	operator=(const CCube& Cube);

			const bool	operator==(const CCube& Cube) const;
			const bool	operator!=(const CCube& Cube) const;

			const int32	operator[](const uint32 uIndex) const;

			const Collection::CArray<int32, 6>	ToArray() const;
		};
	}
}