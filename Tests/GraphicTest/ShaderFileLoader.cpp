#include "ShaderFileLoader.h"
#include <Logger.h>
#include <IO_File.h>
#include <IO_TextReader.h>

namespace GraphicTest{
	CShaderLoader::CShaderLoader(CB::CRefPtr<CB::Graphic::IDevice> pDevice, const CB::CString& strFilename){
		CB::Log::Write(L"Loading shaders from file: " + strFilename);
		auto strSource = this->LoadSource(strFilename);

		try{
			CB::Log::Write(L"Compiling shaders...");
			this->pVertexShader = pDevice->Compile(CB::Graphic::ShaderType::Vertex, CB::Graphic::ShaderVersion::ShaderModel_2, strSource, L"vmain");
			this->pFragmentShader = pDevice->Compile(CB::Graphic::ShaderType::Fragment, CB::Graphic::ShaderVersion::ShaderModel_2, strSource, L"fmain");
		}
		catch(CB::Exception::CException& Exception){
			CR_RETHROW(L"Failed to compile shaders: " + pDevice->GetLastCompilationLog(), Exception);
		}
	}

	const CB::CString	CShaderLoader::LoadSource(const CB::CString& strFilename){
		auto pFileStream = CB::IO::File::Open(strFilename, CB::IO::File::AccessType::ReadOnly, CB::IO::File::OpenAction::Open);
		CB::IO::CTextReader reader(pFileStream.Cast<CB::IO::IStream>(), CB::String::Encoding::ANSI);

		return reader.ReadText();
	}
}