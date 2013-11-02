#pragma once

#include "IO_StreamReader.h"

namespace CB{
	namespace IO{
		class COMMON_API CTextReader : 
			public CStreamReader
		{
		protected:
			String::Encoding	m_uEncoding;
			uint32				m_uReadBufferLength;	// default is 1024

		public:
			CTextReader(const CRefPtr<IStream> pStream);
			CTextReader(const CRefPtr<IStream> pStream, const String::Encoding uSourceEncoding);
			CTextReader(const IStreamWrapper& Wrapper);
			CTextReader(const IStreamWrapper& Wrapper, const String::Encoding uSourceEncoding);

			const CString		ReadText();	// reads text until char 0 or end of stream
			const CString		ReadLine();	// reads text until char new line (windows: return and new line) or end of stream

			void					SetEncoding(const String::Encoding uEncoding);
			const String::Encoding	GetEncoding() const;

			void			SetReadBufferLength(const uint32 uLength);
			const uint32	GetReadBufferLength() const;

		protected:
			const CString		ReadTextUTF16();	// reads text until char 0 or end of stream
			const CString		ReadTextANSI();
			const CString		ReadTextUTF8();
			const CString		ReadLineUTF16();	// reads text until char new line (windows: return and new line) or end of stream
			const CString		ReadLineANSI();
			const CString		ReadLineUTF8();

		private:
			const CTextReader&	operator=(const CTextReader& Reader);
		};
	}
}