#include "stdafx.h"
#include "../Internal/IO_FreeImage.h"
#include "../Include/Exception.h"

namespace FreeImage{
	CStream::CStream() : m_pStream(0){
	}

	CStream::CStream(FIMEMORY* pStream) : m_pStream(pStream){
	}

	CStream::CStream(BYTE* pData, const unsigned uLength) : m_pStream(0){
		this->Create(pData, uLength);
	}

	CStream::CStream(CB::Collection::CList<BYTE>& Data) : m_pStream(0){
		this->Create(Data);
	}

	CStream::~CStream(){
		this->Free();
	}

	void	CStream::Create(CB::Collection::CList<BYTE>& Data){
		this->Create(Data.IsEmpty() ? 0 : &Data[0], Data.GetLength());
	}

	void	CStream::Create(BYTE* pData, const unsigned uLength){
		this->m_pStream = FreeImage_OpenMemory(pData, uLength);
		if(this->m_pStream == 0){
			throw CB::Exception::CException(
				L"Failed to open image stream.", __FUNCTIONW__, __FILEW__, __LINE__);
		}
	}

	void	CStream::Set(FIMEMORY* pStream){
		this->m_pStream = pStream;
	}

	void	CStream::Free(){
		if(this->m_pStream){
			FreeImage_CloseMemory(this->m_pStream);
			this->m_pStream = 0;
		}
	}

	FIMEMORY*	CStream::Get() const{
		return this->m_pStream;
	}
}