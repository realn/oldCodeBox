#include "../Internal/Texture2D.h"
#include "../Internal/Utils.h"

namespace CB{
	COGLTexture2D::COGLTexture2D(CRefPtr<COGLDevice> pDevice, const Math::CSize& Size, const Graphic::BufferAccess uAccess, const Graphic::BufferUsage uUsage, const Graphic::BufferFormat uFormat, const Graphic::BufferFormat uInputFormat, const void* pData) :
		IOGLBaseTexture(pDevice, GL::GL_TEXTURE_2D, Graphic::TextureType::Texture2D, uUsage, uAccess, uFormat),
		GL(pDevice->GetRC()),
		m_uCoordRWrap(Graphic::TextureWrap::Repeat),
		m_uCoordSWrap(Graphic::TextureWrap::Repeat),
		m_Size(Size)
	{
		CTextureBindGuard guard(GL, GL::GL_TEXTURE_2D, GL::GL_TEXTURE_BINDING_2D);
		this->Bind();

		GL.glTexParameteri(this->m_uTarget, GL::GL_TEXTURE_MAG_FILTER, GL::GL_NEAREST);	CR_GLCHECK();
		GL.glTexParameteri(this->m_uTarget, GL::GL_TEXTURE_MIN_FILTER, GL::GL_NEAREST);	CR_GLCHECK();
		GL.glTexParameteri(this->m_uTarget, GL::GL_TEXTURE_MAX_ANISOTROPY, 1);	CR_GLCHECK();
		GL.glTexParameteri(this->m_uTarget, GL::GL_TEXTURE_WRAP_R, GL::GL_REPEAT);	CR_GLCHECK();
		GL.glTexParameteri(this->m_uTarget, GL::GL_TEXTURE_WRAP_S, GL::GL_REPEAT);	CR_GLCHECK();
		GL.glTexParameteri(this->m_uTarget, GL::GL_GENERATE_MIPMAP, GL::GL_TRUE);	CR_GLCHECK();

		GLenum internalFormat = GLUtils::ToInternalFormat(uFormat, this->m_pParent->GetFeatureLevel());

		GLenum transferFormat = 0;
		GLenum transferType = 0;
		if(uInputFormat != Graphic::BufferFormat::Unknown){
			transferFormat = GLUtils::ToTransferFormat(uInputFormat, this->m_pParent->GetFeatureLevel());
			transferType = GLUtils::ToTransferType(uInputFormat, this->m_pParent->GetFeatureLevel());
		}
		else{
			transferFormat = GLUtils::ToTransferFormat(uFormat, this->m_pParent->GetFeatureLevel());
			transferType = GLUtils::ToTransferType(uFormat, this->m_pParent->GetFeatureLevel());
		}

		GL.glTexImage2D(this->m_uTarget, 0, internalFormat, Size.Width, Size.Height, 0, transferFormat, transferType, pData);	CR_GLCHECK();
	}

	void	COGLTexture2D::SetCoordWrap(const Graphic::TextureWrap uRCoord, const Graphic::TextureWrap uSCoord){
		GLenum uGLRCoord = GLUtils::ToTextureWrap(uRCoord);
		GLenum uGLSCoord = GLUtils::ToTextureWrap(uSCoord);

		CTextureBindGuard guard(GL, this->m_uTarget);
		this->Bind();

		GL.glTexParameteri(this->m_uTarget, GL::GL_TEXTURE_WRAP_R, uGLRCoord);	CR_GLCHECK();
		GL.glTexParameteri(this->m_uTarget, GL::GL_TEXTURE_WRAP_S, uGLSCoord);	CR_GLCHECK();
	}

	void	COGLTexture2D::LoadData(const Graphic::BufferFormat uInputFormat, const void* pData, const uint32 uWidth, const uint32 uHeight){
		this->LoadSubData(uInputFormat, pData, 0, 0, uWidth, uHeight);
	}

	void	COGLTexture2D::LoadSubData(const Graphic::BufferFormat uInputFormat, const void* pData, const uint32 uXOffset, const uint32 uYOffset, const uint32 uWidth, const uint32 uHeight){
		GLenum uTransferFormat = GLUtils::ToTransferFormat(uInputFormat, this->m_pParent->GetFeatureLevel());
		GLenum uTransferType = GLUtils::ToTransferType(uInputFormat, this->m_pParent->GetFeatureLevel());

		CTextureBindGuard guard(GL, GL::GL_TEXTURE_2D, GL::GL_TEXTURE_BINDING_2D);
		GL.glBindTexture(this->m_uTarget, this->m_uTexture);	CR_GLCHECK();
		GL.glTexSubImage2D(this->m_uTarget, 0, uXOffset, uYOffset, uWidth, uHeight, uTransferFormat, uTransferType, pData);	CR_GLCHECK();
	}

	const Math::CSize	COGLTexture2D::GetSize() const{
		return this->m_Size;
	}
}