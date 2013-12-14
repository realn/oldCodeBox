#pragma once

#include "Ref.h"
#include "Manage_Singleton.h"
#include "Collection_Dictionary.h"
#include "CBString.h"
#include "IO_Stream.h"
#include "Logger_Consts.h"
#include "Logger_Interface.h"

namespace CB{
	namespace Log{
		class COMMON_API CLogger : 
			public IRef, 
			public Manage::CRefSingleton<CLogger>
		{
		private:
			Collection::CDictionary<CRefPtr<IO::IStream>, CRefPtr<Log::IEntryFormatter>>	m_pStreamList;
			bool	m_bDebugMode;

		public:
			CLogger();
			~CLogger();

			void	AddStream(CRefPtr<IO::IStream> pStream);
			void	AddStream(CRefPtr<IO::IStream> pStream, CRefPtr<Log::IEntryFormatter> pFormatter);
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