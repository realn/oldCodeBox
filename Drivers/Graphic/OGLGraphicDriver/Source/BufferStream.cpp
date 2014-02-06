#include "../Internal/BufferStream.h"
#include "../Internal/BaseBuffer.h"
#include "../Internal/Utils.h"

namespace CB{
	COGLBufferStream::COGLBufferStream(CRefPtr<IOGLBaseBuffer> pBuffer, CGLRenderContext& GL, const Graphic::BufferAccess uAccess, const bool bDiscard, const uint32 uOffset, const uint32 uLength) : 
		Manage::IManagedObject<IOGLBaseBuffer, COGLBufferStream>(pBuffer),
		GL(GL)
	{
		GLenum uGLAccess = 0;
		switch (uAccess)
		{
		case Graphic::BufferAccess::Read:	
			uGLAccess = GL::GL_READ_ONLY;	
			this->m_bCanRead = true;
			break;

		case Graphic::BufferAccess::Write:	
			uGLAccess = GL::GL_WRITE_ONLY;	
			this->m_bCanWrite = true;
			break;

		case Graphic::BufferAccess::ReadAndWrite:	
			uGLAccess = GL::GL_READ_WRITE;	
			this->m_bCanRead = true;
			this->m_bCanWrite = true;
			break;

		default:
			throw Exception::CInvalidArgumentException(L"uAccess", String::ToString(uAccess),
				L"Unknown access for ogl buffer stream.", CR_INFO());
		}

		CBufferBindGurard guard(GL, this->m_pParent->GetTarget());
		this->m_pParent->Bind();

		if(bDiscard){
			GL.glBufferSubData(this->m_pParent->GetTarget(), uOffset, uLength, 0);	CR_GLCHECK();
		}

		this->m_pData = reinterpret_cast<byte*>(GL.glMapBuffer(this->m_pParent->GetTarget(), uGLAccess)); CR_GLCHECK();
		if(this->m_pData == 0){
			CR_THROW(L"Failed to lock buffer for stream.");
		}

		this->m_uPosition = uOffset;
		this->m_uLength = uLength;
	}

	COGLBufferStream::~COGLBufferStream(){
		try{
			CBufferBindGurard guard(GL, this->m_pParent->GetTarget());	CR_GLCHECK();
			this->m_pParent->Bind();

			GL.glUnmapBuffer(this->m_pParent->GetTarget());		CR_GLCHECK();
		}
		catch(Exception::CException& Ex){
			Log::Write(Ex, Log::LogLevel::Warning);
		}
	}
}