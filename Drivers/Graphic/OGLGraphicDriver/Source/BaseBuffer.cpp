#include "../Internal/BaseBuffer.h"
#include "../Internal/Utils.h"
#include "../Internal/BufferStream.h"

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

		GL::glGenBuffers(1, &this->m_uBuffer);						CR_GLCHECK();
		GL::glBindBuffer(this->m_uBufferTarget, this->m_uBuffer);	CR_GLCHECK();

		GLenum uGLUsage = GLUtils::ToBufferUsage(uUsage, uAccess);
		GL::glBufferData(this->m_uBufferTarget, uLength, pData, uGLUsage);	CR_GLCHECK();

		GL::glBindBuffer(this->m_uBufferTarget, 0);	CR_GLCHECK();
	}

	IOGLBaseBuffer::~IOGLBaseBuffer(){
		if(this->m_uBuffer != 0 && GL::glIsBuffer(this->m_uBuffer)){
			GL::glDeleteBuffers(1, &this->m_uBuffer);	CR_GLCHECK();
		}
	}

	void	IOGLBaseBuffer::Bind(){
		CR_GLBINDCHECK(this->m_pParent->GetWindowContext(), this->m_pParent->GetRenderContext());

		GL::glBindBuffer(this->m_uBufferTarget, this->m_uBuffer);	CR_GLCHECK();
	}

	void	IOGLBaseBuffer::Unbind(){
		CR_GLBINDCHECK(this->m_pParent->GetWindowContext(), this->m_pParent->GetRenderContext());

		GL::glBindBuffer(this->m_uBufferTarget, 0);	CR_GLCHECK();
	}

	const GLenum	IOGLBaseBuffer::GetTarget() const{
		return this->m_uBufferTarget;
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

		GL::glBindBuffer(this->m_uBufferTarget, this->m_uBuffer);
		GL::glBufferData(this->m_uBufferTarget, uLength, pData, uUsage);
		GL::glBindBuffer(this->m_uBufferTarget, 0);
	}

	void	IOGLBaseBuffer::LoadSubData(const void* pData, const uint32 uOffset, const uint32 uLength){
		GL::glBindBuffer(this->m_uBufferTarget, this->m_uBuffer);
		GL::glBufferSubData(this->m_uBufferTarget, uOffset, uLength, pData);
		GL::glBindBuffer(this->m_uBufferTarget, 0);
	}

	CRefPtr<IO::IStream>	IOGLBaseBuffer::Map(const Graphic::BufferAccess uAccess){
		return this->Map(uAccess, false, 0, this->m_uLength);
	}

	CRefPtr<IO::IStream>	IOGLBaseBuffer::Map(const Graphic::BufferAccess uAccess, const bool bDiscard){
		return this->Map(uAccess, bDiscard, 0, this->m_uLength);
	}

	CRefPtr<IO::IStream>	IOGLBaseBuffer::Map(const Graphic::BufferAccess uAccess, const bool bDiscard, const uint32 uOffset, const uint32 uLength){
		return new COGLBufferStream(this, uAccess, bDiscard, uOffset, uLength);
	}
}