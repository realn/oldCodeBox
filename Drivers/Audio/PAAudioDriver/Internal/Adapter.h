#pragma once

#include "Manager.h"

namespace CB{
	class CPADevice;
	class CPAAdapter : 
		public Audio::IAdapter,
		public Manage::IManagedObject<CPAManager, CPAAdapter>,
		public Manage::IObjectManager<CPAAdapter, CPADevice>
	{
	private:
		const uint32		m_uIndex;
		const CString		m_strAdapter;
		
		ALCdevice*	m_pAdapter;

	public:
		CPAAdapter(CRefPtr<CPAManager> pManager, const CString& strAdapter, const uint32 uIndex);
		~CPAAdapter();

		ALCdevice*	GetALCDevice() const;

		//	INTERFACE IMPLEMENTATION

		const uint32	GetApiId() const override;

		const CString	GetName() const override;
		const uint32	GetIndex() const override;

		CRefPtr<Audio::IDevice>	CreateDevice() override;

		//	END OF INTERFACE IMPLEMENTATION
	};
}