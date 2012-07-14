
// Tet_Dll.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CTet_DllApp:
// See Tet_Dll.cpp for the implementation of this class
//

class CTet_DllApp : public CWinAppEx
{
public:
	CTet_DllApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CTet_DllApp theApp;