#include <IO_OSConsoleStream.h>
#include <IO_TextWriter.h>
#include <Threads.h>
#include <Math_Vector.h>
#include <Math_Matrix.h>
#include <CBString_Funcs.h>

int main(){
	auto pConsole = CB::IO::Console::Create();
	CB::IO::CTextWriter wr(pConsole.Cast<CB::IO::IStream>(), CB::String::Encoding::ANSI);

	wr.WriteLine(L"Test Console Write!");

	wr.WriteLine(L"Size Size: " + CB::String::ToString(sizeof(CB::Math::CSize))); 
	wr.WriteLine(L"Size3D Size: " + CB::String::ToString(sizeof(CB::Math::CSize3D))); 

	CB::Threads::Wait(2000);
	return 0;
}