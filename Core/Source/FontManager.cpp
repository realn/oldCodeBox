#include "stdafx.h"
#include "../Include/FontManager.h"
#include "../Include/Font.h"
#include "../Include/IO_Stream.h"

namespace CB{
	namespace Font{
		CManager::CManager(){
			FT_Library	pLib = 0;

			auto uError = FT_Init_FreeType(&pLib);
			if(uError != 0){
				CR_THROW(L"Failed to load freetype library, error: " + String::ToHexString(uError));
			}

			this->m_pData.SetCast<FT_Library>(pLib);
		}

		CManager::~CManager(){
			auto pLib = this->m_pData.ResetCast<FT_Library>();
			FT_Done_FreeType(pLib);
		}

		CRefPtr<CFont>	CManager::Load(CRefPtr<IO::IStream> pStream){
			return new CFont(this, pStream);
		}

		CRefPtr<CManager>	CManager::Create(){
			return new CManager();
		}
	}
}