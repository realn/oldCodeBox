#include "../Include/Signals_Slots.h"

namespace CB{
	namespace Signals{
		typedef	ISignal*	SIG_PTR;

		const bool CompareSignals(const SIG_PTR& Item, const ISignal& signal){
			return signal.IsEqual(Item);
			return true;
		}

		ISlot::ISlot(){
		}

		ISlot::~ISlot(){
			this->Clear();
		}

		void	ISlot::AddInternal(ISignal& signal){
			if(!Collection::Contains(this->m_pSignals, CompareSignals, signal)){
				this->m_pSignals.Add(signal.CreateCopy());
			}
		}

		void	ISlot::RemoveInternal(ISignal& signal){
			auto En = this->m_pSignals.GetEnumerator();
			En.ToFirst();
			if(Collection::TryFind(this->m_pSignals, CompareSignals, signal, En)){
				this->m_pSignals.Remove(En)->Destroy();
			}
		}

		void	ISlot::Clear(){
			auto En = this->m_pSignals.GetEnumerator();
			for(En.ToFirst(); En.IsValid(); En.Next()){
				En.Get()->Destroy();
			}
			this->m_pSignals.Clear();
		}

		void	ISlot::Clear(const void* pObj){
			auto En = this->m_pSignals.GetEnumerator();
			for(En.ToFirst(); En.IsValid(); En.Next()){
				if(En.Get()->IsPointerEqual(pObj)){
					En.Get()->Destroy();
					this->m_pSignals.Remove(En);
				}
			}
		}

		const bool	ISlot::IsValid() const{
			return !this->m_pSignals.IsEmpty();
		}

		const bool	ISlot::IsEmpty() const{
			return this->m_pSignals.IsEmpty();
		}

		//===================================================================
		//	ISlotReturnBase void return type specialization definition.
		//===================================================================
		ISlotReturnBase<void>::ISlotReturnBase(){
		}

		void	ISlotReturnBase<void>::InvokeSignals(IArgs* pArgs){
			auto En = this->m_pSignals.GetEnumerator();
			for(En.ToFirst(); En.IsValid(); En.Next()){
				this->GetSignal(En)->SetArgs(pArgs);
				this->GetSignal(En)->InvokeSignal();
			}
		}
	}
}