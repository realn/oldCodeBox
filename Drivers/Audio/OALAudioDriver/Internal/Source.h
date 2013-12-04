#pragma once

#include "Device.h"

namespace CB{
	class COALSource :
		public Audio::ISource,
		Manage::IManagedObject<COALDevice, COALSource>
	{
	private:
		ALuint	m_uSource;

	public:
		COALSource(CRefPtr<COALDevice> pDevice);
		~COALSource();

		//	INTERFACE IMPLEMENTATION

		const uint32	GetApiId() const override;

		void	SetGain(const float32 fGain) override;
		void	SetPosition(const Math::CVector3D& vPosition) override;
		void	SetVelocity(const Math::CVector3D& vVelocity) override;

		const Math::CVector3D	GetPosition() const override;
		const Math::CVector3D	GetVelocity() const override;
		const float32	GetGain() const override;

		void		SetPositionRelative(const bool bEnabled) override;
		const bool	IsPositionRelative() const override;

		//	END OF INTERFACE IMPLEMENTATION
	};
}