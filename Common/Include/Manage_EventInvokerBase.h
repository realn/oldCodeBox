#pragma once

#include "SmartPointers_Ptr.h"
#include "Collection_List.h"
#include "Collection_Funcs.h"
#include "Manage_EventInvoker.h"

namespace CB{
	namespace Manage{
		//===================================================================
		//	EventInvokerBase DEFINITION
		//===================================================================
		template<typename _ItemType>
		class CEventInvokerBase : 
			public virtual IEventInvoker<_ItemType>
		{
		protected:
			typedef Collection::CList<CPtr<_ItemType>> EventHandlerList;

			EventHandlerList	m_EventHandlerList;

			CEventInvokerBase();
			virtual ~CEventInvokerBase();

		public:
			virtual void	AddEventHandler(CPtr<_ItemType> pEventHandler) override;
			virtual void	RemoveEventHandler(CPtr<_ItemType> pEventHandler) override;
		};

		//====================================================================
		//	EventInvokerBase DECLARATION
		//====================================================================
		
		template<typename _ItemType>
		CEventInvokerBase<_ItemType>::CEventInvokerBase(){
		}

		template<typename _ItemType>
		CEventInvokerBase<_ItemType>::~CEventInvokerBase(){
		}

		template<typename _ItemType>
		void	CEventInvokerBase<_ItemType>::AddEventHandler(CPtr<_ItemType> pEventHandler){
			if(Collection::Contains(this->m_EventHandlerList, pEventHandler)){
				return;
			}
			this->m_EventHandlerList.Add(pEventHandler);
		}

		template<typename _ItemType>
		void	CEventInvokerBase<_ItemType>::RemoveEventHandler(CPtr<_ItemType> pEventHandler){
			uint32 uIndex = 0;
			if(Collection::TryFind(this->m_EventHandlerList, pEventHandler, uIndex)){
				this->m_EventHandlerList.Remove(uIndex);
			}
		}

	}
}