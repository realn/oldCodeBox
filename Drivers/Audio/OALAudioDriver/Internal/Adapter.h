#pragma once

#include "Manager.h"

#include <als\alc.h>

namespace CB{
	class COALAdapter : 
		public Audio::IAdapter,
		public Manage::IManagedObject<COALManager, COALAdapter>
	{
	private:
		const uint32		m_uIndex;
		const CString		m_strAdapter;
		
		ALCdevice*	m_pAdapter;

	public:
		COALAdapter(CRefPtr<COALManager> pManager, const CString& strAdapter, const uint32 uIndex);
		~COALAdapter();

		const uint32	GetApiId() const override;

		const CString	GetName() const override;
		const uint32	GetIndex() const override;
	};
}