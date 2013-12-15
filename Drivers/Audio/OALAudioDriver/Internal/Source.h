#pragma once

#include "Device.h"

namespace CB{
	class COALBuffer;

	class COALSource :
		public Audio::ISource,
		Manage::IManagedObject<COALDevice, COALSource>
	{
	private:
		const Audio::SourceType	m_uType;
		uint32	m_uSource;

	public:
		COALSource(CRefPtr<COALDevice> pDevice, const Audio::SourceType uType);
		~COALSource();

		const uint32	GetSourceID() const;

		//	INTERFACE IMPLEMENTATION

		const uint32	GetApiId() const override;

		void	SetVolume(const float32 fGain) override;
		void	SetPosition(const Math::CVector3D& vPosition) override;
		void	SetVelocity(const Math::CVector3D& vVelocity) override;

		const Math::CVector3D	GetPosition() const override;
		const Math::CVector3D	GetVelocity() const override;
		const float32	GetVolume() const override;

		void		SetPositionRelative(const bool bEnabled) override;
		const bool	IsPositionRelative() const override;

		void	Play() override;
		void	Stop() override;
		void	Pause() override;
		void	Rewind() override;

		const Audio::SourceType	GetType() const override;


		//	END OF INTERFACE IMPLEMENTATION
	};
}