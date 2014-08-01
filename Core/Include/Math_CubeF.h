#pragma once

#include "Macros.h"
#include "Types.h"
#include "Math_Vector3D.h"

namespace CB{
	namespace Math{
		class CRectangleF32;

		class COMMON_API CCubeF{
		public:
			CVector3D	Position;
			CVector3D	Size;

			CCubeF();
			CCubeF(const CCubeF& Box);
			CCubeF(const CVector3D& Position, const CVector3D& Size);
			CCubeF(const float32 X, const float32 Y, const float32 Z, const float32 Width, const float32 Height, const float32 Depth);
			CCubeF(const CRectangleF32& rect, const float32 Z, const float32 Depth);
			explicit CCubeF(const Collection::ICountable<float32>& array);

			void	SetZero();
			void	Set(const CCubeF& Box);
			void	Set(const float32 X, const float32 Y, const float32 Z, const float32 Width, const float32 Height, const float32 Depth);

			const bool	IsZero() const;
			const bool	IsPartialZero() const;
			const bool	IsEqual(const CCubeF& Box) const;

			const float32	GetXLower() const;
			const float32	GetXHigher() const;
			const float32	GetYLower() const;
			const float32	GetYHigher() const;
			const float32	GetZLower() const;
			const float32	GetZHigher() const;

			const bool	Contains(const CVector3D& Point) const;
			const bool	Contains(const CCubeF& Box) const;
			const bool	Intersects(const CCubeF& Box) const;

			const CString	ToString() const;

			const CCubeF&	operator=(const CCubeF& Box);

			const bool	operator==(const CCubeF& Box) const;
			const bool	operator!=(const CCubeF& Box) const;

			const float32	operator[](const uint32 uIndex) const;

			const Collection::CArray<float32, 6>	ToArray() const;
		};
	}
}