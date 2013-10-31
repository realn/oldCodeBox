#include "../Internal/IO_WindowsConsoleStream.h"
#include "../Include/WindowsErrors.h"

namespace CB{
	CWindowsConsoleStream*	Manage::CRefSingleton<CWindowsConsoleStream>::ms_pInstance = 0;

	CWindowsConsoleStream::CWindowsConsoleStream(){
		if(!AllocConsole()){
			//throw Exception::CStreamException(
			//	L"Failed to allocate new console.", __FUNCTIONW__, __FILEW__, __LINE__);
		}

		this->m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		if(this->m_hConsole == 0 || this->m_hConsole == INVALID_HANDLE_VALUE){
			throw Exception::CStreamException(
				L"Failed to aquire console handle. " + CWindowsError(GetLastError()).GetMessage(), __FUNCTIONW__, __FILEW__, __LINE__);
		}
	}

	CWindowsConsoleStream::~CWindowsConsoleStream(){
		this->m_hConsole = 0;

		if(!FreeConsole()){
			throw Exception::CStreamException(
				L"Failed to free console stream.", __FUNCTIONW__, __FILEW__, __LINE__);
		}
	}

	const bool	CWindowsConsoleStream::CanRead() const{
		return false;
	}

	const bool	CWindowsConsoleStream::CanWrite() const{
		return true;
	}

	void	CWindowsConsoleStream::Read(void* pData, const unsigned uSizeInBytes, const unsigned uNumberOfElements){
		throw Exception::CStreamException(
			L"Windows console stream cannot be readed.", __FUNCTIONW__, __FILEW__, __LINE__);
	}

	void	CWindowsConsoleStream::Write(const void* pData, const unsigned uSizeInBytes, const unsigned uNumberOfElements){
		Collection::CList<char> Data;

		try{
			Collection::CLinkList<char> List((char*)pData, uSizeInBytes * uNumberOfElements);
	
			Collection::CLinkList<char>::CEnumerator Enumerator = List.GetEnumerator();
			unsigned uIndex = 0;
			for(Enumerator.ToFirst(); Enumerator.HasNext(); Enumerator.Next()){
				if(Enumerator.Get() == '\n'){
					List.Insert(uIndex, '\r');
					uIndex++;
				}
				uIndex++;
			}
			Data = List;
		}
		catch(Exception::CException& Exception){
			throw Exception::CStreamException(
				L"Error while converting data for console buffer write.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
		}

		DWORD dwCount = 0;
		if(!WriteConsoleA(this->m_hConsole, &Data[0], Data.GetLength(), &dwCount, 0)){
			throw Exception::CStreamException(
				L"Failed to write to console buffer. " + CWindowsError(GetLastError()).GetMessage(), __FUNCTIONW__, __FILEW__, __LINE__);
		}
	}

	void	CWindowsConsoleStream::Read(CRefPtr<IStream> pOutStream, const unsigned uSizeInBytes){
		throw Exception::CStreamException(
			L"Windows Console stream cannot be readed.", __FUNCTIONW__, __FILEW__, __LINE__);
	}

	void	CWindowsConsoleStream::Write(CRefPtr<IStream> pInStream, const unsigned uSizeInBytes){
		try{
			Collection::CList<char> Data(uSizeInBytes);
			Memory::SetZeroArray(Data);
			pInStream->Read(Data);
			dynamic_cast<IO::IStream*>(this)->Write(Data);
		}
		catch(Exception::CException& Exception){
			throw Exception::CStreamException(
				L"Error while writing stream to console.", __FUNCTIONW__, __FILEW__, __LINE__, Exception);
		}
	}

	const bool	CWindowsConsoleStream::IsEndOfStream() const{
		return false;
	}

	const bool	CWindowsConsoleStream::IsBeginingOfStream() const{
		return false;
	}

	const bool	CWindowsConsoleStream::IsEmpty() const{
		return false;
	}

	const unsigned	CWindowsConsoleStream::GetLength() const{
		return 0xFFFFFFFF;
	}

	void	CWindowsConsoleStream::SetPos(const int uPos, const IO::StreamPos uType){
		return;
	}

	const unsigned	CWindowsConsoleStream::GetPos() const{
		return 0;
	}

	void	CWindowsConsoleStream::Flush(){
		return;
	}

	// function implementation

	namespace IO{
		namespace Console{
			CRefPtr<IO::IOSConsoleStream>	Create(){
				return	CWindowsConsoleStream::GetInstance().Cast<IO::IOSConsoleStream>();
			}
		}
	}
}