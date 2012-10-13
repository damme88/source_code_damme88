// WorkspaceBar.cpp : implementation file
//

#include "stdafx.h"
#include "Simple_Draw.h"
#include "WorkspaceBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
// CWorkspaceBar

IMPLEMENT_DYNAMIC(CWorkspaceBar, CDockablePane)

CWorkspaceBar::CWorkspaceBar()
{

}

CWorkspaceBar::~CWorkspaceBar()
{
}


BEGIN_MESSAGE_MAP(CWorkspaceBar, CDockablePane)
  ON_WM_CREATE()
  ON_WM_SIZE()
END_MESSAGE_MAP()


int CWorkspaceBar::OnCreate(LPCREATESTRUCT lpCreateStruct) {
  if (CDockablePane::OnCreate(lpCreateStruct) == -1)
    return -1;

  CRect rect;
  rect.SetRectEmpty();

 // Createa tab Windows
  if (!m_wndTabs.Create(CMFCTabCtrl::STYLE_3D, rect, this, 1)) {
    TRACE0("Fail to create Workspace tab Windows\n");
    return -1;
  }
  // m_wndTabs.SetImageList()
  // Create tree windows.
  // TODO: create your own tab windows here:
  const DWORD dwViewStyle =	WS_CHILD | WS_VISIBLE | TVS_HASLINES | 
								TVS_LINESATROOT | TVS_HASBUTTONS;
	
	if (!m_wndTree1.Create (dwViewStyle, rect, &m_wndTabs, 2) ||
		!m_wndTree2.Create (dwViewStyle, rect, &m_wndTabs, 3))
	{
		TRACE0("Failed to create workspace view\n");
		return -1;      // fail to create
	}

	// Setup trees content: Thiet lap ra mot noi dung dang cay 
  // Create 1 tree base Named Root1
	HTREEITEM hRoot1 = m_wndTree1.InsertItem (_T("Option 1"));
  // Trong trees co 2 item moi la item 1 va item 2
	m_wndTree1.InsertItem (_T("Item 1"), hRoot1);
	m_wndTree1.InsertItem (_T("Item 2"), hRoot1);

	HTREEITEM hRoot2 = m_wndTree2.InsertItem (_T("Option 2"));
	m_wndTree2.InsertItem (_T("Item 1"), hRoot2);
	m_wndTree2.InsertItem (_T("Item 2"), hRoot2);

	// Attach tree windows to tab:
	m_wndTabs.AddTab (&m_wndTree1, _T("First View"), 0 /* Image number */);
	m_wndTabs.AddTab (&m_wndTree2, _T("Second View"), 1 /* Image number */);

	return 0;
}

void CWorkspaceBar::OnSize(UINT nType, int cx, int cy) 
{
	CDockablePane::OnSize(nType, cx, cy);

	// Tab control should cover a whole client area:
	m_wndTabs.SetWindowPos (NULL, -1, -1, cx, cy,
		SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}

// CWorkspaceBar message handlers


