#pragma once

#include "Ref.h"
#include "Manage_Singleton.h"
#include "Collection.h"
#include "CBString.h"
#include "IO_Stream.h"

namespace CB{
	namespace Log{
		enum class LogLevel{
			Debug,
			Info,
			Warning,
			Error,
			Fatal
		};

		class IEntryFormatter :
			public virtual IRef
		{
		public:
			virtual void	LogBegin(CRefPtr<IO::IStream> pStream) = 0;
			virtual void	LogEnd(CRefPtr<IO::IStream> pStream) = 0;

			virtual void	EntryBegin(CRefPtr<IO::IStream> pStream) = 0;
			virtual void	EntryEnd(CRefPtr<IO::IStream> pStream) = 0;

			virtual void	FormatEntry(CRefPtr<IO::IStream> pStream, const CString& strEntry, const LogLevel uLevel) = 0;
			virtual void	FormatEntry(CRefPtr<IO::IStream> pStream, const Exception::CException& Exception, const LogLevel uLevel) = 0;
		};

		extern COMMON_API void	Write(const CString& strEntry); // default level: Info
		extern COMMON_API void	Write(const CString& strEntry, const LogLevel uLevel);
		extern COMMON_API void	Write(const Exception::CException& Exception);	// default level: Warning
		extern COMMON_API void	Write(const Exception::CException& Exception, const LogLevel uLevel);
	}

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

	namespace String{
		extern COMMON_API const CString	ToString(const Log::LogLevel uLevel);
	}
}