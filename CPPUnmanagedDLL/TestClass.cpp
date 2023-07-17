#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#include <windows.h>

#include "TestClass.h"


extern "C" CPPUNMANAGEDDLL_API CUnmanagedClass* CreateInstance(FuncCallback callback)
{
	return new CUnmanagedClass(callback);
}

extern "C" CPPUNMANAGEDDLL_API eErrorCode DisposeInstance(CUnmanagedClass* pObject)
{
	if(pObject != NULL)
	{
		delete pObject;
		pObject = NULL;
	}
	return eINSTANCENOTPROVIDED;
}

extern "C" CPPUNMANAGEDDLL_API eErrorCode FuncSetCallbacks(CUnmanagedClass * pObject, CallbackStruct strCallbacksValue)
{
	if (pObject != NULL)
	{
		return pObject->FuncSetCallbacks(strCallbacksValue);
	}

	return eINSTANCENOTPROVIDED;
}
extern "C" CPPUNMANAGEDDLL_API char* FuncReturnString(CUnmanagedClass * pObject)
{
	if (pObject != NULL)
	{
		return pObject->FuncRetString();
	}

	static char s_chString[] = "ERROR: INSTANCE NOT PROVIDED";
	return s_chString;
}

extern "C" CPPUNMANAGEDDLL_API eErrorCode FuncInt(CUnmanagedClass* pObject, int nValue)
{
	if(pObject != NULL)
	{
		pObject->FuncInt(nValue);
	}
	return eINSTANCENOTPROVIDED;
}

extern "C" CPPUNMANAGEDDLL_API eErrorCode FuncString(CUnmanagedClass* pObject, char* pchValue)
{
	if(pObject != NULL)
	{
		pObject->FuncString(pchValue);
	}
	return eINSTANCENOTPROVIDED;
}
