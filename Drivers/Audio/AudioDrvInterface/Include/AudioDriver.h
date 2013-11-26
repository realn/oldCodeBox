#pragma once

#include "Macros.h"
#include <ApiObject.h>
#include <SmartPointers_RefPtr.h>
#include <Math_Vector.h>

namespace CB{
	namespace Audio{
		class I3DObject :
			public IApiObject
		{
		public:
			virtual void	SetGain(const float32 fGain) = 0;
			virtual void	SetPosition(const Math::CVector3D& vPosition) = 0;
			virtual void	SetVelocity(const Math::CVector3D& vVelocity) = 0;

			virtual const Math::CVector3D	GetPosition() const = 0;
			virtual const Math::CVector3D	GetVelocity() const = 0;
			virtual const float32	GetGain() const = 0;
		};

		class ISource :
			public I3DObject
		{
		public:
			virtual void		SetPositionRelative(const bool bEnabled) = 0;
			virtual const bool	IsPositionRelative() const = 0;
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
			public IListener
		{
		public:
			virtual CRefPtr<IListener>	GetListener() const = 0;
			virtual CRefPtr<ISource>	CreateSource() const = 0;

			virtual void	SetSpeedOfSound(const float32 fMetersPerSecond) = 0;

			virtual const float32	GetSpeedOfSound() const = 0;
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
}