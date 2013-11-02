#pragma once

#include "CBStringEx.h"
#include "Exception.h"
#include "SmartPointers_AutoPtr.h"
#include "Collection_LinkList.h"

namespace CB{
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

		class CRoot;
		class CNode;
		
		template class COMMON_API Collection::CLinkList<CPtr<CNode>>;

		class COMMON_API CNode{
		public:
			typedef Collection::CLinkList<CPtr<CNode>>	CNodeList;
			typedef CNodeList::CEnumerator		CNodeEnumerator;

		private:
			friend CRoot;
			friend CNodeList;

			CNode*		m_pParent;
			CNodeList	m_NodeList;
			CString		m_strName;
			CString		m_strValue;
			bool		m_bSet;
			NodeErrorReact	m_uOnMissingNodeRead;
			NodeErrorReact	m_uOnMissingNodeWrite;
			ValueErrorReact	m_uOnValueProcess;

		public:
			void	SetOnMissingNode(const NodeErrorReact uReadReaction, const NodeErrorReact uWriteReaction);
			void	SetOnValueProcess(const ValueErrorReact uReaction);

			const NodeErrorReact	GetOnMissingNodeReadReaction() const;
			const NodeErrorReact	GetOnMissingNodeWriteReaction() const;
			const ValueErrorReact	GetOnValueProcessReaction() const;

			const CString	GetName() const;
			const CString	GetValue() const;
			const int		GetInt32() const;
			const unsigned	GetUInt32() const;
			const float		GetFloat() const;
			const bool		GetBool() const;

			const CString	GetValue(const CString& strDefault) const;
			const int		GetInt32(const int iDefault) const;
			const unsigned	GetUInt32(const unsigned uDefault) const;
			const float		GetFloat(const float fDefault) const;
			const bool		GetBool(const bool bDefault) const;

			CNode&	Add(const CString& strName);
			CNode&	Add(const CString& strName, const CString& strValue);
			CNode&	Add(const CString& strName, const int iValue);
			CNode&	Add(const CString& strName, const float fValue);
			CNode&	Add(const CString& strName, const bool bValue);

			CNode&	Get(const CString& strName);
			const CNode&	Get(const CString& strName) const;

			CNodeEnumerator	GetEnumerator() const;

			const bool	Contains(const CString& strName) const;

			void	Set(const CString& strValue);
			void	Set(const int iValue);
			void	Set(const float fValue);
			void	Set(const bool bValue);
			void	ResetValue();

			void	Remove(const CString& strName);
			void	Remove();

			void	Clear();

			const bool	HasNodes() const;

			const CString	ToString() const;
			const CString	ToString(const bool bWithNewLines) const;
			const CString	ToString(const bool bWithNewLines, const bool bNested) const;

			CNode&	operator[](const CString& strName);
			const CNode&	operator[](const CString& strName) const;

		private:
			CNode(CNode* pParent, const CString& strName);
			CNode(const CNode& Node);

			const unsigned	Parse(const CString& strText, const unsigned uStartIndex);
			const unsigned	ParseStartTag(const CString& strText, const unsigned uIndex);
			const unsigned	ParseEndTag(const CString& strText, const unsigned uStartIndex, const unsigned uIndex);

			const CString	CreateNewLines(const bool bWithNewLines) const;
			const CString	CreateTabs(const bool bNested, const unsigned uNestLevel) const;
			const CString	ToString(const bool bWithNewLines, const bool bNested, const unsigned uNestLevel) const;
		};

		class COMMON_API CRoot{
		private:
			CNode	m_Root;

		public:
			CRoot();

			void	SetOnMissingNode(const NodeErrorReact uReadReaction, const NodeErrorReact uWriteReaction);
			void	SetOnValueProcess(const ValueErrorReact uReaction);

			const NodeErrorReact	GetOnMissingNodeReadReaction() const;
			const NodeErrorReact	GetOnMissingNodeWriteReaction() const;
			const ValueErrorReact	GetOnValueProcessReaction() const;

			CNode&	Add(const CString& strName);
			CNode&	Add(const CString& strName, const CString& strValue);
			CNode&	Add(const CString& strName, const int iValue);
			CNode&	Add(const CString& strName, const float fValue);
			CNode&	Add(const CString& strName, const bool bValue);

			CNode&	Get(const CString& strName);
			const CNode&	Get(const CString& strName) const;

			CNode::CNodeEnumerator	GetEnumerator() const;

			const bool Contains(const CB::CString& strName) const;

			void	Remove(const CString& strName);
			void	Remove(const unsigned uIndex);
			void	Clear();

			const bool	HasNodes() const;
			const bool	IsEmpty() const;

			const CNode&	operator[](const CString& strName) const;
			CNode&			operator[](const CString& strName);

			void			Parse(const CString& strText);

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
			CSXMLException(const CString& strMessage, const CString& strFunction, const CString& strFile, const unsigned uLine);
			CSXMLException(const CString& strMessage, const CString& strFunction, const CString& strFile, const unsigned uLine, const CException& Exception);

			virtual CException*	CreateCopy() const override;
		};

		class COMMON_API	CSXMLNodeException :
			public CSXMLException
		{
		protected:
			CString	m_strNodeName;

		public:
			CSXMLNodeException(const CSXMLNodeException& Exception);
			CSXMLNodeException(const CString& strName, const CString& strFunction, const CString& strFile, const unsigned uLine);
			CSXMLNodeException(const CString& strName, const CString& strFunction, const CString& strFile, const unsigned uLine, const CException& Exception);

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
			CSXMLNodeMissingException(const CString& strName, const CString& strParent, const CString& strFunction, const CString& strFile, const unsigned uLine);
			CSXMLNodeMissingException(const CString& strName, const CString& strParent, const CString& strFunction, const CString& strFile, const unsigned uLine, const CException& InnerException);

			virtual const CString	GetMessage() const override;

			virtual CException*	CreateCopy() const override;
		};

		class COMMON_API	CSXMLValueProcessingException :
			public CSXMLNodeException
		{
		public:
			CSXMLValueProcessingException(const CSXMLValueProcessingException& Exception);
			CSXMLValueProcessingException(const CString& strName, const CString& strFunction, const CString& strFile, const unsigned uLine);
			CSXMLValueProcessingException(const CString& strName, const CString& strFunction, const CString& strFile, const unsigned uLine, const CException& Exception);

			virtual CException*	CreateCopy() const override;
		};

		class COMMON_API	CSXMLValueParsingException :
			public CSXMLValueProcessingException
		{
		protected:
			CString	m_strValue;

		public:
			CSXMLValueParsingException(const CSXMLValueParsingException& Exception);
			CSXMLValueParsingException(const CString& strName, const CString& strValue, const CString& strFunction, const CString& strFile, const unsigned uLine);
			CSXMLValueParsingException(const CString& strName, const CString& strValue, const CString& strFunction, const CString& strFile, const unsigned uLine, const CException& Exception);

			virtual const CString	GetMessage() const override;

			virtual CException* CreateCopy() const override;
		};
	}
}