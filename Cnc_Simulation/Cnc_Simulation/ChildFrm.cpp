
// ChildFrm.cpp : implementation of the ChildFrame class
//

#include "stdafx.h"
#include "Cnc_Simulation.h"

#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ChildFrame

IMPLEMENT_DYNCREATE(ChildFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(ChildFrame, CMDIChildWndEx)
END_MESSAGE_MAP()

// ChildFrame construction/destruction

ChildFrame::ChildFrame()
{
	// TODO: add member initialization code here
}

ChildFrame::~ChildFrame()
{
}


BOOL ChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying the CREATESTRUCT cs
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

// ChildFrame diagnostics

#ifdef _DEBUG
void ChildFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void ChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// ChildFrame message handlers
