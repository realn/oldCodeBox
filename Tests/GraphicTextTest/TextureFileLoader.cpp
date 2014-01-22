#include "TextureFileLoader.h"
#include <IO_File.h>
#include <IO_StreamReader.h>
#include <IO_Image.h>

namespace GraphicTest{
	CTexture2DFileLoader::CTexture2DFileLoader(CB::CRefPtr<CB::Graphic::IDevice> pDevice, const CB::CString& strFilename) :
		m_strFilename(strFilename)
	{
		if(this->m_strFilename.IsEmpty())
			throw CB::Exception::CZeroLengthArgumentException(L"strFilename", L"Invalid filename for texture loading.", CR_INFO());

		this->Reload(pDevice);
	}

	void	CTexture2DFileLoader::Reload(CB::CRefPtr<CB::Graphic::IDevice> pDevice){
		auto pStream = CB::IO::File::Open(this->m_strFilename, CB::IO::File::AccessType::ReadOnly, CB::IO::File::OpenAction::Open);
		CB::IO::CImage img;

		img.ReadFromStream(pStream.Cast<CB::IO::IStream>());
		img.Convert(CB::IO::Image::BitFormat::f24Bit);
		
		CB::Collection::CList<byte> data;
		img.GetPixels(data);

		CB::Graphic::BufferFormat uInputFormat = CB::Graphic::BufferFormat::B8G8R8A8;
		if(img.GetColorFormat() == CB::IO::Image::ColorFormat::RGB){
			uInputFormat = CB::Graphic::BufferFormat::B8G8R8;
		}

		this->pTexture = pDevice->CreateTexture2D(img.GetSize(), CB::Graphic::BufferUsage::Static, CB::Graphic::BufferAccess::Write, CB::Graphic::BufferFormat::R8G8B8A8,  uInputFormat, data);
	}
}