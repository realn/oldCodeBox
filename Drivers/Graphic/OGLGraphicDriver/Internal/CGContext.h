#pragma once

#include <Types.h>
#include "GLTypes.h"

//==============================================
//	CG headers and libs
//==============================================

#define CGGL_NO_OPENGL

#include <Cg\cg.h>
#include <Cg\cgGL.h>

#pragma comment(lib, "cg.lib")
#pragma comment(lib, "cgGL.lib")


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
		CR_NOCOPY(CCGContext);
		CR_NOASSIGN(CCGContext);
	};
}