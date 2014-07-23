#include <Logger.h>
#include <Logger_Formatters.h>
#include <IO_OSConsoleStream.h>
#include <IO_File.h>
#include <MessageBox.h>
#include <WindowDriver.h>
#include <GraphicDriver.h>
#include <Timer.h>

#include "TextureFileLoader.h"
#include "ShaderFileLoader.h"
#include "RectOrthoModel.h"
#include "CubeModel.h"

bool g_bRun = true;
enum class TURN_DIR{
	NONE,
	LEFT,
	RIGHT,
};

enum class MOVE_DIR{
	NONE,
	FORWARD,
	BACKWARD,
};

TURN_DIR	g_uTurnDir = TURN_DIR::NONE;
MOVE_DIR	g_uMoveDir = MOVE_DIR::NONE;

float32 g_fTurnY = 0.0f;
float32 g_fViewZ = -2.0f;
CB::CTimer	g_Timer;
CB::CRefPtr<CB::Graphic::ITexture2D> g_pTexture;

const bool	CloseEvent(CB::CRefPtr<CB::Window::IWindow> pWindow){
	g_bRun = false;
	return true;
}

const bool	CharEvent(CB::CRefPtr<CB::Window::IWindow> pWindow, const wchar character){
	CB::CString strText(character);

	CB::Message::Show(strText);

	return true;
}

const bool	KeyDownEvent(CB::CRefPtr<CB::Window::IWindow> pWindow, const CB::Window::VirtualKey uKey){
	switch (uKey)
	{
	case CB::Window::VirtualKey::W:
		g_uMoveDir = MOVE_DIR::FORWARD;
		return true;

	case CB::Window::VirtualKey::S:
		g_uMoveDir = MOVE_DIR::BACKWARD;
		return true;

	case CB::Window::VirtualKey::A:	
		g_uTurnDir = TURN_DIR::LEFT;
		return true;

	case CB::Window::VirtualKey::D:
		g_uTurnDir = TURN_DIR::RIGHT;
		return true;

	case CB::Window::VirtualKey::T:
		g_pTexture->SetFilters(CB::Graphic::TextureFilter::Nearest, CB::Graphic::TextureFilter::Nearest);
		return true;

	case CB::Window::VirtualKey::G:
		g_pTexture->SetFilters(CB::Graphic::TextureFilter::Linear, CB::Graphic::TextureFilter::Linear);
		return true;

	case CB::Window::VirtualKey::B:
		g_pTexture->SetFilters(CB::Graphic::TextureFilter::Linear, CB::Graphic::TextureFilter::Linear, CB::Graphic::TextureFilter::Linear);
		return true;

	case CB::Window::VirtualKey::Y:
		g_pTexture->SetAnisotropy(1);
		return true;

	case CB::Window::VirtualKey::H:
		g_pTexture->SetAnisotropy(8);
		return true;

	case CB::Window::VirtualKey::N:
		g_pTexture->SetAnisotropy(16);
		return true;
		
	default:
		return false;
	}
}

const bool	KeyUpEvent(CB::CRefPtr<CB::Window::IWindow> pWindow, const CB::Window::VirtualKey uKey){
	switch (uKey)
	{
	case CB::Window::VirtualKey::W:
	case CB::Window::VirtualKey::S:
		g_uMoveDir = MOVE_DIR::NONE;
		return true;

	case CB::Window::VirtualKey::A:
	case CB::Window::VirtualKey::D:
		g_uTurnDir = TURN_DIR::NONE;
		return true;

	default:
		return false;
	}
}

