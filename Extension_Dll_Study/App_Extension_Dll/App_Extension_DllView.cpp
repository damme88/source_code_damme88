
// App_Extension_DllView.cpp : implementation of the CApp_Extension_DllView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "App_Extension_Dll.h"
#endif

#include "App_Extension_DllDoc.h"
#include "App_Extension_DllView.h"
#include "PersonalInfoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CApp_Extension_DllView

IMPLEMENT_DYNCREATE(CApp_Extension_DllView, CView)

BEGIN_MESSAGE_MAP(CApp_Extension_DllView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CApp_Extension_DllView::OnFilePrintPreview)
  ON_COMMAND(ID_PERSONAL_INFOR, &CApp_Extension_DllView::HandlePersonalDlg)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CApp_Extension_DllView construction/destruction

CApp_Extension_DllView::CApp_Extension_DllView()
{
	// TODO: add construction code here

}

CApp_Extension_DllView::~CApp_Extension_DllView()
{
}

BOOL CApp_Extension_DllView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CApp_Extension_DllView drawing

void CApp_Extension_DllView::OnDraw(CDC* /*pDC*/)
{
	CApp_Extension_DllDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CApp_Extension_DllView printing


void CApp_Extension_DllView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CApp_Extension_DllView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CApp_Extension_DllView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CApp_Extension_DllView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CApp_Extension_DllView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CApp_Extension_DllView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CApp_Extension_DllView diagnostics

#ifdef _DEBUG
void CApp_Extension_DllView::AssertValid() const
{
	CView::AssertValid();
}

void CApp_Extension_DllView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CApp_Extension_DllDoc* CApp_Extension_DllView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CApp_Extension_DllDoc)));
	return (CApp_Extension_DllDoc*)m_pDocument;
}
#endif //_DEBUG


// CApp_Extension_DllView message handlers


void CApp_Extension_DllView::HandlePersonalDlg() {
  PersonalInfoDlg dlg;
  dlg.DoModal();
}