#include "../Internal/BaseTexture.h"
#include "../Internal/Utils.h"

namespace CB{
	IOGLBaseTexture::IOGLBaseTexture(CRefPtr<COGLDevice> pDevice, const GLenum uTarget, const Graphic::TextureType uType, const Graphic::BufferUsage uUsage, const Graphic::BufferAccess uAccess, const Graphic::BufferFormat uFormat) :
		Manage::IManagedObject<COGLDevice, IOGLBaseTexture>(pDevice),
		m_uTarget(uTarget),
		m_uType(uType),
		m_uAccess(uAccess),
		m_uUsage(uUsage),
		m_uFormat(uFormat),
		m_uMinFilter(Graphic::TextureFilter::Nearest),
		m_uMagFilter(Graphic::TextureFilter::Nearest),
		m_uMipMapFilter(Graphic::TextureFilter::None),
		m_uMaxAnisotropy(0)
	{
		GL::glGenTextures(1, &this->m_uTexture);	CR_GLCHECK();
	}

	IOGLBaseTexture::~IOGLBaseTexture(){
		GL::glDeleteTextures(1, &this->m_uTexture);
	}

	void	IOGLBaseTexture::Bind(){
		GL::glBindTexture(this->m_uTarget, this->m_uTexture);
	}

	void	IOGLBaseTexture::Unbind(){
		GL::glBindTexture(this->m_uTarget, 0);
	}

	void	IOGLBaseTexture::SetFilters(const Graphic::TextureFilter uMin, const Graphic::TextureFilter uMag){
		this->SetFilters(uMin, uMag, Graphic::TextureFilter::None);
	}

	void	IOGLBaseTexture::SetFilters(const Graphic::TextureFilter uMin, const Graphic::TextureFilter uMag, Graphic::TextureFilter uMipMap){
		GLenum uGLMin = GLUtils::ToTextureMinFilter(uMin);
		GLenum uGLMag = GLUtils::ToTextureMagFilter(uMag, uMipMap);

		CTextureBindGuard guard(this->m_uTarget);
		this->Bind();

		GL::glTexParameteri(this->m_uTarget, GL::GL_TEXTURE_MIN_FILTER, uGLMin);
		GL::glTexParameteri(this->m_uTarget, GL::GL_TEXTURE_MAG_FILTER, uGLMag);
	}

	void	IOGLBaseTexture::SetAnisotropy(const uint32 uMaxAnisotropy){
		CTextureBindGuard guard(this->m_uTarget);
		this->Bind();

		GL::glTexParameteri(this->m_uTarget, GL::GL_TEXTURE_MAX_ANISOTROPY, uMaxAnisotropy);
	}

	GLuint	IOGLBaseTexture::GetTextureID() const{
		return this->m_uTexture;
	}

	const uint32	IOGLBaseTexture::GetApiId() const {
		return g_uApiID;
	}

	CRefPtr<Graphic::IDevice>	IOGLBaseTexture::GetDevice() const{
		return this->m_pParent.Cast<Graphic::IDevice>();
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

	const Graphic::TextureFilter	IOGLBaseTexture::GetMinFilter() const{
		return this->m_uMinFilter;
	}

	const Graphic::TextureFilter	IOGLBaseTexture::GetMaxFilter() const{
		return this->m_uMagFilter;
	}

	const Graphic::TextureFilter	IOGLBaseTexture::GetMipmapFilter() const{
		return this->m_uMipMapFilter;
	}

	const uint32					IOGLBaseTexture::GetAnisotropy() const{
		return this->m_uMaxAnisotropy;
	}

	//===================================================

	CTextureBindGuard::CTextureBindGuard(const GLenum uTarget, const GLenum uBinding) :
		m_uTarget(uTarget),
		m_uBinding(uBinding),
		m_uTexture(0)
	{
		GL::glGetIntegerv(this->m_uBinding, reinterpret_cast<GLint*>(&this->m_uTexture));	CR_GLCHECK();
	}

	CTextureBindGuard::CTextureBindGuard(const GLenum uTarget) :
		m_uTarget(uTarget),
		m_uBinding(GLUtils::ToTargetBinding(uTarget)),
		m_uTexture(0)
	{
		GL::glGetIntegerv(this->m_uBinding, reinterpret_cast<GLint*>(&this->m_uTexture));	CR_GLCHECK();
	}

	CTextureBindGuard::~CTextureBindGuard(){
		if(this->m_uTexture != 0 && GL::glIsTexture(this->m_uTexture)){
			GL::glBindTexture(this->m_uTarget, this->m_uTexture);	CR_GLCHECK();
		}
	}
}
