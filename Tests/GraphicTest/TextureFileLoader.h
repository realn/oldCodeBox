#pragma once

#include <GraphicDriver.h>

namespace GraphicTest{
	class CTexture2DFileLoader{
	private:
		const CB::CString	m_strFilename;

	public:
		CB::CRefPtr<CB::Graphic::ITexture2D>	pTexture;

		CTexture2DFileLoader(CB::CRefPtr<CB::Graphic::IDevice> pDevice, const CB::CString& strFilename);

		void	Reload(CB::CRefPtr<CB::Graphic::IDevice> pDevice);
	};
}