#pragma once

#include "Macros.h"
#include <ApiObject.h>
#include <SmartPointers_RefPtr.h>

namespace CB{
	namespace Audio{
		class IAdapter : 
			public IApiObject
		{
		public:
			virtual const CString	GetName() const = 0;
			virtual const uint32	GetIndex() const = 0;
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