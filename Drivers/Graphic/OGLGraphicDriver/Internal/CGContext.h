#pragma once

#include "OpenGL_Core.h"

namespace CB{
	class CCGContext{
	private:
		mutable	CGcontext m_Context;

	public:
		CCGContext();
		CCGContext(CGcontext Context);
		~CCGContext();

		CGcontext&	Get() const;

	private:
		CCGContext(const CCGContext&);
		const CCGContext& operator=(const CCGContext&);
	};
}