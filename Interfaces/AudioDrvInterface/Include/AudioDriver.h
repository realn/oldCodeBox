#pragma once

#include "Macros.h"
#include <ApiObject.h>
#include <SmartPointers_RefPtr.h>
#include <Math_Vector.h>
#include <Collection_List.h>

namespace CB{
	namespace Audio{
		enum class ChannelFormat{
			Mono,
			Stereo,
		};

		enum class SampleType{
			S8Bit,
			S16Bit,
		};

		enum class SourceType{
			Static,
			Streaming,
		};

		enum class SourceState{
			None = 0,
			Playing,
			Paused,
			Stopped,
		};

		class IBuffer :
			public IApiObject
		{
		public:
			virtual const ChannelFormat	GetFormat() const = 0;
			virtual const SampleType	GetSampleType() const = 0;
			virtual const uint32		GetSamples() const = 0;
			virtual const uint32		GetSampleRate() const = 0;

			virtual void	LoadData(const uint32 uSamples, const void* pData) = 0;
			virtual void	LoadSubData(const uint32 uOffset, const uint32 uSamples, const void* pData) = 0;
		};

		class I3DObject :
			public IApiObject
		{
		public:
			virtual void	SetVolume(const float32 fVolume) = 0;
			virtual void	SetPosition(const Math::CVector3D& vPosition) = 0;
			virtual void	SetVelocity(const Math::CVector3D& vVelocity) = 0;

			virtual const Math::CVector3D	GetPosition() const = 0;
			virtual const Math::CVector3D	GetVelocity() const = 0;
			virtual const float32			GetVolume() const = 0;
		};

		class ISource :
			public I3DObject
		{
		public:
			virtual void		SetPositionRelative(const bool bEnabled) = 0;
			virtual const bool	IsPositionRelative() const = 0;

			virtual void	Play() = 0;
			virtual void	Stop() = 0;
			virtual void	Pause() = 0;
			virtual void	Rewind() = 0;

			virtual const SourceType	GetType() const = 0;
			virtual const SourceState	GetState() const = 0;

			virtual void	AttachBuffer(CRefPtr<IBuffer> pBuffer) = 0;
			virtual void	AttachBuffer(Collection::CList<CRefPtr<IBuffer>> pBufferList) = 0;
			virtual CRefPtr<IBuffer>	ReleaseBuffer() = 0;
			virtual Collection::CList<CRefPtr<IBuffer>>	ReleaseBuffers(const bool bProcessedOnly) = 0;
		};

		class IListener :
			public I3DObject
		{
		public:
			virtual void	SetOrientation(const Math::CVector3D& vForward, const Math::CVector3D& vUp) = 0;

			virtual const Math::CVector3D	GetOrientationForward() const = 0;
			virtual const Math::CVector3D	GetOrientationUp() const = 0;
		};

		class IDevice : 
			public IApiObject
		{
		public:
			virtual CRefPtr<IListener>	CreateListener() const = 0;
			virtual CRefPtr<ISource>	CreateSource(const SourceType uType) const = 0;
			virtual CRefPtr<IBuffer>	CreateBuffer(const ChannelFormat uChannelFormat, const SampleType uType, const uint32 uSampleRate, const uint32 uSamples) = 0;

			virtual void			SetSpeedOfSound(const float32 fUnitsPerSecond) = 0;
			virtual const float32	GetSpeedOfSound() const = 0;

			virtual void	ProcessEvents() = 0;
		};

		class IAdapter : 
			public IApiObject
		{
		public:
			virtual const CString	GetName() const = 0;
			virtual const uint32	GetIndex() const = 0;

			virtual CRefPtr<IDevice>	CreateDevice() = 0;
		};

		class IManager :
			public IApiObject
		{
		public:
			virtual const uint32		GetNumberOfAdapters() const = 0;
			virtual CRefPtr<IAdapter>	GetAdapter(const uint32 uIndex) = 0;
			virtual CRefPtr<IAdapter>	GetDefaultAdapter() = 0;
		};

		class IDriver : 
			public IRef
		{
		public:
			virtual CRefPtr<IManager>	CreateManager() = 0;
		};

		extern AUDIODRVINTERFACE_API	CRefPtr<IDriver>	LoadDriver(const CString& strDriverName);
	}

	namespace String{
		extern AUDIODRVINTERFACE_API	const CString	ToString(const Audio::ChannelFormat uFormat);
		extern AUDIODRVINTERFACE_API	const CString	ToString(const Audio::SourceState uState);
		extern AUDIODRVINTERFACE_API	const CString	ToString(const Audio::SampleType uType);
		extern AUDIODRVINTERFACE_API	const CString	ToString(const Audio::SourceType uType);
	}
}