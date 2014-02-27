#pragma once

#include "Macros.h"
#include "Signals_Signal.h"

namespace CB{
	namespace Signals{
		//===================================================================
		//	IFuncBase - declaration of base interface for functors.
		//===================================================================
		template<typename _ReturnType = void, typename _Arg1 = void, typename _Arg2 = void, typename _Arg3 = void, typename _Arg4 = void, typename _Arg5 = void>
		class IFuncBase : 
			public ISignalBase<_ReturnType>
		{
		public:
			typedef	CArgs<_Arg1, _Arg2, _Arg3, _Arg4, _Arg5> Arg_Type;

		protected:
			Arg_Type*		m_pArgs;

			IFuncBase();
		public:
			void	SetArgs(IArgs* pArgs) override;
		};

		//===================================================================
		//	IFuncBase definition.
		//===================================================================
		template<typename _ReturnType, typename _Arg1, typename _Arg2, typename _Arg3, typename _Arg4, typename _Arg5>
		IFuncBase<_ReturnType, _Arg1, _Arg2, _Arg3, _Arg4, _Arg5>::IFuncBase() :
			m_pArgs(0)
		{}

		template<typename _ReturnType, typename _Arg1, typename _Arg2, typename _Arg3, typename _Arg4, typename _Arg5>
		void IFuncBase<_ReturnType, _Arg1, _Arg2, _Arg3, _Arg4, _Arg5>::SetArgs(IArgs* pArgs){
			if(pArgs->GetNumberOfArgs() == Arg_Type::ms_uArgNumber){
				this->m_pArgs = dynamic_cast<Arg_Type*>(pArgs);
			}
		}

		//===================================================================
		//	CFunc - 5 argument template functor class declaration.
		//===================================================================
		template<typename _ReturnType = void, typename _Arg1 = void, typename _Arg2 = void, typename _Arg3 = void, typename _Arg4 = void, typename _Arg5 = void>
		class CFunc : 
			public IFuncBase<_ReturnType, _Arg1, _Arg2, _Arg3, _Arg4, _Arg5>
		{
		public:
			typedef	_ReturnType	(*Func_Type)(_Arg1, _Arg2, _Arg3, _Arg4, _Arg5);

		protected:
			Func_Type		m_pFunc;

			CFunc();
		public:
			CFunc(Func_Type pFunc);

			virtual _ReturnType	InvokeSignal() override;
			_ReturnType	Invoke(_Arg1 arg1, _Arg2 arg2, _Arg3 arg3, _Arg4 arg4, _Arg5 arg5);
			_ReturnType	operator()(_Arg1 arg1, _Arg2 arg2, _Arg3 arg3, _Arg4 arg4, _Arg5 arg5);

			virtual	const uint32	GetHashCode() const override;
			virtual ISignal*	CreateCopy() const override;
			const bool	IsPointerEqual(const void* pObj) const override;
		};

		//===================================================================
		//	CFunc 5 argruments template class definition.
		//===================================================================
		template<typename _ReturnType, typename _Arg1, typename _Arg2, typename _Arg3, typename _Arg4, typename _Arg5>
		CFunc<_ReturnType, _Arg1, _Arg2, _Arg3, _Arg4, _Arg5>::CFunc() :
			m_pFunc(0)
		{}

		template<typename _ReturnType, typename _Arg1, typename _Arg2, typename _Arg3, typename _Arg4, typename _Arg5>
		CFunc<_ReturnType, _Arg1, _Arg2, _Arg3, _Arg4, _Arg5>::CFunc(CFunc::Func_Type pFunc) :
			m_pFunc(pFunc)
		{}

		template<typename _ReturnType, typename _Arg1, typename _Arg2, typename _Arg3, typename _Arg4, typename _Arg5>
		_ReturnType	CFunc<_ReturnType, _Arg1, _Arg2, _Arg3, _Arg4, _Arg5>::InvokeSignal(){
			return this->m_pFunc(
				this->m_pArgs->m_Arg1, 
				this->m_pArgs->m_Arg2,
				this->m_pArgs->m_Arg3,
				this->m_pArgs->m_Arg4,
				this->m_pArgs->m_Arg5);
		}

