#pragma once

#include "Macros.h"
#include "Types.h"
#include "Ref.h"
#include "Math_Size.h"
#include "Collection_List.h"
#include "Manage_Object.h"
#include "SmartPointers_Hidden.h"

namespace CB{
	template<typename _Type> class CRefPtr;
	namespace IO{
		class IStream;
	}

	namespace Font{
		class CManager;

		class COMMON_API CFont :
			public IRef,
			public Manage::IManagedObject<CManager, CFont>
		{
			friend CManager;
		private:
			Math::CSize	m_FontSize;
			Collection::CList<byte>	m_FontData;
			CHiddenPtr	m_pData;

		public:
			void	SetSize(const uint32 uSize);
			void	SetSize(const Math::CSize& Size);

			void	SelectFace(const uint32 uIndex);
			void	SelectGlyph(const uint32 uIndex);
			void	SelectGlyphByChar(const wchar uChar);

			void		GetGlyphBitmap(Collection::CList<byte>& Data, Math::CSize& Size);

			const Math::CPoint	GetGlyphAdv() const;
			const Math::CPoint	GetGlyphBitmapPos() const;
			const uint32		GetLineHeight() const;
			const Math::CSize	GetSize() const;
			const uint32		GetAscender() const;
			const uint32		GetDescender() const;
			
			const uint32	GetCharGlyphIndex(const wchar uChar) const;

			const uint32	GetNumberOfFaces() const;
			const uint32	GetNumberOfGlyphs() const;
			
		protected:
			CFont(CRefPtr<CManager> pManager, CRefPtr<IO::IStream> pStream);
			~CFont();
		};
	}
}