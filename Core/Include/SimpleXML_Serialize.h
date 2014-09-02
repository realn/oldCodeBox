#pragma once

#include "Macros.h"
#include "Types.h"

namespace CB{
	class CString;

	namespace SXML{
		class CNode;
		class CNodeList;

		class CSerializeBase{
		public:
			CSerializeBase();
			virtual ~CSerializeBase();

			virtual	const bool	WriteNode( CNodeList& nodeList, const CString& strTagName );
			virtual const bool	WriteNode( CNode& node ) = 0;

			virtual const bool	ReadNode( const CNode& node ) = 0;
		};

		template<typename _Type>
		class CSerialize :
			public CSerializeBase
		{
		protected:
			_Type		m_Object;

		public:
			CSerialize();
			virtual ~CSerialize();
			
			void	SetObject( const _Type& obj );
			const _Type& GetObject() const;
		};


		template<typename _Type>
		CSerialize<_Type>::CSerialize() {}

		template<typename _Type>
		CSerialize<_Type>::~CSerialize() {}

		template<typename _Type>
		void	CSerialize<_Type>::SetObject( const _Type& obj ){
			this->m_Object = obj;
		}

		template<typename _Type>
		const _Type&	CSerialize<_Type>::GetObject() const{
			return this->m_Object;
		}
	}

	template<typename _Type>
	class CXMLSerialize :
		public SXML::CSerialize<_Type>
	{
	};

	namespace SXML{
		template<typename _Type>
		const _Type	Read( const CNode& node ){
			CXMLSerialize<_Type> ser;
			ser.ReadNode( node );
			return ser.GetObject();
		}

		template<typename _Type>
		void	Write( CNodeList& nodeList, const CString& strTagName, const _Type& obj ){
			CXMLSerialize<_Type> ser;
			ser.SetObject( obj );
			ser.WriteNode( nodeList, strTagName );
		}

		template<typename _Type>
		void	Write( CNode& node, const _Type& obj ){
			CXMLSerialize<_Type> ser;
			ser.SetObject( obj );
			ser.WriteNode( node );
		}
	}
}