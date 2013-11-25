#pragma once

#include "BaseTexture.h"
#pragma warning(disable : 4250)

namespace CB{
	class COGLTexture2D :
		public Graphic::ITexture2D,
		public IOGLBaseTexture
	{
	private:
		Graphic::TextureWrap	m_uCoordRWrap;
		Graphic::TextureWrap	m_uCoordSWrap;
		Math::CSize				m_Size;

	public:
		COGLTexture2D(CRefPtr<COGLDevice> pDevice, const Math::CSize& Size, const Graphic::BufferAccess uAccess, const Graphic::BufferUsage uUsage, const Graphic::BufferFormat uFormat, const Graphic::BufferFormat uInputFormat, const void* pData);

		void	SetCoordWrap(const Graphic::TextureWrap uRCoord, const Graphic::TextureWrap uSCoord) override;

		void	LoadData(const Graphic::BufferFormat uInputFormat, const void* pData, const uint32 uWidth, const uint32 uHeight) override;
		void	LoadSubData(const Graphic::BufferFormat uInputFormat, const void* pData, const uint32 uXOffset, const uint32 uYOffset, const uint32 uWidth, const uint32 uHeight) override;

		const Math::CSize	GetSize() const override;
	};
}