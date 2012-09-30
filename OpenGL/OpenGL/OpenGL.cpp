// OpenGL.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "OpenGL.h"
#include "MainFrm.h"

#include "OpenGLDoc.h"
#include "OpenGLView.h"
#include "Struct.h"
#include <afxadv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define ID_FILE_MRU_FILE17 ID_FILE_MRU_FILE16 + 1
#define ID_FILE_MRU_FILE18 ID_FILE_MRU_FILE17 + 1
#define ID_FILE_MRU_FILE19 ID_FILE_MRU_FILE18 + 1
#define ID_FILE_MRU_FILE20 ID_FILE_MRU_FILE19 + 1


Triangle GLPoint ;
long unsigned int num=0;


BEGIN_MESSAGE_MAP(COpenGLApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &COpenGLApp::OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &COpenGLApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
  ON_COMMAND_RANGE(ID_FILE_MRU_FILE1, ID_FILE_MRU_FILE20, MyMRUFileHandler)

END_MESSAGE_MAP()


// COpenGLApp construction

COpenGLApp::COpenGLApp()
{
	m_bDrawData = FALSE ;
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}
// The one and only COpenGLApp object
COpenGLApp theApp;


// COpenGLApp initialization

BOOL COpenGLApp::InitInstance()
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

	CWinApp::InitInstance();

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
	LoadStdProfileSettings(1);  // Load standard INI file options (including MRU)
	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(COpenGLDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(COpenGLView));
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
void COpenGLApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

void COpenGLApp::OnFileOpen()
{
	unsigned int nsize=0;
	char str[120];
	double value[1000][3];
	double nor[3];
	char FileName[100];
	CFileDialog Dlg(TRUE) ;
	CString File_Name ;
	int i=0;
	// Thuc hien lay ten file duoc lua chon
	if(IDOK==Dlg.DoModal()){
		File_Name = Dlg.GetFileName();
	}
	// Xu ly doi tu chuoi so CString sang char
	nsize = File_Name.GetLength();
	memset(FileName,0,nsize+1);
	wcstombs(FileName,File_Name,nsize+1);
	// Thu hien doc va xu ly file
	FILE *pFile ;
	pFile=fopen(FileName,"rt");
	while(!feof(pFile))
	{
		fscanf(pFile,"%s",str);
		if(strcmp(str,"VERTEX")==0){
			num=num+1;
		}
	}
	fclose(pFile);

	pFile=fopen(FileName,"rt");
	fgets(str,50,pFile);
	while(!feof(pFile))
	{
		fscanf(pFile,"%s%s%lf%lf%lf",str,str,&nor[0],&nor[1],&nor[2]);
		fgets(str,100,pFile);
		fgets(str,100,pFile);
		for(i=0;i<num;i++){
			fscanf(pFile,"%s%lf%lf%lf",str,&value[i][0],&value[i][1],&value[i][2]);
			GLPoint.Vertex[i][0]=value[i][0];
			GLPoint.Vertex[i][1]=value[i][1];
			GLPoint.Vertex[i][2]=value[i][2];
			if((i+1)%3 == 0){
				fgets(str,100,pFile);
				fgets(str,100,pFile);
				fgets(str,100,pFile);
				fscanf(pFile,"%s%s%lf%lf%lf",str,str,&nor[0],&nor[1],&nor[2]);
				fgets(str,100,pFile);
				fgets(str,100,pFile);
			}
		}	
		m_bDrawData = TRUE ;
		InvalidateRect(NULL,NULL,FALSE);
	}
	fclose(pFile);
}


void COpenGLApp::MyMRUFileHandler(UINT i)
{
    ASSERT_VALID(this);
    ASSERT(m_pRecentFileList != NULL);

    ASSERT(i >= ID_FILE_MRU_FILE1);
    ASSERT(i < ID_FILE_MRU_FILE1 + (UINT)m_pRecentFileList->GetSize());

    CString strName, strCurDir, strMessage;
    int nIndex = i - ID_FILE_MRU_FILE1;
    ASSERT((*m_pRecentFileList)[nIndex].GetLength() != 0);

   strName.Format(L"MRU: open file (%d) '%s'.\n", (nIndex) + 1,(LPCTSTR)(*m_pRecentFileList)[nIndex]);

   if (OpenDocumentFile((*m_pRecentFileList)[nIndex]) == NULL)
	 m_pRecentFileList->Remove(nIndex);
   AfxMessageBox(strName);
}
