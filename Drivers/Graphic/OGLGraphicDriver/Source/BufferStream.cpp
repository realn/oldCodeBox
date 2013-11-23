#include "../Internal/BufferStream.h"
#include "../Internal/BaseBuffer.h"
#include "../Internal/Utils.h"

namespace CB{
	COGLBufferStream::COGLBufferStream(CRefPtr<IOGLBaseBuffer> pBuffer, const Graphic::BufferAccess uAccess, const bool bDiscard, const uint32 uOffset, const uint32 uLength) : 
		Manage::IManagedObject<IOGLBaseBuffer, COGLBufferStream>(pBuffer)
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

		CBufferBindGurard guard(this->m_pParent->GetTarget());
		GL::glBindBuffer(this->m_pParent->GetTarget(), this->m_pParent->GetBufferID());	CR_GLCHECK();

		if(bDiscard){
			GL::glBufferSubData(this->m_pParent->GetTarget(), uOffset, uLength, 0);	CR_GLCHECK();
		}

		this->m_pData = reinterpret_cast<byte*>(GL::glMapBuffer(this->m_pParent->GetTarget(), uGLAccess)); CR_GLCHECK();
		if(this->m_pData == 0){
			CR_THROW(L"Failed to lock buffer for stream.");
		}

		this->m_uPosition = uOffset;
		this->m_uLength = uLength;
	}

	COGLBufferStream::~COGLBufferStream(){
		try{
			CBufferBindGurard guard(this->m_pParent->GetTarget());	CR_GLCHECK();
			GL::glUnmapBuffer(this->m_pParent->GetTarget());		CR_GLCHECK();
		}
		catch(Exception::CException&){}
	}
}