
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Simple_Draw.h"

#include "MainFrm.h"
#include "CustomComboButton.h"
#include "CustomCombo.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_CUSTOMIZE, &CMainFrame::OnViewCustomize)
  ON_REGISTERED_MESSAGE(AFX_WM_RESETTOOLBAR, &CMainFrame::OnToolbarReset)
	ON_REGISTERED_MESSAGE(AFX_WM_CREATETOOLBAR, &CMainFrame::OnToolbarCreateNew)
  ON_COMMAND(ID_SELECT,&CMainFrame::OnComBo)
  ON_CBN_SELENDOK(ID_SELECT,&CMainFrame::OnHandleItem)

  ON_COMMAND(ID_TEXT_STYLE, &CMainFrame::OnComBoTextStyle)
  ON_COMMAND(ID_TEXT_SIZE, &CMainFrame::OnComboTextSize)

END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;
	// set the visual manager used to draw all user interface elements
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));

	if (!m_wndMenuBar.Create(this))
	{
		TRACE0("Failed to create menubar\n");
		return -1;      // fail to create
	}

	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | 
                            CBRS_TOOLTIPS | CBRS_FLYBY);

	// prevent the menu bar from taking the focus on activation
	CMFCPopupMenu::SetForceMenuFocus(FALSE);
  
  m_wndMenuBar.EnableDocking(CBRS_ALIGN_TOP);
  EnableDocking(CBRS_ALIGN_ANY);
  DockPane(&m_wndMenuBar);

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | 
                                   CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | 
                                   CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME_256))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	CString strToolBarName;
	bNameValid = strToolBarName.LoadString(IDS_TOOLBAR_STANDARD);
	ASSERT(bNameValid);
	m_wndToolBar.SetWindowText(strToolBarName);


	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);
	m_wndToolBar.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);

	// Allow user-defined toolbars operations:
	InitUserToolbars(NULL, uiFirstUserToolBarId, uiLastUserToolBarId);

    if (! m_wndToolBar_Direct.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE 
                                     | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS 
                                     | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		! m_wndToolBar_Direct.LoadToolBar(IDR_TOOLBAR_DIRECT))
	{
		TRACE0("Failed to create Toolbar_Direct\n");
		return -1;      // fail to create
	}
 
  m_wndToolBar.EnableDocking(CBRS_ALIGN_TOP);
  m_wndToolBar_Direct.EnableDocking(CBRS_ALIGN_TOP);
  
  EnableDocking(CBRS_ALIGN_ANY);

  DockPane(&m_wndToolBar_Direct);
  DockPaneLeftOf(&m_wndToolBar, &m_wndToolBar_Direct);



  if (! m_wndToolBar_Office.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE 
                                     | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS 
                                     | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
                        ! m_wndToolBar_Office.LoadToolBar(IDR_TOOLBAR_OFFICE))
	{
		TRACE0("Failed to create Toolbar_Office\n");
		return -1;      // fail to create
	}

  if (! m_wndToolBar_Draw.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE 
                                     | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS 
                                     | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
                        ! m_wndToolBar_Draw.LoadToolBar(IDR_TOOLBAR_DRAW))
	{
		TRACE0("Failed to create Toolbar_Draw\n");
		return -1;      // fail to create
	}

  m_wndToolBar_Office.EnableDocking(CBRS_ALIGN_TOP);
  m_wndToolBar_Draw.EnableDocking(CBRS_ALIGN_TOP);
  EnableDocking(CBRS_ALIGN_ANY);
  DockPane(&m_wndToolBar_Office);
  DockPane(&m_wndToolBar_Draw);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: Delete these five lines if you don't want the toolbar and menubar to be dockable

	// enable Visual Studio 2005 style docking window behavior
	CDockingManager::SetDockingMode(DT_SMART);
	// enable Visual Studio 2005 style docking window auto-hide behavior
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// Enable toolbar and docking window menu replacement
	EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);

	// enable quick (Alt+drag) toolbar customization
	CMFCToolBar::EnableQuickCustomization();

	//if (CMFCToolBar::GetUserImages() == NULL)
	//{
	//	// load user-defined toolbar images
	//	if (m_UserImages.Load(_T(".\\UserImages.bmp")))
	//	{
	//		m_UserImages.SetImageSize(CSize(16, 16), FALSE);
	//		CMFCToolBar::SetUserImages(&m_UserImages);
	//	}
	//}

	// enable menu personalization (most-recently used commands)
	// TODO: define your own basic commands, ensuring that each pulldown 
  //  menu has at least one basic command.
	CList<UINT, UINT> lstBasicCommands;

	lstBasicCommands.AddTail(ID_FILE_NEW);
	lstBasicCommands.AddTail(ID_FILE_OPEN);
	lstBasicCommands.AddTail(ID_FILE_SAVE);
	lstBasicCommands.AddTail(ID_FILE_PRINT);
	lstBasicCommands.AddTail(ID_APP_EXIT);
	lstBasicCommands.AddTail(ID_EDIT_CUT);
	lstBasicCommands.AddTail(ID_EDIT_PASTE);
	lstBasicCommands.AddTail(ID_EDIT_UNDO);
	lstBasicCommands.AddTail(ID_APP_ABOUT);
	lstBasicCommands.AddTail(ID_VIEW_STATUS_BAR);
	lstBasicCommands.AddTail(ID_VIEW_TOOLBAR);

	CMFCToolBar::SetBasicCommands(lstBasicCommands);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers

