#pragma once

#include "Macros.h"
#include "Signals_Func.h"
#include "Memory.h"

namespace CB{
	namespace Signals{
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
			CMethod(_ObjType* pObject, Obj_Callback_Type pCallback) :
				m_pObject(pObject), m_pObjCallback(pCallback)
			{}

			_ReturnType	InvokeSignal() override{
				return (this->m_pObject->*this->m_pObjCallback)(
					this->m_pArgs->m_Arg1,
					this->m_pArgs->m_Arg2,
					this->m_pArgs->m_Arg3,
					this->m_pArgs->m_Arg4,
					this->m_pArgs->m_Arg5);
			}

			const unsigned	GetHashCode() const override{
				unsigned uCallback = 0;
				Memory::Copy(&this->m_pObjCallback, &uCallback, sizeof(unsigned));

				return reinterpret_cast<unsigned>(this->m_pObject) ^ uCallback;
			}

			ISignal*	CreateCopy() const override{
				return new CMethod<_ObjType, _ReturnType, _Arg1, _Arg2, _Arg3, _Arg4, _Arg5>(this->m_pObject, this->m_pObjCallback);
			}
		};

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
			CMethod(_ObjType* pObject, Obj_Callback_Type pCallback) :
				m_pObject(pObject), m_pObjCallback(pCallback)
			{}

			_ReturnType	InvokeSignal() override{
				return (this->m_pObject->*this->m_pObjCallback)(
					this->m_pArgs->m_Arg1,
					this->m_pArgs->m_Arg2,
					this->m_pArgs->m_Arg3,
					this->m_pArgs->m_Arg4);
			}

			const unsigned	GetHashCode() const override{
				unsigned uCallback = 0;
				Memory::Copy(&this->m_pObjCallback, &uCallback, sizeof(unsigned));

				return reinterpret_cast<unsigned>(this->m_pObject) ^ uCallback;
			}

			ISignal*	CreateCopy() const override{
				return new CMethod<_ObjType, _ReturnType, _Arg1, _Arg2, _Arg3, _Arg4>(this->m_pObject, this->m_pObjCallback);
			}
		};

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
			CMethod(_ObjType* pObject, Obj_Callback_Type pCallback) :
				m_pObject(pObject), m_pObjCallback(pCallback)
			{}

			_ReturnType	InvokeSignal() override{
				return (this->m_pObject->*this->m_pObjCallback)(
					this->m_pArgs->m_Arg1,
					this->m_pArgs->m_Arg2,
					this->m_pArgs->m_Arg3);
			}

			const unsigned	GetHashCode() const override{
				unsigned uCallback = 0;
				Memory::Copy(&this->m_pObjCallback, &uCallback, sizeof(unsigned));

				return reinterpret_cast<unsigned>(this->m_pObject) ^ uCallback;
			}

			ISignal*	CreateCopy() const override{
				return new CMethod<_ObjType, _ReturnType, _Arg1, _Arg2, _Arg3>(this->m_pObject, this->m_pObjCallback);
			}
		};

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
			CMethod(_ObjType* pObject, Obj_Callback_Type pCallback) :
				m_pObject(pObject), m_pObjCallback(pCallback)
			{}

			_ReturnType	InvokeSignal() override{
				return (this->m_pObject->*this->m_pObjCallback)(
					this->m_pArgs->m_Arg1,
					this->m_pArgs->m_Arg2);
			}

			const unsigned	GetHashCode() const override{
				unsigned uCallback = 0;
				Memory::Copy(&this->m_pObjCallback, &uCallback, sizeof(unsigned));

				return reinterpret_cast<unsigned>(this->m_pObject) ^ uCallback;
			}

			ISignal*	CreateCopy() const override{
				return new CMethod<_ObjType, _ReturnType, _Arg1, _Arg2>(this->m_pObject, this->m_pObjCallback);
			}
		};

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
			CMethod(_ObjType* pObject, Obj_Callback_Type pCallback) :
				m_pObject(pObject), m_pObjCallback(pCallback)
			{}

			_ReturnType	InvokeSignal() override{
				return (this->m_pObject->*this->m_pObjCallback)(this->m_pArgs->m_Arg1);
			}

			const unsigned	GetHashCode() const override{
				unsigned uCallback = 0;
				Memory::Copy(&this->m_pObjCallback, &uCallback, sizeof(unsigned));

				return reinterpret_cast<unsigned>(this->m_pObject) ^ uCallback;
			}

			ISignal*	CreateCopy() const override{
				return new CMethod<_ObjType, _ReturnType, _Arg1>(this->m_pObject, this->m_pObjCallback);
			}
		};

		template<typename _ObjType, typename _ReturnType>
		class CMethod<_ObjType, _ReturnType, void, void, void, void, void> :
			public CFunc<_ReturnType>
		{
		public:
			typedef	_ReturnType	(_ObjType::*Obj_Callback_Type)(_Arg1);

		protected:
			_ObjType*			m_pObject;
			Obj_Callback_Type	m_pObjCallback;

		public:
			CMethod(_ObjType* pObject, Obj_Callback_Type pCallback) :
				m_pObject(pObject), m_pObjCallback(pCallback)
			{}

			_ReturnType	InvokeSignal() override{
				return (this->m_pObject->*this->m_pObjCallback)();
			}

			const unsigned	GetHashCode() const override{
				unsigned uCallback = 0;
				Memory::Copy(&this->m_pObjCallback, &uCallback, sizeof(unsigned));

				return reinterpret_cast<unsigned>(this->m_pObject) ^ uCallback;
			}

			ISignal*	CreateCopy() const override{
				return new CMethod<_ObjType, _ReturnType>(this->m_pObject, this->m_pObjCallback);
			}
		};
	}
}