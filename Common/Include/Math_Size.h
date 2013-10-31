#pragma once

#include "Math_Point.h"

namespace CB{
	namespace Math{
		class COMMON_API CSize{
		public:
			unsigned Width;
			unsigned Height;

			CSize();
			CSize(const CSize& Size);
			CSize(const CPoint& Point);
			CSize(const unsigned uValue);
			CSize(const unsigned uWidth, const unsigned uHeight);

			void		SetZero();
			void		Set(const CSize& Size);
			void		Set(const unsigned uValue);
			void		Set(const unsigned uWidth, const unsigned uHeight);

			const bool	IsZero() const;
			const bool	IsPartialZero() const;
			const bool	IsEqual(const CSize& Size) const;

			const CString	ToString() const;
			const CPoint	ToPoint() const;

			const CSize&	operator=(const CSize& Size);

			const bool	operator==(const CSize& Size) const;
			const bool	operator!=(const CSize& Size) const;

			const unsigned&	operator[](const unsigned uIndex) const;
			unsigned&		operator[](const unsigned uIndex);
		};

		class COMMON_API CSize3D : public CSize{
		public:
			unsigned Depth;

			CSize3D();
			CSize3D(const CSize3D& Size);
			CSize3D(const CSize& Size);
			CSize3D(const CSize& Size, const unsigned uDepth);
			CSize3D(const CPoint3D& Point);
			CSize3D(const CPoint& Point);
			CSize3D(const CPoint& Point, const unsigned uDepth);
			CSize3D(const unsigned uValue);
			CSize3D(const unsigned uWidth, const unsigned uHeight);
			CSize3D(const unsigned uWidth, const unsigned uHeight, const unsigned uDepth);

			void		SetZero();
			void		Set(const CSize3D& Size);
			void		Set(const unsigned uValue);
			void		Set(const unsigned uWidth, const unsigned uHeight);
			void		Set(const unsigned uWidth, const unsigned uHeight, const unsigned uDepth);

			const bool	IsZero() const;
			const bool	IsPartialZero() const;
			const bool	IsEqual(const CSize3D& Size) const;

			const CString	ToString() const;
			const CPoint3D	ToPoint() const;

			const CSize3D&	operator=(const CSize3D& Size);

			const bool	operator==(const CSize3D& Size) const;
			const bool	operator!=(const CSize3D& Size) const;

			const unsigned&	operator[](const unsigned uIndex) const;
			unsigned&		operator[](const unsigned uIndex);
		};
	}
}