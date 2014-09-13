#pragma once

#include "Macros.h"
#include "Signals_Func.h"
#include "Memory.h"

namespace CB{
	namespace Signals{
		//===================================================================
		//	CMethod - 5 argument template class for method functors.
		//===================================================================
		template<typename _ObjType, typename _ReturnType = void, typename _Arg1 = void, typename _Arg2 = void, typename _Arg3 = void, typename _Arg4 = void, typename _Arg5 = void>
		class CMethod :
			public CFunc<_ReturnType, _Arg1, _Arg2, _Arg3, _Arg4, _Arg5>
		{
		public:
			typedef	_ReturnType	(_ObjType::*Obj_Callback_Type)(_Arg1, _Arg2, _Arg3, _Arg4, _Arg5);

		protected:
			_ObjType*			m_pObject;
			Obj_Callback_Type	m_pObjCallback;

		public:
			CMethod(_ObjType* pObject, Obj_Callback_Type pCallback);

			_ReturnType	InvokeSignal() override;

			const uint32	GetHashCode() const override;
			ISignal*	CreateCopy() const override;
			const bool	IsPointerEqual(const void* pObj) const override;
		};

		//===================================================================
		//	CMethod 5 argument template class definition.
		//===================================================================
		template<typename _ObjType, typename _ReturnType, typename _Arg1, typename _Arg2, typename _Arg3, typename _Arg4, typename _Arg5>
		CMethod<_ObjType, _ReturnType, _Arg1, _Arg2, _Arg3, _Arg4, _Arg5>::CMethod(_ObjType* pObject, Obj_Callback_Type pCallback) :
			m_pObject(pObject), 
			m_pObjCallback(pCallback)
		{}

		template<typename _ObjType, typename _ReturnType, typename _Arg1, typename _Arg2, typename _Arg3, typename _Arg4, typename _Arg5>
		_ReturnType	CMethod<_ObjType, _ReturnType, _Arg1, _Arg2, _Arg3, _Arg4, _Arg5>::InvokeSignal(){
			return (this->m_pObject->*this->m_pObjCallback)(
				this->m_pArgs->m_Arg1,
				this->m_pArgs->m_Arg2,
				this->m_pArgs->m_Arg3,
				this->m_pArgs->m_Arg4,
				this->m_pArgs->m_Arg5);
		}

		template<typename _ObjType, typename _ReturnType, typename _Arg1, typename _Arg2, typename _Arg3, typename _Arg4, typename _Arg5>
		const uint32	CMethod<_ObjType, _ReturnType, _Arg1, _Arg2, _Arg3, _Arg4, _Arg5>::GetHashCode() const{
			uint32 uCallback = 0;
			Memory::Copy(&this->m_pObjCallback, &uCallback, sizeof(uint32));

			return reinterpret_cast<uint32>(this->m_pObject) ^ uCallback;
		}

		template<typename _ObjType, typename _ReturnType, typename _Arg1, typename _Arg2, typename _Arg3, typename _Arg4, typename _Arg5>
		ISignal*	CMethod<_ObjType, _ReturnType, _Arg1, _Arg2, _Arg3, _Arg4, _Arg5>::CreateCopy() const{
			return new CMethod<_ObjType, _ReturnType, _Arg1, _Arg2, _Arg3, _Arg4, _Arg5>(this->m_pObject, this->m_pObjCallback);
		}

		template<typename _ObjType, typename _ReturnType, typename _Arg1, typename _Arg2, typename _Arg3, typename _Arg4, typename _Arg5>
		const bool	CMethod<_ObjType, _ReturnType, _Arg1, _Arg2, _Arg3, _Arg4, _Arg5>::IsPointerEqual(const void* pObj) const{
			return this->m_pObject == pObj;
		}

		//===================================================================
		//	CMethod - 4 argument template class specialization for method functors.
		//===================================================================
		template<typename _ObjType, typename _ReturnType, typename _Arg1, typename _Arg2, typename _Arg3, typename _Arg4>
		class CMethod<_ObjType, _ReturnType, _Arg1, _Arg2, _Arg3, _Arg4, void> :
			public CFunc<_ReturnType, _Arg1, _Arg2, _Arg3, _Arg4>
		{
		public:
			typedef	_ReturnType	(_ObjType::*Obj_Callback_Type)(_Arg1, _Arg2, _Arg3, _Arg4);

		protected:
			_ObjType*			m_pObject;
			Obj_Callback_Type	m_pObjCallback;

		public:
			CMethod(_ObjType* pObject, Obj_Callback_Type pCallback);
			CMethod( const CMethod& method );

			_ReturnType	InvokeSignal() override;

			const uint32	GetHashCode() const override;
			ISignal*	CreateCopy() const override;
			const bool	IsPointerEqual(const void* pObj) const override;
		};

