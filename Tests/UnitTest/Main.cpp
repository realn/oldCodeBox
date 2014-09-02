#include <IO_OSConsoleStream.h>
#include <IO_TextWriter.h>
#include <Threads_Thread.h>
#include <CBString_Funcs.h>

#include <SimpleXML.h>
#include <IO_File.h>

#include <Math_Size2D.h>
#include <SimpleXML_Serialize_Math.h>

int main(){
	auto pConsole = CB::IO::Console::Create();
	CB::IO::CTextWriter wr(pConsole.Cast<CB::IO::IStream>(), CB::String::Encoding::ANSI);

	wr.WriteLine(L"Test Console Write!");

	CB::SXML::CDocument xmlDoc;
	CB::Math::CSize2D size( 640, 480 );

	auto& mainNode = xmlDoc.Nodes.Add( L"MainRoot" );

	auto& attrNode = mainNode.Nodes.Add( L"SubItem1" );
	attrNode.Attributes.Add( L"TestAttrib", L"Val" );
	attrNode.Attributes.Add( L"TestAttrib2", CB::String::ToString(1.33f) );
	attrNode.Attributes.Add( L"Testaaa" );
	attrNode.Set( L"Alabama" );
	mainNode.Nodes.Add( L"SubItem2", L"Value" );
	mainNode.Nodes.Add( L"SubItem3" ).Attributes.Add(L"Attribute");

	auto& sizeNode = mainNode.Nodes.Add( L"Resolution" );
	CB::SXML::Write<CB::Math::CSize2D>( sizeNode, size );
	size.SetZero();

	CB::CString xmlSource = xmlDoc.ToString( true, true );
	wr.WriteLine( xmlSource );

	{
		auto pFileStream = CB::IO::File::Open( L"test.xml", CB::IO::File::AccessType::WriteOnly, CB::IO::File::OpenAction::AlwaysCreate );
		CB::IO::CTextWriter file( (CB::IO::IStream*)pFileStream, CB::String::Encoding::ANSI );

		file.WriteText( xmlSource );
	}

	{
		CB::SXML::CDocument doc;

		doc.Parse( xmlSource );
		size = CB::SXML::Read<CB::Math::CSize2D>( doc.Nodes[L"MainRoot"].Nodes[L"Resolution"] );

		wr.WriteLine( doc.ToString( true, true ) );
	}

	CB::Threads::Wait(10000);
	return 0;
}