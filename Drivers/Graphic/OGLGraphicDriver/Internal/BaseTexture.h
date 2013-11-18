#pragma once

#include "Device.h"

namespace CB{
	class IOGLBaseTexture :
		public virtual Graphic::IBaseTexture,
		public Manage::IManagedObject<COGLDevice, IOGLBaseTexture>
	{
	protected:
		const Graphic::TextureType	m_uType;
		const Graphic::BufferAccess	m_uAccess;
		const Graphic::BufferUsage	m_uUsage;
		const Graphic::BufferFormat	m_uFormat;
		const uint32				m_uLength;

		const GLenum	m_uTarget;
		GLuint	m_uTexture;

	public:
		void	Bind();

		//	INTERFACE IMPLEMENTATION

		const uint32	GetApiId() const override;

		CRefPtr<Graphic::IDevice>	GetDevice() const override;
		const Graphic::BufferType	GetType() const override;
		const Graphic::BufferAccess	GetAccess() const override;
		const Graphic::BufferUsage	GetUsage() const override;
		const Graphic::BufferFormat	GetFormat() const override;
		const Graphic::TextureType	GetTextureType() const override;
		const uint32				GetLength() const override;

		CRefPtr<IO::IStream>	Map(const Graphic::BufferAccess uAccess) override;
		CRefPtr<IO::IStream>	Map(const Graphic::BufferAccess uAccess, const bool bDiscard) override;
		CRefPtr<IO::IStream>	Map(const Graphic::BufferAccess uAccess, const bool bDiscard, const uint32 uOffset, const uint32 uLength) override;

		//	END OF INTERFACE IMPLEMENTATION

		virtual CRefPtr<IO::IStream>	MapData(const Graphic::BufferAccess uAccess, const bool bDiscard, const uint32 uOffset, const uint32 uLength) = 0;

	protected:
		IOGLBaseTexture(
			CRefPtr<COGLDevice> pDevice, 
			const GLenum uTarget, 
			const uint32 uLength, 
			const Graphic::TextureType uType, 
			const Graphic::BufferUsage uUsage, 
			const Graphic::BufferAccess uAccess, 
			const Graphic::BufferFormat uFormat
			);
		~IOGLBaseTexture();
	};

	class CTextureBindGuard{
	private:
		const GLenum	m_uTarget;
		const GLenum	m_uBinding;
		GLuint	m_uTexture;

	public:
		CTextureBindGuard(const GLenum uTarget, const GLenum uBinding);
		~CTextureBindGuard();
	};
}