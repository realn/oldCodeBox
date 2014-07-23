#pragma once

#include "Signals_Signal.h"
#include "Collection.h"
#include "Signals_Func.h"

#pragma warning(disable : 4251)

namespace CB{
	namespace Signals{
		//===================================================================
		//	ISlot - base asbtract class for template slot classes.
		//===================================================================
		class COMMON_API ISlot{
		protected:
			typedef	Collection::CLinkList<ISignal*> SignalList;

			SignalList	m_pSignals;

			void	AddInternal(ISignal& pSignal);
			void	RemoveInternal(ISignal& pSignal);

			ISlot();
			virtual ~ISlot();

		public:
			void	Clear();
			void	Clear(const void* pObj);
			const bool	IsValid() const;
			const bool	IsEmpty() const;
		};

		//===================================================================
		//	ISlotReturn - template abstract class for ecapsulating 
		//	same functionality across specializations.
		//===================================================================
		template<typename _ReturnType>
		class ISlotReturn :
			public ISlot
		{
		protected:
			ISlotReturn();

		protected:
			ISignalBase<_ReturnType>*	GetSignal(SignalList::CEnumerator& En);
		};

		//===================================================================
		//	ISlotReturn - method definitions.
		//===================================================================
		template<typename _ReturnType>
		ISlotReturn<_ReturnType>::ISlotReturn(){
		}

		template<typename _ReturnType>
		ISignalBase<_ReturnType>*	ISlotReturn<_ReturnType>::GetSignal(SignalList::CEnumerator& En){
			return reinterpret_cast<ISignalBase<_ReturnType>*>(En.Get());
		}

	
		//===================================================================
		//	ISlotReturnBase - final template class for future return type
		//	specialization.
		//===================================================================
		template<typename _ReturnType>
		class ISlotReturnBase : 
			public ISlotReturn<_ReturnType>
		{
		public:
			typedef	void	(*CombineCallback)(_ReturnType* pResult, _ReturnType Value);

		protected:
			CombineCallback	m_pCombine;

			ISlotReturnBase();

		public:
			void	SetCombiner(CombineCallback pCombine);

		protected:
			_ReturnType	InvokeSignals(IArgs* pArgs);
		};

		//===================================================================
		//	ISignalReturnBase - method definitions.
		//===================================================================
		template<typename _ReturnType>
		ISlotReturnBase<_ReturnType>::ISlotReturnBase() :
			m_pCombine(0)
		{}

		template<typename _ReturnType>
		_ReturnType	ISlotReturnBase<_ReturnType>::InvokeSignals(IArgs* pArgs){
			auto En = this->m_pSignals.GetEnumerator();
			En.ToFirst();
			if(En.IsValid()){
				this->GetSignal(En)->SetArgs(pArgs);
				_ReturnType result(this->GetSignal(En)->InvokeSignal());

				for(En.Next(); En.IsValid(); En.Next()){
					this->GetSignal(En)->SetArgs(pArgs);
					if(this->m_pCombine){
						this->m_pCombine(&result, this->GetSignal(En)->InvokeSignal());
					}
					else{
						this->GetSignal(En)->InvokeSignal();
					}
				}
				return result;
			}
			return _ReturnType();
		}

		template<typename _ReturnType>
		void	ISlotReturnBase<_ReturnType>::SetCombiner(CombineCallback pCombine){
			this->m_pCombine = pCombine;
		}


		//===================================================================
		//	ISlotReturnBase template class specialization declaration for void return type.
		//===================================================================
		template<>
		class COMMON_API ISlotReturnBase<void> : 
			public ISlotReturn<void>
		{
		protected:
			ISlotReturnBase();

			void	InvokeSignals(IArgs* pArgs);
		};

		//===================================================================
		//	ISlotBase - base template class for method functor declaration.
		//===================================================================
		template<typename _ReturnType, typename _Arg1, typename _Arg2, typename _Arg3, typename _Arg4, typename _Arg5>
		class ISlotBase :
			public ISlotReturnBase<_ReturnType>
		{
		public:
			typedef CFunc<_ReturnType, _Arg1, _Arg2, _Arg3, _Arg4, _Arg5> Func_Type;
			typedef CArgs<_Arg1, _Arg2, _Arg3, _Arg4, _Arg5> Arg_Type;

			void	Add(Func_Type& signal);
			void	Remove(Func_Type& signal);

			void	operator+=(Func_Type& signal);
			void	operator-=(Func_Type& signal);
		};