void CMainFrame::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, 
                                              TRUE /* scan menus */);
	pDlgCust->EnableUserDefinedToolbars();
	pDlgCust->Create();
}

LRESULT CMainFrame::OnToolbarCreateNew(WPARAM wp,LPARAM lp)
{
	LRESULT lres = CFrameWndEx::OnToolbarCreateNew(wp,lp);
	if (lres == 0)
	{
		return 0;
	}

	CMFCToolBar* pUserToolbar = (CMFCToolBar*)lres;
	ASSERT_VALID(pUserToolbar);

	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
	return lres;
}

BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, 
                           CWnd* pParentWnd, CCreateContext* pContext) 
{
	// base class does the real work

	if (!CFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle,
                              pParentWnd, pContext))
	{
		return FALSE;
	}


	// enable customization button for all user toolbars
	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	for (int i = 0; i < iMaxUserToolbars; i ++)
	{
		CMFCToolBar* pUserToolbar = GetUserToolBarByIndex(i);
		if (pUserToolbar != NULL)
		{
			pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE,
                                          strCustomize);
		}
	}

	return TRUE;
}

LRESULT CMainFrame::OnToolbarReset(WPARAM wParam, LPARAM lParam) {
  UINT id = (UINT)wParam;
  if (id == IDR_TOOLBAR_OFFICE) {
   /* CMFCToolBarComboBoxButton combo(ID_SELECT, 
      GetCmdMgr()->GetCmdImage(ID_SELECT), 
                                    CBS_DROPDOWNLIST);
    combo.OnSize(60);
    combo.AddItem(L"Green");
    combo.AddItem(L"Red");
    combo.AddItem(L"Yellow");
    combo.AddItem(L"Blue");
    combo.AddItem(L"Gray");
    combo.AddItem(L"Orange");
    VERIFY(combo.SelectItem(1));
    int rplum_driect = m_wndToolBar_Direct.ReplaceButton(ID_SELECT, 
                                                         combo, FALSE);*/

    CMFCToolBarComboBoxButton combo_office(ID_TEXT_STYLE, 
      GetCmdMgr()->GetCmdImage(ID_TEXT_STYLE), 
                                    CBS_DROPDOWNLIST);
    combo_office.AddItem(L"Time New Romance");
    combo_office.AddItem(L"Arian");
    combo_office.AddItem(L"Consola");
    VERIFY(combo_office.SelectItem(0));
    int rplum_text_style = m_wndToolBar_Office.ReplaceButton(ID_TEXT_STYLE, 
                                                       combo_office, FALSE);

    CMFCToolBarComboBoxButton combo_text_size(ID_TEXT_SIZE, 
      GetCmdMgr()->GetCmdImage(ID_TEXT_SIZE), 
                                    CBS_DROPDOWNLIST);
    combo_text_size.OnSize(50);
    combo_text_size.AddItem(L"10");
    combo_text_size.AddItem(L"12");
    combo_text_size.AddItem(L"14");
    VERIFY(combo_text_size.SelectItem(0));
    int rplum_text_size = m_wndToolBar_Office.ReplaceButton(ID_TEXT_SIZE, 
                                                        combo_text_size, FALSE);

 //int index = m_wndToolBar_Office.CommandToIndex(ID_TEXT_SIZE);
 //CustomComboButton combox_btn(ID_TEXT_SIZE, GetCmdMgr()->GetCmdImage(ID_TEXT_SIZE), CBS_DROPDOWNLIST);

 //int rplum_text_size = m_wndToolBar_Office.ReplaceButton(ID_TEXT_SIZE, combox_btn, FALSE); 

 //CustomComboButton *ccb = reinterpret_cast<CustomComboButton *>(m_wndToolBar_Office.GetButton(index));
 // CustomCombo *combo1 = reinterpret_cast<CustomCombo*>(ccb->GetComboBox());
 // combo1->AddItemCombo(_T("Item 1"), IDI_ICON1);
 }
  return 0L;
}



void CMainFrame::OnHandleItem() {
  int index = m_wndToolBar_Direct.CommandToIndex(ID_SELECT);
  CMFCToolBarComboBoxButton *combo = reinterpret_cast<CMFCToolBarComboBoxButton *>
                                     (m_wndToolBar_Direct.GetButton(index));
  CString item_combo = combo->GetText();

  int image;
  CDC *pDC = GetDC();
  CRect rect(1, 1, 1, 1);
  CMFCToolBarImages pImages;
  
  HINSTANCE hInstance = (HINSTANCE) GetModuleHandle (NULL);
  HBITMAP hbmp = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BITMAP_RED));
  pImages.AddImage(hbmp);
  
  if (item_combo.Compare(_T("Green")) == 0) {
  }
  else if (item_combo.Compare(_T("Red")) == 0)
    MessageBox(_T("Option Red"));
  else if (item_combo.Compare(_T("Yellow")) == 0)
    MessageBox(_T("Option Yellow"));
  else if (item_combo.Compare(_T("Blue")) == 0)
    MessageBox(_T("Option Blue"));
  else if (item_combo.Compare(_T("Gray")) == 0)
    MessageBox(_T("Option Gray"));
  else if (item_combo.Compare(_T("Orange")) == 0)
    MessageBox(_T("Option Orange"));
}

void CMainFrame::OnComBo() {
 ;
}

void CMainFrame::OnComBoTextStyle() {
 ;
}

void CMainFrame::OnComboTextSize() {
 ;
}