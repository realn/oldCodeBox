#include "../Include/GraphicTools.h"
#include <CBStringEx.h>
#include <Logger.h>
#include <IO_Image.h>

namespace CB{
	namespace Tools{
		CFontTextureGenerator::CFontTextureGenerator(CRefPtr<Graphic::IDevice> pDevice) :
			m_pDevice(pDevice),
			bSkipInvalid(true),
			MaxTextureSize(256, 256),
			CharPadding(5, 5)
		{

		}

		CRefPtr<Graphic::ITexture2D>	CFontTextureGenerator::Generate(CRefPtr<Font::CFont> pFont, Collection::CList<CFontCharDesc>& OutCharacterList){
			auto defaultChars = String::ToArray(L" !?><,./;:'\"\\|[]{}-_=+@#$%^&*()`~ABCDEFGHIJKLMNOPRSTQWXYZ0123456789abcdefghijklmnoprstqwxyz");

			return this->Generate(pFont, defaultChars, OutCharacterList);
		}

		CRefPtr<Graphic::ITexture2D>	CFontTextureGenerator::Generate(CRefPtr<Font::CFont> pFont, const Collection::ICountable<wchar>& CharsToGen, Collection::CList<CFontCharDesc>& OutCharacterList){
			this->m_pFont = pFont;
			this->m_FontSize = pFont->GetSize();
			
			IO::CImage textureImage(this->MaxTextureSize, IO::Image::BitFormat::f32Bit);
			Math::CVector2D vTextureSize(this->MaxTextureSize.Width, this->MaxTextureSize.Height);

			Math::CPoint texturePos = this->CharPadding.ToPoint();
			uint32	maxCharHeight = 0;

			IO::CImage charImg;
			CFontCharDesc desc;
			for(uint32 uCharIdx = 0; uCharIdx < CharsToGen.GetLength(); uCharIdx++){
				wchar charCode = CharsToGen[uCharIdx];				

				if(!this->GenerateChar(charCode, charImg, desc)){
					continue;
				}

				auto imgSize = charImg.GetSize();
				
				if(texturePos.X + imgSize.Width + CharPadding.Width > MaxTextureSize.Width){
					texturePos.X = this->CharPadding.Width;
					texturePos.Y += maxCharHeight + CharPadding.Height;
					maxCharHeight = 0;
				}
				if(texturePos.Y + imgSize.Height > MaxTextureSize.Height){
					continue;
				}

				//charImg.Flip(IO::Image::FlipType::Vertical);
				charImg.PasteTo(textureImage, texturePos);

				desc.vTexCoord.Position = Math::CVector2D(texturePos) / vTextureSize;
				desc.vTexCoord.Size		= Math::CVector2D(imgSize.ToPoint()) / vTextureSize;

				OutCharacterList.Add(desc);

				texturePos.X += imgSize.Width + this->CharPadding.Width;
				if(imgSize.Height > maxCharHeight)
					maxCharHeight = imgSize.Height;
			}

			textureImage.Flip(IO::Image::FlipType::Vertical);
			return CreateTextureFromImage(this->m_pDevice, textureImage, Graphic::BufferUsage::Static, CB::Graphic::BufferAccess::Read, Graphic::BufferFormat::R8G8B8A8);
		}
		
		const bool CFontTextureGenerator::GenerateChar(const wchar charCode, IO::CImage& img, CFontCharDesc& desc){
			Collection::CList<byte> pixelData;
			Math::CSize pixelSize;
			Math::CPoint Adv;
			Math::CPoint bitmapPos;
			try{
				this->m_pFont->SelectGlyphByChar(charCode);

				this->m_pFont->GetGlyphBitmap(pixelData, pixelSize);
				Adv = this->m_pFont->GetGlyphAdv();
				bitmapPos = this->m_pFont->GetGlyphBitmapPos();

				if(!pixelSize.IsZero()){
					img.Create(pixelSize, IO::Image::BitFormat::f32Bit);
					img.SetPixels(pixelData);
				}
				else{
					img.Create(Math::CSize(1), IO::Image::BitFormat::f32Bit);
				}

				auto vFontSize = Math::CVector2D(this->m_FontSize.Width, this->m_FontSize.Height);

				desc.cCharacter = charCode;
				desc.vPosCorrection = Math::CVector2D(bitmapPos) / vFontSize;
				desc.vPosCorrection.Y = -desc.vPosCorrection.Y;
				desc.vAdvance = Math::CVector2D(Adv) / vFontSize;
				desc.vSize = Math::CVector2D(pixelSize.ToPoint()) / vFontSize;

				return true;
			}
			catch(Exception::CException& Exception){
				CString strError = L"Failed to load char " + String::ToHexString((uint32)charCode) + L"(" + charCode + L") fot texture generation.";
				if(!this->bSkipInvalid){
					CR_RETHROW(strError, Exception);
				}
				else{
					Log::Write(strError);
					Log::Write(Exception);

					return false;
				}
			}
		}
	}
}