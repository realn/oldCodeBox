#pragma once

#include "Exception.h"
#include "Ref.h"
#include "SmartPointers.h"

namespace CB{
	namespace Manage{
		template <typename _Type>
		class CSingleton{
		protected:
			static _Type*	ms_pInstance;

			CSingleton(){
				if(ms_pInstance != 0){
					throw CB::Exception::CInvalidArgumentException(L"ms_Instance", CB::String::ToHexString((unsigned)ms_pInstance),
						L"Singleton already exists while creating a new one.", __FUNCTIONW__, __FILEW__, __LINE__);
				}
				ms_pInstance = dynamic_cast<_Type*>(this);
			}
			virtual ~CSingleton(){
				if(ms_pInstance == 0){
					throw CB::Exception::CNullPointerException(L"ms_pInstance",
						L"Singleton class not exists while deleting one.", __FUNCTIONW__, __FILEW__, __LINE__);
				}
				ms_pInstance = 0;
			}

			const CSingleton<_Type>& operator=(const CSingleton& Singleton){
				throw CB::Exception::CException(L"Not implemented.", __FUNCTIONW__, __FILEW__, __LINE__);
			}

		public:
			static _Type*	GetInstance(){
				if(ms_pInstance){
					return ms_pInstance;
				}
				return new _Type;
			}

			void	Destroy(){
				delete this;
			}
		};

		template <typename _Type>
		class CRefSingleton{
		protected:
			static _Type*	ms_pInstance;

			CRefSingleton(){
				if(ms_pInstance != 0){
					throw CB::Exception::CInvalidArgumentException(L"ms_Instance", CB::String::ToHexString((unsigned)ms_pInstance),
						L"Singleton already exists while creating a new one.", __FUNCTIONW__, __FILEW__, __LINE__);
				}
				ms_pInstance = static_cast<_Type*>(this);
			}
			virtual ~CRefSingleton(){
				ms_pInstance = 0;
			}

			const CRefSingleton<_Type>& operator=(const CRefSingleton& Singleton){return *this;}

		public:
			static CRefPtr<_Type>	GetInstance(){
				if(ms_pInstance){
					return ms_pInstance;
				}
				return new _Type;
			}
		};
	}
}