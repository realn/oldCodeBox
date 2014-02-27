#include "../Include/Signals_Signal.h"

namespace CB{
	namespace Signals{
		ISignal::~ISignal(){
		}

		void	ISignal::Destroy(){
			delete this;
		}

		const bool	ISignal::IsEqual(ISignal* pSignal) const{
			return this->GetHashCode() == pSignal->GetHashCode();
		}

		//===================================================================
		//	CArgs 0 arguments template specialization definition.
		//===================================================================
		CArgs<void, void, void, void, void>::CArgs(){
		}

		const uint32 CArgs<void, void, void, void, void>::GetNumberOfArgs() const{
			return this->ms_uArgNumber;
		}

		const uint32	CArgs<void, void, void, void, void>::ms_uArgNumber = 0;
	}
}