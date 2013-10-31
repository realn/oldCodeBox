#pragma once

#include "Math_Point.h"
#include "Math_Size.h"

namespace CB{
	namespace Math{
		// oriented from top-left
		class CRectangle{
		public:
			CPoint	Position;
			CSize	Size;

			CRectangle();
			CRectangle(const CRectangle& Rectangle);
			CRectangle(const CPoint& Position, const CSize& Size);
			CRectangle(const int iX, const int iY, const CSize& Size);
			CRectangle(const CPoint& Position, const unsigned uWidth, const unsigned uHeight);
			CRectangle(const int iX, const int iY, const unsigned uWidth, const unsigned uHeight);

			void		SetZero();
			void		Set(const CRectangle& Rect);
			void		Set(const int iX, const int iY, const unsigned uWidth, const unsigned uHeight);

			const bool	IsZero() const;
			const bool	IsPartialZero() const;
			const bool	IsEqual(const CRectangle& Rectangle) const;

			const bool	Contains(const CPoint& Point) const;
			const bool	Contains(const CRectangle& Rectangle) const;
			const bool	Intersects(const CRectangle& Rectangle) const;

			const int	GetLeft() const;
			const int	GetRight() const;
			const int	GetTop() const;
			const int	GetBottom() const;

			const CB::CString	ToString() const;

			const CRectangle&	operator=(const CRectangle& Rectangle);

			const bool	operator==(const CRectangle& Rectangle) const;
			const bool	operator!=(const CRectangle& Rectangle) const;

			const int	operator[](const unsigned uIndex) const;
		};
	}
}