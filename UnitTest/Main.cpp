#include <WindowDriver.h>
#include <MessageBox.h>
#include <GraphicDriver.h>
#include <Logger.h>
#include <IO_File.h>
#include <IO_TextReader.h>
#include <IO_Image.h>
#include <Font.h>
#include <AudioDriver.h>
#include <IO_Sound.h>

bool bRun = true;

const bool	CloseEvent(CB::CRefPtr<CB::Window::IWindow> pWindow){
	bRun = false;

	return true;
}

int __stdcall wWinMain(void* hInstance, void* hPrevInstance, wchar_t* lpCmdLine, int nShowCmd){
	CB::CRefPtr<CB::Log::CLogger> pLog = CB::Log::CLogger::GetInstance();

	pLog->AddStream(CB::IO::File::Open(L"main.log", CB::IO::File::AccessType::WriteOnly, CB::IO::File::OpenAction::AlwaysCreate).Cast<CB::IO::IStream>());
	pLog->SetDebugMode(true);

	try{
		auto pWinDriver = CB::Window::LoadDriver(L"MSWindowDriver");
		auto pGraphicDriver = CB::Graphic::LoadDriver(L"OGLGraphicDriver");
		auto pAudioDriver = CB::Audio::LoadDriver(L"OALAudioDriver");
		{
			auto pWinManager = pWinDriver->CreateManager();
			auto pGraphicManager = pGraphicDriver->CreateManager(pWinManager);

			auto pWindow = pWinManager->CreateWindow(L"Sample Window", CB::Window::Style::Single, CB::Math::CSize(640, 480));

			CB::Graphic::CDeviceDesc desc(pWindow, CB::Graphic::CDisplayMode(pWindow->GetSize(), 0, CB::Graphic::BufferFormat::R8G8B8A8_sRGB), CB::Graphic::BufferFormat::D24S8, false);
			CB::Collection::CList<CB::Graphic::FeatureLevel> featureLevels;
			featureLevels.Add(CB::Graphic::FeatureLevel::Level_1);
			auto pGraphicDevice = pGraphicManager->GetDefaultAdapter()->CreateDevice(pWindow, desc, featureLevels);

			pWindow->OnClose += CB::Signals::CFunc<const bool, CB::CRefPtr<CB::Window::IWindow>>(CloseEvent);
			pWindow->SetVisible(true);

			CB::Collection::CList<CB::Math::CVector3D> verts;
			verts.Add(CB::Math::CVector3D(-0.5f, -0.2f, 0.0f));
			verts.Add(CB::Math::CVector3D(0.0f, 0.6f, 0.0f));
			verts.Add(CB::Math::CVector3D(0.5f, -0.2f, 0.0f));

			CB::Collection::CList<CB::Math::CVector2D> tcoord;
			tcoord.Add(CB::Math::CVector2D(0.0f, 1.0f));
			tcoord.Add(CB::Math::CVector2D(0.5f, 0.0f));
			tcoord.Add(CB::Math::CVector2D(1.0f, 1.0f));

			auto pVertexBuffer = pGraphicDevice->CreateBuffer(CB::Graphic::BufferType::Vertex, CB::Graphic::BufferUsage::Static, CB::Graphic::BufferAccess::Write, verts);
			auto pTCoordBuffer = pGraphicDevice->CreateBuffer(CB::Graphic::BufferType::Vertex, CB::Graphic::BufferUsage::Static, CB::Graphic::BufferAccess::Write, tcoord);
			CB::CString strShaderSource;
			{
				auto pFileStream = CB::IO::File::Open(L"BasicShader.cg", CB::IO::File::AccessType::ReadOnly, CB::IO::File::OpenAction::Open);
				CB::IO::CTextReader reader(pFileStream.Cast<CB::IO::IStream>(), CB::String::Encoding::ANSI);

				strShaderSource = reader.ReadText();
			}
			
			CB::CRefPtr<CB::Graphic::ITexture2D> pTexture;
			{
				auto pFileStream = CB::IO::File::Open(L"Crate.jpg", CB::IO::File::AccessType::ReadOnly, CB::IO::File::OpenAction::Open);

				CB::IO::CImage img;
				img.ReadFromStream(pFileStream.Cast<CB::IO::IStream>());
				img.Convert(CB::IO::Image::BitFormat::f32Bit);
				img.Resize(CB::Math::CSize(256,256));
				CB::Collection::CList<byte> Pixels;
				img.GetPixels(Pixels);

				pTexture = pGraphicDevice->CreateTexture2D(img.GetSize(), CB::Graphic::BufferUsage::Static, CB::Graphic::BufferAccess::Write, CB::Graphic::BufferFormat::R8G8B8A8, CB::Graphic::BufferFormat::B8G8R8A8, Pixels);
			}

			CB::CRefPtr<CB::Graphic::IShader> pVertexShader;
			CB::CRefPtr<CB::Graphic::IShader> pFragmentShader;

			try{
				pVertexShader = pGraphicDevice->Compile(CB::Graphic::ShaderType::Vertex, CB::Graphic::ShaderVersion::ShaderModel_2, strShaderSource, L"vmain");
				pFragmentShader = pGraphicDevice->Compile(CB::Graphic::ShaderType::Fragment, CB::Graphic::ShaderVersion::ShaderModel_2, strShaderSource, L"fmain");
			}
			catch(CB::Exception::CException& Ex){
				auto listing = pGraphicDevice->GetLastCompilationLog();
				throw;
			}

			CB::Collection::CList<CB::Graphic::CVertexElement> elems;

			elems.Add(CB::Graphic::CVertexElement(0, L"input.vPosition", 0, CB::Graphic::VertexType::Float, 3));
			elems.Add(CB::Graphic::CVertexElement(1, L"input.vTexCoord", 0, CB::Graphic::VertexType::Float, 2));

			auto pDeclaration = pGraphicDevice->CreateVertexDeclaration(pVertexShader, elems);

			pFragmentShader->SetSampler(L"texDiffuse", pTexture.Cast<CB::Graphic::IBaseTexture>());

			auto mProjection = CB::Math::CMatrix::GetOrtho(4.0f, 3.0f, -1.0f, 1.0f);
			pGraphicDevice->SetRenderPrimitive(CB::Graphic::PrimitiveType::Triangles);

			auto pAudioManager = pAudioDriver->CreateManager();
			auto pAudioAdapter = pAudioManager->GetDefaultAdapter();
			auto pAudioDevice = pAudioAdapter->CreateDevice();

			CB::CRefPtr<CB::Audio::IBuffer> pBuffer;

			{
				auto pFile = CB::IO::File::Open(L"Sound.wav", CB::IO::File::AccessType::ReadOnly, CB::IO::File::OpenAction::Open);
				CB::IO::CSound sound(pFile.Cast<CB::IO::IStream>());

				CB::Collection::CList<int16> data(sound.GetNumberOfChannels() * sound.GetNumberOfFrames());
				sound.ReadFrames(data);

				CB::Audio::BufferFormat uFormat = CB::Audio::BufferFormat::Stereo16Bit;
				if(sound.GetNumberOfChannels() == 1)
					uFormat = CB::Audio::BufferFormat::Mono16Bit;

				pBuffer = pAudioDevice->CreateBuffer(uFormat, sound.GetFrequency(), sound.GetNumberOfFrames());
			}

			auto pSource = pAudioDevice->CreateSource();

			pSource->SetStaticBuffer(pBuffer);
			pSource->SetPosition(CB::Math::CVector3D());
			pAudioDevice->SetPosition(CB::Math::CVector3D());

			pSource->Play();

			CB::Log::Write(L"Entering Main Loop.", CB::Log::LogLevel::Debug);
			while(bRun){
				pGraphicDevice->Clear(CB::Math::CColor(0.2f, 0.2f, 0.2f, 1.0f));

				pGraphicDevice->SetShader(pVertexShader);
				pGraphicDevice->SetShader(pFragmentShader);

				pVertexShader->SetUniform(L"mProj", mProjection);

				pGraphicDevice->SetVertexDeclaration(pDeclaration);

				pGraphicDevice->SetVertexBuffer(0, pVertexBuffer);
				pGraphicDevice->SetVertexBuffer(1, pTCoordBuffer);

				pGraphicDevice->Render(1);

				pWinManager->ProcessEvents();
				pAudioDevice->ProcessEvents();
				pGraphicDevice->Swap();
			}
			CB::Log::Write(L"Leaving Main Loop.", CB::Log::LogLevel::Debug);
		}
	}
	catch(CB::Exception::CException& Excpetion){
		CB::Message::Show(Excpetion, CB::Message::Icon::Error);
	}
	return 0;
}