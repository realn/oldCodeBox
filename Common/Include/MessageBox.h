#pragma once

#include "Macros.h"
#include "CBString.h"
#include "Exception.h"

namespace CB{
	namespace Message{
		enum class Icon{
			None,
			Question,
			Information,
			Exclamation,
			Warning,
			Error,
		};

		extern COMMON_API void Show(const CString& strText);
		extern COMMON_API void Show(const CString& strText, const CString& strCaption);
		extern COMMON_API void Show(const CString& strText, const CString& strCaption, const Icon uIcon);
		extern COMMON_API void Show(const Exception::CException& Exception);
		extern COMMON_API void Show(const Exception::CException& Exception, const Icon uIcon);
	}
}