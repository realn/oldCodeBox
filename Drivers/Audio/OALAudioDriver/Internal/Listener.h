#pragma once 

#include "Device.h"

namespace CB{
	class COALListener :
		public Audio::IListener,
		public Manage::IManagedObject<COALDevice, COALListener>
	{
	public:
		COALListener(CRefPtr<COALDevice> pDevice);
		~COALListener();

		//	INTERFACE IMPLEMENTATION

		const uint32	GetApiId() const override;

		void	SetVolume(const float32 fGain) override;
		void	SetPosition(const Math::CVector3D& vPosition) override;
		void	SetVelocity(const Math::CVector3D& vVelocity) override;

		const Math::CVector3D	GetPosition() const override;
		const Math::CVector3D	GetVelocity() const override;
		const float32	GetVolume() const override;

		void	SetOrientation(const Math::CVector3D& vForward, const Math::CVector3D& vUp) override;

		const Math::CVector3D	GetOrientationForward() const override;
		const Math::CVector3D	GetOrientationUp() const override;

		//	END OF INTERFACE IMPLEMENTATION
	};
}