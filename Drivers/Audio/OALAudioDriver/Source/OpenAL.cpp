#include "../Internal/OpenAL.h"
#include <Exception.h>
#include <Logger.h>

namespace AL{
	void ReportALBindMismatch(const CB::CString& strFunction, const CB::CString& strFile, const uint32 uLine){
#ifdef CR_AL_ERROR_AS_EXCEPTION
		throw Exception::CException(L"Incorrect AL or device context currently bound.", strFunction, strFile, uLine);
#else
		CB::Log::Write(CB::CString(L"Incorrect AL or Device context currently bound. ") + strFunction + L", " + strFile + L", " + CB::String::ToString(uLine), CB::Log::LogLevel::Warning);
#endif // CR_AL_ERROR_AS_EXCEPTION
	}

	void ReportALError(const ALenum uError, const CB::CString& strFunction, const CB::CString& strFile, const uint32 uLine){
		CB::CString strError = L"AL Error: " + CB::String::ToHexString(uError);
#ifdef CR_AL_ERROR_AS_EXCEPTION
		throw Exception::CException(strError, strFunction, strFile, uLine);
#else
		CB::Log::Write(strError + L", " + strFunction + L", " + strFile + L", " + CB::String::ToString(uLine), CB::Log::LogLevel::Error);
#endif
	}
}