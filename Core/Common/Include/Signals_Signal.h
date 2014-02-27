#pragma once

#include "Macros.h"
#include "Types.h"

namespace CB{
	namespace Signals{
		//===================================================================
		//	IArgs base interface declaration.
		//===================================================================
		class COMMON_API IArgs{
		public:
			virtual ~IArgs(){};

			virtual	const uint32 GetNumberOfArgs() const = 0;
		};

		//===================================================================
		//	ISignal base interface declaration.
		//===================================================================
		class COMMON_API ISignal{
		public:
			virtual ~ISignal();

			virtual	const uint32	GetHashCode() const = 0;
			virtual ISignal*	CreateCopy() const = 0;
			virtual const bool	IsPointerEqual(const void* pObj) const = 0;
			void	Destroy();

			virtual const bool	IsEqual(ISignal* pSignal) const;
		};

		//===================================================================
		//	ISignal base interface invoke template declaration.
		//===================================================================
		template<typename _ReturnType>
		class ISignalBase :
			public ISignal
		{
		public:
			virtual void		SetArgs(IArgs* pArgs) = 0;
			virtual	_ReturnType	InvokeSignal() = 0;
		};

		//===================================================================
		//	CArgs 5 arguments template declaration.
		//===================================================================
		template<typename _Arg1 = void, typename _Arg2 = void, typename _Arg3 = void, typename _Arg4 = void, typename _Arg5 = void>
		class CArgs :
			public IArgs
		{
		public:
			_Arg1	m_Arg1;
			_Arg2	m_Arg2;
			_Arg3	m_Arg3;
			_Arg4	m_Arg4;
			_Arg5	m_Arg5;
			static const uint32	ms_uArgNumber = 5;

		public:
			CArgs(_Arg1 arg1, _Arg2 arg2, _Arg3 arg3, _Arg4 arg4, _Arg5 arg5);

			const uint32	GetNumberOfArgs() const override;
		};

		//===================================================================
		//	CArgs 5 arguments template definition.
		//===================================================================
		template<typename _Arg1, typename _Arg2, typename _Arg3, typename _Arg4, typename _Arg5>
		CArgs<_Arg1, _Arg2, _Arg3, _Arg4, _Arg5>::CArgs(_Arg1 arg1, _Arg2 arg2, _Arg3 arg3, _Arg4 arg4, _Arg5 arg5) :
			m_Arg1(arg1), m_Arg2(arg2), m_Arg3(arg3), m_Arg4(arg4), m_Arg5(arg5)
		{}

		template<typename _Arg1, typename _Arg2, typename _Arg3, typename _Arg4, typename _Arg5>
		const uint32	CArgs<_Arg1, _Arg2, _Arg3, _Arg4, _Arg5>::GetNumberOfArgs() const{
			return this->ms_uArgNumber;
		}

		//===================================================================
		//	CArgs 4 arguments template specialization declaration.
		//===================================================================
		template<typename _Arg1, typename _Arg2, typename _Arg3, typename _Arg4>
		class CArgs<_Arg1, _Arg2, _Arg3, _Arg4, void> :
			public IArgs
		{
		public:
			_Arg1	m_Arg1;
			_Arg2	m_Arg2;
			_Arg3	m_Arg3;
			_Arg4	m_Arg4;
			static const uint32	ms_uArgNumber = 4;

		public:
			CArgs(_Arg1 arg1, _Arg2 arg2, _Arg3 arg3, _Arg4 arg4);

			const uint32	GetNumberOfArgs() const override;			
		};

		//===================================================================
		//	CArgs 4 arguments template specialization definition.
		//==================================================================
		template<typename _Arg1, typename _Arg2, typename _Arg3, typename _Arg4>
		CArgs<_Arg1, _Arg2, _Arg3, _Arg4, void>::CArgs(_Arg1 arg1, _Arg2 arg2, _Arg3 arg3, _Arg4 arg4) :
			m_Arg1(arg1), m_Arg2(arg2), m_Arg3(arg3), m_Arg4(arg4)
		{}

