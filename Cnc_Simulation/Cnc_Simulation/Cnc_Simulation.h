
// Cnc_Simulation.h : main header file for the Cnc_Simulation application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// Cnc_SimulationApp:
// See Cnc_Simulation.cpp for the implementation of this class
//

class Cnc_SimulationApp : public CWinAppEx
{
public:
	Cnc_SimulationApp();


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

extern Cnc_SimulationApp theApp;
