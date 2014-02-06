#include <Logger.h>
#include <Logger_Formatters.h>
#include <IO_OSConsoleStream.h>
#include <IO_File.h>
#include <MessageBox.h>
#include <WindowDriver.h>
#include <GraphicDriver.h>
#include <Timer.h>
#include <GraphicTools.h>
#include <Font.h>

#include "TextureFileLoader.h"
#include "ShaderFileLoader.h"

bool g_bRun = true;
CB::CTimer	g_Timer;
CB::CRefPtr<CB::Graphic::ITexture2D> g_pTexture;

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

			CB::Graphic::CDepthStencilStateDesc depthDesc;
			depthDesc.bDepthTestEnabled = true;
			depthDesc.uDepthFunction = CB::Graphic::CompareFunc::LessEqual;
			auto pDepthState = pGraphicDevice->CreateState(depthDesc);
			pGraphicDevice->SetState(pDepthState.Cast<CB::Graphic::IDeviceState>());

			CB::Graphic::CRasterizerStateDesc rastDesc;
			rastDesc.uCullMode = CB::Graphic::CullMode::None;
			auto pRastState = pGraphicDevice->CreateState(rastDesc);
			pGraphicDevice->SetState(pRastState.Cast<CB::Graphic::IDeviceState>());

			CB::Graphic::CBlendStateDesc blendDesc;
			blendDesc.ColorBlend.uDestOperand = CB::Graphic::BlendOption::OneMinusSourceAlpha;
			blendDesc.ColorBlend.uSourceOperand = CB::Graphic::BlendOption::SourceAlpha;
			blendDesc.ColorBlend.uOperation = CB::Graphic::BlendOperation::Add;
			blendDesc.AlphaBlend.uDestOperand = CB::Graphic::BlendOption::OneMinusSourceAlpha;
			blendDesc.AlphaBlend.uSourceOperand = CB::Graphic::BlendOption::SourceAlpha;
			blendDesc.AlphaBlend.uOperation = CB::Graphic::BlendOperation::Add;
			blendDesc.bEnabled[0] = true;
			auto pBlendState = pGraphicDevice->CreateState(blendDesc);
			pGraphicDevice->SetState(pBlendState.Cast<CB::Graphic::IDeviceState>());

			auto pFontManager = CB::Font::CManager::Create();

			auto pFontStream = CB::IO::File::Open(L"Assets/font.ttf").Cast<CB::IO::IStream>();
			auto pFont = pFontManager->Load(pFontStream);
			
			pFont->SelectFace(0);
			pFont->SetSize(24);

			CB::Collection::CList<CB::Tools::CFontCharDesc> charDescs;
			CB::Tools::CFontTextureGenerator fontGen(pGraphicDevice);

			fontGen.MaxTextureSize.Set(512, 512);
			auto pTexture = fontGen.Generate(pFont, charDescs);

			CB::Tools::CTextMeshGenerator textGen(charDescs);
			CB::Tools::CMeshRawIVT textMesh;

			textGen.Generate(L"Marek	M³ynarski!", textMesh);

			CB::Collection::CList<CB::Graphic::CVertexElement> vEls;
			vEls.Add(CB::Graphic::CVertexElement(0, L"vinput.vPosition", CB::Graphic::VertexType::Float, 3, 0));
			vEls.Add(CB::Graphic::CVertexElement(1, L"vinput.vTexCoord", CB::Graphic::VertexType::Float, 2, 0));

			GraphicTest::CShaderLoader shaders(pGraphicDevice, L"Shaders/TextureShader.cg");

			auto pTextDecl = pGraphicDevice->CreateVertexDeclaration(shaders.pVertexShader, vEls);

			auto pTextVertexBuffer = pGraphicDevice->CreateBuffer(CB::Graphic::BufferType::Vertex, CB::Graphic::BufferUsage::Dynamic, CB::Graphic::BufferAccess::Write, textMesh.Vertices);
			auto pTextTCoordBuffer = pGraphicDevice->CreateBuffer(CB::Graphic::BufferType::Vertex, CB::Graphic::BufferUsage::Dynamic, CB::Graphic::BufferAccess::Write, textMesh.TexCoords);
			auto pTextIndexBuffer = pGraphicDevice->CreateBuffer(CB::Graphic::BufferType::Index, CB::Graphic::BufferUsage::Dynamic, CB::Graphic::BufferAccess::Write, textMesh.Indices);

			float32 fAspect = (float32)outSize.Width / (float32)outSize.Height;
			CB::Math::CMatrix mProj = CB::Math::CMatrix::GetPerspective(fAspect, 60.0f, 1.0f, 100.0f);
			CB::Math::CMatrix mView = CB::Math::CMatrix::GetTranslation(-4.0f, 0.0f, -3.4f);
			CB::Math::CMatrix mModel = CB::Math::CMatrix::GetIdentity();

			shaders.pFragmentShader->SetSampler(L"texDiffuse", pTexture.Cast<CB::Graphic::IBaseTexture>());
			pTexture->SetFilters(CB::Graphic::TextureFilter::Linear, CB::Graphic::TextureFilter::Linear, CB::Graphic::TextureFilter::Linear);
			pTexture->SetAnisotropy(8);
			//g_pTexture = texture.pTexture;			

			while(g_bRun){
				pGraphicDevice->Clear(1.0f, 1);
				pGraphicDevice->Clear(CB::Math::CColor(1.0f, 0.5f, 0.0f, 1.0f));

				pGraphicDevice->BeginRender();

				pGraphicDevice->SetShader(shaders.pVertexShader);
				pGraphicDevice->SetShader(shaders.pFragmentShader);

				static float32 fV = 0.0f;
				fV += 20 * g_Timer.GetTimeDelta();
				mModel = CB::Math::CMatrix::GetRotation(CB::Math::AxisOrientation::AxisX, fV);

				shaders.pVertexShader->SetUniform(L"vinput.mProj", mProj);
				shaders.pVertexShader->SetUniform(L"vinput.mView", mView);
				shaders.pVertexShader->SetUniform(L"vinput.mModel", mModel);

				pGraphicDevice->SetVertexDeclaration(pTextDecl);
				pGraphicDevice->SetVertexBuffer(0, pTextVertexBuffer);
				pGraphicDevice->SetVertexBuffer(1, pTextTCoordBuffer);
				pGraphicDevice->SetIndexBuffer(pTextIndexBuffer);

				pGraphicDevice->RenderIndexed(textMesh.uNumberOfPolygons);

				pGraphicDevice->EndRender();

				g_Timer.Update();
				pWinManager->ProcessEvents();

				float fFPS = 1.0f / (g_Timer.GetTimeDelta() == 0.0f ? 1.0f : g_Timer.GetTimeDelta());
				uint32 uFPS = (uint32)fFPS;

				textMesh.Clear();
				textGen.Generate(L"FPS: " + CB::String::ToString(uFPS), textMesh);

				pTextVertexBuffer->LoadData(textMesh.Vertices);
				pTextTCoordBuffer->LoadData(textMesh.TexCoords);
				pTextIndexBuffer->LoadData(textMesh.Indices);

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