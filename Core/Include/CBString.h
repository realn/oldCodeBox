#pragma once

#include "Macros.h"
#include "Types.h"
#include "Collection_Interface.h"

namespace CB{
	class COMMON_API CString :
		public Collection::ICountable<wchar>,
		public Collection::IPacked<wchar>
	{
	private:
		wchar*	m_pStr;
		uint32	m_uLength;

	public:
		CString(); // no data taken, not even for zero
		CString(const CString& strText);
		CString(const Collection::IPacked<wchar>& Data); // data without zero
		CString(const wchar* pStr);	// must end with zero
		CString(const wchar* pStr, const uint32 uLength); // without zero
		CString(const wchar chStr); // automaticaly adds zero
		~CString();

		void	Resize();
		void	Resize(const uint32 uLength);
		void	Clear();

		const uint32	GetLength() const;
		const uint32	GetSizeInBytes() const;

		const wchar*	GetPointer() const;
		wchar*			GetPointer();
		
		const wchar&	Get(const uint32 uIndex) const;
		wchar&			Get(const uint32 uIndex);

		const bool		IsEmpty() const;
		const bool		IsEmptyOrWhiteSpace() const;

		const CString	SubString(const uint32 uIndex) const;
		const CString	SubString(const uint32 uIndex, const uint32 uLength) const;
		const CString	SubStringIndexed(const uint32 uStartPos, const uint32 uEndPos) const;

		const CString	Trim() const;
		const CString	Trim(const CString& strCharList) const;

		const bool		SubCompare(const uint32 uIndex, const CB::CString& strCompare) const;

		const bool		Find(const CString& strFind) const;
		const bool		Find(const CString& strFind, uint32& uPos) const;
		const bool		Find(const CString& strFind, const uint32 uStartPos, uint32& uPos) const;

		const bool		FindLast(const CString& strFind, uint32& uPos) const;
		const bool		FindLast(const CString& strFind, const uint32 uReverseStartPos, uint32& uPos) const;

		const CString	Replace(const CString& strFind, const CString& strReplace) const;
		const CString	Replace(const CString& strFind, const CString& strReplace, uint32& uNumberOfReplaced) const;

		void			Assign(const CString& strText);
		const CString	Add(const CString& strText) const;

		const bool		IsEqual(const CString& strText) const;
		const bool		IsNotEqual(const CString& strText) const;

		const wchar&	operator[](const uint32 uIndex) const;
		wchar&			operator[](const uint32 uIndex);

		const CString&	operator=(const CString& strText);
		const CString	operator+(const CString& strText) const;

		const bool		operator==(const CString& strText) const;
		const bool		operator!=(const CString& strText) const;

		const CString&	operator+=(const CString& strText);
	};
}

extern COMMON_API const CB::CString		operator+(const wchar* pStr, const CB::CString& strText);
extern COMMON_API const bool			operator==(const wchar* pStr, const CB::CString& strText);
extern COMMON_API const bool			operator!=(const wchar* pStr, const CB::CString& strText);