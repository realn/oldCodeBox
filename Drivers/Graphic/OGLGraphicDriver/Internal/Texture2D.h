#pragma once

#include "BaseTexture.h"

namespace CB{
	class COGLTexture2D :
		public Graphic::ITexture2D,
		public IOGLBaseTexture
	{
	private:
		Math::CSize	m_Size;

	public:
		COGLTexture2D(CRefPtr<COGLDevice> pDevice, const Math::CSize& Size, const Graphic::BufferAccess uAccess, const Graphic::BufferUsage uUsage, const Graphic::BufferFormat uFormat, const void* pData);

		void	LoadData(const void* pData, const uint32 uLength) override;
		void	LoadSubData(const void* pData, const uint32 uOffset, const uint32 uLength) override;

		CRefPtr<IO::IStream>	MapData(const Graphic::BufferAccess uAccess, const bool bDiscard, const uint32 uOffset, const uint32 uLength) override;

		const Math::CSize	GetSize() const override;
	};
}