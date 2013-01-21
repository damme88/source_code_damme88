// DialogBar.cpp : implementation file
//

#include "stdafx.h"
#include "Cad_Show.h"
#include "DialogBar.h"
#include "MainFrm.h"
#include "Cad_ShowView.h"

// DialogBar

IMPLEMENT_DYNCREATE(DialogBar, CFormView)

DialogBar::DialogBar()
	: CFormView(DialogBar::IDD)
{

}

DialogBar::~DialogBar()
{
}

void DialogBar::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(DialogBar, CFormView)
END_MESSAGE_MAP()


// DialogBar diagnostics

#ifdef _DEBUG
void DialogBar::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void DialogBar::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// DialogBar message handlers
void DialogBar::OnInitialUpdate() {
  CFormView::OnInitialUpdate();
}

CView *DialogBar::GetDialogBarView() {
  CCad_ShowApp *pApp= (CCad_ShowApp*)AfxGetApp();
  CMainFrame *pMainFrame = (CMainFrame*)pApp->m_pMainWnd;
  CView *pView = (CView*)pMainFrame->m_wndSplitter.GetPane(0, 1);
  return pView;
}