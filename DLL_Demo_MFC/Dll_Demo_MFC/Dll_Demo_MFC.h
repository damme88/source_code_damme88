// Dll_Demo_MFC.h : main header file for the Dll_Demo_MFC DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CDll_Demo_MFCApp
// See Dll_Demo_MFC.cpp for the implementation of this class
 
class CDll_Demo_MFCApp : public CWinApp
{
public:
	CDll_Demo_MFCApp();
// Overrides
public:
	virtual BOOL InitInstance();
	DECLARE_MESSAGE_MAP()
};
