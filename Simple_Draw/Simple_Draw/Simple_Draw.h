
// Simple_Draw.h : main header file for the Simple_Draw application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CSimple_DrawApp:
// See Simple_Draw.cpp for the implementation of this class
//

class CSimple_DrawApp : public CWinAppEx
{
public:
	CSimple_DrawApp();

public:
   //Variable for Object Color
   GLfloat glred_color_;
   GLfloat glgreen_color_;
   GLfloat glblue_color_;
   // variable for storing size of object
   GLfloat glline_grid_size_;
public:
	virtual BOOL InitInstance();

// Implementation
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();
  virtual BOOL PreTranslateMessage(MSG* pMsg) ;
  //virtual BOOL LoadState(LPCTSTR lpszSectionName = NULL, CFrameImpl *pFrameImpl = NULL);
	afx_msg void OnAppAbout();
  afx_msg void OnAppTextEditor();
  afx_msg void OnAppContextDialog();

  // open file and save file
  afx_msg void OnFileOpen();
	DECLARE_MESSAGE_MAP()
};

extern CSimple_DrawApp theApp;
