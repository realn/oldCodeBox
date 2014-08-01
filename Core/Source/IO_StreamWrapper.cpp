#include "stdafx.h"
#include "../Include/CBString.h"
#include "../Include/IO_StreamWrapper.h"
#include "../Include/IO_Stream.h"

namespace CB{
	namespace IO{
		IStreamWrapper::IStreamWrapper(const CRefPtr<IStream> pStream) : 
			m_pStream(pStream)
		{
		}

		IStreamWrapper::IStreamWrapper(const IStreamWrapper& Wrapper) : 
			m_pStream(Wrapper.m_pStream)
		{
		}

		IStreamWrapper::~IStreamWrapper(){
		}

		CRefPtr<IStream>	IStreamWrapper::GetStream(){
			return this->m_pStream;
		}
		const CRefPtr<IStream>	IStreamWrapper::GetStream() const{
			return this->m_pStream;
		}
	}
}