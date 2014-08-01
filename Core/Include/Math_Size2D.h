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

		class COMMON_API CSize2D{
		public:
			uint32 Width;
			uint32 Height;

			CSize2D();
			CSize2D(const CSize2D& Size);
			CSize2D(const uint32 uValue);
			CSize2D(const uint32 uWidth, const uint32 uHeight);
			explicit CSize2D(const CPoint2D& Point);
			explicit CSize2D(const Collection::ICountable<uint32>& array);

			void		SetZero();
			void		Set(const CSize2D& Size);
			void		Set(const uint32 uValue);
			void		Set(const uint32 uWidth, const uint32 uHeight);

			const bool	IsZero() const;
			const bool	IsPartialZero() const;
			const bool	IsEqual(const CSize2D& Size) const;

			const CString	ToString() const;

			const CSize2D&	operator=(const CSize2D& Size);

			const bool	operator==(const CSize2D& Size) const;
			const bool	operator!=(const CSize2D& Size) const;

			const uint32&	operator[](const uint32 uIndex) const;
			uint32&		operator[](const uint32 uIndex);

			const Collection::CArray<uint32, 2>	ToArray() const;
		};
	}
}