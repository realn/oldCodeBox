#pragma once

#include "Macros.h"
#include "Types.h"
#include "Math_Vector2D.h"

namespace CB{
	namespace Math{
		class COMMON_API CRectangleF32{
		public:
			CVector2D	Position;
			CVector2D	Size;

			CRectangleF32();
			CRectangleF32(const CRectangleF32& Rectangle);
			CRectangleF32(const CVector2D& Position, const CVector2D& Size);
			CRectangleF32(const float32 fX, const float32 fY, const CVector2D& Size);
			CRectangleF32(const CVector2D& Position, const float32 fWidth, const float32 fHeight);
			CRectangleF32(const float32 fX, const float32 fY, const float32 fWidth, const float32 fHeight);
			CRectangleF32(const Collection::ICountable<float32>& array);

			void		SetZero();
			void		Set(const CRectangleF32& Rect);
			void		Set(const float32 fX, const float32 fY, const float32 fWidth, const float32 fHeight);

			const bool	IsZero() const;
			const bool	IsPartialZero() const;
			const bool	IsEqual(const CRectangleF32& Rectangle) const;

			const bool	Contains(const CVector2D& Point) const;
			const bool	Contains(const CRectangleF32& Rectangle) const;
			const bool	Intersects(const CRectangleF32& Rectangle) const;

			const float32	GetXLower() const;	// Position.X
			const float32	GetXHigher() const;	// Position.X + Size.X

			const float32	GetYLower() const;	// Position.Y
			const float32	GetYHigher() const;	// Position.Y + Size.X

			const CB::CString	ToString() const;

			const CRectangleF32&	operator=(const CRectangleF32& Rectangle);

			const bool	operator==(const CRectangleF32& Rectangle) const;
			const bool	operator!=(const CRectangleF32& Rectangle) const;

			const float32	operator[](const uint32 uIndex) const;

			const Collection::CArray<float32, 4>	ToArray() const;
		};
	}
}