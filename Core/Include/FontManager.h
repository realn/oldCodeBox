#pragma once

#include "Ref.h"
#include "SmartPointers_Hidden.h"
#include "SmartPointers_RefPtr.h"
#include "IO_Stream.h"
#include "Manage_Object.h"

namespace CB{
	namespace Font{
		class CFont;
		class COMMON_API CManager :
			public virtual IRef,
			public Manage::IObjectManager<CManager, CFont>
		{
			friend CFont;
		private:
			CHiddenPtr	m_pData;

		public:
			CRefPtr<CFont>	Load(CRefPtr<IO::IStream> pStream);

			static	CRefPtr<CManager>	Create();

		protected:
			CManager();
			~CManager();
		};
	}
}