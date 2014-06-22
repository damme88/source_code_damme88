
// Cad_Show.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "Cad_Show.h"
#include "MainFrm.h"

#include "Cad_ShowDoc.h"
#include "Cad_ShowView.h"
#include "Cad_Point.h"
#include "glm.h"
#include "FileWork.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//Triangle GLPoint ;
// CCad_ShowApp

BEGIN_MESSAGE_MAP(CCad_ShowApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CCad_ShowApp::OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CCad_ShowApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
#ifdef USE_SUB_MENU_RECENT_FILE
	ON_UPDATE_COMMAND_UI(ID_FILE_MRU_FILE1, OnUpdateFileMruFile1)
#endif
END_MESSAGE_MAP()


// CCad_ShowApp construction

CCad_ShowApp::CCad_ShowApp()
{
  gl_point_ = NULL;
  normal_vector_ = NULL;
	m_bHiColorIcons = TRUE;
  number_of_point_ = 0;
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// If the application is built using Common Language Runtime support (/clr):
	//     1) This additional setting is needed for Restart Manager support to work properly.
	//     2) In your project, you must add a reference to System.Windows.Forms in order to build.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: replace application ID string below with unique ID string; recommended
	// format for string is CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("Cad_Show.AppID.NoVersion"));

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CCad_ShowApp object

CCad_ShowApp theApp;


// CCad_ShowApp initialization

BOOL CCad_ShowApp::InitInstance()
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

	EnableTaskbarInteraction(FALSE);

	// AfxInitRichEdit2() is required to use RichEdit control	
	// AfxInitRichEdit2();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(10);  // Load standard INI file options (including MRU)


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
		RUNTIME_CLASS(CCad_ShowDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CCad_ShowView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

		m_pMainWnd->DragAcceptFiles();
	// The one and only window has been initialized, so show and update it
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// call DragAcceptFiles only if there's a suffix
	//  In an SDI app, this should occur after ProcessShellCommand
	return TRUE;
}

int CCad_ShowApp::ExitInstance()
{
	//TODO: handle additional resources you may have added
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CCad_ShowApp message handlers


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
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

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// App command to run the dialog
void CCad_ShowApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CCad_ShowApp customization load/save methods

void CCad_ShowApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CCad_ShowApp::LoadCustomState()
{
}

void CCad_ShowApp::SaveCustomState()
{
}

BOOL CCad_ShowApp::LoadState(LPCTSTR lpszSectionName, CFrameImpl *pFrameImpl) {
  return TRUE;
}

CDocument*  CCad_ShowApp::OpenDocumentFile(LPCTSTR lpszFileName) {
	CString str_extension = GetExtensionFile(lpszFileName);
	CString str_stl = _T("stl");
	CString str_obj = _T("obj");
	if (str_extension.CompareNoCase(str_stl.GetString()) == false) {
	  OpenFile3DStl(lpszFileName);
  } else if (str_extension.CompareNoCase(str_obj) == false) {
	  OpenFile3DObj(lpszFileName);
	}
  return CWinAppEx::OpenDocumentFile(lpszFileName);
}

// Handle event Open file
void CCad_ShowApp::OnFileOpen() {
	CFileDialog dlg(TRUE, L"", L"",
		OFN_HIDEREADONLY | OFN_FILEMUSTEXIST,
		_T("3D Stl File (*.STL)|*.STL|3d obj File(*.obj)|*.obj||"));
  CString file_name_stl = L"";
  // Get file name 
  if (IDOK == dlg.DoModal()) {
    file_name_stl = dlg.GetPathName();
		AfxGetApp()->OpenDocumentFile(file_name_stl);
  }
}

void CCad_ShowApp::OpenFile3DStl(LPCTSTR file_path) { 
	CString file_name_stl = (CString)file_path;
	UINT n_size = 0;
	char str[MAX_PATH];
	FILE *pFile = NULL;
	Point *value_stl = NULL;
	Point *asscii_value_stl = NULL;
  // Convert CString to char*
  char file_name[MAX_PATH];
  n_size = file_name_stl.GetLength();
  memset(file_name, 0, n_size + 1);
  wcstombs(file_name, file_name_stl, n_size);

  pFile = fopen(file_name, "r");
  if (pFile == NULL)
    return;
  fclose(pFile);
  bool is_asscii = IsAssciiFormat(file_name);
  if (is_asscii == true) {  // Check format file STL. Is binary or Asscii
    pFile = fopen(file_name, "r");
    if (pFile == NULL)
      return;
    while(!feof(pFile)) {
      fscanf(pFile, "%s", str);
      if (strcmp(str, "vertex") == 0 || strcmp(str, "VERTEX") == 0) {
        number_of_point_ += 1;
      }
    }
    fclose(pFile);
    // check number_of_point
    if (number_of_point_ == 0) {
      ::MessageBox(NULL, L"Can not read STL file", L"Inform", MB_OK | MB_ICONWARNING);
      return;
    }

    static long count_normal_vector = 0;
    if (gl_point_ != NULL) {
      delete [] gl_point_;
      gl_point_ = NULL;
    }
    if (normal_vector_ != NULL) {
      delete [] normal_vector_;
      count_normal_vector = 0;
      normal_vector_ = NULL;
    }
    gl_point_ = new Triangle[number_of_point_];
    value_stl = new Point[number_of_point_];
    normal_vector_ = new Vector[number_of_point_ /3];
    // read data form stl file
    pFile = fopen(file_name, "r");
    fgets(str, MAX_PATH, pFile);
    while(!feof(pFile)) {
      fscanf(pFile, "%s%s%f%f%f", str, str,
             &normal_vector_[count_normal_vector][0],
             &normal_vector_[count_normal_vector][1],
             &normal_vector_[count_normal_vector][2]);
      count_normal_vector = 1;
      fgets(str, MAX_PATH, pFile);
      fgets(str, MAX_PATH, pFile);
      for (long i = 0; i< number_of_point_; i++) {
        fscanf(pFile,"%s%f%f%f",str, &value_stl[i][0],
              &value_stl[i][1],
              &value_stl[i][2]);
        gl_point_->Vertex[i][0] = value_stl[i][0];
        gl_point_->Vertex[i][1] = value_stl[i][1];
			  gl_point_->Vertex[i][2] = value_stl[i][2];
			  if((i+1)%3 == 0) {
				  fgets(str,100,pFile);
				  fgets(str,100,pFile);
				  fgets(str,100,pFile);
				  fscanf(pFile,"%s%s%f%f%f", str, str,
                 &normal_vector_[count_normal_vector][0],
                 &normal_vector_[count_normal_vector][1],
                 &normal_vector_[count_normal_vector][2]);
          count_normal_vector ++;
				  fgets(str,100,pFile);
				  fgets(str,100,pFile);
        }
      }
    }
    allow_draw_data_ = TRUE ;
	  InvalidateRect(NULL,NULL,FALSE);
    if (value_stl != NULL) {
      delete [] value_stl;
      value_stl = NULL;
    }
	  fclose(pFile);
  } else {
    // Is binary
    pFile = fopen(file_name, "rb");
    rewind(pFile); // reposition file pointer at begin file
    const char *str_header= new char [100];
    unsigned long triangle_count = 0;
    fread((void*)str_header, 80, 1, pFile);
    fread(&triangle_count, 4, 1, pFile); 
    number_of_point_ = 3*triangle_count;
    if (number_of_point_ <= 0) {
      ::MessageBox(NULL, L"Can not read STL file", L"Inform", MB_OK | MB_ICONWARNING);
      return;
    }
    if (gl_point_ != NULL) {
      delete [] gl_point_;
      gl_point_ = NULL;
    }

    if (normal_vector_ != NULL) {
      delete [] normal_vector_;
      normal_vector_ = NULL;
    }

    value_stl = new Point[number_of_point_];
    gl_point_ = new Triangle[triangle_count];
    normal_vector_ = new Vector[triangle_count];
    int k = 0;
    for (long i = 0; i< triangle_count; i++) {
      fread(&normal_vector_[i][0], 1, sizeof(float), pFile);  // get data of normal vector
      fread(&normal_vector_[i][1], 1, sizeof(float), pFile);
      fread(&normal_vector_[i][2], 1, sizeof(float), pFile);
      for(int j = 0; j<= 2; j++) {
        fread(&value_stl[k][0], 1, sizeof(float), pFile);  // get vertext
        fread(&value_stl[k][1], 1, sizeof(float), pFile);
        fread(&value_stl[k][2], 1, sizeof(float), pFile);

        gl_point_->Vertex[k][0] =  value_stl[k][0];  // assign for gl_point
        gl_point_->Vertex[k][1] =  value_stl[k][1];
        gl_point_->Vertex[k][2] =  value_stl[k][2];
        k = k+1;
      }
      float value = 0.0;
      fread(&value, 1, 2, pFile);  //get data of 2 byte which don't use
    }
    allow_draw_data_ = TRUE ;
	  InvalidateRect(NULL,NULL,FALSE);
    if (value_stl != NULL) { 
      delete [] value_stl;
      value_stl = NULL; // free value_stl
    }
    fclose(pFile);
  }
}

void CCad_ShowApp::OpenFile3DObj(LPCTSTR file_path) {
	GLfloat scale_factor = 0.0f;
	GLMmodel *object_1;
	CString str = file_path;
	str.Replace(L"\\", L"//");
	// convert to char
	char * strch = new char [MAX_PATH];
	long nsize = str.GetLength();
	memset(strch, 0, nsize);
	wcstombs(strch, str, nsize+1);

	if (FileWrk::FileWork::ChecIsExistFile(strch)) {

		object_1 = glmReadOBJ(strch);
		if (!scale_factor)
			scale_factor = glmUnitize(object_1);
		else 
			glmScale(object_1, scale_factor);

		glmScale(object_1, 2.5);

		obj_list_ = glmList(object_1, GLM_SMOOTH);
		glmDelete(object_1);
	} else {
		;
	}
}


void CCad_ShowApp::FreePoint() {
  if (gl_point_ != NULL) {
    delete [] gl_point_;
    gl_point_ = NULL;
  }
  if (normal_vector_ != NULL) {
    delete [] normal_vector_;
    normal_vector_ = NULL;
  }
}

// This function for sub menu recent file
#ifdef USE_SUB_MENU_RECENT_FILE
void CCad_ShowApp::OnUpdateFileMruFile1(CCmdUI *pcmd) {
	if (pcmd->m_pSubMenu != NULL)
	{
		return;
	}
	CWinApp::OnUpdateRecentFileMenu(pcmd);
	return;
}
#endif

bool CCad_ShowApp::IsAssciiFormat(const char * path_file) {
  FILE *pFile = fopen(path_file, "rb");
  assert(pFile != NULL);
  char buff[MAX_PATH];
  int rc = fread(buff, 1, sizeof(buff), pFile);
  for(int i = 0; i< rc; i++) {
    if(!__isascii(buff[i])) {
      return false;
    }
  }
  return true;
}

CString CCad_ShowApp::GetExtensionFile(LPCTSTR file_path) {
  CString str = file_path;
	int dot_pos = str.ReverseFind('.');
	int length = str.GetLength();
	CString str_ex = str.Mid(dot_pos + 1, length-1);
	return str_ex;
}