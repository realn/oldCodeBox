#pragma once

#include "Collection.h"
#include "Ref.h"
#include "SmartPointers.h"
#pragma warning(disable : 4250)

namespace CB{
	namespace Manage{
		template<typename _ItemType>
		class IEventInvoker : public virtual IRef{
		protected:
			IEventInvoker(){}
			virtual ~IEventInvoker(){}

		public:
			virtual void	AddEventHandler(_ItemType* Item) = 0;
			virtual void	RemoveEventHandler(_ItemType* Item) = 0;
		};

		template<typename _ItemType>
		class IBaseEventInvoker : public virtual IEventInvoker<_ItemType>{
		protected:
			typedef Collection::CLinkList<_ItemType*> EventHandlerList;

			typename EventHandlerList	m_EventHandlerList;

			IBaseEventInvoker(){}
			virtual ~IBaseEventInvoker(){}

		public:
			virtual void	AddEventHandler(_ItemType* pEventHandler) override{
				if(Collection::Contains(this->m_EventHandlerList, pEventHandler)){
					return;
				}
				this->m_EventHandlerList.Add(pEventHandler);
			}
			virtual void	RemoveEventHandler(_ItemType* pEventHandler) override{
				typename EventHandlerList::CEnumerator Enumerator = this->m_EventHandlerList.GetEnumerator();
				Enumerator.ToFirst();
				if(Collection::TryGetEnumerator(this->m_EventHandlerList, pEventHandler, Enumerator)){
					this->m_EventHandlerList.Remove(Enumerator);
				}
			}
		};

		template<typename _ItemType>
		class CEventHandlerGuard{
		private:
			class CGuardItem{
			public:
				CRefPtr<IEventInvoker<_ItemType>>	m_pInvoker;
				_ItemType*		m_pItem;

				CGuardItem() : m_pItem(0){}
				CGuardItem(const CGuardItem& Item) : m_pInvoker(Item.m_pInvoker), m_pItem(Item.m_pItem){}
				CGuardItem(CRefPtr<IEventInvoker<_ItemType>> pInvoker, _ItemType* pItem) : m_pInvoker(pInvoker), m_pItem(pItem){}

				const bool operator==(const CGuardItem& Item){
					return this->m_pInvoker == Item.m_pInvoker && this->m_pItem == Item.m_pItem;
				}
			};
			Collection::CLinkList<CGuardItem> m_pGuardList;

		public:
			CEventHandlerGuard(){
			}
			CEventHandlerGuard(CRefPtr<IEventInvoker<_ItemType>> pInvoker, _ItemType* pEventHandler){
				this->SetHandler(pInvoker, pEventHandler);
			}
			virtual ~CEventHandlerGuard(){
				this->ReleaseHandler();
			}

			void	SetHandler(CRefPtr<IEventInvoker<_ItemType>> pInvoker, _ItemType* pEventHandler){
				CGuardItem item(pInvoker, pEventHandler);
				if(!Collection::Contains(this->m_pGuardList, item)){
					pInvoker->AddEventHandler(pEventHandler);
					this->m_pGuardList.Add(item);
				}
			}

			void	ReleaseHandler(){
				if(this->IsHandlerSet()){
					typename auto En = this->m_pGuardList.GetEnumerator();
					for(En.ToFirst(); En.IsValid(); En.Next()){
						En.Get().m_pInvoker->RemoveEventHandler(En.Get().m_pItem);
					}
					this->m_pGuardList.Clear();
				}
			}

			const bool	IsHandlerSet() const{
				return !this->m_pGuardList.IsEmpty();
			}
		};
	}
}