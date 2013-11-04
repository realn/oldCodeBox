#pragma once

#include "../../Common/Include/CBString.h"

namespace CB{
	class CWindowsError{
	private:
		uint32	m_dwErrorCode;

	public:
		CWindowsError(const uint32 dwErrorCode);

		const CString	GetMessage() const;
	};
}