#include "../Include/IO_Image.h"
#include "../Include/Exception.h"
#include "../Internal/IO_FreeImage.h"
#include "../Include/Math.h"
#include "../Include/CBStringEx.h"

namespace CB{
	namespace IO{
		CImage::CImage(){
		}

		CImage::CImage(const CImage& Image){
			Image.CopyTo(*this);
		}

		CImage::CImage(const Math::CSize& Size){
			this->Create(Size);
		}

		CImage::CImage(const Math::CSize& Size, const Image::BitFormat uFormat){
			this->Create(Size, uFormat);
		}

		CImage::~CImage(){
			this->Free();
		}

		void	CImage::Create(const Math::CSize& Size){
			this->Create(Size, IO::Image::BitFormat::f32Bit);
		}

		void	CImage::Create(const Math::CSize& Size, const Image::BitFormat uFormat){
			this->Free();

			unsigned uBits = 0;
			switch (uFormat)
			{
			case Image::BitFormat::f4Bit:	uBits = 4; break;
			case Image::BitFormat::f8Bit:	uBits = 8; break;
			case Image::BitFormat::f16Bit:	uBits = 16; break;
			case Image::BitFormat::f24Bit:	uBits = 24; break;
			case Image::BitFormat::f32Bit:	uBits = 32; break;
			default:
				throw Exception::CInvalidArgumentException(L"uFormat", String::ToString(uFormat),
					L"Invalid image bit format.", __FUNCTIONW__, __FILEW__, __LINE__);
			}

			try{
				CAutoPtr<FreeImage::CData> pData = new FreeImage::CData(FIF_BMP);

				pData->Bitmap.Create(Size, uBits);

				this->m_Data.Set<FreeImage::CData>(pData.Reset());
			}
			catch(Exception::CException& Exception){
				throw Exception::CException(
					L"Error while creating image.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
			}
		}

		void	CImage::Free(){
			this->m_Data.Delete<FreeImage::CData>();
		}

		void	CImage::ReadFromStream(CRefPtr<IO::IStream> pStream){
			if(pStream.IsNull()){
				throw Exception::CNullArgumentException(L"pStream",
					L"Need valid stream for reading.", __FUNCTIONW__, __FILEW__, __LINE__);
			}

			try{
				Collection::CList<BYTE> Data(pStream->GetLength());
				pStream->Read(Data);

				FreeImage::CStream imageStream(Data);
				CAutoPtr<FreeImage::CData> ImageData = new FreeImage::CData();

				ImageData->Format = FreeImage_GetFileTypeFromMemory(imageStream.Get());

				if(ImageData->Format == FIF_UNKNOWN){
					throw Exception::CException(
						L"Failed to recognize file type.", __FUNCTIONW__, __FILEW__, __LINE__);
				}

				ImageData->Bitmap.Set(FreeImage_LoadFromMemory(ImageData->Format, imageStream.Get()));
				if(!ImageData->Bitmap.IsValid()){
					throw Exception::CException(
						L"Failed to load image from memory.", __FUNCTIONW__, __FILEW__, __LINE__);
				}

				this->Free();
				this->m_Data.Set<FreeImage::CData>(ImageData.Reset());
			}
			catch(Exception::CException& Exception){
				throw Exception::CException(
					L"Error while loading image from stream.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
			}
		}

		void	CImage::WriteToStream(CRefPtr<IO::IStream> pStream) const{
			Image::FileType uFileType = Image::FileType::Bitmap;
			if(this->m_Data.IsValid()){
				switch(this->m_Data.Get<FreeImage::CData>()->Format){
				case FIF_BMP:	uFileType = Image::FileType::Bitmap;
				case FIF_PNG:	uFileType = Image::FileType::Png;
				case FIF_TARGA:	uFileType = Image::FileType::Targa;
				case FIF_JPEG:	uFileType = Image::FileType::Jpeg;
				}
			}
			this->WriteToStream(pStream, uFileType);
		}

		void	CImage::WriteToStream(CRefPtr<IO::IStream> pStream, Image::FileType uFileType) const{
			if(pStream == 0){
				throw Exception::CNullArgumentException(L"pStream",
					L"Need valid stream to write image.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
			if(!this->IsLoaded()){
				throw Exception::CException(
					L"Image must be loaded for writing to stream.", __FUNCTIONW__, __FILEW__, __LINE__);
			}

			try{
				FREE_IMAGE_FORMAT uFormat;
				switch (uFileType)
				{
				case Image::FileType::Bitmap:	uFormat = FIF_BMP;		break;
				case Image::FileType::Targa:	uFormat = FIF_TARGA;	break;
				case Image::FileType::Jpeg:		uFormat = FIF_JPEG;		break;
				case Image::FileType::Png:		uFormat = FIF_PNG;		break;
				default:
					throw Exception::CInvalidArgumentException(L"uFileType", String::ToString(uFileType),
						L"Invalid file type.", __FUNCTIONW__, __FILEW__, __LINE__);
				}

				FreeImage::CStream FreeStream(0, 0);

				if(!FreeImage_SaveToMemory(uFormat, this->m_Data.Get<FreeImage::CData>()->Bitmap.Get(), FreeStream.Get())){
					throw Exception::CException(
						L"Failed to save image data.", __FUNCTIONW__, __FILEW__, __LINE__);
				}

				BYTE* pByteData = 0;
				DWORD dwLength = 0;
				if(!FreeImage_AcquireMemory(FreeStream.Get(), &pByteData, &dwLength)){
					throw Exception::CException(
						L"Failed to acquire image data.", __FUNCTIONW__, __FILEW__, __LINE__);
				}

				pStream->Write(pByteData, dwLength);
			}
			catch(Exception::CException& Exception){
				throw Exception::CException(
					L"Failed to write image to stream.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
			}
		}

		const Math::CSize	CImage::GetSize() const{
			if(!this->IsLoaded()){
				return Math::CSize();
			}
			FreeImage::CData* pData = this->m_Data.Get<FreeImage::CData>();
			return Math::CSize(FreeImage_GetWidth(pData->Bitmap.Get()), FreeImage_GetHeight(pData->Bitmap.Get()));
		}

		const Image::BitFormat	CImage::GetBitFormat() const{
			if(!this->IsLoaded()){
				return Image::BitFormat::Unknown;
			}
			switch (FreeImage_GetBPP(this->m_Data.Get<FreeImage::CData>()->Bitmap.Get()))
			{
			case 4:		return Image::BitFormat::f4Bit;
			case 8:		return Image::BitFormat::f8Bit;
			case 16:	return Image::BitFormat::f16Bit;
			case 24:	return Image::BitFormat::f24Bit;
			case 32:	return Image::BitFormat::f32Bit;
			default:
				return Image::BitFormat::Unknown;
			}
		}

		const unsigned	CImage::GetBytesPerPixel() const{
			if(!this->IsLoaded()){
				return 0;
			}
			return FreeImage_GetBPP(this->m_Data.Get<FreeImage::CData>()->Bitmap.Get()) / 8;
		}

		const Image::ColorFormat	CImage::GetColorFormat() const{
			if(!this->IsLoaded()){
				return Image::ColorFormat::Unknown;
			}
			switch (FreeImage_GetColorType(this->m_Data.Get<FreeImage::CData>()->Bitmap.Get()))
			{
			case FIC_RGB:		return Image::ColorFormat::RGB;
			case FIC_RGBALPHA:	return Image::ColorFormat::RGBA;
			default:
				return Image::ColorFormat::Unknown;
			}
		}

		void	CImage::GetPixels(Collection::CList<unsigned char>& Array) const{
			if(!this->IsLoaded()){
				throw Exception::CException(
					L"Cannot retrieve data when image not loaded.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
			Math::CSize Size = this->GetSize();
			unsigned uBytes = this->GetBytesPerPixel();

			Array.Resize(Size.Width * Size.Height * uBytes);
			Memory::CopyArray(FreeImage_GetBits(this->m_Data.Get<FreeImage::CData>()->Bitmap.Get()), &Array[0], Array.GetLength());
		}

		const bool	CImage::IsLoaded() const{
			return this->m_Data.IsValid();
		}

		void	CImage::Convert(const Image::BitFormat uFormat){
			if(!this->IsLoaded()){
				throw Exception::CException(
					L"Cannot convert not loaded image.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
			FreeImage::CBitmap Bitmap;
			switch (uFormat)
			{
			case Image::BitFormat::f4Bit:	
				Bitmap.Set(FreeImage_ConvertTo4Bits(this->m_Data.Get<FreeImage::CData>()->Bitmap.Get()));	break;

			case Image::BitFormat::f8Bit:	
				Bitmap.Set(FreeImage_ConvertTo8Bits(this->m_Data.Get<FreeImage::CData>()->Bitmap.Get()));	break;
			
			case Image::BitFormat::f16Bit:	
				Bitmap.Set(FreeImage_ConvertTo16Bits565(this->m_Data.Get<FreeImage::CData>()->Bitmap.Get()));	break;
			
			case Image::BitFormat::f24Bit:	
				Bitmap.Set(FreeImage_ConvertTo24Bits(this->m_Data.Get<FreeImage::CData>()->Bitmap.Get()));	break;
			
			case Image::BitFormat::f32Bit:	
				Bitmap.Set(FreeImage_ConvertTo32Bits(this->m_Data.Get<FreeImage::CData>()->Bitmap.Get()));	break;

			default:
				throw Exception::CInvalidArgumentException(L"uFormat", String::ToString(uFormat),
					L"Failed to convert bitmap image.", __FUNCTIONW__, __FILEW__, __LINE__);
			}

			if(!Bitmap.IsValid()){
				throw Exception::CException(
					L"Image conversion failed.", __FUNCTIONW__, __FILEW__, __LINE__);
			}

			this->m_Data.Get<FreeImage::CData>()->Bitmap.Free();
			this->m_Data.Get<FreeImage::CData>()->Bitmap.Set(Bitmap.Release());
		}

		void	CImage::Flip(const Image::FlipType uType){
			if(!this->IsLoaded()){
				throw Exception::CException(
					L"Cannot flip not loaded image.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
			switch (uType)
			{
			case Image::FlipType::Horizontal:	
				FreeImage_FlipHorizontal(this->m_Data.Get<FreeImage::CData>()->Bitmap.Get());	break;
			
			case Image::FlipType::Vertical:	
				FreeImage_FlipVertical(this->m_Data.Get<FreeImage::CData>()->Bitmap.Get());	break;
			
			default:
				throw Exception::CInvalidArgumentException(L"uType", String::ToString(uType),
					L"Invalid flip type.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
		}

		void	CImage::Resize(const Math::CSize& Size){
			this->Resize(Size, Image::ScaleFilter::BiCubic, false);
		}

		void	CImage::Resize(const Math::CSize& Size, const Image::ScaleFilter uFilter){
			this->Resize(Size, uFilter, false);
		}

		void	CImage::Resize(const Math::CSize& Size, const Image::ScaleFilter uFilter, const bool bKeepRatio){
			if(!this->IsLoaded()){
				throw Exception::CException(
					L"Cannot resize not loaded image.", __FUNCTIONW__, __FILEW__, __LINE__);
			}

			unsigned uWidth = Size.Width;
			unsigned uHeight = Size.Height;
			FREE_IMAGE_FILTER uFreeFilter;

			switch (uFilter)
			{
			case Image::ScaleFilter::Box:			uFreeFilter = FILTER_BOX;	break;
			case Image::ScaleFilter::BiLinear:		uFreeFilter = FILTER_BILINEAR;	break;
			case Image::ScaleFilter::BiCubic:		uFreeFilter = FILTER_BICUBIC;	break;
			case Image::ScaleFilter::BSpline:		uFreeFilter = FILTER_BSPLINE;	break;
			case Image::ScaleFilter::CatmullRom:	uFreeFilter = FILTER_CATMULLROM;	break;
			case Image::ScaleFilter::Lanczos3:		uFreeFilter = FILTER_LANCZOS3;	break;
			default:
				throw Exception::CInvalidArgumentException(L"uFilter", String::ToString(uFilter),
					L"Invalid filter to resize image.", __FUNCTIONW__, __FILEW__, __LINE__);
			}

			if(bKeepRatio){
				Math::CSize imgSize = this->GetSize();
				float fRatio = float(imgSize.Width) / float(imgSize.Height);
				if(imgSize.Width > imgSize.Height){
					uHeight = unsigned(float(uWidth) / fRatio);
				}
				else{
					uWidth = unsigned(float(uHeight) * fRatio);
				}
			}

			FreeImage::CBitmap Bitmap(FreeImage_Rescale(this->m_Data.Get<FreeImage::CData>()->Bitmap.Get(), uWidth, uHeight, uFreeFilter));
			if(!Bitmap.IsValid()){
				throw Exception::CException(
					L"Failed to resize image.", __FUNCTIONW__, __FILEW__, __LINE__);
			}

			this->m_Data.Get<FreeImage::CData>()->Bitmap.Free();
			this->m_Data.Get<FreeImage::CData>()->Bitmap.Set(Bitmap.Release());
		}

		void	CImage::CopyTo(CImage& Image) const{
			if(!this->IsLoaded()){
				throw Exception::CException(
					L"Cannot copy not loaded image.", __FUNCTIONW__, __FILEW__, __LINE__);
			}

			CAutoPtr<FreeImage::CData> Data = new FreeImage::CData(this->m_Data.Get<FreeImage::CData>()->Format);
			Data->Bitmap.Set(FreeImage_Clone(this->m_Data.Get<FreeImage::CData>()->Bitmap.Get()));

			if(!Data->Bitmap.IsValid()){
				throw Exception::CException(
					L"Failed to copy image.", __FUNCTIONW__, __FILEW__, __LINE__);
			}

			Image.Free();
			Image.m_Data.Set<FreeImage::CData>(Data.Reset());
		}

		void	CImage::CopyTo(CImage& Image, const Math::CRectangle& rtSource) const{
			if(!this->IsLoaded()){
				throw Exception::CException(
					L"Cannot copy from not loaded image.", __FUNCTIONW__, __FILEW__, __LINE__);
			}

			CAutoPtr<FreeImage::CData> pData = new FreeImage::CData(this->m_Data.Get<FreeImage::CData>()->Format);

			pData->Bitmap.Set(FreeImage_Copy(this->m_Data.Get<FreeImage::CData>()->Bitmap.Get(), rtSource.GetLeft(), rtSource.GetTop(), rtSource.GetRight(), rtSource.GetBottom()));

			if(!pData->Bitmap.IsValid()){
				throw Exception::CException(
					L"Failed to copy image.", __FUNCTIONW__, __FILEW__, __LINE__);
			}

			Image.Free();
			Image.m_Data.Set<FreeImage::CData>(pData.Reset());
		}

		void	CImage::PasteTo(CImage& Image, const Math::CPoint& ptPosition) const{
			this->PasteTo(Image, ptPosition, 1.0f);
		}

		void	CImage::PasteTo(CImage& Image, const Math::CPoint& ptPosition, const float fAlpha) const{
			if(!this->IsLoaded()){
				throw Exception::CException(
					L"Cannot paste from not loaded image.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
			if(!Image.IsLoaded()){
				throw Exception::CException(
					L"Cannot paste to not loaded image.", __FUNCTIONW__, __FILEW__, __LINE__);
			}

			if(!FreeImage_Paste(Image.m_Data.Get<FreeImage::CData>()->Bitmap.Get(), this->m_Data.Get<FreeImage::CData>()->Bitmap.Get(), 
				ptPosition.X, ptPosition.Y, int(Math::Clamp01(fAlpha) * 255.0f))){
					throw Exception::CException(
						L"Failed to paste image.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
		}

		const CString	CImage::ToString() const{
			if(!this->IsLoaded()){
				return L"Not loaded.";
			}
			Collection::CStringList varList;

			varList.Add(L"Size: " + this->GetSize().ToString());
			varList.Add(L"Bit format: " + String::ToString(this->GetBitFormat()));
			varList.Add(L"Color format: " + String::ToString(this->GetColorFormat()));

			return L"(" + varList.ToString(L", ") + L")";
		}

		const CImage&	CImage::operator=(const CImage& Image){
			Image.CopyTo(*this);
			return *this;
		}

	}

	namespace String{
		// function implementation

		const CString	ToString(const IO::Image::BitFormat uFormat){
			switch (uFormat)
			{
			case IO::Image::BitFormat::f4Bit:	return L"4 Bits";
			case IO::Image::BitFormat::f8Bit:	return L"8 Bits";
			case IO::Image::BitFormat::f16Bit:	return L"16 Bits";
			case IO::Image::BitFormat::f24Bit:	return L"24 Bits";
			case IO::Image::BitFormat::f32Bit:	return L"32 Bits";
			default:
				return L"Unknwon";
			}
		}

		const CString	ToString(const IO::Image::ColorFormat uFormat){
			switch (uFormat)
			{
			case IO::Image::ColorFormat::RGB:	return L"RGB";
			case IO::Image::ColorFormat::RGBA:	return L"RGBA";
			default:
				return L"Unknown";
			}
		}

		const CString	ToString(const IO::Image::FileType uType){
			switch (uType)
			{
			case IO::Image::FileType::Bitmap:	return L"Bitmap";
			case IO::Image::FileType::Jpeg:		return L"Jpeg";
			case IO::Image::FileType::Png:		return L"Png";
			case IO::Image::FileType::Targa:	return L"Targa";
			default:
				return L"Unknown";
			}
		}

		const CString	ToString(const IO::Image::FlipType uType){
			switch (uType)
			{
			case IO::Image::FlipType::Horizontal:	return L"Horizontal";
			case IO::Image::FlipType::Vertical:		return L"Vertical";
			default:
				throw Exception::CInvalidArgumentException(L"uType", FromUInt32((unsigned)uType),
					L"Invalid flip type", __FUNCTIONW__, __FILEW__, __LINE__);
			}
		}

		const CString	ToString(const IO::Image::ScaleFilter uFilter){
			switch (uFilter)
			{
			case IO::Image::ScaleFilter::BiCubic:		return L"BiCubic";
			case IO::Image::ScaleFilter::BiLinear:		return L"BiLinear";
			case IO::Image::ScaleFilter::Box:			return L"Box";
			case IO::Image::ScaleFilter::BSpline:		return L"BSpLine";
			case IO::Image::ScaleFilter::CatmullRom:	return L"CatmullRom";
			case IO::Image::ScaleFilter::Lanczos3:		return L"Lanczos3";
			default:
				throw Exception::CInvalidArgumentException(L"uFilter", FromUInt32((unsigned)uFilter),
					L"Unknown image filter type.", __FUNCTIONW__, __FILEW__, __LINE__);
			}
		}
	}
}