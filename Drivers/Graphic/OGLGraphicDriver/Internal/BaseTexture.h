#pragma once

#include "Device.h"

namespace CB{
	class IOGLBaseTexture :
		public virtual Graphic::IBaseTexture,
		public Manage::IManagedObject<COGLDevice, IOGLBaseTexture>
	{
	protected:
		CGLRenderContext&			GL;
		const Graphic::TextureType	m_uType;
		const Graphic::BufferAccess	m_uAccess;
		const Graphic::BufferUsage	m_uUsage;
		const Graphic::BufferFormat	m_uFormat;
		const GLenum				m_uTarget;

		GLuint					m_uTexture;
		Graphic::TextureFilter	m_uMinFilter;
		Graphic::TextureFilter	m_uMagFilter;
		Graphic::TextureFilter	m_uMipMapFilter;
		uint32					m_uMaxAnisotropy;

	public:
		void	Bind();
		void	Unbind();

		GLuint	GetTextureID() const;

		//	INTERFACE IMPLEMENTATION

		const uint32	GetApiId() const override;

		void	SetFilters(const Graphic::TextureFilter uMin, const Graphic::TextureFilter uMag) override;
		void	SetFilters(const Graphic::TextureFilter uMin, const Graphic::TextureFilter uMag, Graphic::TextureFilter uMipMap) override;
		void	SetAnisotropy(const uint32 uMaxAnisotropy) override;

		CRefPtr<Graphic::IDevice>		GetDevice() const override;
		const Graphic::BufferAccess		GetAccess() const override;
		const Graphic::BufferUsage		GetUsage() const override;
		const Graphic::BufferFormat		GetFormat() const override;
		const Graphic::TextureType		GetTextureType() const override;
		const Graphic::TextureFilter	GetMinFilter() const override;
		const Graphic::TextureFilter	GetMaxFilter() const override;
		const Graphic::TextureFilter	GetMipmapFilter() const override;
		const uint32					GetAnisotropy() const override;

		//	END OF INTERFACE IMPLEMENTATION

	protected:
		IOGLBaseTexture(CRefPtr<COGLDevice> pDevice, const GLenum uTarget, const Graphic::TextureType uType, const Graphic::BufferUsage uUsage, const Graphic::BufferAccess uAccess, const Graphic::BufferFormat uFormat);
		~IOGLBaseTexture();
	};

	class CTextureBindGuard{
	private:
		CGLRenderContext&	GL;
		const GLenum		m_uTarget;
		const GLenum		m_uBinding;
		GLuint				m_uTexture;

	public:
		CTextureBindGuard(CGLRenderContext& GL, const GLenum uTarget, const GLenum uBinding);
		CTextureBindGuard(CGLRenderContext& GL, const GLenum uTarget);
		~CTextureBindGuard();
	};
}