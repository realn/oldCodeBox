#include "../Include/Logger.h"

namespace CB{
	CLogger*	Manage::CRefSingleton<CLogger>::ms_pInstance = 0;

	CLogger::CLogger() : 
		m_bDebugMode(false)
	{
	}

	CLogger::~CLogger(){
		auto En = this->m_pStreamList.GetEnumerator();
		for(En.ToFirst(); En.IsValid(); En.Next()){
			En.Get()->Flush();
		}
	}

	void	CLogger::AddStream(CRefPtr<IO::IStream> pStream){
		if(Collection::Contains(this->m_pStreamList, pStream)){
			return;
		}
		this->m_pStreamList.Add(pStream);
	}

	void	CLogger::RemoveStream(CRefPtr<IO::IStream> pStream){
		Collection::CLinkList<CRefPtr<IO::IStream>>::CEnumerator Enumerator = this->m_pStreamList.GetEnumerator();
		if(Collection::TryGetEnumerator(this->m_pStreamList, pStream, Enumerator)){
			this->m_pStreamList.Remove(Enumerator);
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
			Collection::CLinkList<CRefPtr<IO::IStream>>::CEnumerator Enumerator = this->m_pStreamList.GetEnumerator();
			for(Enumerator.ToFirst(); Enumerator.IsValid(); Enumerator.Next()){
				IO::CTextWriter writer(Enumerator.Get());

				writer.WriteLineANSI(String::ToString(uLevel) + L": " + strEntry);

				if(uLevel == Log::LogLevel::Error || uLevel == Log::LogLevel::Fatal){
					writer.GetStream()->Flush();
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
			Collection::CLinkList<CRefPtr<IO::IStream>>::CEnumerator Enumerator = this->m_pStreamList.GetEnumerator();
			for(Enumerator.ToFirst(); Enumerator.IsValid(); Enumerator.Next()){
				IO::CTextWriter writer(Enumerator.Get());

				writer.WriteLineANSI(String::ToString(uLevel) + L": EXCEPTION:");
				writer.WriteLineANSI(L"\tFile:\t" + Exception.GetFile());
				writer.WriteLineANSI(L"\tLine:\t" + String::FromUInt32(Exception.GetLine()));
				writer.WriteLineANSI(L"\tFunction:\t" + Exception.GetFunction());
				writer.WriteLineANSI(L"\tMessage:\t" + Exception.GetMessage());

				const Exception::CException* pException = &Exception;
				while(pException->HasInnerException()){
					pException = &pException->GetInnerException();

					writer.WriteLineANSI(L"\tInner exception:");
					writer.WriteLineANSI(L"\t\tFile:\t" + pException->GetFile());
					writer.WriteLineANSI(L"\t\tLine:\t" + String::FromUInt32(pException->GetLine()));
					writer.WriteLineANSI(L"\t\tFunction:\t" + pException->GetFunction());
					writer.WriteLineANSI(L"\t\tMessage:\t" + pException->GetMessage());
				}

				if(uLevel == Log::LogLevel::Error || uLevel == Log::LogLevel::Fatal){
					writer.GetStream()->Flush();
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

	namespace Log{
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