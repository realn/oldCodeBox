#pragma once

#include "Collection_List.h"
#include "Collection_Funcs.h"
#include "SmartPointers_Ptr.h"
#include "Ref.h"

namespace CB{
	namespace Manage{
		template<typename _ParentType, typename _Type>	class IManagedObject;

		//=================================
		//	IObjectManager DECLARATION
		//=================================
		template<typename _ParentType, typename _Type>
		class IObjectManager :
			public virtual IRef
		{
			friend	IManagedObject<_ParentType, _Type>;
		public:
			typedef	CPtr<_Type>	CObjectPtr;
			typedef Collection::CList<CObjectPtr>	ObjectList;

		protected:
			typename mutable ObjectList	m_pObjectList;

			IObjectManager(){}
			IObjectManager(const IObjectManager& Manager){}

			virtual void	AddObject(CObjectPtr pObject);
			virtual void	RemoveObject(CObjectPtr pObject);
		};

		//===================================
		//	IObjectManager IMPLEMENTATION
		//===================================

		template<typename _ParentType, typename _Type>
		void	IObjectManager<_ParentType, _Type>::AddObject(typename IObjectManager<_ParentType, _Type>::CObjectPtr pObject){
			if(!Collection::Contains(this->m_pObjectList, pObject)){
				this->m_pObjectList.Add(pObject);
			}
		}

		template<typename _ParentType, typename _Type>
		void	IObjectManager<_ParentType, _Type>::RemoveObject(typename IObjectManager<_ParentType, _Type>::CObjectPtr pObject){
			uint32 uIndex = 0;
			if(Collection::TryFind(this->m_pObjectList, pObject, uIndex)){
				this->m_pObjectList.Remove(uIndex);
			}
		}
	}
}