		//===================================================================
		//	ISlotBase template class definition.
		//===================================================================
		template<typename _ReturnType, typename _Arg1, typename _Arg2, typename _Arg3, typename _Arg4, typename _Arg5>
		void	ISlotBase<_ReturnType, _Arg1, _Arg2, _Arg3, _Arg4, _Arg5>::Add(Func_Type& signal){
			this->AddInternal(signal);
		}

		template<typename _ReturnType, typename _Arg1, typename _Arg2, typename _Arg3, typename _Arg4, typename _Arg5>
		void	ISlotBase<_ReturnType, _Arg1, _Arg2, _Arg3, _Arg4, _Arg5>::Remove(Func_Type& signal){
			this->RemoveInternal(signal);
		}

		template<typename _ReturnType, typename _Arg1, typename _Arg2, typename _Arg3, typename _Arg4, typename _Arg5>
		void	ISlotBase<_ReturnType, _Arg1, _Arg2, _Arg3, _Arg4, _Arg5>::operator+=(Func_Type& signal){
			this->Add(signal);
		}

		template<typename _ReturnType, typename _Arg1, typename _Arg2, typename _Arg3, typename _Arg4, typename _Arg5>
		void	ISlotBase<_ReturnType, _Arg1, _Arg2, _Arg3, _Arg4, _Arg5>::operator-=(Func_Type& signal){
			this->Remove(signal);
		}

		//===================================================================
		//	CSlot - final 5 argument functor class for template argument specialization.
		//===================================================================
		template<typename _ReturnType = void, typename _Arg1 = void, typename _Arg2 = void, typename _Arg3 = void, typename _Arg4 = void, typename _Arg5 = void>
		class CSlot :
			public ISlotBase<_ReturnType, _Arg1, _Arg2, _Arg3, _Arg4, _Arg5>
		{
		public:
			_ReturnType	Invoke(_Arg1 arg1, _Arg2 arg2, _Arg3 arg3, _Arg4 arg4, _Arg5 arg5);

			_ReturnType	operator()(_Arg1 arg1, _Arg2 arg2, _Arg3 arg3, _Arg4 arg4, _Arg5 arg5);
		};

		//===================================================================
		//	CSlot final 5 argument class definition.
		//===================================================================
		template<typename _ReturnType, typename _Arg1, typename _Arg2, typename _Arg3, typename _Arg4, typename _Arg5>
		_ReturnType	CSlot<_ReturnType, _Arg1, _Arg2, _Arg3, _Arg4, _Arg5>::Invoke(_Arg1 arg1, _Arg2 arg2, _Arg3 arg3, _Arg4 arg4, _Arg5 arg5){
			typename Arg_Type args(arg1, arg2, arg3, arg4, arg5);

			return this->InvokeSignals(&args);
		}

		template<typename _ReturnType, typename _Arg1, typename _Arg2, typename _Arg3, typename _Arg4, typename _Arg5>
		_ReturnType	CSlot<_ReturnType, _Arg1, _Arg2, _Arg3, _Arg4, _Arg5>::operator()(_Arg1 arg1, _Arg2 arg2, _Arg3 arg3, _Arg4 arg4, _Arg5 arg5){
			return this->Invoke(arg1, arg2, arg3, arg4, arg5);
		}


		//===================================================================
		//	CSlot 4 argument template specialization declaration.
		//===================================================================
		template<typename _ReturnType, typename _Arg1, typename _Arg2, typename _Arg3, typename _Arg4>
		class CSlot<_ReturnType, _Arg1, _Arg2, _Arg3, _Arg4, void> :
			public ISlotBase<_ReturnType, _Arg1, _Arg2, _Arg3, _Arg4, void>
		{
		public:
			_ReturnType	Invoke(_Arg1 arg1, _Arg2 arg2, _Arg3 arg3, _Arg4 arg4);
			_ReturnType	operator()(_Arg1 arg1, _Arg2 arg2, _Arg3 arg3, _Arg4 arg4);
		};

		//===================================================================
		//	CSlot 4 argument template specialization definition.
		//===================================================================
		template<typename _ReturnType, typename _Arg1, typename _Arg2, typename _Arg3, typename _Arg4>
		_ReturnType	CSlot<_ReturnType, _Arg1, _Arg2, _Arg3, _Arg4, void>::Invoke(_Arg1 arg1, _Arg2 arg2, _Arg3 arg3, _Arg4 arg4){
			typename Arg_Type args(arg1, arg2, arg3, arg4);

			return this->InvokeSignals(&args);
		}

		template<typename _ReturnType, typename _Arg1, typename _Arg2, typename _Arg3, typename _Arg4>
		_ReturnType	CSlot<_ReturnType, _Arg1, _Arg2, _Arg3, _Arg4, void>::operator()(_Arg1 arg1, _Arg2 arg2, _Arg3 arg3, _Arg4 arg4){
			return this->Invoke(arg1, arg2, arg3, arg4);
		}


