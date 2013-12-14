#pragma once

#include "Math_Vector.h"

namespace CB{
	namespace Math{
		class COMMON_API CBoxF{
		public:
			CVector3D	Position;
			CVector3D	Size;

			CBoxF();
			CBoxF(const CBoxF& Box);
			CBoxF(const CVector3D& Position, const CVector3D& Size);
			CBoxF(const float32 X, const float32 Y, const float32 Z, const float32 Width, const float32 Height, const float32 Depth);

			void	SetZero();
			void	Set(const CBoxF& Box);
			void	Set(const float32 X, const float32 Y, const float32 Z, const float32 Width, const float32 Height, const float32 Depth);

			const bool	IsZero() const;
			const bool	IsPartialZero() const;
			const bool	IsEqual(const CBoxF& Box) const;

			const float32	GetXLower() const;
			const float32	GetXHigher() const;
			const float32	GetYLower() const;
			const float32	GetYHigher() const;
			const float32	GetZLower() const;
			const float32	GetZHigher() const;

			const bool	Contains(const CVector3D& Point) const;
			const bool	Contains(const CBoxF& Box) const;
			const bool	Intersects(const CBoxF& Box) const;

			const CString	ToString() const;

			const CBoxF&	operator=(const CBoxF& Box);

			const bool	operator==(const CBoxF& Box) const;
			const bool	operator!=(const CBoxF& Box) const;

			const float32	operator[](const uint32 uIndex) const;
		};
	}
}