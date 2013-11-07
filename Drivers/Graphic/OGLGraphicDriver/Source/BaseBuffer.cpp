#include "../Internal/BaseBuffer.h"
#include "../Internal/Utils.h"

namespace CB{
	IOGLBaseBuffer::IOGLBaseBuffer(CRefPtr<COGLDevice> pDevice, const Graphic::BufferType uType, const GLenum uBufferTarget, const Graphic::BufferUsage uUsage, const Graphic::BufferAccess uAccess, const uint32 uLength, const void* pData) :
		m_uBufferTarget(uBufferTarget),
		m_uType(uType),
		m_uLength(uLength),
		m_uUsage(uUsage),
		m_uAccess(uAccess),
		Manage::IManagedObject<COGLDevice, IOGLBaseBuffer>(pDevice)
	{
		if(uLength == 0){
			throw Exception::CZeroLengthArgumentException(L"uLength", 
				L"Vertex buffer cannot be zero length.", CR_INFO());
		}

		CR_GLBINDCHECK(this->m_pParent->GetWindowContext(), this->m_pParent->GetRenderContext());

		glGenBuffers(1, &this->m_uBuffer);						CR_GLCHECK();
		glBindBuffer(this->m_uBufferTarget, this->m_uBuffer);	CR_GLCHECK();

		GLenum uGLUsage = GLUtils::ToBufferUsage(uUsage, uAccess);
		glBufferData(this->m_uBufferTarget, uLength, pData, uGLUsage);	CR_GLCHECK();

		glBindBuffer(this->m_uBufferTarget, 0);	CR_GLCHECK();
	}

	IOGLBaseBuffer::~IOGLBaseBuffer(){
		if(this->m_uBuffer != 0 && glIsBuffer(this->m_uBuffer)){
			glDeleteBuffers(1, &this->m_uBuffer);	CR_GLCHECK();
		}
	}

	void	IOGLBaseBuffer::Bind(){
		CR_GLBINDCHECK(this->m_pParent->GetWindowContext(), this->m_pParent->GetRenderContext());

		glBindBuffer(this->m_uBufferTarget, this->m_uBuffer);	CR_GLCHECK();
	}

	void	IOGLBaseBuffer::Unbind(){
		CR_GLBINDCHECK(this->m_pParent->GetWindowContext(), this->m_pParent->GetRenderContext());

		glBindBuffer(this->m_uBufferTarget, 0);	CR_GLCHECK();
	}

	const uint32	IOGLBaseBuffer::GetApiId() const{
		return g_uApiID;
	}

	CRefPtr<Graphic::IDevice>	IOGLBaseBuffer::GetDevice() const{
		return this->m_pParent.Cast<Graphic::IDevice>();
	}

	const Graphic::BufferType	IOGLBaseBuffer::GetType() const{
		return this->m_uType;
	}

	const Graphic::BufferUsage	IOGLBaseBuffer::GetUsage() const{
		return this->m_uUsage;
	}

	const Graphic::BufferAccess	IOGLBaseBuffer::GetAccess() const{
		return this->m_uAccess;
	}

	const uint32	IOGLBaseBuffer::GetLength() const{
		return this->m_uLength;
	}

	void	IOGLBaseBuffer::LoadData(const void* pData, const uint32 uLength){
		GLenum uUsage = GLUtils::ToBufferUsage(this->m_uUsage, this->m_uAccess);

		glBindBuffer(this->m_uBufferTarget, this->m_uBuffer);
		glBufferData(this->m_uBufferTarget, uLength, pData, uUsage);
		glBindBuffer(this->m_uBufferTarget, 0);
	}

	void	IOGLBaseBuffer::LoadSubData(const void* pData, const uint32 uOffset, const uint32 uLength){
		glBindBuffer(this->m_uBufferTarget, this->m_uBuffer);
		glBufferSubData(this->m_uBufferTarget, uOffset, uLength, pData);
		glBindBuffer(this->m_uBufferTarget, 0);
	}

	CRefPtr<IO::IStream>	IOGLBaseBuffer::Map(const Graphic::BufferAccess uAccess){
		return this->Map(uAccess, false, 0, this->m_uLength);
	}

	CRefPtr<IO::IStream>	IOGLBaseBuffer::Map(const Graphic::BufferAccess uAccess, const bool bDiscard){
		return this->Map(uAccess, bDiscard, 0, this->m_uLength);
	}

	CRefPtr<IO::IStream>	IOGLBaseBuffer::Map(const Graphic::BufferAccess uAccess, const bool bDiscard, const unsigned uOffset, const unsigned uLength){
		//if(uOffset >= this->m_uLength){
		//	throw Exception::CInvalidArgumentException(L"uOffset", String::FromUInt32(uOffset),
		//		L"Offset greater than buffer length.", __FUNCTIONW__, __FILEW__, __LINE__);
		//}
		//if(uLength == 0){
		//	throw Exception::CZeroLengthArgumentException(L"uLength",
		//		L"Cannot map zero length to buffer.", __FUNCTIONW__, __FILEW__, __LINE__);
		//}
		//if(uOffset + uLength > this->m_uLength){
		//	throw Exception::CInvalidArgumentException(L"uOffset + uLength", String::FromUInt32(uOffset) + L"+" + String::FromUInt32(uLength),
		//		L"Length greater than buffer length.", __FUNCTIONW__, __FILEW__, __LINE__);
		//}

		//unsigned uFlags = 0;
		//if(bRead && !bWrite)
		//	uFlags |= D3DLOCK_READONLY;
		//if(bDiscard)
		//	uFlags |= D3DLOCK_DISCARD;

		//return new CDX9VertexBufferStream(this, uOffset, uLength, uFlags);
		CR_THROWNOTIMPLEMENTED();
	}
}