		template<typename _Arg1, typename _Arg2, typename _Arg3, typename _Arg4>
		const uint32 CArgs<_Arg1, _Arg2, _Arg3, _Arg4, void>::GetNumberOfArgs() const{
			return this->ms_uArgNumber;
		}

		//===================================================================
		//	CArgs 3 arguments template specialization declaration.
		//===================================================================
		template<typename _Arg1, typename _Arg2, typename _Arg3>
		class CArgs<_Arg1, _Arg2, _Arg3, void, void> :
			public IArgs
		{
		public:
			_Arg1	m_Arg1;
			_Arg2	m_Arg2;
			_Arg3	m_Arg3;
			static const uint32	ms_uArgNumber = 3;

		public:
			CArgs(_Arg1 arg1, _Arg2 arg2, _Arg3 arg3);

			const uint32	GetNumberOfArgs() const override;
		};

		//===================================================================
		//	CArgs 3 arguments template specialization definition.
		//===================================================================
		template<typename _Arg1, typename _Arg2, typename _Arg3>
		CArgs<_Arg1, _Arg2, _Arg3, void, void>::CArgs(_Arg1 arg1, _Arg2 arg2, _Arg3 arg3) :
			m_Arg1(arg1), m_Arg2(arg2), m_Arg3(arg3)
		{}

		template<typename _Arg1, typename _Arg2, typename _Arg3>
		const uint32 CArgs<_Arg1, _Arg2, _Arg3, void, void>::GetNumberOfArgs() const{
			return this->ms_uArgNumber;
		}

		//===================================================================
		//	CArgs 2 arguments template specialization declaration.
		//===================================================================
		template<typename _Arg1, typename _Arg2>
		class CArgs<_Arg1, _Arg2, void, void, void> :
			public IArgs
		{
		public:
			_Arg1	m_Arg1;
			_Arg2	m_Arg2;
			static const uint32	ms_uArgNumber = 2;

		public:
			CArgs(_Arg1 arg1, _Arg2 arg2);

			const uint32	GetNumberOfArgs() const override;	
		};

		//===================================================================
		//	CArgs 2 arguments template specialization definition.
		//===================================================================
		template<typename _Arg1, typename _Arg2>
		CArgs<_Arg1, _Arg2, void, void, void>::CArgs(_Arg1 arg1, _Arg2 arg2) :
			m_Arg1(arg1), m_Arg2(arg2)
		{}

		template<typename _Arg1, typename _Arg2>
		const uint32 CArgs<_Arg1, _Arg2, void, void, void>::GetNumberOfArgs() const{
			return this->ms_uArgNumber;
		}			


		//===================================================================
		//	CArgs 1 argument template specialization declaration.
		//===================================================================
		template<typename _Arg1>
		class CArgs<_Arg1, void, void, void, void> :
			public IArgs
		{
		public:
			_Arg1	m_Arg1;
			static const uint32	ms_uArgNumber = 1;

		public:
			CArgs(_Arg1 arg1);

			const uint32	GetNumberOfArgs() const override;
		};

		//===================================================================
		//	CArgs 1 argument template specialization definition.
		//===================================================================
		template<typename _Arg1>
		CArgs<_Arg1, void, void, void, void>::CArgs(_Arg1 arg1) :
			m_Arg1(arg1)
		{}

		template<typename _Arg1>
		const uint32	CArgs<_Arg1, void, void, void, void>::GetNumberOfArgs() const{
			return this->ms_uArgNumber;
		}

		//===================================================================
		//	CArgs 0 arguments template specialization declaration.
		//===================================================================
		template<>
		class CArgs<void, void, void, void, void> :
			public IArgs
		{
		public:
			static const uint32	ms_uArgNumber = 0;

		public:
			CArgs();

			const unsigned	GetNumberOfArgs() const override;
		};

		//===================================================================
		//	CArgs 0 arguments template specialization definition.
		//===================================================================
		CArgs<void, void, void, void, void>::CArgs(){
		}

		const uint32 CArgs<void, void, void, void, void>::GetNumberOfArgs() const{
			return this->ms_uArgNumber;
		}
	}
}