int main(){
	auto pLogger = CB::Log::CLogger::GetInstance();
	pLogger->AddStream(CB::IO::File::Open(L"main.log", CB::IO::File::AccessType::WriteOnly, CB::IO::File::OpenAction::AlwaysCreate).Cast<CB::IO::IStream>());
	pLogger->AddStream(CB::IO::Console::Create().Cast<CB::IO::IStream>(), CB::Log::CTextFormatter::Create(CB::String::Encoding::ANSI).Cast<CB::Log::IEntryFormat>());
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
			//pWindow->OnChar += CB::Signals::CFunc<const bool, CB::CRefPtr<CB::Window::IWindow>, const wchar>(CharEvent);
			pWindow->OnKeyDown += CB::Signals::CFunc<const bool, CB::CRefPtr<CB::Window::IWindow>, const CB::Window::VirtualKey>(KeyDownEvent);
			pWindow->OnKeyUp += CB::Signals::CFunc<const bool, CB::CRefPtr<CB::Window::IWindow>, const CB::Window::VirtualKey>(KeyUpEvent);

			pWindow->SetVisible(true);

			CB::Graphic::CDepthStencilStateDesc depthDesc;
			depthDesc.bDepthTestEnabled = true;
			depthDesc.uDepthFunction = CB::Graphic::CompareFunc::LessEqual;
			auto pDepthState = pGraphicDevice->CreateState(depthDesc);
			pGraphicDevice->SetState(pDepthState.Cast<CB::Graphic::IDeviceState>());

			CB::Graphic::CRasterizerStateDesc rastDesc;
			//rastDesc.uCullMode = CB::Graphic::CullMode::None;
			auto pRastState = pGraphicDevice->CreateState(rastDesc);
			pGraphicDevice->SetState(pRastState.Cast<CB::Graphic::IDeviceState>());

			GraphicTest::CTexture2DFileLoader texture(pGraphicDevice, L"Assets/Crate.jpg");
			GraphicTest::CShaderLoader shaders(pGraphicDevice, L"Shaders/TextureShader.cg");

			GraphicTest::CVertexShaderConfig vconfig;
			vconfig.uFlags = (uint32)GraphicTest::VSCFlags::Vertex | (uint32)GraphicTest::VSCFlags::TCoord;
			vconfig.pVertexShader = shaders.pVertexShader;
			vconfig.strVertexName = L"vinput.vPosition";
			vconfig.strTCoordName = L"vinput.vTexCoord";

			float32 fAspect = (float32)outSize.Width / (float32)outSize.Height;
			CB::Math::CMatrix mProj = CB::Math::CMatrix::GetPerspective(fAspect, 60.0f, 1.0f, 100.0f);
			CB::Math::CMatrix mView = CB::Math::CMatrix::GetRotation(CB::Math::AxisOrientation::AxisX, -35.0f) * CB::Math::CMatrix::GetTranslation(0.0f, 0.0f, -2.4f);

			GraphicTest::CCubeModel model(pGraphicDevice, CB::Math::CVector3D(1.0f), vconfig);

			shaders.pFragmentShader->SetSampler(L"texDiffuse", texture.pTexture.Cast<CB::Graphic::IBaseTexture>());
			//texture.pTexture->SetFilters(CB::Graphic::TextureFilter::Linear, CB::Graphic::TextureFilter::Linear, CB::Graphic::TextureFilter::Linear);
			//texture.pTexture->SetAnisotropy(8);
			g_pTexture = texture.pTexture;

			CB::Log::Write(L"Max texture size: " + CB::String::ToString(pGraphicDevice->GetMaxTextureSize(CB::Graphic::TextureType::Texture2D)));
			CB::Log::Write(L"Max 3D texture size: " + CB::String::ToString(pGraphicDevice->GetMaxTextureSize(CB::Graphic::TextureType::Texture3D)));

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

				pGraphicDevice->SetVertexBuffer(0, model.pBuffer);
				pGraphicDevice->SetIndexBuffer(model.pIndices);

				model.Render(pGraphicDevice);

				pGraphicDevice->EndRender();

				g_Timer.Update();
				pWinManager->ProcessEvents();
				model.Update(g_Timer.GetTimeDelta());
				switch (g_uTurnDir)
				{
				case TURN_DIR::LEFT:
					g_fTurnY -= 60.0f * g_Timer.GetTimeDelta();
					break;
				case TURN_DIR::RIGHT:
					g_fTurnY += 60.0f * g_Timer.GetTimeDelta();
					break;
				default:
					break;
				}

				switch (g_uMoveDir)
				{
				case MOVE_DIR::FORWARD:
					g_fViewZ -= 1.0f * g_Timer.GetTimeDelta();
					break;
				case MOVE_DIR::BACKWARD:
					g_fViewZ += 1.0f * g_Timer.GetTimeDelta();
					break;
				default:
					break;
				}

				mView = CB::Math::CMatrix::GetTranslation(0.0f, 0.0f, g_fViewZ) * 
					CB::Math::CMatrix::GetRotation(CB::Math::AxisOrientation::AxisY, g_fTurnY) *
					CB::Math::CMatrix::GetRotation(CB::Math::AxisOrientation::AxisX, -35.0f)
					;

				pGraphicDevice->Swap();
			}

			g_pTexture.Release();
		}
	}
	catch(CB::Exception::CException& Exception){
		CB::Log::Write(Exception, CB::Log::LogLevel::Fatal);
		CB::Message::Show(Exception, CB::Message::Icon::Error);
	}
	return 0;
}