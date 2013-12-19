#pragma once

#include "Device.h"

namespace CB{
	class COALBuffer;

	class COALSource :
		public Audio::ISource,
		Manage::IManagedObject<COALDevice, COALSource>
	{
	private:
		Collection::CList<CRefPtr<COALBuffer>>	m_pBufferList;
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

		void			SetDistanceModel(const Audio::DistanceModel uModel) override;
		const Audio::DistanceModel	GetDistanceModel() const override;

		void			SetPitch(const float32 fValue) override;
		const float32	GetPitch() const override;

		void			SetCone(const float32 fInnerDeg, const float32 fOuterDeg) override;
		const float32	GetConeInner() const override;
		const float32	GetConeOuter() const override;

		void			SetConeOuterVolume(const float fVolume) override;
		const float32	GetConeOuterVolume() const override;

		void			SetVolumeClamp(const float32 fMin, const float32 fMax) override;
		const float32	GetVolumeMin() const override;
		const float32	GetVolumeMax() const override;

		void					SetDirection(const Math::CVector3D& vDirection) override;
		const Math::CVector3D	GetDirection() const override;

		void			SetRollOffFactor(const float32 fFactor) override;
		const float32	GetRollOffFactor() const override;

		void			SetDistance(const float32 fReference, const float32 fMax) override;
		const float32	GetDistanceReference() const override;
		const float32	GetDistanceMax() const override;

		void		SetPositionRelative(const bool bEnabled) override;
		const bool	IsPositionRelative() const override;

		void	Play() override;
		void	Stop() override;
		void	Pause() override;
		void	Rewind() override;

		const Audio::SourceType		GetType() const override;
		const Audio::SourceState	GetState() const override;

		void	AttachBuffer(CRefPtr<Audio::IBuffer> pBuffer) override;
		void	AttachBuffer(Collection::ICountable<CRefPtr<Audio::IBuffer>>& pBufferList) override;
		CRefPtr<Audio::IBuffer>	GetBuffer() const override;
		Collection::CList<CRefPtr<Audio::IBuffer>>	GetBuffers(const bool bProcessedOnly) const override;
		void	FreeBuffer() override;
		const bool	HasAttachedBuffer() const override;
		const bool	HasProcessedBuffers() const override;

		//	END OF INTERFACE IMPLEMENTATION

	private:
		const float32	GetSourceFloat(const uint32 uEnum) const;
		const int32		GetSourceInt(const uint32 uEnum) const;
	};
}