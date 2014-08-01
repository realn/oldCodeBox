#pragma once

#include "Macros.h"
#include "Types.h"

namespace CB{
	class CString;

	namespace Collection{
		template<typename _Type> class ICountable;
		template<typename _Type, uint32 _Len> class CArray;
	}

	namespace Math{
		class CPoint2D;
		class CPoint3D;
		class CSize2D;

		class COMMON_API CSize3D {
		public:
			uint32	Width;
			uint32	Height;
			uint32	Depth;

			CSize3D();
			CSize3D(const CSize3D& Size);
			CSize3D(const uint32 uValue);
			CSize3D(const uint32 uWidth, const uint32 uHeight);
			CSize3D(const uint32 uWidth, const uint32 uHeight, const uint32 uDepth);
			explicit CSize3D(const CSize2D& Size);
			explicit CSize3D(const CSize2D& Size, const uint32 uDepth);
			explicit CSize3D(const CPoint3D& Point);
			explicit CSize3D( const Collection::ICountable<uint32>& array );

			void		SetZero();
			void		Set(const CSize3D& Size);
			void		Set(const uint32 uValue);
			void		Set(const uint32 uWidth, const uint32 uHeight);
			void		Set(const uint32 uWidth, const uint32 uHeight, const uint32 uDepth);

			const bool	IsZero() const;
			const bool	IsPartialZero() const;
			const bool	IsEqual(const CSize3D& Size) const;

			const CString	ToString() const;

			const CSize3D&	operator=(const CSize3D& Size);

			const bool	operator==(const CSize3D& Size) const;
			const bool	operator!=(const CSize3D& Size) const;

			const uint32&	operator[](const uint32 uIndex) const;
			uint32&		operator[](const uint32 uIndex);

			const Collection::CArray<uint32, 3> ToArray() const;
		};
	}
}
