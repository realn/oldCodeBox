#include <IO_OSConsoleStream.h>
#include <IO_TextWriter.h>

int main(){
	auto pConsole = CB::IO::Console::Create();
	CB::IO::CTextWriter wr(pConsole.Cast<CB::IO::IStream>(), CB::String::Encoding::ANSI);

	wr.WriteLine(L"Test Console Write!");

	return 0;
}