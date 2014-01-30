#pragma once

#include "Macros.h"

namespace CB{
	namespace Signals{
		class COMMON_API IArgs{
		public:
			virtual ~IArgs(){};

			virtual	const unsigned GetNumberOfArgs() const = 0;
		};

		class COMMON_API ISignal{
		public:
			virtual ~ISignal();

			virtual	const unsigned	GetHashCode() const = 0;
			virtual ISignal*	CreateCopy() const = 0;
			virtual const bool	IsPointerEqual(const void* pObj) const = 0;
			void	Destroy();

			virtual const bool	IsEqual(ISignal* pSignal) const;
		};

		template<typename _ReturnType>
		class ISignalBase :
			public ISignal
		{
		public:
			virtual void		SetArgs(IArgs* pArgs) = 0;
			virtual	_ReturnType	InvokeSignal() = 0;
		};

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
			static const unsigned	ms_uArgNumber = 5;

			CArgs(_Arg1 arg1, _Arg2 arg2, _Arg3 arg3, _Arg4 arg4, _Arg5 arg5) :
				m_Arg1(arg1), m_Arg2(arg2), m_Arg3(arg3), m_Arg4(arg4), m_Arg5(arg5)
			{}

			const unsigned	GetNumberOfArgs() const override{
				return 5;
			}
		};

		template<typename _Arg1, typename _Arg2, typename _Arg3, typename _Arg4>
		class CArgs<_Arg1, _Arg2, _Arg3, _Arg4, void> :
			public IArgs
		{
		public:
			_Arg1	m_Arg1;
			_Arg2	m_Arg2;
			_Arg3	m_Arg3;
			_Arg4	m_Arg4;
			static const unsigned	ms_uArgNumber = 4;

			CArgs(_Arg1 arg1, _Arg2 arg2, _Arg3 arg3, _Arg4 arg4) :
				m_Arg1(arg1), m_Arg2(arg2), m_Arg3(arg3), m_Arg4(arg4)
			{}

			const unsigned	GetNumberOfArgs() const override{
				return 4;
			}			
		};

		template<typename _Arg1, typename _Arg2, typename _Arg3>
		class CArgs<_Arg1, _Arg2, _Arg3, void, void> :
			public IArgs
		{
		public:
			_Arg1	m_Arg1;
			_Arg2	m_Arg2;
			_Arg3	m_Arg3;
			static const unsigned	ms_uArgNumber = 3;

			CArgs(_Arg1 arg1, _Arg2 arg2, _Arg3 arg3) :
				m_Arg1(arg1), m_Arg2(arg2), m_Arg3(arg3)
			{}

			const unsigned	GetNumberOfArgs() const override{
				return 3;
			}			
		};

		template<typename _Arg1, typename _Arg2>
		class CArgs<_Arg1, _Arg2, void, void, void> :
			public IArgs
		{
		public:
			_Arg1	m_Arg1;
			_Arg2	m_Arg2;
			static const unsigned	ms_uArgNumber = 2;

			CArgs(_Arg1 arg1, _Arg2 arg2) :
				m_Arg1(arg1), m_Arg2(arg2)
			{}

			const unsigned	GetNumberOfArgs() const override{
				return 2;
			}			
		};

		template<typename _Arg1>
		class CArgs<_Arg1, void, void, void, void> :
			public IArgs
		{
		public:
			_Arg1	m_Arg1;
			static const unsigned	ms_uArgNumber = 1;

			CArgs(_Arg1 arg1) :
				m_Arg1(arg1)
			{}

			const unsigned	GetNumberOfArgs() const override{
				return 1;
			}			
		};

		template<>
		class CArgs<void, void, void, void, void> :
			public IArgs
		{
		public:
			static const unsigned	ms_uArgNumber = 0;

			CArgs()
			{}

			const unsigned	GetNumberOfArgs() const override{
				return 0;
			}			
		};

	}
}