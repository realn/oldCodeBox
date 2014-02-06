#pragma once

#include <Types.h>
#include <GraphicDriver.h>
#include <Math_Vector.h>
#include <Math_RectangleF.h>
#include <Font.h>
#include <IO_Image.h>

#include "Macros.h"
#include "Tools_Mesh.h"

namespace CB{
	namespace Tools{
		class GRAPHICTOOLS_API CFontCharDesc{
		public:
			wchar				cCharacter;
			Math::CRectangleF32	vTexCoord;
			Math::CVector2D		vPosCorrection;
			Math::CVector2D		vSize;
			Math::CVector2D		vAdvance;

			inline CFontCharDesc() : cCharacter(0){};
		};

		class GRAPHICTOOLS_API CFontTextureGenerator{
		private:
			CRefPtr<Graphic::IDevice>	m_pDevice;
			CRefPtr<Font::CFont>		m_pFont;
			Math::CSize					m_FontSize;

		public:			
			Math::CSize	MaxTextureSize;
			Math::CSize CharPadding;
			bool		bSkipInvalid;

			CFontTextureGenerator(CRefPtr<Graphic::IDevice> pDevice);

			CRefPtr<Graphic::ITexture2D>	Generate(CRefPtr<Font::CFont> pFont, Collection::CList<CFontCharDesc>& OutCharacterList);
			CRefPtr<Graphic::ITexture2D>	Generate(CRefPtr<Font::CFont> pFont, const Collection::ICountable<wchar>& CharsToGen, Collection::CList<CFontCharDesc>& OutCharacterList);

		private:
			const bool GenerateChar(const wchar charCode, IO::CImage& img, CFontCharDesc& desc);
		};

		class GRAPHICTOOLS_API CTextMeshGenerator{
		private:
			Collection::CList<CFontCharDesc>	m_FontChars;

		public:
			wchar	cInvalidCharReplace;

			CTextMeshGenerator(const Collection::ICountable<CFontCharDesc>& FontCharDescs);

			void	Generate(const CString& strText, CMeshRawIVT& OutMesh) const;
			void	Generate(const CString& strText, const Math::CVector2D& vScale, CMeshRawIVT& OutMesh) const;

			const CB::Math::CVector2D	GetTextSize(const CString& strText) const;
			const CB::Math::CVector2D	GetTextSize(const CString& strText, const CB::Math::CVector2D& vScale) const;

		private:
			const CFontCharDesc&	GetChar(const wchar uCode) const;
			void	AddQuad(const Math::CRectangleF32& vQuad, const Math::CRectangleF32& vTexCoords, CMeshRawIVT& Mesh) const;
		};
	}
}