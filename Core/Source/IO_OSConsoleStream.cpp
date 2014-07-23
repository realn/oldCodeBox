#include "OSConsoleStream.h"
#include "../Singleton.h"
#include <Windows.h>
#undef GetMessage

class CWindowsConsoleStream : public CB::IOSConsoleStream, public CB::CRefSingleton<CWindowsConsoleStream>{
private:
	HANDLE	m_hConsole;

public:
	CWindowsConsoleStream();
	~CWindowsConsoleStream();

	const bool	CanRead() const;

	void	Read(void* pData, const unsigned uSizeInBytes, const unsigned uNumberOfElements);
	void	Write(const void* pData, const unsigned uSizeInBytes, const unsigned uNumberOfElements);

	const bool	IsEndOfStream() const;		// can be slow
	const bool	IsBeginingOfStream() const;	// can be slow
	const bool	IsEmpty() const;

	const unsigned	GetLength() const;	// it may be slow

	void	SetPos(const int uPos, const StreamPosType uType);

	const unsigned	GetPos() const;

	void	Flush();
};

//	Class implementation

CWindowsConsoleStream*	CB::CRefSingleton<CWindowsConsoleStream>::ms_pInstance = 0;

CWindowsConsoleStream::CWindowsConsoleStream(){
	this->SetClassName(L"CWindowsConsoleStream");

	if(!AllocConsole()){
		throw CB::Exception::CStreamException(
			_T(L"Failed to allocate new console."), __FUNCTIONW__, __FILEW__, __LINE__);
	}

	this->m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if(this->m_hConsole == 0 || this->m_hConsole == INVALID_HANDLE_VALUE){
		throw CB::Exception::CInvalidVarValueException(L"m_hConsole", CB::String::ToHexString((unsigned)this->m_hConsole),
			_T(L"Failed to aquire console output handle."), __FUNCTIONW__, __FILEW__, __LINE__);
	}
}

CWindowsConsoleStream::~CWindowsConsoleStream(){
	this->m_hConsole = 0;

	if(!FreeConsole()){
		throw CB::Exception::CStreamException(
			_T(L"Failed to free console stream."), __FUNCTIONW__, __FILEW__, __LINE__);
	}
}

const bool	CWindowsConsoleStream::CanRead() const{
	return false;
}

void	CWindowsConsoleStream::Read(void* pData, const unsigned uSizeInBytes, const unsigned uNumberOfElements){
	return;
}

void	CWindowsConsoleStream::Write(const void* pData, const unsigned uSizeInBytes, const unsigned uNumberOfElements){
	CB::Collection::CArray<char> Data;

	try{
		CB::Collection::CList<char> List(uSizeInBytes * uNumberOfElements, (char*)pData);
	
		CB::Collection::CList<char>::CEnumerator Enumerator = List.GetEnumerator();
		unsigned uIndex = 0;
		for(Enumerator.ToFirst(); Enumerator.HasNext(); Enumerator.Next()){
			if(Enumerator.GetValue() == '\n'){
				List.Insert(uIndex, '\r');
				uIndex++;
			}
			uIndex++;
		}
		Data = List.ToArray();
	}
	catch(CB::Exception::CException& Exception){
		throw CB::Exception::CStreamException(
			_T(L"Error while converting data for console buffer write."), __FUNCTIONW__, __FILEW__, __LINE__, Exception);
	}

	DWORD dwCount = 0;
	if(!WriteConsoleA(this->m_hConsole, &Data[0], Data.GetLength(), &dwCount, 0)){
		throw CB::Exception::CStreamException(
			_T(L"Failed to write to console buffer."), __FUNCTIONW__, __FILEW__, __LINE__);
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

void	CWindowsConsoleStream::SetPos(const int uPos, const CB::IO::IStream::StreamPosType uType){
	return;
}

const unsigned	CWindowsConsoleStream::GetPos() const{
	return 0;
}

void	CWindowsConsoleStream::Flush(){
	return;
}

// function implementation

CB::CRefPtr<CB::IOSConsoleStream>	CB::Console::Create(){
	return	CWindowsConsoleStream::GetInstance().Cast<IOSConsoleStream>();
}