		//===================================================================
		//	CSlot 3 argument template specialization declaration.
		//===================================================================
		template<typename _ReturnType, typename _Arg1, typename _Arg2, typename _Arg3>
		class CSlot<_ReturnType, _Arg1, _Arg2, _Arg3, void, void> :
			public ISlotBase<_ReturnType, _Arg1, _Arg2, _Arg3, void, void>
		{
		public:
			_ReturnType	Invoke(_Arg1 arg1, _Arg2 arg2, _Arg3 arg3);

			_ReturnType	operator()(_Arg1 arg1, _Arg2 arg2, _Arg3 arg3);
		};

		//===================================================================
		//	CSlot 3 argument template specialization definition.
		//===================================================================
		template<typename _ReturnType, typename _Arg1, typename _Arg2, typename _Arg3>
		_ReturnType	CSlot<_ReturnType, _Arg1, _Arg2, _Arg3, void, void>::Invoke(_Arg1 arg1, _Arg2 arg2, _Arg3 arg3){
			typename Arg_Type args(arg1, arg2, arg3);

			return this->InvokeSignals(&args);
		}

		template<typename _ReturnType, typename _Arg1, typename _Arg2, typename _Arg3>
		_ReturnType	CSlot<_ReturnType, _Arg1, _Arg2, _Arg3, void, void>::operator()(_Arg1 arg1, _Arg2 arg2, _Arg3 arg3){
			return this->Invoke(arg1, arg2, arg3);
		}

		//===================================================================
		//	CSlot 2 argument template specialization declaration.
		//===================================================================
		template<typename _ReturnType, typename _Arg1, typename _Arg2>
		class CSlot<_ReturnType, _Arg1, _Arg2, void, void, void> :
			public ISlotBase<_ReturnType, _Arg1, _Arg2, void, void, void>
		{
		public:
			_ReturnType	Invoke(_Arg1 arg1, _Arg2 arg2);
			_ReturnType	operator()(_Arg1 arg1, _Arg2 arg2);
		};

		//===================================================================
		//	CSlot 2 argument template specialization definition.
		//===================================================================
		template<typename _ReturnType, typename _Arg1, typename _Arg2>
		_ReturnType	CSlot<_ReturnType, _Arg1, _Arg2, void, void, void>::Invoke(_Arg1 arg1, _Arg2 arg2){
			typename Arg_Type args(arg1, arg2);

			return this->InvokeSignals(&args);
		}

		template<typename _ReturnType, typename _Arg1, typename _Arg2>
		_ReturnType	CSlot<_ReturnType, _Arg1, _Arg2, void, void, void>::operator()(_Arg1 arg1, _Arg2 arg2){
			return this->Invoke(arg1, arg2);
		}

		//===================================================================
		//	CSlot 1 argument template specialization declaration.
		//===================================================================
		template<typename _ReturnType, typename _Arg1>
		class CSlot<_ReturnType, _Arg1, void, void, void, void> :
			public ISlotBase<_ReturnType, _Arg1, void, void, void, void>
		{
		public:
			_ReturnType	Invoke(_Arg1 arg1);
			_ReturnType	operator()(_Arg1 arg1);
		};

		//===================================================================
		//	CSlot 1 argument template specialization definition.
		//===================================================================
		template<typename _ReturnType, typename _Arg1>
		_ReturnType	CSlot<_ReturnType, _Arg1, void, void, void, void>::Invoke(_Arg1 arg1){
			typename Arg_Type args(arg1);

			return this->InvokeSignals(&args);
		}

		template<typename _ReturnType, typename _Arg1>
		_ReturnType	CSlot<_ReturnType, _Arg1, void, void, void, void>::operator()(_Arg1 arg1){
			return this->Invoke(arg1);
		}

		//===================================================================
		//	CSlot 0 argument template specialization declaration.
		//===================================================================
		template<typename _ReturnType>
		class CSlot<_ReturnType, void, void, void, void, void> :
			public ISlotBase<_ReturnType, void, void, void, void, void>
		{
		public:
			_ReturnType	Invoke();
			_ReturnType	operator()();
		};

		//===================================================================
		//	CSlot 0 argument template specialization definition.
		//===================================================================
		template<typename _ReturnType>
		_ReturnType	CSlot<_ReturnType, void, void, void, void, void>::Invoke(){
			typename Arg_Type args;

			return this->InvokeSignals(&args);
		}

		template<typename _ReturnType>
		_ReturnType	CSlot<_ReturnType, void, void, void, void, void>::operator()(){
			return this->Invoke();
		}
	}
}