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
		
		//template class COMMON_API Collection::CLinkList<CPtr<CNode>>;

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
			CAttribute(const CAttribute& Attribute);
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
		};

		class COMMON_API CNode{
		private:
			//friend CRoot;
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

		private:
			CNode(CNodeList* pParent, const CString& strName);
			CNode(const CNode& Node);

			const uint32	Parse(const CString& strText, const uint32 uStartIndex);
			const uint32	ParseStartTag(const CString& strText, const uint32 uIndex);
			const uint32	ParseEndTag(const CString& strText, const uint32 uStartIndex, const uint32 uIndex);

		public:
			const CString	ToString(const bool bWithNewLines, const bool bNested, const uint32 uNestLevel) const;
		};

		class COMMON_API CDocument{
		public:
			CNodeList	Nodes;

			CDocument();

			void	Parse(const CString& strText);

			const CString	ToString() const;
			const CString	ToString(const bool bWithNewLines) const;
			const CString	ToString(const bool bWithNewLines, const bool bNested) const;
		};

	}

	namespace Exception{
		class COMMON_API	CSXMLException : 
			public CException
		{
		public:
			CSXMLException(const CSXMLException& Exception);
			CSXMLException(const CString& strMessage, const CString& strFunction, const CString& strFile, const uint32 uLine);
			CSXMLException(const CString& strMessage, const CString& strFunction, const CString& strFile, const uint32 uLine, const CException& Exception);

			virtual CException*	CreateCopy() const override;
		};

		class COMMON_API	CSXMLNodeException :
			public CSXMLException
		{
		protected:
			CString	m_strNodeName;

		public:
			CSXMLNodeException(const CSXMLNodeException& Exception);
			CSXMLNodeException(const CString& strName, const CString& strFunction, const CString& strFile, const uint32 uLine);
			CSXMLNodeException(const CString& strName, const CString& strFunction, const CString& strFile, const uint32 uLine, const CException& Exception);

			virtual const CString	GetMessage() const override;

			virtual CException*	CreateCopy() const override;
		};

		class COMMON_API	CSXMLNodeMissingException :
			public CSXMLNodeException
		{
		protected:
			CString	m_strChildName;

		public:
			CSXMLNodeMissingException(const CSXMLNodeMissingException& Exception);
			CSXMLNodeMissingException(const CString& strName, const CString& strParent, const CString& strFunction, const CString& strFile, const uint32 uLine);
			CSXMLNodeMissingException(const CString& strName, const CString& strParent, const CString& strFunction, const CString& strFile, const uint32 uLine, const CException& InnerException);

			virtual const CString	GetMessage() const override;

			virtual CException*	CreateCopy() const override;
		};

		class COMMON_API	CSXMLValueProcessingException :
			public CSXMLNodeException
		{
		public:
			CSXMLValueProcessingException(const CSXMLValueProcessingException& Exception);
			CSXMLValueProcessingException(const CString& strName, const CString& strFunction, const CString& strFile, const uint32 uLine);
			CSXMLValueProcessingException(const CString& strName, const CString& strFunction, const CString& strFile, const uint32 uLine, const CException& Exception);

			virtual CException*	CreateCopy() const override;
		};

		class COMMON_API	CSXMLValueParsingException :
			public CSXMLValueProcessingException
		{
		protected:
			CString	m_strValue;

		public:
			CSXMLValueParsingException(const CSXMLValueParsingException& Exception);
			CSXMLValueParsingException(const CString& strName, const CString& strValue, const CString& strFunction, const CString& strFile, const uint32 uLine);
			CSXMLValueParsingException(const CString& strName, const CString& strValue, const CString& strFunction, const CString& strFile, const uint32 uLine, const CException& Exception);

			virtual const CString	GetMessage() const override;

			virtual CException* CreateCopy() const override;
		};
	}
}