		template<typename _ReturnType, typename _Arg1, typename _Arg2, typename _Arg3, typename _Arg4, typename _Arg5>
		_ReturnType	CFunc<_ReturnType, _Arg1, _Arg2, _Arg3, _Arg4, _Arg5>::Invoke(_Arg1 arg1, _Arg2 arg2, _Arg3 arg3, _Arg4 arg4, _Arg5 arg5){
			typename Arg_Type tempArgs(arg1, arg2, arg3, arg4, arg5);
			this->m_pArgs = &tempArgs;
			return this->InvokeSignal();
		}

		template<typename _ReturnType, typename _Arg1, typename _Arg2, typename _Arg3, typename _Arg4, typename _Arg5>
		_ReturnType	CFunc<_ReturnType, _Arg1, _Arg2, _Arg3, _Arg4, _Arg5>::operator()(_Arg1 arg1, _Arg2 arg2, _Arg3 arg3, _Arg4 arg4, _Arg5 arg5){
			return this->Invoke(arg1, arg2, arg3, arg4, arg5);
		}

		template<typename _ReturnType, typename _Arg1, typename _Arg2, typename _Arg3, typename _Arg4, typename _Arg5>
		const uint32	CFunc<_ReturnType, _Arg1, _Arg2, _Arg3, _Arg4, _Arg5>::GetHashCode() const{
			return static_cast<uint32>(this->m_pFunc);
		}

		template<typename _ReturnType, typename _Arg1, typename _Arg2, typename _Arg3, typename _Arg4, typename _Arg5>
		ISignal*	CFunc<_ReturnType, _Arg1, _Arg2, _Arg3, _Arg4, _Arg5>::CreateCopy() const{
			return new CFunc<_ReturnType, _Arg1, _Arg2, _Arg3, _Arg4, _Arg5>(this->m_pFunc);
		}

		template<typename _ReturnType, typename _Arg1, typename _Arg2, typename _Arg3, typename _Arg4, typename _Arg5>
		const bool	CFunc<_ReturnType, _Arg1, _Arg2, _Arg3, _Arg4, _Arg5>::IsPointerEqual(const void* pObj) const{
			return this->m_pFunc == pObj;
		}


		//===================================================================
		//	CFunc 4 argument template class specialization declaration.
		//===================================================================
		template<typename _ReturnType, typename _Arg1, typename _Arg2, typename _Arg3, typename _Arg4>
		class CFunc<_ReturnType, _Arg1, _Arg2, _Arg3, _Arg4, void> : 
			public IFuncBase<_ReturnType, _Arg1, _Arg2, _Arg3, _Arg4>
		{
		public:
			typedef	_ReturnType	(*Func_Type)(_Arg1, _Arg2, _Arg3, _Arg4);

		protected:
			Func_Type		m_pFunc;

			CFunc();
		public:
			CFunc(Func_Type pFunc);

			virtual _ReturnType	InvokeSignal() override;
			_ReturnType	Invoke(_Arg1 arg1, _Arg2 arg2, _Arg3 arg3, _Arg4 arg4);
			_ReturnType	operator()(_Arg1 arg1, _Arg2 arg2, _Arg3 arg3, _Arg4 arg4);

			virtual	const uint32	GetHashCode() const override;
			virtual ISignal*	CreateCopy() const override;
			const bool	IsPointerEqual(const void* pObj) const override
		};

		//===================================================================
		//	CFunt 4 arguments template class specialization definition.
		//===================================================================
		template<typename _ReturnType, typename _Arg1, typename _Arg2, typename _Arg3, typename _Arg4>
		CFunc<_ReturnType, _Arg1, _Arg2, _Arg3, _Arg4, void>::CFunc() :
			m_pFunc(0)
		{}

		template<typename _ReturnType, typename _Arg1, typename _Arg2, typename _Arg3, typename _Arg4>
		CFunc<_ReturnType, _Arg1, _Arg2, _Arg3, _Arg4, void>::CFunc(Func_Type pFunc) :
			m_pFunc(pFunc)
		{}

