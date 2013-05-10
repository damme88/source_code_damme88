
// Cnc_SimulationView.cpp : implementation of the Cnc_SimulationView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Cnc_Simulation.h"
#endif

#include "Cnc_SimulationDoc.h"
#include "Cnc_SimulationView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cnc_SimulationView

IMPLEMENT_DYNCREATE(Cnc_SimulationView, CView)

BEGIN_MESSAGE_MAP(Cnc_SimulationView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &Cnc_SimulationView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// Cnc_SimulationView construction/destruction

Cnc_SimulationView::Cnc_SimulationView()
{
	// TODO: add construction code here

}

Cnc_SimulationView::~Cnc_SimulationView()
{
}

BOOL Cnc_SimulationView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Cnc_SimulationView drawing

void Cnc_SimulationView::OnDraw(CDC* /*pDC*/)
{
	Cnc_SimulationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// Cnc_SimulationView printing


void Cnc_SimulationView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL Cnc_SimulationView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void Cnc_SimulationView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void Cnc_SimulationView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void Cnc_SimulationView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void Cnc_SimulationView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Cnc_SimulationView diagnostics

#ifdef _DEBUG
void Cnc_SimulationView::AssertValid() const
{
	CView::AssertValid();
}

void Cnc_SimulationView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Cnc_SimulationDoc* Cnc_SimulationView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cnc_SimulationDoc)));
	return (Cnc_SimulationDoc*)m_pDocument;
}
#endif //_DEBUG


// Cnc_SimulationView message handlers
