#include "../Include/IO_Stream.h"

namespace CB{
	namespace Exception{
		CStreamException::CStreamException(const CStreamException& Exception) : CException(Exception){
		}

		CStreamException::CStreamException(const CString& strMessage, const CString& strFunction, const CString& strFile, const unsigned uLine)
			: CException(strMessage, strFunction, strFile, uLine){
		}

		CStreamException::CStreamException(const CString& strMessage, const CString& strFunction, const CString& strFile, const unsigned uLine, CException& InnerException)
			: CException(strMessage, strFunction, strFile, uLine, InnerException){
		}

		CException*	CStreamException::CreateCopy() const{
			return new CStreamException(*this);
		}
	}
}