		template<typename _ReturnType, typename _Arg1, typename _Arg2, typename _Arg3, typename _Arg4>
		_ReturnType	CFunc<_ReturnType, _Arg1, _Arg2, _Arg3, _Arg4, void>::InvokeSignal(){
			return this->m_pFunc(
				this->m_pArgs->m_Arg1, 
				this->m_pArgs->m_Arg2,
				this->m_pArgs->m_Arg3,
				this->m_pArgs->m_Arg4);
		}

		template<typename _ReturnType, typename _Arg1, typename _Arg2, typename _Arg3, typename _Arg4>
		_ReturnType	CFunc<_ReturnType, _Arg1, _Arg2, _Arg3, _Arg4, void>::Invoke(_Arg1 arg1, _Arg2 arg2, _Arg3 arg3, _Arg4 arg4){
			typename Arg_Type tempArgs(arg1, arg2, arg3, arg4);
			this->m_pArgs = &tempArgs;
			return this->InvokeSignal();
		}

		template<typename _ReturnType, typename _Arg1, typename _Arg2, typename _Arg3, typename _Arg4>
		_ReturnType	CFunc<_ReturnType, _Arg1, _Arg2, _Arg3, _Arg4, void>::operator()(_Arg1 arg1, _Arg2 arg2, _Arg3 arg3, _Arg4 arg4){
			return this->Invoke(arg1, arg2, arg3, arg4);
		}

		template<typename _ReturnType, typename _Arg1, typename _Arg2, typename _Arg3, typename _Arg4>
		const uint32	CFunc<_ReturnType, _Arg1, _Arg2, _Arg3, _Arg4, void>::GetHashCode() const{
			return static_cast<uint32>(this->m_pFunc);
		}

		template<typename _ReturnType, typename _Arg1, typename _Arg2, typename _Arg3, typename _Arg4>
		ISignal*	CFunc<_ReturnType, _Arg1, _Arg2, _Arg3, _Arg4, void>::CreateCopy() const{
			return new CFunc<_ReturnType, _Arg1, _Arg2, _Arg3, _Arg4>(this->m_pFunc);
		}

		template<typename _ReturnType, typename _Arg1, typename _Arg2, typename _Arg3, typename _Arg4>
		const bool	CFunc<_ReturnType, _Arg1, _Arg2, _Arg3, _Arg4, void>::IsPointerEqual(const void* pObj) const{
			return this->m_pFunc == pObj;
		}



		template<typename _ReturnType, typename _Arg1, typename _Arg2, typename _Arg3>
		class CFunc<_ReturnType, _Arg1, _Arg2, _Arg3, void, void> : 
			public IFuncBase<_ReturnType, _Arg1, _Arg2, _Arg3>
		{
		public:
			typedef	_ReturnType	(*Func_Type)(_Arg1, _Arg2, _Arg3);

		protected:
			Func_Type		m_pFunc;

			CFunc() :
				m_pFunc(0)
			{}
		public:
			CFunc(Func_Type pFunc) :
				m_pFunc(pFunc)
			{}

			virtual _ReturnType	InvokeSignal() override{
				return this->m_pFunc(
					this->m_pArgs->m_Arg1, 
					this->m_pArgs->m_Arg2,
					this->m_pArgs->m_Arg3);
			}

			_ReturnType	Invoke(_Arg1 arg1, _Arg2 arg2, _Arg3 arg3){
				typename Arg_Type tempArgs(arg1, arg2, arg3);
				this->m_pArgs = &tempArgs;
				return this->InvokeSignal();
			}

			_ReturnType	operator()(_Arg1 arg1, _Arg2 arg2, _Arg3 arg3){
				return this->Invoke(arg1, arg2, arg3);
			}

			virtual	const unsigned	GetHashCode() const override{
				return reinterpret_cast<unsigned>(this->m_pFunc);
			}

			virtual ISignal*	CreateCopy() const override{
				return new CFunc<_ReturnType, _Arg1, _Arg2, _Arg3>(this->m_pFunc);
			}
			const bool	IsPointerEqual(const void* pObj) const override{
				return this->m_pFunc == pObj;
			}
		};

