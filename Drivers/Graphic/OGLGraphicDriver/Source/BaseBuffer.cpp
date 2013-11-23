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
		m_bBinded(false),
		Manage::IManagedObject<COGLDevice, IOGLBaseBuffer>(pDevice)
	{
		if(uLength == 0){
			throw Exception::CZeroLengthArgumentException(L"uLength", 
				L"Vertex buffer cannot be zero length.", CR_INFO());
		}

		CR_GLBINDCHECK(this->m_pParent->GetWindowContext(), this->m_pParent->GetRenderContext());
		GL::glGenBuffers(1, &this->m_uBuffer);						CR_GLCHECK();

		CBufferBindGurard guard(this->m_uBufferTarget);
		GLenum uGLUsage = GLUtils::ToBufferUsage(uUsage, uAccess);

		GL::glBindBuffer(this->m_uBufferTarget, this->m_uBuffer);	CR_GLCHECK();
		GL::glBufferData(this->m_uBufferTarget, uLength, pData, uGLUsage);	CR_GLCHECK();
	}

	IOGLBaseBuffer::~IOGLBaseBuffer(){
		if(this->m_bBinded){
			this->Unbind();
		}
		if(this->m_uBuffer != 0 && GL::glIsBuffer(this->m_uBuffer)){
			GL::glDeleteBuffers(1, &this->m_uBuffer);	CR_GLCHECK();
		}
	}

	void	IOGLBaseBuffer::Bind(){
		CR_GLBINDCHECK(this->m_pParent->GetWindowContext(), this->m_pParent->GetRenderContext());

		GL::glBindBuffer(this->m_uBufferTarget, this->m_uBuffer);	CR_GLCHECK();
		this->m_bBinded = true;
	}

	void	IOGLBaseBuffer::Unbind(){
		CR_GLBINDCHECK(this->m_pParent->GetWindowContext(), this->m_pParent->GetRenderContext());

		GL::glBindBuffer(this->m_uBufferTarget, 0);	CR_GLCHECK();
		this->m_bBinded = false;
	}

	const GLenum	IOGLBaseBuffer::GetTarget() const{
		return this->m_uBufferTarget;
	}

	const GLuint	IOGLBaseBuffer::GetBufferID() const{
		return this->m_uBuffer;
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
		CR_GLBINDCHECK(this->m_pParent->GetWindowContext(), this->m_pParent->GetRenderContext());
		GLenum uUsage = GLUtils::ToBufferUsage(this->m_uUsage, this->m_uAccess);
		CBufferBindGurard guard(this->m_uBufferTarget);

		GL::glBindBuffer(this->m_uBufferTarget, this->m_uBuffer);			CR_GLCHECK();
		GL::glBufferData(this->m_uBufferTarget, uLength, pData, uUsage);	CR_GLCHECK();
	}

	void	IOGLBaseBuffer::LoadSubData(const void* pData, const uint32 uOffset, const uint32 uLength){
		CR_GLBINDCHECK(this->m_pParent->GetWindowContext(), this->m_pParent->GetRenderContext());
		CBufferBindGurard guard(this->m_uBufferTarget);

		GL::glBindBuffer(this->m_uBufferTarget, this->m_uBuffer);				CR_GLCHECK();
		GL::glBufferSubData(this->m_uBufferTarget, uOffset, uLength, pData);	CR_GLCHECK();
	}

	CRefPtr<IO::IStream>	IOGLBaseBuffer::Map(const Graphic::BufferAccess uAccess){
		return this->Map(uAccess, false, 0, this->m_uLength);
	}

	CRefPtr<IO::IStream>	IOGLBaseBuffer::Map(const Graphic::BufferAccess uAccess, const bool bDiscard){
		return this->Map(uAccess, bDiscard, 0, this->m_uLength);
	}

	CRefPtr<IO::IStream>	IOGLBaseBuffer::Map(const Graphic::BufferAccess uAccess, const bool bDiscard, const uint32 uOffset, const uint32 uLength){
		CR_GLBINDCHECK(this->m_pParent->GetWindowContext(), this->m_pParent->GetRenderContext());
		return new COGLBufferStream(this, uAccess, bDiscard, uOffset, uLength);
	}

	//=================================================================
	//	BUFFER BIND GUARD
	//=================================================================

	CBufferBindGurard::CBufferBindGurard(const GLenum uTarget) :
		m_uTarget(uTarget),
		m_uBinding(GLUtils::ToTargetBinding(uTarget)),
		m_uBufferID(0)
	{
		GL::glGetIntegerv(this->m_uBinding, reinterpret_cast<GLint*>(&this->m_uBufferID));	CR_GLCHECK();
	}

	CBufferBindGurard::CBufferBindGurard(const GLenum uTarget, const GLenum uBinding) :
		m_uTarget(uTarget),
		m_uBinding(uBinding),
		m_uBufferID(0)
	{
		GL::glGetIntegerv(this->m_uBinding, reinterpret_cast<GLint*>(&this->m_uBufferID));	CR_GLCHECK();
	}

	CBufferBindGurard::~CBufferBindGurard(){
		if(this->m_uBufferID != 0 && GL::glIsBuffer(this->m_uBufferID)){
			GL::glBindBuffer(this->m_uTarget, this->m_uBufferID);	CR_GLCHECK();
		}
	}
}