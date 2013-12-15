#pragma once

#include "Manager.h"

typedef struct ALCdevice_struct ALCdevice;

namespace CB{
	class COALDevice;
	class COALAdapter : 
		public Audio::IAdapter,
		public Manage::IManagedObject<COALManager, COALAdapter>,
		public Manage::IObjectManager<COALAdapter, COALDevice>
	{
	private:
		const uint32		m_uIndex;
		const CString		m_strAdapter;
		
		ALCdevice*	m_pAdapter;

	public:
		COALAdapter(CRefPtr<COALManager> pManager, const CString& strAdapter, const uint32 uIndex);
		~COALAdapter();

		ALCdevice*	GetALCDevice() const;

		//	INTERFACE IMPLEMENTATION

		const uint32	GetApiId() const override;

		const CString	GetName() const override;
		const uint32	GetIndex() const override;

		CRefPtr<Audio::IDevice>	CreateDevice() override;

		//	END OF INTERFACE IMPLEMENTATION
	};
}