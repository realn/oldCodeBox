#include "stdafx.h"
#include "../Include/IO_Stream_Exceptions.h"

namespace CB{
	namespace Exception{
		CStreamException::CStreamException(const CStreamException& Exception) : CException(Exception){
		}

		CStreamException::CStreamException(const CString& strMessage, const CString& strFunction, const CString& strFile, const uint32 uLine)
			: CException(strMessage, strFunction, strFile, uLine){
		}

		CStreamException::CStreamException(const CString& strMessage, const CString& strFunction, const CString& strFile, const uint32 uLine, CException& InnerException)
			: CException(strMessage, strFunction, strFile, uLine, InnerException){
		}

		CException*	CStreamException::CreateCopy() const{
			return new CStreamException(*this);
		}
	}
}