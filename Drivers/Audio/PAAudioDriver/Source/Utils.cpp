#include "../Internal/Utils.h"

namespace CB{
	namespace Utils{
		const CString	ToErrorString(const PaError uError){
			auto szError = Pa_GetErrorText(uError);
			if(szError == 0)
				return L"";
			return String::FromANSI(reinterpret_cast<const int8*>(szError));
		}
	}
}