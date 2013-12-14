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
	}
}