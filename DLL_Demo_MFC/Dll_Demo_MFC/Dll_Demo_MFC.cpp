// Dll_Demo_MFC.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "Dll_Demo_MFC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: If this DLL is dynamically linked against the MFC DLLs,
//		any functions exported from this DLL which call into
//		MFC must have the AFX_MANAGE_STATE macro added at the
//		very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

// CDll_Demo_MFCApp

BEGIN_MESSAGE_MAP(CDll_Demo_MFCApp, CWinApp)
END_MESSAGE_MAP()


// CDll_Demo_MFCApp construction

CDll_Demo_MFCApp::CDll_Demo_MFCApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CDll_Demo_MFCApp object

CDll_Demo_MFCApp theApp;


// CDll_Demo_MFCApp initialization

BOOL CDll_Demo_MFCApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}


extern "C"__declspec(dllexport) int Add(int a, int b) {
  AFX_MANAGE_STATE(AfxGetStaticModuleState());
  return a+b;
}

extern "C"__declspec(dllexport) int Mul(int a, int b) {
  AFX_MANAGE_STATE(AfxGetStaticModuleState());
  return a*b;
}

extern "C"__declspec(dllexport) int Sub(int a, int b) {
  AFX_MANAGE_STATE(AfxGetStaticModuleState());
  return a-b;
}

extern "C" __declspec(dllexport) float Div(float a, float b) {
  AFX_MANAGE_STATE(AfxGetStaticModuleState());
  return a/b;
}

