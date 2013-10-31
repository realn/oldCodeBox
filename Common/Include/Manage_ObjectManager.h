#pragma once

#include "Collection_List.h"
#include "Collection_Funcs.h"
#include "SmartPointers_Ptr.h"
#include "Ref.h"

namespace CB{
	namespace Manage{
		//=================================
		//	IObjectManager DECLARATION
		//=================================
		template<typename _Type>
		class IObjectManager :
			public virtual IRef
		{
		public:
			typedef	CPtr<_Type>	CObjectPtr;
			typedef Collection::CList<CObjectPtr>	ObjectList;

		protected:
			typename mutable ObjectList	m_pObjectList;

			IObjectManager(){}
			IObjectManager(const IObjectManager& Manager){}
		public:
			virtual void	AddObject(CObjectPtr pObject);
			virtual void	RemoveObject(CObjectPtr pObject);
		};

		//===================================
		//	IObjectManager IMPLEMENTATION
		//===================================

		template<typename _Type>
		void	IObjectManager<_Type>::AddObject(typename IObjectManager<_Type>::CObjectPtr pObject){
			if(!Collection::Contains(this->m_pObjectList, pObject)){
				this->m_pObjectList.Add(pObject);
			}
		}

		template<typename _Type>
		void	IObjectManager<_Type>::RemoveObject(typename IObjectManager<_Type>::CObjectPtr pObject){
			uint32 uIndex = 0;
			if(Collection::TryFind(this->m_pObjectList, pObject, uIndex)){
				this->m_pObjectList.Remove(uIndex);
			}
		}
	}
}