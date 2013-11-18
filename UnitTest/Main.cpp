#include <WindowDriver.h>
#include <MessageBox.h>
#include <GraphicDriver.h>
#include <Logger.h>
#include <IO_File.h>
#include <IO_TextReader.h>

bool bRun = true;

const bool	CloseEvent(CB::CRefPtr<CB::Window::IWindow> pWindow){
	bRun = false;

	return true;
}

int __stdcall wWinMain(void* hInstance, void* hPrevInstance, wchar_t* lpCmdLine, int nShowCmd){
	CB::CRefPtr<CB::Log::CLogger> pLog = CB::Log::CLogger::GetInstance();

	pLog->AddStream(CB::IO::File::Open(L"main.log", CB::IO::File::AccessType::WriteOnly).Cast<CB::IO::IStream>());
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

			auto pVertexBuffer = pGraphicDevice->CreateBuffer(CB::Graphic::BufferType::Vertex, CB::Graphic::BufferUsage::Static, CB::Graphic::BufferAccess::Write, verts);
			CB::CString strShaderSource;
			{
				auto pFileStream = CB::IO::File::Open(L"BasicShader.cg", CB::IO::File::AccessType::ReadOnly, CB::IO::File::OpenAction::Open);
				CB::IO::CTextReader reader(pFileStream.Cast<CB::IO::IStream>(), CB::String::Encoding::ANSI);

				strShaderSource = reader.ReadText();
			}

			auto pVertexShader = pGraphicDevice->Compile(CB::Graphic::ShaderType::Vertex, CB::Graphic::ShaderVersion::ShaderModel_2, strShaderSource, L"vmain");
			auto pFragmentShader = pGraphicDevice->Compile(CB::Graphic::ShaderType::Fragment, CB::Graphic::ShaderVersion::ShaderModel_2, strShaderSource, L"fmain");

			CB::Collection::CList<CB::Graphic::CVertexElement> elems;

			elems.Add(CB::Graphic::CVertexElement(0, L"input.vPosition", 0, CB::Graphic::VertexType::Float, 3));

			auto pDeclaration = pGraphicDevice->CreateVertexDeclaration(pVertexShader, elems);

			auto mProjection = CB::Math::CMatrix::GetOrtho(4.0f, 3.0f, -1.0f, 1.0f);
			pGraphicDevice->SetRenderPrimitive(CB::Graphic::PrimitiveType::Triangles);

			while(bRun){
				pGraphicDevice->Clear(CB::Math::CColor(0.2f, 0.2f, 0.2f, 1.0f));

				pGraphicDevice->SetShader(pVertexShader);
				pGraphicDevice->SetShader(pFragmentShader);

				pVertexShader->SetUniform(L"mProj", mProjection);

				pGraphicDevice->SetVertexDeclaration(pDeclaration);

				pGraphicDevice->SetVertexBuffer(0, pVertexBuffer);

				pGraphicDevice->Render(1);

				pWinManager->ProcessEvents();
				pGraphicDevice->Swap();
			}
		}
	}
	catch(CB::Exception::CException& Excpetion){
		CB::Message::Show(Excpetion, CB::Message::Icon::Error);
	}
	return 0;
}