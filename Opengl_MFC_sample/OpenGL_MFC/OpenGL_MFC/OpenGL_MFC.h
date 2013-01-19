
// OpenGL_MFC.h : main header file for the OpenGL_MFC application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// COpenGL_MFCApp:
// See OpenGL_MFC.cpp for the implementation of this class
//

class COpenGL_MFCApp : public CWinAppEx
{
public:
	COpenGL_MFCApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern COpenGL_MFCApp theApp;
