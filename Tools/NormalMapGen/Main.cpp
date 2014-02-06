#include <iostream>
#include <IO_Image.h>
#include <IO_File.h>
#include <Collection.h>
#include <Math_Vector.h>
#include <CBMath.h>

const CB::CString strFilename = L"crate_height.png";
const CB::CString strOutFilename = L"crate_normal.png";

uint32 GetIdx(const CB::Math::CSize& Size, uint32 x, uint32 y){
	return y * Size.Width + x;
}

int main(){

	CB::Math::CSize imgSize;
	uint32 uBPP = 0;
	CB::Collection::CList<byte> Data;
	CB::Collection::CList<byte> OutData;
	{
		CB::IO::CImage img;
		auto pStream = CB::IO::File::Open(strFilename).Cast<CB::IO::IStream>();

		img.ReadFromStream(pStream);
		img.GetPixels(Data);
		imgSize = img.GetSize();
		uBPP = img.GetBytesPerPixel();
		std::wcout << L"Size: " << img.GetSize().ToString().GetPointer() << std::endl;
	}

	float32 fAdj = 2.0f;
	OutData.Resize(imgSize.Width * imgSize.Height * 3);
	for(uint32 y = 0; y < imgSize.Height - 1; y++){
		for(uint32 x = 0; x < imgSize.Width - 1; x++){
			uint32 uIndex = GetIdx(imgSize, x, y);
			uint32 uIndexX = GetIdx(imgSize, x + 1, y);
			uint32 uIndexY = GetIdx(imgSize, x, y + 1);

			byte P = Data[uIndex * uBPP];
			byte X = Data[uIndexX * uBPP];
			byte Y = Data[uIndexY * uBPP];

			float32 fX = float32(P - X) * fAdj;
			float32 fY = float32(P - Y) * fAdj;

			CB::Math::CVector3D v(fX, fY, 1.0f);
			v.Normalize();

			v *= 0.5f;
			v += 0.5f;

			OutData[uIndex * 3 + 0] = CB::Math::Convert01to0255(v.X);
			OutData[uIndex * 3 + 1] = CB::Math::Convert01to0255(v.Y);
			OutData[uIndex * 3 + 2] = CB::Math::Convert01to0255(v.Z);
		}
	}

	if(CB::IO::File::Exists(strOutFilename))
		CB::IO::File::Delete(strOutFilename);

	{
		CB::IO::CImage img(imgSize, CB::IO::Image::BitFormat::f24Bit);

		img.SetPixels(OutData);

		auto pOutStream = CB::IO::File::Open(strOutFilename, CB::IO::File::AccessType::WriteOnly, CB::IO::File::OpenAction::AlwaysCreate).Cast<CB::IO::IStream>();

		img.WriteToStream(pOutStream, CB::IO::Image::FileType::Png);

	}

	std::wcin.get();
	return 0;
}