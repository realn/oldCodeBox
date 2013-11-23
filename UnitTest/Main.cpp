#include <WindowDriver.h>
#include <MessageBox.h>
#include <GraphicDriver.h>
#include <Logger.h>
#include <IO_File.h>
#include <IO_TextReader.h>
#include <IO_Image.h>
#include <Font.h>

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
				auto pFileStream = CB::IO::File::Open(L"ETHNOCEN.TTF", CB::IO::File::AccessType::ReadOnly, CB::IO::File::OpenAction::Open);

				auto pFontManager = CB::Font::CManager::Create();
				auto pFont = pFontManager->Load(pFileStream.Cast<CB::IO::IStream>());

				pFont->SetSize(CB::Math::CSize(256, 256));
				pFont->SelectGlyphByChar(L'B');

				CB::Collection::CList<byte> Pixels;
				CB::Math::CSize Size;
				uint32 uBPP = 0;
				pFont->GetGlyphBitmap(Pixels, Size, uBPP);

				CB::Collection::CList<byte> Data(Size.Width * Size.Height * 4);
				for(uint32 uIndex = 0; uIndex < Pixels.GetLength(); uIndex++){
					Data[uIndex * 4 + 0] = Pixels[uIndex];
					Data[uIndex * 4 + 1] = Pixels[uIndex];
					Data[uIndex * 4 + 2] = Pixels[uIndex];
					Data[uIndex * 4 + 3] = Pixels[uIndex];
				}

				pTexture = pGraphicDevice->CreateTexture2D(Size, CB::Graphic::BufferUsage::Static, CB::Graphic::BufferAccess::Write, CB::Graphic::BufferFormat::R8G8B8A8, CB::Graphic::BufferFormat::R8G8B8A8, Data);
			}

			CB::CRefPtr<CB::Graphic::IShader> pVertexShader;
			CB::CRefPtr<CB::Graphic::IShader> pFragmentShader;

			try{
				pVertexShader = pGraphicDevice->Compile(CB::Graphic::ShaderType::Vertex, CB::Graphic::ShaderVersion::ShaderModel_2, strShaderSource, L"vmain");
				pFragmentShader = pGraphicDevice->Compile(CB::Graphic::ShaderType::Fragment, CB::Graphic::ShaderVersion::ShaderModel_2, strShaderSource, L"fmain");
			}
			catch(CB::Exception::CException& Ex){
				auto listing = pGraphicDevice->GetLastCompilationLog();
			}

			CB::Collection::CList<CB::Graphic::CVertexElement> elems;

			elems.Add(CB::Graphic::CVertexElement(0, L"input.vPosition", 0, CB::Graphic::VertexType::Float, 3));
			elems.Add(CB::Graphic::CVertexElement(1, L"input.vTexCoord", 0, CB::Graphic::VertexType::Float, 2));

			auto pDeclaration = pGraphicDevice->CreateVertexDeclaration(pVertexShader, elems);

			pFragmentShader->SetSampler(L"texDiffuse", pTexture.Cast<CB::Graphic::IBaseTexture>());

			auto mProjection = CB::Math::CMatrix::GetOrtho(4.0f, 3.0f, -1.0f, 1.0f);
			pGraphicDevice->SetRenderPrimitive(CB::Graphic::PrimitiveType::Triangles);

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