#include <Logger.h>
#include <Logger_Formatters.h>
#include <IO_OSConsoleStream.h>
#include <IO_File.h>
#include <MessageBox.h>
#include <WindowDriver.h>
#include <GraphicDriver.h>

#include "ShaderFileLoader.h"
#include "RectOrthoModel.h"

bool g_bRun = true;

const bool	CloseEvent(CB::CRefPtr<CB::Window::IWindow> pWindow){
	g_bRun = false;
	return true;
}

int main(){
	auto pLogger = CB::Log::CLogger::GetInstance();
	pLogger->AddStream(CB::IO::File::Open(L"main.log", CB::IO::File::AccessType::WriteOnly, CB::IO::File::OpenAction::AlwaysCreate).Cast<CB::IO::IStream>());
	pLogger->AddStream(CB::IO::Console::Create().Cast<CB::IO::IStream>(), CB::Log::CTextFormatter::Create(CB::String::Encoding::ANSI).Cast<CB::Log::IEntryFormatter>());
	pLogger->SetDebugMode(true);

	try{
		auto pWinDriver = CB::Window::LoadDriver(L"MSWindowDriver");
		auto pGraphicDriver = CB::Graphic::LoadDriver(L"OGLGraphicDriver");
		{
			auto pWinManager = pWinDriver->CreateManager();
			auto pGraphicManager = pGraphicDriver->CreateManager(pWinManager);
			
			CB::Math::CSize outSize(640, 480);
			auto pWindow = pWinManager->CreateWindow(L"GraphicTest", CB::Window::Style::Single, outSize);

			auto pGraphicAdapter = pGraphicManager->GetDefaultAdapter();

			CB::Graphic::CDisplayMode dispMode(pWindow->GetSize(), 0, CB::Graphic::BufferFormat::B8G8R8X8);
			CB::Graphic::CDeviceDesc devDesc(pWindow, dispMode, CB::Graphic::BufferFormat::D24S8, false);

			CB::Collection::CList<CB::Graphic::FeatureLevel> featureLevels;
			featureLevels.Add(CB::Graphic::FeatureLevel::Level_1);

			auto pGraphicDevice = pGraphicAdapter->CreateDevice(pWindow, devDesc, featureLevels);

			pWindow->OnClose += CB::Signals::CFunc<const bool, CB::CRefPtr<CB::Window::IWindow>>(CloseEvent);
			pWindow->SetVisible(true);

			GraphicTest::CShaderLoader shaders(pGraphicDevice, L"Shaders/BasicShader.cg");

			float32 fAspect = (float32)outSize.Width / (float32)outSize.Height;
			CB::Math::CMatrix mProj = CB::Math::CMatrix::GetPerspective(fAspect, 90.0f, 0.5f, 10.0f);
			CB::Math::CMatrix mView = CB::Math::CMatrix::GetTranslation(0.0f, 0.0f, -1.0f);

			GraphicTest::CRectOrthoModel model(pGraphicDevice, shaders.pVertexShader, 1.0f, 1.0f);

			while(g_bRun){
				pGraphicDevice->Clear(1.0f, 1);
				pGraphicDevice->Clear(CB::Math::CColor(1.0f, 0.5f, 0.0f, 1.0f));

				pGraphicDevice->BeginRender();

				pGraphicDevice->SetShader(shaders.pVertexShader);
				pGraphicDevice->SetShader(shaders.pFragmentShader);
				pGraphicDevice->SetVertexDeclaration(model.pVertexDecl);

				shaders.pVertexShader->SetUniform(L"vinput.mProj", mProj);
				shaders.pVertexShader->SetUniform(L"vinput.mView", mView);
				shaders.pVertexShader->SetUniform(L"vinput.mModel", model.mModelMatrix);

				pGraphicDevice->SetVertexBuffer(0, model.pVertexBuffer);

				model.Render(pGraphicDevice);

				pGraphicDevice->EndRender();

				pWinManager->ProcessEvents();
				model.Update(1.0f);

				pGraphicDevice->Swap();
			}
		}
	}
	catch(CB::Exception::CException& Exception){
		CB::Log::Write(Exception, CB::Log::LogLevel::Fatal);
		CB::Message::Show(Exception, CB::Message::Icon::Error);
	}
	return 0;
}