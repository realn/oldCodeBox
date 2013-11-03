#pragma once

#include "Math_Point.h"
#include "Math_Size.h"

namespace CB{
	namespace Math{
		class CRectangle{
		public:
			CPoint	Position;
			CSize	Size;

			CRectangle();
			CRectangle(const CRectangle& Rectangle);
			CRectangle(const CPoint& Position, const CSize& Size);
			CRectangle(const int32 iX, const int32 iY, const CSize& Size);
			CRectangle(const CPoint& Position, const uint32 uWidth, const uint32 uHeight);
			CRectangle(const int32 iX, const int32 iY, const uint32 uWidth, const uint32 uHeight);

			void		SetZero();
			void		Set(const CRectangle& Rect);
			void		Set(const int32 iX, const int32 iY, const uint32 uWidth, const uint32 uHeight);

			const bool	IsZero() const;
			const bool	IsPartialZero() const;
			const bool	IsEqual(const CRectangle& Rectangle) const;

			const bool	Contains(const CPoint& Point) const;
			const bool	Contains(const CRectangle& Rectangle) const;
			const bool	Intersects(const CRectangle& Rectangle) const;

			const int32	GetXLower() const;	// Position.X
			const int32	GetXHigher() const;	// Position.X + Size.Width

			const int32	GetYLower() const;	// Position.Y
			const int32	GetYHigher() const;	// Position.Y + Size.Height

			const CB::CString	ToString() const;

			const CRectangle&	operator=(const CRectangle& Rectangle);

			const bool	operator==(const CRectangle& Rectangle) const;
			const bool	operator!=(const CRectangle& Rectangle) const;

			const int32	operator[](const uint32 uIndex) const;
		};
	}
}