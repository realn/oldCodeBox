#pragma once

#include "Macros.h"
#include "Types.h"
#include "Exception.h"

namespace CB{
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