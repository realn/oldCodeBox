#pragma once

#include "Math_Point.h"

namespace CB{
	namespace Math{
		class COMMON_API CSize{
		public:
			uint32 Width;
			uint32 Height;

			CSize();
			CSize(const CSize& Size);
			CSize(const CPoint& Point);
			CSize(const uint32 uValue);
			CSize(const uint32 uWidth, const uint32 uHeight);

			void		SetZero();
			void		Set(const CSize& Size);
			void		Set(const uint32 uValue);
			void		Set(const uint32 uWidth, const uint32 uHeight);

			const bool	IsZero() const;
			const bool	IsPartialZero() const;
			const bool	IsEqual(const CSize& Size) const;

			const CString	ToString() const;
			const CPoint	ToPoint() const;

			const CSize&	operator=(const CSize& Size);

			const bool	operator==(const CSize& Size) const;
			const bool	operator!=(const CSize& Size) const;

			const uint32&	operator[](const uint32 uIndex) const;
			uint32&		operator[](const uint32 uIndex);
		};

		class COMMON_API CSize3D : 
			public CSize
		{
		public:
			uint32 Depth;

			CSize3D();
			CSize3D(const CSize3D& Size);
			CSize3D(const CSize& Size);
			CSize3D(const CSize& Size, const uint32 uDepth);
			CSize3D(const CPoint3D& Point);
			CSize3D(const CPoint& Point);
			CSize3D(const CPoint& Point, const uint32 uDepth);
			CSize3D(const uint32 uValue);
			CSize3D(const uint32 uWidth, const uint32 uHeight);
			CSize3D(const uint32 uWidth, const uint32 uHeight, const uint32 uDepth);

			void		SetZero();
			void		Set(const CSize3D& Size);
			void		Set(const uint32 uValue);
			void		Set(const uint32 uWidth, const uint32 uHeight);
			void		Set(const uint32 uWidth, const uint32 uHeight, const uint32 uDepth);

			const bool	IsZero() const;
			const bool	IsPartialZero() const;
			const bool	IsEqual(const CSize3D& Size) const;

			const CString	ToString() const;
			const CPoint3D	ToPoint() const;

			const CSize3D&	operator=(const CSize3D& Size);

			const bool	operator==(const CSize3D& Size) const;
			const bool	operator!=(const CSize3D& Size) const;

			const uint32&	operator[](const uint32 uIndex) const;
			uint32&		operator[](const uint32 uIndex);
		};
	}
}