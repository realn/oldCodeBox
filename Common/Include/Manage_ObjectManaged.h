#pragma once

#include "SmartPointers_RefPtr.h"
#include "Manage_ObjectManager.h"

namespace CB{
	namespace Manage{

		//===================================
		//	IManagedObject	DECLARATION
		//===================================

		template<typename _ParentType, typename _Type>
		class IManagedObject{
		private:
			IManagedObject(const IManagedObject& Object){}

		protected:
			CRefPtr<_ParentType>	m_pParent;

			IManagedObject(CRefPtr<_ParentType> pParent);
			virtual ~IManagedObject();
		public:
			CRefPtr<_ParentType>	GetParent() const;
		};

		//=====================================
		//	IManagedObject	IMPLEMENTATION
		//=====================================

		template<typename _ParentType, typename _Type>
		IManagedObject<_ParentType, _Type>::IManagedObject(CRefPtr<_ParentType> pParent) :
			m_pParent(pParent)
		{
			if(this->m_pParent.IsValid()){
				this->m_pParent.Cast<IObjectManager<_Type>>()->AddObject(static_cast<_Type* const>(this));
			}
		}

		template<typename _ParentType, typename _Type>
		IManagedObject<_ParentType, _Type>::~IManagedObject(){
			if(this->m_pParent.IsValid()){
				this->m_pParent.Cast<IObjectManager<_Type>>()->RemoveObject(static_cast<_Type* const>(this));
			}
		}

		template<typename _ParentType, typename _Type>
		CRefPtr<_ParentType>	IManagedObject<_ParentType, _Type>::GetParent() const{
			return this->m_pParent;
		}
	}
}