		//===================================================================
		//	CMethod 4 argument template class specialization definition.
		//===================================================================
		template<typename _ObjType, typename _ReturnType, typename _Arg1, typename _Arg2, typename _Arg3, typename _Arg4>
		CMethod<_ObjType, _ReturnType, _Arg1, _Arg2, _Arg3, _Arg4, void>::CMethod(_ObjType* pObject, Obj_Callback_Type pCallback) :
			m_pObject(pObject), m_pObjCallback(pCallback)
		{}

		template<typename _ObjType, typename _ReturnType, typename _Arg1, typename _Arg2, typename _Arg3, typename _Arg4>
		CMethod<_ObjType, _ReturnType, _Arg1, _Arg2, _Arg3, _Arg4, void>::CMethod(const CMethod& method) :
			m_pObject(method.m_pObject), m_pObjCallback(method.m_pObjCallback)
		{}		

		template<typename _ObjType, typename _ReturnType, typename _Arg1, typename _Arg2, typename _Arg3, typename _Arg4>
		_ReturnType	CMethod<_ObjType, _ReturnType, _Arg1, _Arg2, _Arg3, _Arg4, void>::InvokeSignal(){
			return (this->m_pObject->*this->m_pObjCallback)(
				this->m_pArgs->m_Arg1,
				this->m_pArgs->m_Arg2,
				this->m_pArgs->m_Arg3,
				this->m_pArgs->m_Arg4);
		}

		template<typename _ObjType, typename _ReturnType, typename _Arg1, typename _Arg2, typename _Arg3, typename _Arg4>
		const uint32	CMethod<_ObjType, _ReturnType, _Arg1, _Arg2, _Arg3, _Arg4, void>::GetHashCode() const{
			uint32 uCallback = 0;
			Memory::Copy(&this->m_pObjCallback, &uCallback, sizeof(uint32));

			return reinterpret_cast<uint32>(this->m_pObject) ^ uCallback;
		}

		template<typename _ObjType, typename _ReturnType, typename _Arg1, typename _Arg2, typename _Arg3, typename _Arg4>
		ISignal*	CMethod<_ObjType, _ReturnType, _Arg1, _Arg2, _Arg3, _Arg4, void>::CreateCopy() const{
			return new CMethod<_ObjType, _ReturnType, _Arg1, _Arg2, _Arg3, _Arg4>(this->m_pObject, this->m_pObjCallback);
		}

		template<typename _ObjType, typename _ReturnType, typename _Arg1, typename _Arg2, typename _Arg3, typename _Arg4>
		const bool	CMethod<_ObjType, _ReturnType, _Arg1, _Arg2, _Arg3, _Arg4, void>::IsPointerEqual(const void* pObj) const{
			return this->m_pObject == pObj;
		}

		//===================================================================
		//	CMethod - 3 argument template class specialization for method functors.
		//===================================================================
		template<typename _ObjType, typename _ReturnType, typename _Arg1, typename _Arg2, typename _Arg3>
		class CMethod<_ObjType, _ReturnType, _Arg1, _Arg2, _Arg3, void, void> :
			public CFunc<_ReturnType, _Arg1, _Arg2, _Arg3>
		{
		public:
			typedef	_ReturnType	(_ObjType::*Obj_Callback_Type)(_Arg1, _Arg2, _Arg3);

		protected:
			_ObjType*			m_pObject;
			Obj_Callback_Type	m_pObjCallback;

		public:
			CMethod(_ObjType* pObject, Obj_Callback_Type pCallback);

			_ReturnType	InvokeSignal() override;

			const uint32	GetHashCode() const override;
			ISignal*	CreateCopy() const override;
			const bool	IsPointerEqual(const void* pObj) const override;
		};

		//===================================================================
		//	CMethod 3 argument template class specialization definition.
		//===================================================================
		template<typename _ObjType, typename _ReturnType, typename _Arg1, typename _Arg2, typename _Arg3>
		CMethod<_ObjType, _ReturnType, _Arg1, _Arg2, _Arg3, void, void>::CMethod(_ObjType* pObject, Obj_Callback_Type pCallback) :
			m_pObject(pObject), m_pObjCallback(pCallback)
		{}

