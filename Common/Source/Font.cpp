#include "../Include/Font.h"

#include <ft2build.h>
#include FT_FREETYPE_H

namespace CB{
	namespace Font{
		CFont::CFont(CRefPtr<CManager> pManager, CRefPtr<IO::IStream> pStream) :
			Manage::IManagedObject<CManager, CFont>(pManager)
		{
			if(pStream->IsEmpty()){
				CR_THROW(L"Failed to load font - source stream is empty.");
			}
			uint32 uStreamLength = pStream->GetLengthLeft();
			this->m_FontData.Resize(uStreamLength);
			pStream->Read(this->m_FontData);

			FT_Face	pFace = 0;
			auto pLib = this->m_pParent->m_pData.GetCast<FT_Library>();
			auto uError = FT_New_Memory_Face(pLib, this->m_FontData.GetPointer(), this->m_FontData.GetSizeInBytes(), 0, &pFace);
			if(uError != 0){
				CR_THROW(L"Failed to load font, error: " + String::ToHexString(uError));
			}

			this->m_pData.SetCast<FT_Face>(pFace);
		}

		CFont::~CFont(){
			auto pFace = this->m_pData.ResetCast<FT_Face>();

			FT_Done_Face(pFace);
		}

		void	CFont::SetSize(const uint32 uSize){
			auto pFace = this->m_pData.GetCast<FT_Face>();

			auto uError = FT_Set_Pixel_Sizes(pFace, 0, uSize);
			if(uError != 0){
				CR_THROW(L"Failed to change font face size, error: " + String::ToHexString(uError));
			}
		}

		void	CFont::SetSize(const Math::CSize& Size){
			auto pFace = this->m_pData.GetCast<FT_Face>();

			auto uError = FT_Set_Pixel_Sizes(pFace, Size.Width, Size.Height);
			if(uError != 0){
				CR_THROW(L"Failed to change font face size, error: " + String::ToHexString(uError));
			}
		}

		void	CFont::SelectFace(const uint32 uIndex){
			auto pFace = this->m_pData.GetCast<FT_Face>();
			if(uIndex >= (uint32)pFace->num_faces){
				CR_THROW(L"Invalid font face index: " + String::ToString(uIndex));
			}

			auto uError = FT_Done_Face(pFace);
			if(uError != 0){
				CR_THROW(L"Failed to unload previous face." + String::ToHexString(uError));
			}

			auto pLib = this->m_pParent->m_pData.GetCast<FT_Library>();
			uError = FT_New_Memory_Face(pLib, this->m_FontData.GetPointer(), this->m_FontData.GetSizeInBytes(), uIndex, &pFace);
			if(uError != 0){
				CR_THROW(L"Failed to load new font face, error: " + String::ToHexString(uError));
			}

			this->m_pData.SetCast<FT_Face>(pFace);
		}
		
		void	CFont::SelectGlyph(const uint32 uIndex){
			auto pFace = this->m_pData.GetCast<FT_Face>();
			if(uIndex >= (uint32)pFace->num_glyphs){
				CR_THROW(L"Invalid font glyph index: " + String::ToHexString(uIndex));
			}

			auto uError = FT_Load_Glyph(pFace, uIndex, FT_LOAD_DEFAULT);
			if(uError != 0){
				CR_THROW(L"Failed to load new glyph, error: " + String::ToHexString(uError));
			}

			FT_Render_Glyph(pFace->glyph, FT_RENDER_MODE_NORMAL);
		}
		
		void	CFont::SelectGlyphByChar(const wchar uChar){
			this->SelectGlyph(this->GetCharGlyphIndex(uChar));
		}

		void		CFont::GetGlyphBitmap(Collection::CList<byte>& Data, Math::CSize& Size, uint32& uBPP){
			auto pFace = this->m_pData.GetCast<FT_Face>();
			FT_Bitmap& Bitmap = pFace->glyph->bitmap;

			Size.Set(Bitmap.width, Bitmap.rows);
			uBPP = Bitmap.pitch / Bitmap.width * 8;

			Data.Clear();
			if(!Size.IsZero()){
				Data.Resize(Bitmap.pitch * Bitmap.rows);
				Memory::CopyArray(Bitmap.buffer, Data.GetPointer(), sizeof(byte), Data.GetLength());
			}
		}

		const Math::CPoint	CFont::GetGlyphAdv() const{
			auto pFace = this->m_pData.GetCast<FT_Face>();

			return Math::CPoint(pFace->glyph->advance.x * 64, pFace->glyph->advance.y * 64);
		}

		const Math::CPoint	CFont::GetGlyphBitmapPos() const{
			auto pFace = this->m_pData.GetCast<FT_Face>();

			return Math::CPoint(pFace->glyph->bitmap_left, pFace->glyph->bitmap_top);
		}

		const uint32	CFont::GetLineHeight() const{
			auto pFace = this->m_pData.GetCast<FT_Face>();

			return pFace->height * 64;
		}

		const uint32	CFont::GetCharGlyphIndex(const wchar uChar) const{
			auto pFace = this->m_pData.GetCast<FT_Face>();

			auto uIndex = FT_Get_Char_Index(pFace, uChar);
			if(uIndex == 0){
				CR_THROW(L"Unknown face glyph for character " + String::ToString((uint32) uChar));
			}
			return uIndex;
		}

		const uint32	CFont::GetNumberOfFaces() const{
			auto pFace = this->m_pData.GetCast<FT_Face>();

			return pFace->num_faces;
		}

		const uint32	CFont::GetNumberOfGlyphs() const{
			auto pFace = this->m_pData.GetCast<FT_Face>();

			return pFace->num_glyphs;
		}
	}
}