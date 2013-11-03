#pragma once

#include "Exception.h"
#include "Ref.h"
#include "SmartPointers.h"

namespace CB{
	namespace Manage{
		//===================================================================================
		//	CSingleton	DECLARATION
		//===================================================================================
		template <typename _Type>
		class CSingleton{
		protected:
			static _Type*	ms_pInstance;

			CSingleton();
			virtual ~CSingleton();

			const CSingleton<_Type>& operator=(const CSingleton& Singleton);

		public:
			static _Type*	GetInstance();

			void	Destroy();
		};

		//===================================================================================
		//	CSingleton DEFINITION
		//===================================================================================

		template <typename _Type>
		CSingleton<_Type>::CSingleton(){
			if(ms_pInstance != 0){
				throw CB::Exception::CInvalidArgumentException(L"ms_Instance", CB::String::ToHexString((uint32)ms_pInstance),
					L"Singleton already exists while creating a new one.", CR_INFO());
			}
			ms_pInstance = dynamic_cast<_Type*>(this);
		}

		template <typename _Type>
		CSingleton<_Type>::~CSingleton(){
			if(ms_pInstance == 0){
				throw CB::Exception::CNullPointerException(L"ms_pInstance",
					L"Singleton class not exists while deleting one.", CR_INFO());
			}
			ms_pInstance = 0;
		}

		template <typename _Type>
		const CSingleton<_Type>& CSingleton<_Type>::operator=(const CSingleton& Singleton){
			CR_THROWNOTIMPLEMENTED();
		}

		template <typename _Type>
		_Type*	CSingleton<_Type>::GetInstance(){
			if(ms_pInstance){
				return ms_pInstance;
			}
			return new _Type;
		}

		template <typename _Type>
		void	CSingleton<_Type>::Destroy(){
			delete this;
		}

		//===================================================================================
		//	CRefSingleton DECLARATION
		//===================================================================================
		template <typename _Type>
		class CRefSingleton{
		protected:
			static _Type*	ms_pInstance;

			CRefSingleton();
			virtual ~CRefSingleton();

			const CRefSingleton<_Type>& operator=(const CRefSingleton& Singleton);

		public:
			static CRefPtr<_Type>	GetInstance();
		};

		//===================================================================================
		//	CRefSingleton DECLARATION
		//===================================================================================

		template <typename _Type>
		CRefSingleton<_Type>::CRefSingleton(){
			if(ms_pInstance != 0){
				throw CB::Exception::CInvalidArgumentException(L"ms_pInstance", CB::String::ToHexString((uint32)ms_pInstance),
					L"Singleton already exists while creating a new one.", CR_INFO());
			}
			ms_pInstance = static_cast<_Type*>(this);
		}

		template <typename _Type>
		CRefSingleton<_Type>::~CRefSingleton(){
			ms_pInstance = 0;
		}

		template <typename _Type>
		const CRefSingleton<_Type>& CRefSingleton<_Type>::operator=(const CRefSingleton& Singleton){
			CR_THROWNOTIMPLEMENTED();
		}

		template <typename _Type>
		CRefPtr<_Type>	CRefSingleton<_Type>::GetInstance(){
			if(ms_pInstance){
				return ms_pInstance;
			}
			return new _Type;
		}
	}
}