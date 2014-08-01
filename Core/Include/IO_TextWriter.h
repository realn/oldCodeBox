#pragma once

#include "IO_StreamWriter.h"
#include "CBString_Consts.h"

namespace CB{
	namespace IO{
		class COMMON_API CTextWriter : 
			public CStreamWriter
		{
		protected:
			String::Encoding	m_uEncoding;

		public:
			CTextWriter(const CRefPtr<IStream> pStream);
			CTextWriter(const CRefPtr<IStream> pStream, const String::Encoding uDestEncoding);
			CTextWriter(const IStreamWrapper& Wrapper);
			CTextWriter(const IStreamWrapper& Wrapper, const String::Encoding uDestEncoding);

			void	WriteText(const CString& strValue);	// string without 0
			void	WriteLine(const CString& strValue); // string with new line int8 (windows: return and new line), without 0

			void					SetEncoding(const String::Encoding uEncoding);
			const String::Encoding	GetEncoding() const;

		protected:
			void	WriteTextANSI(const CString& strValue);
			void	WriteTextUTF8(const CString& strValue);
			void	WriteTextUTF16(const CString& strValue);
			void	WriteLineANSI(const CString& strValue);
			void	WriteLineUTF8(const CString& strValue);
			void	WriteLineUTF16(const CString& strValue);

		private:
			const CTextWriter&	operator=(const CTextWriter& Writer);
		};
	}
}