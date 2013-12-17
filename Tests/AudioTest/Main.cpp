#include <Logger.h>
#include <AudioDriver.h>
#include <IO_File.h>
#include <IO_OSConsoleStream.h>
#include <MessageBox.h>
#include <IO_Sound.h>
#include <Threads.h>
#include <Math.h>

int main(){
	auto pLogger = CB::Log::CLogger::GetInstance();
	try{
		pLogger->SetDebugMode(true);
		pLogger->AddStream(CB::IO::File::Open(L"main.log", CB::IO::File::AccessType::WriteOnly, CB::IO::File::OpenAction::AlwaysCreate).Cast<CB::IO::IStream>());
		pLogger->AddStream(CB::IO::Console::Create().Cast<CB::IO::IStream>());
		auto pDriver = CB::Audio::LoadDriver(L"OALAudioDriver");
		{
			auto pManager = pDriver->CreateManager();
			auto pAdapter = pManager->GetDefaultAdapter();
			auto pDevice = pAdapter->CreateDevice();

			auto pListener = pDevice->CreateListener();
			
			uint32 uSampleRate = 0;
			uint32 uSamples = 0;
			uint32 uChannels = 0;
			CB::Collection::CList<int16> Samples;
			{
				auto pStream = CB::IO::File::Open(L"sound.wav", CB::IO::File::AccessType::ReadOnly, CB::IO::File::OpenAction::Open);
				CB::IO::CSound sound(pStream.Cast<CB::IO::IStream>());

				uSampleRate = sound.GetFrequency();
				uChannels = sound.GetNumberOfChannels();
				uSamples = sound.GetNumberOfFrames();
				Samples.Resize(uChannels * uSamples);
				sound.ReadFrames(Samples);		

				if(uChannels == 2){
					CB::Collection::CList<int16> tempSamples(Samples);

					Samples.Resize(uSamples);
					for(uint32 uIndex = 0; uIndex < uSamples; uIndex++){
						Samples[uIndex] = tempSamples[uIndex * 2];
					}
					uChannels = 1;
				}
			}

			auto uChanType = uChannels == 1 ? CB::Audio::ChannelFormat::Mono : CB::Audio::ChannelFormat::Stereo;
			auto pBuffer = pDevice->CreateBuffer(uChanType, CB::Audio::SampleType::S16Bit, uSampleRate, uSamples);
			pBuffer->LoadData(uSamples, Samples.GetPointer());

			auto pSource = pDevice->CreateSource(CB::Audio::SourceType::Static);
			pSource->AttachBuffer(pBuffer);
			pSource->Play();
			pSource->SetPosition(CB::Math::CVector3D());
			pSource->SetVolume(1.0f);

			pListener->SetPosition(CB::Math::CVector3D());
			pListener->SetOrientation(CB::Math::CVector3D(0.0f, 0.0f, 1.0f), CB::Math::CVector3D(0.0f, 1.0f, 0.0f));
			pListener->SetVolume(1.0f);
			for(uint32 uSeconds = 0; uSeconds < 10; uSeconds++){
				pSource->SetPosition(CB::Math::CVector3D(CB::Math::SinRad(uSeconds), 0.0f, 0.0f));
				pDevice->ProcessEvents();
				CB::Threads::Wait(500);
			}
		}
	}
	catch(CB::Exception::CException& Exception){
		CB::Log::Write(Exception);
		CB::Message::Show(Exception, CB::Message::Icon::Error);
		return 0;
	}
}