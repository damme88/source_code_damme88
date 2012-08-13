
// MainFrm.cpp : implementation of the CMainFrame class

#include "stdafx.h"
#include "Simple_Draw.h"
#include "MainFrm.h"
#include "CustomComboButton.h"
#include "CustomCombo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define ID_SHOW_BAR_START ID_DOCKING_VIEWTOOLBAR
#define ID_SHOW_BAR_END   ID_DOCKING_OFFICETOOLBAR

// CMainFrame
IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 0;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_CUSTOMIZE, &CMainFrame::OnViewCustomize)
  ON_REGISTERED_MESSAGE(AFX_WM_RESETTOOLBAR, &CMainFrame::OnToolbarReset)
	ON_REGISTERED_MESSAGE(AFX_WM_CREATETOOLBAR, &CMainFrame::OnToolbarCreateNew)

  ON_COMMAND(ID_SELECT,&CMainFrame::OnComBo)
  ON_CBN_SELENDOK(ID_SELECT, &CMainFrame::OnHanleItemCombo)

  ON_COMMAND(ID_TEXT_STYLE, &CMainFrame::OnComBoTextStyle)
  ON_COMMAND(ID_TEXT_SIZE, &CMainFrame::OnComboTextSize)
  ON_COMMAND_RANGE(ID_SHOW_BAR_START, ID_SHOW_BAR_END,
                   &CMainFrame::OnHanleShowBar)
  ON_UPDATE_COMMAND_UI_RANGE(ID_SHOW_BAR_START, ID_SHOW_BAR_END,
                             &CMainFrame::OnUpdateHandleShowBar)

  ON_COMMAND(ID_VIEW_WORKSPACE, &CMainFrame::OnViewWorkspace)
  ON_UPDATE_COMMAND_UI(ID_VIEW_WORKSPACE, &CMainFrame::OnUpdateViewWorkspace)

END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame construction/destruction

CMainFrame::CMainFrame() :
 red_color_(0),
 green_color_(0),
 blue_color_(0)
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

  /*
	if (!m_wndMenuBar.Create(this))
	{
		TRACE0("Failed to create menubar\n");
		return -1;      // fail to create
	//}

	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | 
                            CBRS_TOOLTIPS | CBRS_FLYBY);
  m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
  EnableDocking(CBRS_ALGIN_ANY)
  DockPane(&m_wndMenuBar); 
  */
	// prevent the menu bar from taking the focus on activation
	CMFCPopupMenu::SetForceMenuFocus(FALSE);
  
/***************************Create File Toolbar*******************************/

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | 
                                   CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | 
                                   CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME_256))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
   m_wndToolBar.SetWindowText(__T("File Toolbar"));
   m_wndToolBar.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, __T("Customize..."));
   m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
   EnableDocking(CBRS_ALIGN_ANY);
   DockPane(&m_wndToolBar);
//	CString strToolBarName;
//	bNameValid = strToolBarName.LoadString(IDS_TOOLBAR_STANDARD);
	//ASSERT(bNameValid);
	//CString strCustomize;
	//bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	//ASSERT(bNameValid);


/************************Create File Toolbar*********************************/

	// Allow user-defined toolbars operations:
	//InitUserToolbars(NULL, uiFirstUserToolBarId, uiLastUserToolBarId);

/************************Create Direct Toolbar********************************/
    if (! m_wndToolBar_Direct.Create(this, WS_CHILD | WS_VISIBLE 
                                     | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS 
                                     | CBRS_FLYBY | CBRS_SIZE_DYNAMIC | CBRS_BORDER_3D, ID_CUSTOMIZE_VIEW) ||
		! m_wndToolBar_Direct.LoadToolBar(IDR_TOOLBAR_DIRECT))
	{
		TRACE0("Failed to create Toolbar_Direct\n");
		return -1;      // fail to create
	}
  m_wndToolBar_Direct.SetWindowText(__T("Direction Toolbar"));
  m_wndToolBar_Direct.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, __T("Customize"));
  m_wndToolBar_Direct.EnableDocking(CBRS_ALIGN_ANY);
  EnableDocking(CBRS_ALIGN_ANY);
  DockPane(&m_wndToolBar_Direct);

/************************Create Office Toolbar********************************/
  if (! m_wndToolBar_Office.Create(this, WS_CHILD | WS_VISIBLE 
                                     | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS 
                                     | CBRS_FLYBY | CBRS_SIZE_DYNAMIC | CBRS_BORDER_3D, ID_CUSTOMIZE_OFFICE) ||
                        ! m_wndToolBar_Office.LoadToolBar(IDR_TOOLBAR_OFFICE))
	{
		TRACE0("Failed to create Toolbar_Office\n");
		return -1;      // fail to create
	}
  m_wndToolBar_Office.SetWindowText(__T("Office ToolBar"));
  m_wndToolBar_Office.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, __T("Customize..."));
  m_wndToolBar_Office.EnableDocking(CBRS_ALIGN_ANY);
  EnableDocking(CBRS_ALIGN_ANY);
  DockPane(&m_wndToolBar_Office);

/************************Create Draw Toolbar********************************/

  if (! m_wndToolBar_Draw.Create(this, WS_CHILD | WS_VISIBLE 
                                     | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS 
                                     | CBRS_FLYBY | CBRS_SIZE_DYNAMIC |CBRS_BORDER_3D, ID_CUSTOMIZE_DRAW) ||
                        ! m_wndToolBar_Draw.LoadToolBar(IDR_TOOLBAR_DRAW))
	{
		TRACE0("Failed to create Toolbar_Draw\n");
		return -1;      // fail to create
	}
  m_wndToolBar_Draw.SetWindowText(__T("Draw Toolbar"));
  m_wndToolBar_Draw.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, __T("Customize..."));
  m_wndToolBar_Draw.EnableDocking(CBRS_ALIGN_ANY);
  EnableDocking(CBRS_ALIGN_ANY);
  DockPane(&m_wndToolBar_Draw);

