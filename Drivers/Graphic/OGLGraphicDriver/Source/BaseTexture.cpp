#include "../Internal/BaseTexture.h"

namespace CB{
	IOGLBaseTexture::IOGLBaseTexture(
		CRefPtr<COGLDevice> pDevice, 
		const GLenum uTarget, 
		const uint32 uLength, 
		const Graphic::TextureType uType, 
		const Graphic::BufferUsage uUsage, 
		const Graphic::BufferAccess uAccess, 
		const Graphic::BufferFormat uFormat
		) :
		Manage::IManagedObject<COGLDevice, IOGLBaseTexture>(pDevice),
		m_uTarget(uTarget),
		m_uType(uType),
		m_uLength(uLength),
		m_uAccess(uAccess),
		m_uUsage(uUsage),
		m_uFormat(uFormat)
	{
		GL::glGenTextures(1, &this->m_uTexture);	CR_GLCHECK();
	}

	IOGLBaseTexture::~IOGLBaseTexture(){
		GL::glDeleteTextures(1, &this->m_uTexture);
	}

	void	IOGLBaseTexture::Bind(){
		GL::glBindTexture(this->m_uTarget, this->m_uTexture);
	}

	const uint32	IOGLBaseTexture::GetApiId() const {
		return g_uApiID;
	}

	CRefPtr<Graphic::IDevice>	IOGLBaseTexture::GetDevice() const{
		return this->m_pParent.Cast<Graphic::IDevice>();
	}

	const Graphic::BufferType	IOGLBaseTexture::GetType() const{
		return Graphic::BufferType::Texture;
	}

	const Graphic::BufferAccess	IOGLBaseTexture::GetAccess() const{
		return this->m_uAccess;
	}

	const Graphic::BufferUsage	IOGLBaseTexture::GetUsage() const{
		return this->m_uUsage;
	}

	const Graphic::BufferFormat	IOGLBaseTexture::GetFormat() const{
		return this->m_uFormat;
	}

	const Graphic::TextureType	IOGLBaseTexture::GetTextureType() const{
		return this->m_uType;
	}

	const uint32	IOGLBaseTexture::GetLength() const{
		return this->m_uLength;
	}

	CRefPtr<IO::IStream>	IOGLBaseTexture::Map(const Graphic::BufferAccess uAccess) {
		return this->MapData(uAccess, false, 0, this->m_uLength);
	}

	CRefPtr<IO::IStream>	IOGLBaseTexture::Map(const Graphic::BufferAccess uAccess, const bool bDiscard) {
		return this->MapData(uAccess, bDiscard, 0, this->m_uLength);
	}

	CRefPtr<IO::IStream>	IOGLBaseTexture::Map(const Graphic::BufferAccess uAccess, const bool bDiscard, const uint32 uOffset, const uint32 uLength) {
		return this->MapData(uAccess, bDiscard, uOffset, uLength);
	}


	//===================================================

	CTextureBindGuard::CTextureBindGuard(const GLenum uTarget, const GLenum uBinding) :
		m_uTarget(uTarget),
		m_uBinding(uBinding),
		m_uTexture(0)
	{
		GL::glGetIntegerv(this->m_uBinding, reinterpret_cast<GLint*>(&this->m_uTexture));
	}

	CTextureBindGuard::~CTextureBindGuard(){
		GL::glBindTexture(this->m_uTarget, this->m_uTexture);
	}
}
