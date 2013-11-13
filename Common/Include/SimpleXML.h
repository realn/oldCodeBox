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
		
		//template class COMMON_API Collection::CLinkList<CPtr<CNode>>;

		class COMMON_API CNode :
			public Collection::ICountable<CNode>
		{
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
			const int32		GetInt32() const;
			const uint32	GetUInt32() const;
			const float32	GetFloat() const;
			const bool		GetBool() const;

			const CString	GetValue(const CString& strDefault) const;
			const int32		GetInt32(const int32 iDefault) const;
			const uint32	GetUInt32(const uint32 uDefault) const;
			const float32	GetFloat(const float32 fDefault) const;
			const bool		GetBool(const bool bDefault) const;

			CNode&	Add(const CString& strName);
			CNode&	Add(const CString& strName, const CString& strValue);
			CNode&	Add(const CString& strName, const int32 iValue);
			CNode&	Add(const CString& strName, const float32 fValue);
			CNode&	Add(const CString& strName, const bool bValue);

			CNode&			Get(const CString& strName);
			const CNode&	Get(const CString& strName) const;

			CNode&			Get(const uint32 uIndex) override;
			const CNode&	Get(const uint32 uIndex) const override;

			const uint32	GetLength() const override;
			const bool		IsEmpty() const override;

			CNodeEnumerator	GetEnumerator() const;

			const bool	Contains(const CString& strName) const;

			void	Set(const CString& strValue);
			void	Set(const int32 iValue);
			void	Set(const float32 fValue);
			void	Set(const bool bValue);
			void	ResetValue();

			void	Remove(const CString& strName);
			void	Remove();

			void	Clear();

			const bool	HasNodes() const;

			const CString	ToString() const;
			const CString	ToString(const bool bWithNewLines) const;
			const CString	ToString(const bool bWithNewLines, const bool bNested) const;

			CNode&			operator[](const CString& strName);
			const CNode&	operator[](const CString& strName) const;

			CNode&			operator[](const uint32 uIndex) override;
			const CNode&	operator[](const uint32 uIndex) const override;

		private:
			CNode(CNode* pParent, const CString& strName);
			CNode(const CNode& Node);

			const uint32	Parse(const CString& strText, const uint32 uStartIndex);
			const uint32	ParseStartTag(const CString& strText, const uint32 uIndex);
			const uint32	ParseEndTag(const CString& strText, const uint32 uStartIndex, const uint32 uIndex);

			const CString	CreateNewLines(const bool bWithNewLines) const;
			const CString	CreateTabs(const bool bNested, const uint32 uNestLevel) const;
			const CString	ToString(const bool bWithNewLines, const bool bNested, const uint32 uNestLevel) const;
		};

		class COMMON_API CRoot : 
			public Collection::ICountable<CNode>
		{
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
			CNode&	Add(const CString& strName, const int32 iValue);
			CNode&	Add(const CString& strName, const float32 fValue);
			CNode&	Add(const CString& strName, const bool bValue);

			CNode&	Get(const CString& strName);
			const CNode&	Get(const CString& strName) const;

			CNode::CNodeEnumerator	GetEnumerator() const;

			const bool Contains(const CB::CString& strName) const;

			void	Remove(const CString& strName);
			void	Remove(const uint32 uIndex);
			void	Clear();

			const bool	HasNodes() const;
			const bool	IsEmpty() const override;

			const uint32	GetLength() const override;

			const CNode&	Get(const uint32 uIndex) const override;
			CNode&			Get(const uint32 uIndex) override;

			const CNode&	operator[](const CString& strName) const;
			CNode&			operator[](const CString& strName);

			const CNode&	operator[](const uint32 uIndex) const override;
			CNode&			operator[](const uint32 uIndex) override;

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