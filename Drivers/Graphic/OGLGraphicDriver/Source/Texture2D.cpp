#include "../Internal/Texture2D.h"
#include "../Internal/Utils.h"

namespace CB{
	COGLTexture2D::COGLTexture2D(CRefPtr<COGLDevice> pDevice, const Math::CSize& Size, const Graphic::BufferAccess uAccess, const Graphic::BufferUsage uUsage, const Graphic::BufferFormat uFormat, const void* pData) :
		IOGLBaseTexture(pDevice, GL::GL_TEXTURE_2D, Size.Width * Size.Height * GLUtils::GetBitsPerPixel(uFormat), Graphic::TextureType::Texture2D, uUsage, uAccess, uFormat),
		m_Size(Size)
	{
		CTextureBindGuard guard(GL::GL_TEXTURE_2D, GL::GL_TEXTURE_BINDING_2D);

		GL::glBindTexture(this->m_uTarget, this->m_uTexture);
		GL::glTexParameteri(this->m_uTarget, GL::GL_TEXTURE_MAG_FILTER, GL::GL_LINEAR);
		GL::glTexParameteri(this->m_uTarget, GL::GL_TEXTURE_MIN_FILTER, GL::GL_LINEAR);
		GL::glTexParameteri(this->m_uTarget, GL::GL_GENERATE_MIPMAP, GL::GL_TRUE);

		GLenum internalFormat = GLUtils::ToInternalFormat(uFormat);
		GLenum transferFormat = GLUtils::ToTransferFormat(uFormat);
		GLenum transferType = GLUtils::ToTransferType(uFormat);

		GL::glTexImage2D(this->m_uTarget, 0, internalFormat, Size.Width, Size.Height, 0, transferFormat, transferType, pData);
	}

	void	COGLTexture2D::LoadData(const void* pData, const uint32 uLength){
		this->LoadSubData(pData, 0, uLength);
	}

	void	COGLTexture2D::LoadSubData(const void* pData, const uint32 uOffset, const uint32 uLength){
		uint32 uCompSize = GLUtils::GetBitsPerPixel(this->m_uFormat) / 8;

		if(uOffset % (this->m_Size.Width * uCompSize) != 0){
			throw Exception::CInvalidArgumentException(L"uOffset", String::ToString(uOffset),
				L"Offset isn't aligned by texture splice.", CR_INFO());
		}
		if(uLength % (this->m_Size.Width * uCompSize) != 0){
			throw Exception::CInvalidArgumentException(L"uLength", String::ToString(uLength),
				L"Length isn't aligned by texture splice.", CR_INFO());
		}

		uint32 yOffset = uOffset / (this->m_Size.Width * uCompSize);
		uint32 yLength = uLength / (this->m_Size.Width * uCompSize);

		GLenum uTransferFormat = GLUtils::ToTransferFormat(this->m_uFormat);
		GLenum uTransferType = GLUtils::ToTransferType(this->m_uFormat);

		CTextureBindGuard guard(GL::GL_TEXTURE_2D, GL::GL_TEXTURE_BINDING_2D);
		GL::glBindTexture(this->m_uTarget, this->m_uTexture);
		GL::glTexSubImage2D(this->m_uTarget, 0, this->m_Size.Width, yOffset, this->m_Size.Width, yLength, uTransferFormat, uTransferType, pData);
	}

	CRefPtr<IO::IStream>	COGLTexture2D::MapData(const Graphic::BufferAccess uAccess, const bool bDiscard, const uint32 uOffset, const uint32 uLength){
		CR_THROWNOTIMPLEMENTED();
	}

	const Math::CSize	COGLTexture2D::GetSize() const{
		return this->m_Size;
	}
}