/************************Create Workspace Bar********************************/
	if (!m_wndWorkSpace.Create (_T("Workspace"), this, CSize (200, 200),
		TRUE /* Has gripper */, ID_VIEW_WORKSPACE,
		WS_CHILD | WS_VISIBLE | CBRS_LEFT))
	{
		TRACE0("Failed to create workspace bar\n");
		return -1;      // fail to create
	}
  m_wndWorkSpace.EnableDocking(CBRS_ALIGN_ANY);
  EnableDocking(CBRS_ALIGN_ANY);
  DockPane(&m_wndWorkSpace);

/************************Status Bar******************************************/

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT)); 
  
  // TODO: Delete these five lines 
  // if you don't want the toolbar and menubar to be dockable

	// enable Visual Studio 2005 style docking window behavior
	CDockingManager::SetDockingMode(DT_SMART);
	// enable Visual Studio 2005 style docking window auto-hide behavior
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// Enable toolbar and docking window menu replacement
	//EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);

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
  lstBasicCommands.AddTail(ID_ZOOM_IN);

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
    CMFCToolBarComboBoxButton combo(ID_SELECT, 
      GetCmdMgr()->GetCmdImage(ID_SELECT), 
                                    CBS_DROPDOWNLIST);
    combo.OnSize(80);
    combo.AddItem(L"Red");
    combo.AddItem(L"Green");
    combo.AddItem(L"Blue");
    VERIFY(combo.SelectItem(0));
    int rplum_driect = m_wndToolBar_Direct.ReplaceButton(ID_SELECT, 
                                                         combo, FALSE);

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
    combo_text_size.OnSize(80);
    combo_text_size.AddItem(L"10");
    combo_text_size.AddItem(L"12");
    combo_text_size.AddItem(L"14");
    VERIFY(combo_text_size.SelectItem(0));
    int rplum_text_size = m_wndToolBar_Office.ReplaceButton(ID_TEXT_SIZE, 
                                                        combo_text_size, FALSE);
 }
  return 0L;
}

/*****************************************************************************
* Function Name : OnHandleItemCombo
* Purpose       : Hanlde items in Color ComboBox for a OpengGL Graphics Object
* Input Param   : Nothing
* Output Param  : Nothing
* Environment   : Visual C++ 2008 with MFC and OpenGl
* Writer        : Damme88_Developer_Phamtoanbonmat@gmail.com
* Time          : 08/2012
*****************************************************************************/

void CMainFrame::OnHanleItemCombo() {
  int index = m_wndToolBar_Direct.CommandToIndex(ID_SELECT);
  CMFCToolBarComboBoxButton *combo = reinterpret_cast<CMFCToolBarComboBoxButton *>
                                     (m_wndToolBar_Direct.GetButton(index));
  int item_combo = combo->GetCurSel();
  if (item_combo == 0) {
    theApp.red_color_ = 1.0f;
    theApp.green_color_ = 0.0f;
    theApp.blue_color_ = 0.0f;
    InvalidateRect(NULL, FALSE);
  } else if (item_combo == 1) {
    theApp.red_color_ = 0.0f;
    theApp.green_color_ = 1.0f;
    theApp.blue_color_ = 0.0f;
    InvalidateRect(NULL, FALSE);
  } else if (item_combo == 2) {
    theApp.red_color_ = 0.0f;
    theApp.green_color_ = 0.0f;
    theApp.blue_color_ = 1.0f;
    InvalidateRect(NULL, FALSE);
  } else {
    theApp.red_color_ = 1.0f;
    theApp.green_color_ = 1.0f;
    theApp.blue_color_ = 1.0f;
    InvalidateRect(NULL, FALSE);
  }
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

void CMainFrame::OnHanleShowBar(UINT nID) {
  if (nID == ID_DOCKING_VIEWTOOLBAR) {
    ShowPane(&m_wndToolBar_Direct, !(m_wndToolBar_Direct.IsVisible()), FALSE, TRUE);
    RecalcLayout();
  }
  if (nID == ID_DOCKING_DRAWTOOLBAR) {
    ShowPane(&m_wndToolBar_Draw, !(m_wndToolBar_Draw.IsVisible()), FALSE, TRUE);
    RecalcLayout();
  }
  if (nID == ID_DOCKING_OFFICETOOLBAR) {
    ShowPane(&m_wndToolBar_Office, !(m_wndToolBar_Office.IsVisible()), FALSE, TRUE);
    RecalcLayout();
  }
}

void CMainFrame::OnUpdateHandleShowBar(CCmdUI* pcmd) {
  if (pcmd->m_nID == ID_DOCKING_VIEWTOOLBAR) {
    pcmd->SetCheck(m_wndToolBar_Direct.IsVisible());
  }
  if (pcmd->m_nID == ID_DOCKING_DRAWTOOLBAR) {
    pcmd->SetCheck(m_wndToolBar_Draw.IsVisible());
  }
  if (pcmd->m_nID == ID_DOCKING_OFFICETOOLBAR) {
    pcmd->SetCheck(m_wndToolBar_Office.IsVisible());
  }
}

void CMainFrame::OnViewWorkspace() {
	ShowPane (&m_wndWorkSpace,
					!(m_wndWorkSpace.IsVisible ()),
					FALSE, TRUE);
	RecalcLayout ();
}

void CMainFrame::OnUpdateViewWorkspace(CCmdUI* pCmdUI) {
	pCmdUI->SetCheck (m_wndWorkSpace.IsVisible ());
}