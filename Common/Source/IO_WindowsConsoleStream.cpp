#include "../Internal/IO_WindowsConsoleStream.h"
#include "../Include/WindowsErrors.h"
#include "../Include/Collection_List.h"

namespace CB{
	CWindowsConsoleStream*	Manage::CRefSingleton<CWindowsConsoleStream>::ms_pInstance = 0;

	CWindowsConsoleStream::CWindowsConsoleStream() : 
		m_hConsole(0)
	{
		if(!AllocConsole()){
			//throw Exception::CStreamException(
			//	L"Failed to allocate new console.", CR_INFO());
		}

		this->m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		if(this->m_hConsole == 0 || this->m_hConsole == INVALID_HANDLE_VALUE){
			throw Exception::CStreamException(
				L"Failed to aquire console handle. " + CWindowsError(GetLastError()).GetMessage(), CR_INFO());
		}
	}

	CWindowsConsoleStream::~CWindowsConsoleStream(){
		this->m_hConsole = 0;

		if(!FreeConsole()){
			throw Exception::CStreamException(
				L"Failed to free console stream.", CR_INFO());
		}
	}

	const bool	CWindowsConsoleStream::CanRead() const{
		return false;
	}

	const bool	CWindowsConsoleStream::CanWrite() const{
		return true;
	}

	void	CWindowsConsoleStream::Read(void* pData, const uint32 uSizeInBytes, const uint32 uNumberOfElements){
		throw Exception::CStreamException(
			L"Windows console stream cannot be readed.", CR_INFO());
	}

	void	CWindowsConsoleStream::Write(const void* pData, const uint32 uSizeInBytes, const uint32 uNumberOfElements){
		Collection::CList<byte> Data;
		try{
			Data.Set(uSizeInBytes * uNumberOfElements, (byte*)pData);
	
			for(uint32 uIndex = 0; uIndex < Data.GetLength(); uIndex++){
				if(Data[uIndex] == (byte)'\n'){
					if(uIndex > 0 && Data[uIndex - 1] == (byte)'\r'){
						continue;
					}
					Data.Insert(uIndex, (byte)'\r');
					uIndex++;
				}
			}
		}
		catch(Exception::CException& Exception){
			throw Exception::CStreamException(
				L"Error while converting data for console buffer write.", CR_INFO(), Exception);
		}

		DWORD dwCount = 0;
		if(!WriteConsoleA(this->m_hConsole, Data.GetPointer(), Data.GetSizeInBytes(), &dwCount, 0)){
			throw Exception::CStreamException(
				L"Failed to write to console buffer. " + CWindowsError(GetLastError()).GetMessage(), CR_INFO());
		}
	}

	void	CWindowsConsoleStream::Read(CRefPtr<IStream> pOutStream, const uint32 uSizeInBytes){
		throw Exception::CStreamException(
			L"Windows Console stream cannot be readed.", CR_INFO());
	}

	void	CWindowsConsoleStream::Write(CRefPtr<IStream> pInStream, const uint32 uSizeInBytes){
		try{
			Collection::CList<byte> Data(uSizeInBytes);
			pInStream->Read(Data);
			dynamic_cast<IO::IStream*>(this)->Write(Data);
		}
		catch(Exception::CException& Exception){
			throw Exception::CStreamException(
				L"Error while writing stream to console.", CR_INFO(), Exception);
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

	const uint32	CWindowsConsoleStream::GetLength() const{
		return 0xFFFFFFFF;
	}

	void	CWindowsConsoleStream::SetPos(const uint32 uPos, const IO::Direction uDirection, const IO::StreamPos uType){
		return;
	}

	const uint32	CWindowsConsoleStream::GetPos() const{
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