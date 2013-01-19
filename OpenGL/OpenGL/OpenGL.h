// OpenGL.h : main header file for the OpenGL application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols
#include "Struct.h"

// COpenGLApp:
// See OpenGL.cpp for the implementation of this class
//

class COpenGLApp : public CWinApp
{
public:
	COpenGLApp();
// Overrides

private:
  unsigned long int number8;
public:
	BOOL m_bDrawData ;
public:
	virtual BOOL InitInstance();
  void MyMRUFileHandler(UINT i);
// Implementation
	afx_msg void OnAppAbout();
	void OnFileOpen();
	DECLARE_MESSAGE_MAP()
};

extern COpenGLApp theApp;