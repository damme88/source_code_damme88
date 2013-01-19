
// Simple_Draw.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "Simple_Draw.h"
#include "MainFrm.h"

#include "Simple_DrawDoc.h"
#include "Simple_DrawView.h"
#include "TextEditor.h"
#include "ControlContextDlg.h"
#include "SplashWindows.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSimple_DrawApp

BEGIN_MESSAGE_MAP(CSimple_DrawApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CSimple_DrawApp::OnAppAbout)
  ON_COMMAND(ID_OFFICE_TEXTEDITOR, &CSimple_DrawApp::OnAppTextEditor)
  ON_COMMAND(ID_VIEW_CONTEXT_DLG, &CSimple_DrawApp::OnAppContextDialog)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)

END_MESSAGE_MAP()



// Contructors
CSimple_DrawApp::CSimple_DrawApp():
  m_bHiColorIcons(TRUE),
  //Variable for Object Color
  glred_color_(1.0f),
  glgreen_color_(1.0f),
  glblue_color_(1.0f)
{
  glline_grid_size_ = 3.0f;
}


CSimple_DrawApp theApp;

// CSimple_DrawApp initialization
BOOL CSimple_DrawApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)
  SetRegistryBase(__T("Setting"));
	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CSimple_DrawDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CSimple_DrawView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	SplashWindows::EnableSplashWindows(cmdInfo.m_bShowSplash);
  SplashWindows::ShowSplashWindows(1000, IDB_SPLASH_WINDOWS, NULL);

	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// The one and only window has been initialized, so show and update it
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// call DragAcceptFiles only if there's a suffix
	//  In an SDI app, this should occur after ProcessShellCommand
	return TRUE;
}



// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// App command to run the dialog
void CSimple_DrawApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CSimple_DrawApp customization load/save methods


void CSimple_DrawApp::OnAppTextEditor() {
 TextEditor text_editor_Dlg;
 text_editor_Dlg.DoModal();
}

void CSimple_DrawApp::OnAppContextDialog () {
  CControlContextDlg context_dlg;
  context_dlg.DoModal();
}


void CSimple_DrawApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CSimple_DrawApp::LoadCustomState()
{
}

void CSimple_DrawApp::SaveCustomState()
{
}

//BOOL CSimple_DrawApp::LoadState(LPCTSTR lpszSectionName, CFrameImpl *pFrameImpl) {
//  return TRUE;
//}

void CSimple_DrawApp::OnFileOpen() {
 CFileDialog dlg(TRUE, NULL, L"", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
		L"All Files (*.*)|*.*||");
  dlg.DoModal();
}
// CSimple_DrawApp message handlers

BOOL CSimple_DrawApp::PreTranslateMessage(MSG* pMsg) 
{
	// Route messages to the splash screen while it is visible
  if (SplashWindows::PreTranslateAppMessage(pMsg)) {
		return TRUE;
	}
	
	return CWinApp::PreTranslateMessage(pMsg);
}

