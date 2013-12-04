#pragma once

#include "Adapter.h"
#include "OpenAL.h"

namespace CB{
	class COALSource;

	class COALDevice :
		public Audio::IDevice,
		public Manage::IManagedObject<COALAdapter, COALDevice>,
		public Manage::IObjectManager<COALDevice, COALSource>
	{
	private:
		ALCcontext*	m_pContext;

	public:
		COALDevice(CRefPtr<COALAdapter> pAdapter);
		~COALDevice();

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
		CRefPtr<Audio::ISource>	CreateSource() const override;

		void	SetSpeedOfSound(const float32 fUnitsPerSecond) override;

		const float32	GetSpeedOfSound() const override;

		//	END OF INTERFACE IMPLEMENTATION
	};
}