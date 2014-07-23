#include "../Include/Logger.h"
#include "../Include/Logger_Formatters.h"

CB::Log::CLogger*	CB::Manage::CRefSingleton<CB::Log::CLogger>::ms_pInstance = 0;

namespace CB{
	namespace Log{
		CLogger::CLogger() : 
			m_bDebugMode(false)
		{
		}

		CLogger::~CLogger(){
			auto En = this->m_pStreamList.GetEnumerator();
			for(En.ToFirst(); En.IsValid(); En.Next()){
				En.GetValue()->LogEnd(En.GetKey());
				En.GetKey()->Flush();
			}
		}

		void	CLogger::AddStream(CRefPtr<IO::IStream> pStream){
			CRefPtr<IEntryFormat> pFormatter = Log::CTextFormatter::Create().Cast<Log::IEntryFormat>();
			this->AddStream(pStream, pFormatter);
		}

		void	CLogger::AddStream(CRefPtr<IO::IStream> pStream, CRefPtr<Log::IEntryFormat> pFormatter){
			if(this->m_pStreamList.Contains(pStream)){
				return;
			}
			this->m_pStreamList.Add(pStream, pFormatter);
			pFormatter->LogBegin(pStream);
		}

		void	CLogger::RemoveStream(CRefPtr<IO::IStream> pStream){
			uint32 uIndex = 0;
			if(this->m_pStreamList.FindKey(pStream, uIndex)){
				this->m_pStreamList[pStream]->LogEnd(pStream);
				this->m_pStreamList.Remove(uIndex);
			}
		}

		void	CLogger::Write(const CString& strEntry){
			this->Write(strEntry, Log::LogLevel::Info);
		}

		void	CLogger::Write(const Exception::CException& Exception){
			this->Write(Exception, Log::LogLevel::Warning);
		}

		void	CLogger::Write(const CString& strEntry, const Log::LogLevel uLevel){
			if(!this->m_bDebugMode && uLevel == Log::LogLevel::Debug){
				return;
			}

			try{
				auto Enumerator = this->m_pStreamList.GetEnumerator();
				for(Enumerator.ToFirst(); Enumerator.IsValid(); Enumerator.Next()){

					Enumerator.GetValue()->EntryBegin(Enumerator.GetKey());
					Enumerator.GetValue()->FormatEntry(Enumerator.GetKey(), strEntry, uLevel);
					Enumerator.GetValue()->EntryEnd(Enumerator.GetKey());

					if(uLevel == Log::LogLevel::Error || uLevel == Log::LogLevel::Fatal){
						Enumerator.GetKey()->Flush();
					}
				}
			}
			catch(Exception::CException&){
				return;
			}
		}

		void	CLogger::Write(const Exception::CException& Exception, Log::LogLevel uLevel){
			if(!this->m_bDebugMode && uLevel == Log::LogLevel::Debug){
				return;
			}

			try{
				auto Enumerator = this->m_pStreamList.GetEnumerator();
				for(Enumerator.ToFirst(); Enumerator.IsValid(); Enumerator.Next()){

					Enumerator.GetValue()->EntryBegin(Enumerator.GetKey());
					Enumerator.GetValue()->FormatEntry(Enumerator.GetKey(), Exception, uLevel);
					Enumerator.GetValue()->EntryEnd(Enumerator.GetKey());

					if(uLevel == Log::LogLevel::Error || uLevel == Log::LogLevel::Fatal){
						Enumerator.GetKey()->Flush();
					}
				}
			}
			catch(Exception::CException&){
				return;
			}
		}

		void	CLogger::SetDebugMode(const bool bMode){
			this->m_bDebugMode = bMode;
		}

		const bool	CLogger::IsDebugMode() const{
			return this->m_bDebugMode;
		}

	//	Functions implementation

		void	Write(const CString& strEntry){
			CLogger::GetInstance()->Write(strEntry);
		}

		void	Write(const CString& strEntry, const LogLevel uLevel){
			CLogger::GetInstance()->Write(strEntry, uLevel);
		}

		void	Write(const Exception::CException& Exception){
			CLogger::GetInstance()->Write(Exception);
		}

		void	Write(const Exception::CException& Exception, const LogLevel uLevel){
			CLogger::GetInstance()->Write(Exception, uLevel);
		}
	}

	namespace String{
		const CString	ToString(const Log::LogLevel uLevel){
			switch (uLevel)
			{
			case Log::LogLevel::Info:	return L"INFO";
			case Log::LogLevel::Debug:	return L"DEBUG";
			case Log::LogLevel::Warning:	return L"WARNING";
			case Log::LogLevel::Error:	return L"ERROR";
			case Log::LogLevel::Fatal:	return L"FATAL";
			default:
				return L"UNKNOWN";
			}
		}
	}
}