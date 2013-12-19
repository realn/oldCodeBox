#pragma once

#include "Adapter.h"

typedef struct ALCcontext_struct ALCcontext;

namespace CB{
	class COALBuffer;
	class COALSource;
	class COALListener;

	class COALDevice :
		public Audio::IDevice,
		public Manage::IManagedObject<COALAdapter, COALDevice>,
		public Manage::IObjectManager<COALDevice, COALBuffer>,
		public Manage::IObjectManager<COALDevice, COALSource>,
		public Manage::IObjectManager<COALDevice, COALListener>
	{
	private:
		ALCcontext*	m_pContext;

	public:
		COALDevice(CRefPtr<COALAdapter> pAdapter);
		~COALDevice();

		ALCcontext*	GetContext() const;

		//	INTERFACE IMPLEMENTATION

		const uint32	GetApiId() const override;

		CRefPtr<Audio::IListener>	CreateListener() override;
		CRefPtr<Audio::ISource>		CreateSource(const Audio::SourceType uType) override;
		CRefPtr<Audio::IBuffer>		CreateBuffer(const Audio::ChannelFormat uFormat, const Audio::SampleType uType, const uint32 uSampleRate, const uint32 uSamples) override;

		void						SetDistanceModel(const Audio::DistanceModel uModel) override;
		const Audio::DistanceModel	GetDistanceModel() const override;

		void			SetDopplerFactor(const float32 fFactor) override;
		const float32	GetDopplerFactor() const override;

		void	SetSpeedOfSound(const float32 fUnitsPerSecond) override;
		const float32	GetSpeedOfSound() const override;

		void			SetSourceDistanceModels(const bool bEnabled) override;
		const bool		IsSourceDistanceModelsEnabled() const override;

		void	ProcessEvents() override;

		//	END OF INTERFACE IMPLEMENTATION
	};
}