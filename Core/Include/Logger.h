#pragma once

#include "Macros.h"
#include "Types.h"
#include "Ref.h"
#include "Manage_Singleton.h"
#include "Collection_Dictionary.h"
#include "Logger_Consts.h"

namespace CB{
	class CString;
	template<typename _Type> class CRefPtr;

	namespace IO{
		class IStream;
	}

	namespace Log{
		class IEntryFormat;

		class COMMON_API CLogger : 
			public IRef, 
			public Manage::CRefSingleton<CLogger>
		{
		private:
			Collection::CDictionary<CRefPtr<IO::IStream>, CRefPtr<Log::IEntryFormat>>	m_pStreamList;
			bool	m_bDebugMode;

		public:
			CLogger();
			~CLogger();

			void	AddStream(CRefPtr<IO::IStream> pStream);
			void	AddStream(CRefPtr<IO::IStream> pStream, CRefPtr<Log::IEntryFormat> pFormatter);
			void	RemoveStream(CRefPtr<IO::IStream> pStream);

			void	SetDebugMode(const bool bMode);
			const bool	IsDebugMode() const;

			void	Write(const CString& strEntry); // default level: Info
			void	Write(const CString& strEntry, const Log::LogLevel uLevel);
			void	Write(const Exception::CException& Exception);	// default level: Warning
			void	Write(const Exception::CException& Exception, const Log::LogLevel uLevel);
		};

		extern COMMON_API void	Write(const CString& strEntry); // default level: Info
		extern COMMON_API void	Write(const CString& strEntry, const LogLevel uLevel);
		extern COMMON_API void	Write(const Exception::CException& Exception);	// default level: Warning
		extern COMMON_API void	Write(const Exception::CException& Exception, const LogLevel uLevel);
	}
}