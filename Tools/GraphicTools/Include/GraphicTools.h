#pragma once

#include "Macros.h"
#include <GraphicDriver.h>
#include <Font.h>
#include <IO_Image.h>
#include <Math_RectangleF.h>

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

			void	Generate(const CString& strText, CMeshRawIVT& OutMesh);
			void	Generate(const CString& strText, const Math::CVector2D& vSize, CMeshRawIVT& OutMesh);

		private:
			const CFontCharDesc&	GetChar(const wchar uCode) const;
			void	AddQuad(const Math::CRectangleF32& vQuad, const Math::CRectangleF32& vTexCoords, CMeshRawIVT& Mesh);
		};

		class GRAPHICTOOLS_API CRectVT{
		private:
			CRefPtr<Graphic::IVertexDeclaration>	m_pVertexDeclaration;
			CRefPtr<Graphic::IBuffer>				m_pVertexBuffer;
			CRefPtr<Graphic::IBuffer>				m_pIndexBuffer;
			uint32	m_uNumberOfPolygons;

		public:
			CRectVT(CRefPtr<Graphic::IDevice> pDevice, const Math::CVector2D& vSize, CRefPtr<Graphic::IShader> pVertexShader, const CString& strVertexName, const CString& strTexCoordName);

			CRefPtr<Graphic::IVertexDeclaration>	GetDeclaration() const;
			CRefPtr<Graphic::IBuffer>	GetVertexBuffer() const;
			CRefPtr<Graphic::IBuffer>	GetIndexBuffer() const;
			const uint32	GetNumberOfPolygons() const;
		};

		extern GRAPHICTOOLS_API CRefPtr<Graphic::ITexture2D>	CreateTextureFromImage(CRefPtr<Graphic::IDevice> pDevice, const IO::CImage& image, const Graphic::BufferUsage uUsage, const Graphic::BufferAccess uAccess, const Graphic::BufferFormat uFormat);
	}
}