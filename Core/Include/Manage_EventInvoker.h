#pragma once

#include "Ref.h"

namespace CB{
	namespace Manage{
		//==================================================
		//	EventInvoker DECLARATION
		//==================================================
		template<typename _ItemType>
		class IEventInvoker : 
			public virtual IRef
		{
		protected:
			IEventInvoker();
			virtual ~IEventInvoker();

		public:
			virtual void	AddEventHandler(_ItemType* Item) = 0;
			virtual void	RemoveEventHandler(_ItemType* Item) = 0;
		};

		//==================================================
		//	EventInvoker DEFINITION
		//==================================================

		template<typename _ItemType>
		IEventInvoker<_ItemType>::IEventInvoker(){
		}

		template<typename _ItemType>
		IEventInvoker<_ItemType>::~IEventInvoker(){
		}
	}
}