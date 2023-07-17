#include <iostream>

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#include <windows.h>

#include "CPPUnmanagedDLL.h"



#ifdef _MANAGED
#pragma managed(push, off)
#endif

BOOL APIENTRY DllMain(
	HMODULE		/*hModule*/,
	DWORD		ul_reason_for_call,
	LPVOID		/*lpReserved*/)
{
	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
	}
	return TRUE;
}

#ifdef _MANAGED
#pragma managed(pop)
#endif

CUnmanagedClass::CUnmanagedClass(FuncCallback callback)
{
	this->funcCallback = callback;
}

CUnmanagedClass::~CUnmanagedClass()
{
	this->funcCallback = NULL;
}

eErrorCode CUnmanagedClass::FuncSetCallbacks(CallbackStruct strCallbacksValue)
{
	this->callBacksStructure = strCallbacksValue;
	return eSUCCESS;
}

char* CUnmanagedClass::FuncRetString()
{
	static char s_chString[] = "Hi from FuncRetString()";
	std::cout << "FuncRetString() was called" << std::endl;
	this->funcCallback(5, s_chString);
	if (this->callBacksStructure.function1 != NULL)
	{
		this->callBacksStructure.function1("Hi from FuncRetString() using callBacksStructure.function1");
	}
	return s_chString;
}

eErrorCode CUnmanagedClass::FuncInt(int nValue)
{
	std::cout << "FuncInt() was called" << std::endl;
	std::cout << "Input value is " << nValue << std::endl;
	this->funcCallback(nValue, "FuncInt() was called");
	if (this->callBacksStructure.function2 != NULL)
	{
		this->callBacksStructure.function2(nValue);
	}
	return eSUCCESS;
}

eErrorCode CUnmanagedClass::FuncString(char* pchValue)
{
	std::cout << "FuncString() was called" << std::endl;
	std::cout << "Input string is " << pchValue << std::endl;
	this->funcCallback(-1, "FuncString() was called");
	return eSUCCESS;
}
