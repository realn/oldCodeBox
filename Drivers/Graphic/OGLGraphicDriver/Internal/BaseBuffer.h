#pragma once

#include "Device.h"

namespace CB{
	class COGLBufferStream;

	class IOGLBaseBuffer : 
		public Graphic::IBuffer,
		public Manage::IManagedObject<COGLDevice, IOGLBaseBuffer>,
		public Manage::IObjectManager<IOGLBaseBuffer, COGLBufferStream>
	{
	private:
		CGLRenderContext&			GL;
		const Graphic::BufferType	m_uType;
		const GLenum				m_uBufferTarget;
		const uint32				m_uLength;
		const Graphic::BufferUsage	m_uUsage;
		const Graphic::BufferAccess m_uAccess;
		GLuint						m_uBuffer;
		bool						m_bBinded;

	public:
		IOGLBaseBuffer(CRefPtr<COGLDevice> pDevice, const Graphic::BufferType uType, const GLenum uBufferTarget, const Graphic::BufferUsage uUsage, const Graphic::BufferAccess uAccess, const uint32 uLength, const void* pData);
		~IOGLBaseBuffer();

		void	Bind();
		void	Unbind();

		const GLenum	GetTarget() const;
		const GLuint	GetBufferID() const;

		//	INTERFACE IMPLEMENTATION	===============================

		const uint32	GetApiId() const override;

		const Graphic::BufferType	GetType() const override;

		CRefPtr<Graphic::IDevice>	GetDevice() const override;
		const uint32				GetLength() const override;
		const Graphic::BufferUsage	GetUsage() const override;
		const Graphic::BufferAccess	GetAccess() const override;

		void	LoadData(const void* pData, const uint32 uLength) override;
		void	LoadSubData(const void* pData, const uint32 uOffset, const uint32 uLength) override;

		CRefPtr<IO::IStream>	Map(const Graphic::BufferAccess uAccess) override;
		CRefPtr<IO::IStream>	Map(const Graphic::BufferAccess uAccess, const bool bDiscard) override;
		CRefPtr<IO::IStream>	Map(const Graphic::BufferAccess uAccess, const bool bDiscard, const uint32 uOffset, const uint32 uLength) override;

		//	END OF INTERFACE IMPLEMENTATION	===========================
	};

	class CBufferBindGurard{
	private:
		CGLRenderContext& GL;
		const GLenum	m_uTarget;
		const GLenum	m_uBinding;
		GLuint			m_uBufferID;
	public:
		CBufferBindGurard(CGLRenderContext& GL, const GLenum uTarget);
		CBufferBindGurard(CGLRenderContext& GL, const GLenum uTarget, const GLenum uBinding);
		~CBufferBindGurard();
	};
}