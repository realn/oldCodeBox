#pragma once

#include "Types.h"
#include "Macros.h"

namespace CB{
	class COMMON_API IRef {
	private:
		uint32	m_uRefCount;

	protected:
		IRef();
		virtual ~IRef();

	public:
		const uint32	AddRef();
		const uint32	Release();

		const uint32	GetRefCount() const;
	};
}