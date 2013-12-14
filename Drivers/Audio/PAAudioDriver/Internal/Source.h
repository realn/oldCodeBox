#pragma once

#include "Device.h"

namespace CB{
	class COALBuffer;

	class COALSource :
		public Audio::ISource,
		Manage::IManagedObject<COALDevice, COALSource>
	{
	private:
		CRefPtr<COALBuffer>	m_pBuffer;
		Collection::CList<CRefPtr<COALBuffer>>	m_pBufferList;
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

		void	Play() override;
		void	Stop() override;
		void	Pause() override;
		void	Rewind() override;

		const Audio::SourceType	GetType() const override;

		void	SetStaticBuffer(CRefPtr<Audio::IBuffer> pBuffer) override;
		void	QueueStreamingBuffers(const Collection::ICountable<CRefPtr<Audio::IBuffer>>& pBufferList) override;

		CRefPtr<Audio::IBuffer>	GetStaticBuffer() const override;
		const Collection::CList<CRefPtr<Audio::IBuffer>>	GetStremingBuffers() const override;

		void	FreeStaticBuffer() override;
		void	FreeStreamingBuffers() override;

		const Collection::CList<CRefPtr<Audio::IBuffer>>	UnqueueProcessedBuffers() override;

		//	END OF INTERFACE IMPLEMENTATION
	};
}