		template<typename _ReturnType, typename _Arg1, typename _Arg2>
		class CFunc<_ReturnType, _Arg1, _Arg2, void, void, void> : 
			public IFuncBase<_ReturnType, _Arg1, _Arg2, void>
		{
		public:
			typedef	_ReturnType	(*Func_Type)(_Arg1, _Arg2);

		protected:
			Func_Type		m_pFunc;

			CFunc() :
				m_pFunc(0)
			{}
		public:
			CFunc(Func_Type pFunc) :
				m_pFunc(pFunc)
			{}

			virtual _ReturnType	InvokeSignal() override{
				return this->m_pFunc(
					this->m_pArgs->m_Arg1, 
					this->m_pArgs->m_Arg2);
			}

			_ReturnType	Invoke(_Arg1 arg1, _Arg2 arg2){
				typename Arg_Type tempArgs(arg1, arg2);
				this->m_pArgs = &tempArgs;
				return this->InvokeSignal();
			}

			_ReturnType	operator()(_Arg1 arg1, _Arg2 arg2){
				return this->Invoke(arg1, arg2);
			}

			virtual	const unsigned	GetHashCode() const override{
				return reinterpret_cast<unsigned>(this->m_pFunc);
			}

			virtual ISignal*	CreateCopy() const override{
				return new CFunc<_ReturnType, _Arg1, _Arg2>(this->m_pFunc);
			}
			const bool	IsPointerEqual(const void* pObj) const override{
				return this->m_pFunc == pObj;
			}
		};

		template<typename _ReturnType, typename _Arg1>
		class CFunc<_ReturnType, _Arg1, void, void, void, void> : 
			public IFuncBase<_ReturnType, _Arg1, void, void, void, void>
		{
		public:
			typedef	_ReturnType	(*Func_Type)(_Arg1);

		protected:
			Func_Type		m_pFunc;

			CFunc() :
				m_pFunc(0)
			{}
		public:
			CFunc(Func_Type pFunc) :
				m_pFunc(pFunc)
			{}

			virtual _ReturnType	InvokeSignal() override{
				return this->m_pFunc(this->m_pArgs->m_Arg1);
			}

			_ReturnType	Invoke(_Arg1 arg1){
				typename Arg_Type tempArgs(arg1);
				this->m_pArgs = &tempArgs;
				return this->InvokeSignal();
			}

			_ReturnType	operator()(_Arg1 arg1){
				return this->Invoke(arg1);
			}

			virtual	const unsigned	GetHashCode() const override{
				return reinterpret_cast<unsigned>(this->m_pFunc);
			}

			virtual ISignal*	CreateCopy() const override{
				return new CFunc<_ReturnType, _Arg1>(this->m_pFunc);
			}
			const bool	IsPointerEqual(const void* pObj) const override{
				return this->m_pFunc == pObj;
			}
		};

		template<typename _ReturnType>
		class CFunc<_ReturnType, void, void, void, void, void> : 
			public IFuncBase<_ReturnType, void, void, void, void, void>
		{
		public:
			typedef	_ReturnType	(*Func_Type)();

		protected:
			Func_Type		m_pFunc;

			CFunc() :
				m_pFunc(0)
			{}
		public:
			CFunc(Func_Type pFunc) :
				m_pFunc(pFunc)
			{}

			virtual _ReturnType	InvokeSignal() override{
				return this->m_pFunc();
			}

			_ReturnType	Invoke(){
				return this->InvokeSignal();
			}

			_ReturnType	operator()(){
				return this->Invoke();
			}

			virtual	const unsigned	GetHashCode() const override{
				return reinterpret_cast<unsigned>(this->m_pFunc);
			}

			virtual ISignal*	CreateCopy() const override{
				return new CFunc<_ReturnType>(this->m_pFunc);
			}

			const bool	IsPointerEqual(const void* pObj) const override{
				return this->m_pFunc == pObj;
			}
		};
	}
}