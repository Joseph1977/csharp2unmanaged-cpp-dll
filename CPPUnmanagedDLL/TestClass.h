#ifndef __TestClass_h__
#define __TestClass_h__

#include "CPPUnmanagedDLL.h"		// needed for CPPUNMANAGEDDLL_API

#ifdef __cplusplus
extern "C" {
#endif

extern CPPUNMANAGEDDLL_API CUnmanagedClass* CreateInstance(FuncCallback callback);
extern CPPUNMANAGEDDLL_API eErrorCode DisposeInstance(CUnmanagedClass* pObject);

extern CPPUNMANAGEDDLL_API eErrorCode FuncSetCallbacks(CUnmanagedClass* pObject, CallbackStruct strCallbacksValue);
extern CPPUNMANAGEDDLL_API char* FuncReturnString(CUnmanagedClass* pObject);
extern CPPUNMANAGEDDLL_API eErrorCode FuncInt(CUnmanagedClass * pObject, int nValue);

extern CPPUNMANAGEDDLL_API eErrorCode FuncString(CUnmanagedClass* pObject, char* pchValue);

#ifdef __cplusplus
}
#endif

#endif // __TestClass_h__

