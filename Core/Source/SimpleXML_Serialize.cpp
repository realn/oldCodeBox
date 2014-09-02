#include "stdafx.h"
#include "../Include/SimpleXML_Serialize.h"
#include "../Include/SimpleXML.h"

namespace CB{
	namespace SXML{
		CSerializeBase::CSerializeBase(){
		}

		CSerializeBase::~CSerializeBase(){
		}

		const bool	CSerializeBase::WriteNode( CNodeList& nodeList, const CString& strTagName ){
			if( !nodeList.Contains( strTagName ) )
				nodeList.Add( strTagName );

			return this->WriteNode( nodeList[strTagName] );
		}
	}
}