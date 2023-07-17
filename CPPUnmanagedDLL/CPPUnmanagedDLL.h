#ifndef __CPPUnmanagedDLL_h__
#define __CPPUnmanagedDLL_h__

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the CPPUNMANAGEDDLL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// CPPUNMANAGEDDLL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef CPPUNMANAGEDDLL_EXPORTS
	#define CPPUNMANAGEDDLL_API __declspec(dllexport)
#else
	#define CPPUNMANAGEDDLL_API __declspec(dllimport)
#endif

enum eErrorCode {
	/// <summary>
	/// No error.
	/// </summary>
	eSUCCESS =0,
	/// <summary>
	/// Mucst call CreateInstance and pass the instance reference.
	/// </summary>
	eINSTANCENOTPROVIDED,
	/// <summary>
	/// One or more of the parameters are missing or incorrect
	/// </summary>
	eINVALIDPARAMETER,
};

typedef void(__stdcall* FuncCallback)(int, const char*);
typedef void(__stdcall* FuncCallbackType1)(const char*);
typedef void(__stdcall* FuncCallbackType2)(int);

/// <summary>
/// This structure use to allow you send multiple callbacks
/// </summary>
struct CallbackStruct
{
	FuncCallbackType1 function1;
	FuncCallbackType2 function2;
};



class CPPUNMANAGEDDLL_API CUnmanagedClass
{
private:
	FuncCallback funcCallback;
	CallbackStruct callBacksStructure;
public:
	CUnmanagedClass(FuncCallback callback);
	virtual ~CUnmanagedClass();


	eErrorCode FuncSetCallbacks(CallbackStruct strCallbacksValue); //this show how to send a structure that include multiple callbacks in one shot
	char* FuncRetString();
	eErrorCode FuncInt(int nValue);
	eErrorCode FuncString(char* pchValue);
};

#endif	// __CPPUnmanagedDLL_h__