		template<typename _ObjType, typename _ReturnType, typename _Arg1, typename _Arg2, typename _Arg3>
		_ReturnType	CMethod<_ObjType, _ReturnType, _Arg1, _Arg2, _Arg3, void, void>::InvokeSignal(){
			return (this->m_pObject->*this->m_pObjCallback)(
				this->m_pArgs->m_Arg1,
				this->m_pArgs->m_Arg2,
				this->m_pArgs->m_Arg3);
		}

		template<typename _ObjType, typename _ReturnType, typename _Arg1, typename _Arg2, typename _Arg3>
		const uint32	CMethod<_ObjType, _ReturnType, _Arg1, _Arg2, _Arg3, void, void>::GetHashCode() const{
			uint32 uCallback = 0;
			Memory::Copy(&this->m_pObjCallback, &uCallback, sizeof(uint32));

			return reinterpret_cast<uint32>(this->m_pObject) ^ uCallback;
		}

		template<typename _ObjType, typename _ReturnType, typename _Arg1, typename _Arg2, typename _Arg3>
		ISignal*	CMethod<_ObjType, _ReturnType, _Arg1, _Arg2, _Arg3, void, void>::CreateCopy() const{
			return new CMethod<_ObjType, _ReturnType, _Arg1, _Arg2, _Arg3>(this->m_pObject, this->m_pObjCallback);
		}

		template<typename _ObjType, typename _ReturnType, typename _Arg1, typename _Arg2, typename _Arg3>
		const bool	CMethod<_ObjType, _ReturnType, _Arg1, _Arg2, _Arg3, void, void>::IsPointerEqual(const void* pObj) const{
			return this->m_pObject == pObj;
		}


		//===================================================================
		//	CMethod - 2 argument template class specialization for method functors.
		//===================================================================
		template<typename _ObjType, typename _ReturnType, typename _Arg1, typename _Arg2>
		class CMethod<_ObjType, _ReturnType, _Arg1, _Arg2, void, void, void> :
			public CFunc<_ReturnType, _Arg1, _Arg2>
		{
		public:
			typedef	_ReturnType	(_ObjType::*Obj_Callback_Type)(_Arg1, _Arg2);

		protected:
			_ObjType*			m_pObject;
			Obj_Callback_Type	m_pObjCallback;

		public:
			CMethod(_ObjType* pObject, Obj_Callback_Type pCallback);

			_ReturnType	InvokeSignal() override;

			const uint32	GetHashCode() const override;
			ISignal*	CreateCopy() const override;
			const bool	IsPointerEqual(const void* pObj) const override;
		};

		//===================================================================
		//	CMethod 2 argument template class specialization definition.
		//===================================================================
		template<typename _ObjType, typename _ReturnType, typename _Arg1, typename _Arg2>
		CMethod<_ObjType, _ReturnType, _Arg1, _Arg2, void, void, void>::CMethod(_ObjType* pObject, Obj_Callback_Type pCallback) :
			m_pObject(pObject), m_pObjCallback(pCallback)
		{}

		template<typename _ObjType, typename _ReturnType, typename _Arg1, typename _Arg2>
		_ReturnType	CMethod<_ObjType, _ReturnType, _Arg1, _Arg2, void, void, void>::InvokeSignal(){
			return (this->m_pObject->*this->m_pObjCallback)(
				this->m_pArgs->m_Arg1,
				this->m_pArgs->m_Arg2);
		}

		template<typename _ObjType, typename _ReturnType, typename _Arg1, typename _Arg2>
		const uint32	CMethod<_ObjType, _ReturnType, _Arg1, _Arg2, void, void, void>::GetHashCode() const{
			uint32 uCallback = 0;
			Memory::Copy(&this->m_pObjCallback, &uCallback, sizeof(uint32));

			return reinterpret_cast<uint32>(this->m_pObject) ^ uCallback;
		}

		template<typename _ObjType, typename _ReturnType, typename _Arg1, typename _Arg2>
		ISignal*	CMethod<_ObjType, _ReturnType, _Arg1, _Arg2, void, void, void>::CreateCopy() const{
			return new CMethod<_ObjType, _ReturnType, _Arg1, _Arg2>(this->m_pObject, this->m_pObjCallback);
		}

		template<typename _ObjType, typename _ReturnType, typename _Arg1, typename _Arg2>
		const bool	CMethod<_ObjType, _ReturnType, _Arg1, _Arg2, void, void, void>::IsPointerEqual(const void* pObj) const{
			return this->m_pObject == pObj;
		}


