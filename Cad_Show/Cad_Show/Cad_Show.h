
// Cad_Show.h : main header file for the Cad_Show application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols
#include "Cad_Point.h"

// CCad_ShowApp:
// See Cad_Show.cpp for the implementation of this class
//

class CCad_ShowApp : public CWinAppEx
{
public:
	CCad_ShowApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();
  virtual BOOL LoadState(LPCTSTR lpszSectionName = NULL, CFrameImpl *pFrameImpl = NULL);
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

private:
  long number_of_point_;
  BOOL allow_draw_data_;
  Triangle *gl_point_;
  Vector *normal_vector_;
public:
  void OnFileOpen();
  long GetNumberOfPoint() { return number_of_point_;}
  BOOL GetStateDrawStl() {return allow_draw_data_;}
  Triangle* GetTrianglePoint() {return gl_point_;}
  void FreePoint();
  Vector* GetNormalVector () {return normal_vector_;} 
};

extern CCad_ShowApp theApp;
