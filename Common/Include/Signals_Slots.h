#pragma once

#include "Signals_Signal.h"
#include "Collection.h"
#include "Signals_Func.h"

#pragma warning(disable : 4251)

namespace CB{
	namespace Signals{

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
			const bool	IsValid() const;
			const bool	IsEmpty() const;
		};

		template<typename _ReturnType>
		class ISlotReturn :
			public ISlot
		{
		protected:
			ISignalBase<_ReturnType>*	GetSignal(SignalList::CEnumerator& En){
				return reinterpret_cast<ISignalBase<_ReturnType>*>(En.Get());
			}

			ISlotReturn(){}
		};

		template<typename _ReturnType>
		class ISlotReturnBase : 
			public ISlotReturn<_ReturnType>
		{
		public:
			typedef	void	(*CombineCallback)(_ReturnType* pResult, _ReturnType Value);

		protected:
			CombineCallback	m_pCombine;

			_ReturnType	InvokeSignals(IArgs* pArgs){
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

			ISlotReturnBase() :
				m_pCombine(0)
			{}
		public:
			void	SetCombiner(CombineCallback pCombine){
				this->m_pCombine = pCombine;
			}
		};

		template<>
		class ISlotReturnBase<void> : 
			public ISlotReturn<void>
		{
		protected:
			void	InvokeSignals(IArgs* pArgs){
				auto En = this->m_pSignals.GetEnumerator();
				for(En.ToFirst(); En.IsValid(); En.Next()){
					this->GetSignal(En)->SetArgs(pArgs);
					this->GetSignal(En)->InvokeSignal();
				}
			}

			ISlotReturnBase(){}
		};

		template<typename _ReturnType, typename _Arg1, typename _Arg2, typename _Arg3, typename _Arg4, typename _Arg5>
		class ISlotBase :
			public ISlotReturnBase<_ReturnType>
		{
		public:
			typedef CFunc<_ReturnType, _Arg1, _Arg2, _Arg3, _Arg4, _Arg5> Func_Type;
			typedef CArgs<_Arg1, _Arg2, _Arg3, _Arg4, _Arg5> Arg_Type;

			void	Add(Func_Type& signal){
				this->AddInternal(signal);
			}
			void	Remove(Func_Type& signal){
				this->RemoveInternal(signal);
			}

			void	operator+=(Func_Type& signal){
				this->Add(signal);
			}
			void	operator-=(Func_Type& signal){
				this->Remove(signal);
			}
		};

		template<typename _ReturnType = void, typename _Arg1 = void, typename _Arg2 = void, typename _Arg3 = void, typename _Arg4 = void, typename _Arg5 = void>
		class CSlot :
			public ISlotBase<_ReturnType, _Arg1, _Arg2, _Arg3, _Arg4, _Arg5>
		{
		public:
			_ReturnType	Invoke(_Arg1 arg1, _Arg2 arg2, _Arg3 arg3, _Arg4 arg4, _Arg5 arg5){
				typename Arg_Type args(arg1, arg2, arg3, arg4, arg5);

				return this->InvokeSignals(&args);
			}

			_ReturnType	operator()(_Arg1 arg1, _Arg2 arg2, _Arg3 arg3, _Arg4 arg4, _Arg5 arg5){
				return this->Invoke(arg1, arg2, arg3, arg4, arg5);
			}
		};

		template<typename _ReturnType, typename _Arg1, typename _Arg2, typename _Arg3, typename _Arg4>
		class CSlot<_ReturnType, _Arg1, _Arg2, _Arg3, _Arg4, void> :
			public ISlotBase<_ReturnType, _Arg1, _Arg2, _Arg3, _Arg4, void>
		{
		public:
			_ReturnType	Invoke(_Arg1 arg1, _Arg2 arg2, _Arg3 arg3, _Arg4 arg4){
				typename Arg_Type args(arg1, arg2, arg3, arg4);

				return this->InvokeSignals(&args);
			}

			_ReturnType	operator()(_Arg1 arg1, _Arg2 arg2, _Arg3 arg3, _Arg4 arg4){
				return this->Invoke(arg1, arg2, arg3, arg4);
			}
		};

		template<typename _ReturnType, typename _Arg1, typename _Arg2, typename _Arg3>
		class CSlot<_ReturnType, _Arg1, _Arg2, _Arg3, void, void> :
			public ISlotBase<_ReturnType, _Arg1, _Arg2, _Arg3, void, void>
		{
		public:
			_ReturnType	Invoke(_Arg1 arg1, _Arg2 arg2, _Arg3 arg3){
				typename Arg_Type args(arg1, arg2, arg3);

				return this->InvokeSignals(&args);
			}

			_ReturnType	operator()(_Arg1 arg1, _Arg2 arg2, _Arg3 arg3){
				return this->Invoke(arg1, arg2, arg3);
			}
		};

		template<typename _ReturnType, typename _Arg1, typename _Arg2>
		class CSlot<_ReturnType, _Arg1, _Arg2, void, void, void> :
			public ISlotBase<_ReturnType, _Arg1, _Arg2, void, void, void>
		{
		public:
			_ReturnType	Invoke(_Arg1 arg1, _Arg2 arg2){
				typename Arg_Type args(arg1, arg2);

				return this->InvokeSignals(&args);
			}

			_ReturnType	operator()(_Arg1 arg1, _Arg2 arg2){
				return this->Invoke(arg1, arg2);
			}
		};

		template<typename _ReturnType, typename _Arg1>
		class CSlot<_ReturnType, _Arg1, void, void, void, void> :
			public ISlotBase<_ReturnType, _Arg1, void, void, void, void>
		{
		public:
			_ReturnType	Invoke(_Arg1 arg1){
				typename Arg_Type args(arg1);

				return this->InvokeSignals(&args);
			}

			_ReturnType	operator()(_Arg1 arg1){
				return this->Invoke(arg1);
			}
		};

		template<typename _ReturnType>
		class CSlot<_ReturnType, void, void, void, void, void> :
			public ISlotBase<_ReturnType, void, void, void, void, void>
		{
		public:
			_ReturnType	Invoke(){
				return this->InvokeSignals(&args);
			}

			_ReturnType	operator()(){
				return this->Invoke(arg1);
			}
		};
	}
}