		//===================================================================
		//	CMethod - 1 argument template class specialization for method functors.
		//===================================================================
		template<typename _ObjType, typename _ReturnType, typename _Arg1>
		class CMethod<_ObjType, _ReturnType, _Arg1, void, void, void, void> :
			public CFunc<_ReturnType, _Arg1>
		{
		public:
			typedef	_ReturnType	(_ObjType::*Obj_Callback_Type)(_Arg1);

		protected:
			_ObjType*			m_pObject;
			Obj_Callback_Type	m_pObjCallback;

		public:
			CMethod(_ObjType* pObject, Obj_Callback_Type pCallback);

			_ReturnType	InvokeSignal() override;

			const uint32	GetHashCode() const override;
			ISignal*	CreateCopy() const override;
			const bool	IsPointerEqual(const void* pObj) const override;
		};

		//===================================================================
		//	CMethod 1 argument template class specialization definition.
		//===================================================================
		template<typename _ObjType, typename _ReturnType, typename _Arg1>
		CMethod<_ObjType, _ReturnType, _Arg1, void, void, void, void>::CMethod(_ObjType* pObject, Obj_Callback_Type pCallback) :
			m_pObject(pObject), m_pObjCallback(pCallback)
		{}

		template<typename _ObjType, typename _ReturnType, typename _Arg1>
		_ReturnType	CMethod<_ObjType, _ReturnType, _Arg1, void, void, void, void>::InvokeSignal(){
			return (this->m_pObject->*this->m_pObjCallback)(this->m_pArgs->m_Arg1);
		}

		template<typename _ObjType, typename _ReturnType, typename _Arg1>
		const uint32	CMethod<_ObjType, _ReturnType, _Arg1, void, void, void, void>::GetHashCode() const{
			uint32 uCallback = 0;
			Memory::Copy(&this->m_pObjCallback, &uCallback, sizeof(uint32));

			return reinterpret_cast<uint32>(this->m_pObject) ^ uCallback;
		}

		template<typename _ObjType, typename _ReturnType, typename _Arg1>
		ISignal*	CMethod<_ObjType, _ReturnType, _Arg1, void, void, void, void>::CreateCopy() const{
			return new CMethod<_ObjType, _ReturnType, _Arg1>(this->m_pObject, this->m_pObjCallback);
		}

		template<typename _ObjType, typename _ReturnType, typename _Arg1>
		const bool	CMethod<_ObjType, _ReturnType, _Arg1, void, void, void, void>::IsPointerEqual(const void* pObj) const{
			return this->m_pObject == pObj;
		}


		//===================================================================
		//	CMethod - 0 argument template class specialization for method functors.
		//===================================================================
		template<typename _ObjType, typename _ReturnType>
		class CMethod<_ObjType, _ReturnType, void, void, void, void, void> :
			public CFunc<_ReturnType>
		{
		public:
			typedef	_ReturnType	(_ObjType::*Obj_Callback_Type)();

		protected:
			_ObjType*			m_pObject;
			Obj_Callback_Type	m_pObjCallback;

		public:
			CMethod(_ObjType* pObject, Obj_Callback_Type pCallback);

			_ReturnType	InvokeSignal() override;

			const uint32	GetHashCode() const override;
			ISignal*	CreateCopy() const override;
			const bool	IsPointerEqual(const void* pObj) const override;
		};

		//===================================================================
		//	CMethod 1 argument template class specialization definition.
		//===================================================================
		template<typename _ObjType, typename _ReturnType>
		CMethod<_ObjType, _ReturnType, void, void, void, void, void>::CMethod(_ObjType* pObject, Obj_Callback_Type pCallback) :
			m_pObject(pObject), m_pObjCallback(pCallback)
		{}

		template<typename _ObjType, typename _ReturnType>
		_ReturnType	CMethod<_ObjType, _ReturnType, void, void, void, void, void>::InvokeSignal(){
			return (this->m_pObject->*this->m_pObjCallback)();
		}

		template<typename _ObjType, typename _ReturnType>
		const uint32	CMethod<_ObjType, _ReturnType, void, void, void, void, void>::GetHashCode() const{
			uint32 uCallback = 0;
			Memory::Copy(&this->m_pObjCallback, &uCallback, sizeof(uint32));

			return reinterpret_cast<uint32>(this->m_pObject) ^ uCallback;
		}

		template<typename _ObjType, typename _ReturnType>
		ISignal*	CMethod<_ObjType, _ReturnType, void, void, void, void, void>::CreateCopy() const{
			return new CMethod<_ObjType, _ReturnType>(this->m_pObject, this->m_pObjCallback);
		}

		template<typename _ObjType, typename _ReturnType>
		const bool	CMethod<_ObjType, _ReturnType, void, void, void, void, void>::IsPointerEqual(const void* pObj) const{
			return this->m_pObject == pObj;
		}
	}
}