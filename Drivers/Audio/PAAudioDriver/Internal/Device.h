#pragma once

#include "Adapter.h"

namespace CB{
	class CPABuffer;
	class CPASource;

	class CPADevice :
		public Audio::IDevice,
		public Manage::IManagedObject<CPAAdapter, CPADevice>,
		public Manage::IObjectManager<CPADevice, CPABuffer>,
		public Manage::IObjectManager<CPADevice, CPASource>
	{
	private:
		CHiddenPtr	m_pStream;

	public:
		CPADevice(CRefPtr<CPAAdapter> pAdapter);
		~CPADevice();

		//	INTERFACE IMPLEMENTATION

		const uint32	GetApiId() const override;

		void	SetGain(const float32 fGain) override;
		void	SetPosition(const Math::CVector3D& vPosition) override;
		void	SetVelocity(const Math::CVector3D& vVelocity) override;

		const Math::CVector3D	GetPosition() const override;
		const Math::CVector3D	GetVelocity() const override;
		const float32	GetGain() const override;

		void	SetOrientation(const Math::CVector3D& vForward, const Math::CVector3D& vUp) override;

		const Math::CVector3D	GetOrientationForward() const override;
		const Math::CVector3D	GetOrientationUp() const override;

		CRefPtr<Audio::IListener>	GetListener() const override;
		CRefPtr<Audio::ISource>		CreateSource() const override;
		CRefPtr<Audio::IBuffer>		CreateBuffer(const Audio::BufferFormat uFormat, const uint32 uSampleRate, const uint32 uSamples) override;

		void	SetSpeedOfSound(const float32 fUnitsPerSecond) override;

		const float32	GetSpeedOfSound() const override;

		void	ProcessEvents() override;

		//	END OF INTERFACE IMPLEMENTATION
	};
}