#pragma once

#include "Manage_EventInvoker.h"
#include "SmartPointers_RefPtr.h"
#include "Collection_List.h"
#include "Collection_Funcs.h"

namespace CB{
	namespace Manage{
		//=======================================================================================
		//	CEventHandlerGuard DECLARATION
		//=======================================================================================
		template<typename _ItemType>
		class CEventHandlerGuard{
		private:
			class CGuardItem{
			public:
				CRefPtr<IEventInvoker<_ItemType>>	m_pInvoker;
				CPtr<_ItemType>						m_pItem;

				CGuardItem();
				CGuardItem(const CGuardItem& Item);
				CGuardItem(CRefPtr<IEventInvoker<_ItemType>> pInvoker, CPtr<_ItemType> pItem);

				const bool operator==(const CGuardItem& Item) const;
			};
			Collection::CList<CGuardItem> m_pGuardList;

		public:
			CEventHandlerGuard();
			CEventHandlerGuard(CRefPtr<IEventInvoker<_ItemType>> pInvoker, CPtr<_ItemType> pEventHandler);
			virtual ~CEventHandlerGuard();

			void	SetHandler(CRefPtr<IEventInvoker<_ItemType>> pInvoker, CPtr<_ItemType> pEventHandler);
			void	ReleaseHandler();

			const bool	IsHandlerSet() const;
		};

		//===========================================================================================
		//	CEventHandlerGuard::CGuardItem DEFINITION
		//===========================================================================================

		template<typename _ItemType>
		CEventHandlerGuard<_ItemType>::CGuardItem::CGuardItem() : 
			m_pItem(0)
		{
		}

		template<typename _ItemType>
		CEventHandlerGuard<_ItemType>::CGuardItem::CGuardItem(const CGuardItem& Item) : 
			m_pInvoker(Item.m_pInvoker), 
			m_pItem(Item.m_pItem)
		{
		}
		
		template<typename _ItemType>
		CEventHandlerGuard<_ItemType>::CGuardItem::CGuardItem(CRefPtr<IEventInvoker<_ItemType>> pInvoker, CPtr<_ItemType> pItem) : 
			m_pInvoker(pInvoker), 
			m_pItem(pItem)
		{
		}

		template<typename _ItemType>
		const bool CEventHandlerGuard<_ItemType>::CGuardItem::operator==(const CGuardItem& Item) const{
			return this->m_pInvoker == Item.m_pInvoker && this->m_pItem == Item.m_pItem;
		}

		//===========================================================================================
		//	CEventHandlerGuard DEFINITION
		//===========================================================================================
		
		template<typename _ItemType>
		CEventHandlerGuard<_ItemType>::CEventHandlerGuard(){
		}

		template<typename _ItemType>
		CEventHandlerGuard<_ItemType>::CEventHandlerGuard(CRefPtr<IEventInvoker<_ItemType>> pInvoker, CPtr<_ItemType> pEventHandler){
			this->SetHandler(pInvoker, pEventHandler);
		}

		template<typename _ItemType>
		virtual CEventHandlerGuard<_ItemType>::~CEventHandlerGuard(){
			this->ReleaseHandler();
		}

		template<typename _ItemType>
		void	CEventHandlerGuard<_ItemType>::SetHandler(CRefPtr<IEventInvoker<_ItemType>> pInvoker, CPtr<_ItemType> pEventHandler){
			CGuardItem item(pInvoker, pEventHandler);
			if(!Collection::Contains(this->m_pGuardList, item)){
				pInvoker->AddEventHandler(pEventHandler);
				this->m_pGuardList.Add(item);
			}
		}

		template<typename _ItemType>
		void	CEventHandlerGuard<_ItemType>::ReleaseHandler(){
			if(this->IsHandlerSet()){
				for(uint32 uIndex = 0; uIndex < this->m_pGuardList.GetLength(); uIndex++){
					typename CEventHandlerGuard<_ItemType>::CGuardItem& Item = this->m_pGuardList[uIndex];

					Item.m_pInvoker->RemoveEventHandler(Item.m_pItem);
				}
				this->m_pGuardList.Clear();
			}
		}

		template<typename _ItemType>
		const bool	CEventHandlerGuard<_ItemType>::IsHandlerSet() const{
			return !this->m_pGuardList.IsEmpty();
		}
	}
}