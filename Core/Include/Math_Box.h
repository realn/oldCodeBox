#pragma once

#include "Math_Point.h"
#include "Math_Size.h"

namespace CB{
	namespace Math{
		class COMMON_API CBox{
		public:
			CPoint3D	Position;
			CSize3D		Size;

			CBox();
			CBox(const CBox& Box);
			CBox(const CPoint3D& Position, const CSize3D& Size);
			CBox(const int32 X, const int32 Y, const int32 Z, const uint32 Width, const uint32 Height, const uint32 Depth);

			void	SetZero();
			void	Set(const CBox& Box);
			void	Set(const int32 X, const int32 Y, const int32 Z, const uint32 Width, const uint32 Height, const uint32 Depth);

			const bool	IsZero() const;
			const bool	IsPartialZero() const;
			const bool	IsEqual(const CBox& Box) const;

			const int32	GetXLower() const;
			const int32	GetXHigher() const;
			const int32	GetYLower() const;
			const int32	GetYHigher() const;
			const int32	GetZLower() const;
			const int32	GetZHigher() const;

			const bool	Contains(const CPoint3D& Point) const;
			const bool	Contains(const CBox& Box) const;
			const bool	Intersects(const CBox& Box) const;

			const CString	ToString() const;

			const CBox&	operator=(const CBox& Box);

			const bool	operator==(const CBox& Box) const;
			const bool	operator!=(const CBox& Box) const;

			const int32	operator[](const uint32 uIndex) const;
		};
	}
}