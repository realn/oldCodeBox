#pragma once

#include "Macros.h"
#include "Types.h"
#include "Exception.h"
#include "SmartPointers_AutoPtr.h"
#include "Collection_List.h"

namespace CB{
	class CString;
	template<typename _Type> class CPtr;

	namespace SXML{
		enum class NodeErrorReact{
			ThrowException,
			CreateNew,
			Ignore,
		};
		enum class ValueErrorReact{
			ThrowException,
			UseDefault,
		};

		class CAttributeList;
		class CNode;
		class CDocument;
		
		class COMMON_API CAttribute{
		private:
			friend CAttributeList;

			CAttributeList*	m_pParent;
			CString	m_strName;
			CString	m_strValue;
			
		public:
			const CString	GetName() const;
			const CString	GetValue() const;
			
			void	Set(const CString& strValue);

			const CString	ToString() const;

		private:
			CAttribute(CAttributeList* pParent, const CString& strName);
			CAttribute(CAttributeList* pParent, const CString& strName, const CString& strValue );
			CAttribute(const CAttribute& Attribute);

			static CAttribute*	Parse( CAttributeList* pParent, const CString& strText, const uint32 uStartIndex, uint32& uOutIndex );
		};

		class COMMON_API CAttributeList :
			public Collection::ICountable<CAttribute>
		{
		private:
			friend CNode;

			CNode*	m_pParent;
			Collection::CList<CPtr<CAttribute>>	m_List;

		public:
			virtual ~CAttributeList();

			CAttribute&	Add(const CString& strName);
			CAttribute& Add(const CString& strName, const CString& strValue);

			const uint32	GetLength() const override;
			const bool		IsEmpty() const override;

			const CAttribute&	Get(const uint32 uIndex) const override;
			CAttribute&			Get(const uint32 uIndex) override;

			const CAttribute&	Get(const CString& strName) const;
			CAttribute&			Get(const CString& strName);

			const bool		Contains(const CString& strName) const;

			const bool	Remove(const CString& strName);
			
			void	Clear();

			const CAttribute&	operator[](const uint32 uIndex) const override;
			CAttribute&			operator[](const uint32 uIndex) override;

			const CAttribute&	operator[](const CString& strName) const;
			CAttribute&			operator[](const CString& strName);

			const CString	ToString() const;

		private:
			CAttributeList(CNode* pParent);
			CAttributeList(const CAttributeList& List);

			const uint32	Parse( const CString& strText, const uint32 uStartIndex );
		};

		class COMMON_API CNodeList :
			public Collection::ICountable<CNode>
		{
		private:
			friend CNode;
			friend CDocument;

			CNode*	m_pParent;
			Collection::CList<CPtr<CNode>>	m_List;

		public:
			virtual ~CNodeList();

			CNode&	Add(const CString& strName);
			CNode&	Add(const CString& strName, const CString& strValue);
			
			CNode&			Get(const CString& strName);
			const CNode&	Get(const CString& strName) const;

			CNode&			Get(const uint32 uIndex) override;
			const CNode&	Get(const uint32 uIndex) const override;

			const uint32	GetLength() const override;
			const bool		IsEmpty() const override;

			const bool	Contains(const CString& strName) const;

			void	Remove(const CString& strName);

			void	Clear();

			const CString	ToString() const;
			const CString	ToString(const bool bWithNewLines) const;
			const CString	ToString(const bool bWithNewLines, const bool bNested) const;

			CNode&			operator[](const CString& strName);
			const CNode&	operator[](const CString& strName) const;

			CNode&			operator[](const uint32 uIndex) override;
			const CNode&	operator[](const uint32 uIndex) const override;

		private:
			CNodeList(CNode* pParent);
			CNodeList(const CNodeList& List);

			const CString	ToString(const bool bWithNewLines, const bool bNested, const uint32 uNestLevel) const;
			const bool		Parse( const CString& strText, const uint32 uIndex, uint32& uOutIndex );
		};

		class COMMON_API CNode{
		private:
			friend CNodeList;

			CNodeList*	m_pParent;
			CString		m_strName;
			CString		m_strValue;

		public:
			CAttributeList	Attributes;
			CNodeList		Nodes;

			const CString	GetName() const;
			const CString	GetValue() const;

			void	Set(const CString& strValue);

			const bool	HasAttributes() const;
			const bool	HasNodes() const;

			void	SetAttributeValue( const CString& strName, const CString& strValue );
			const CString	GetAttributeValue( const CString& strName, const CString& strDefault ) const;

		private:
			CNode(CNodeList* pParent, const CString& strName);
			CNode(const CNode& Node);

			static CNode*	Parse( CNodeList* pParent, const CString& strText, const uint32 uStartIndex, uint32& uOutIndex );

		public:
			const CString	ToString(const bool bWithNewLines, const bool bNested, const uint32 uNestLevel) const;
		};

		class COMMON_API CDocument{
		public:
			CNodeList	Nodes;

			CDocument();
			~CDocument();

			void	Clear();

			void	Parse(const CString& strText);

			const CString	ToString() const;
			const CString	ToString(const bool bWithNewLines) const;
			const CString	ToString(const bool bWithNewLines, const bool bNested) const;
		};

	}
}