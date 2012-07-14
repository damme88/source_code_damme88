
// Tet_DllDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Tet_Dll.h"
#include "Tet_DllDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// MYPROC la mot con tro ham no se tro vao vao vung nho co kieu du lieu la int
// vung nho nay phai la ket qua tra lai cua 1 ham co 2 tham so kieu int
typedef int (*MYPROC)(int, int);
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


// CTet_DllDlg dialog




CTet_DllDlg::CTet_DllDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTet_DllDlg::IDD, pParent)
  , num_1(0)
  , num_2(0)
  , num_3(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTet_DllDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  DDX_Text(pDX, IDC_NUM1, num_1);
  DDX_Text(pDX, IDC_NUM2, num_2);
  DDX_Text(pDX, IDC_NUM3, num_3);
}

BEGIN_MESSAGE_MAP(CTet_DllDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
  ON_BN_CLICKED(IDCANCEL, &CTet_DllDlg::OnBnClickedCancel)
  ON_BN_CLICKED(IDC_MUL, &CTet_DllDlg::OnBnClickedMul)
END_MESSAGE_MAP()


// CTet_DllDlg message handlers

BOOL CTet_DllDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTet_DllDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTet_DllDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTet_DllDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTet_DllDlg::OnBnClickedCancel()
{
  // TODO: Add your control notification handler code here
  OnCancel();
}

void CTet_DllDlg::OnBnClickedMul()
{
  HMODULE hmodule;
  hmodule = LoadLibrary(_T("Dll_Demo_MFC.dll"));
  MYPROC Mul;
  if (hmodule == NULL) {
    MessageBox(L"Khong tim thay file DLL_Demo.dll");
    return;
  }
  Mul = (MYPROC)GetProcAddress(hmodule, "Mul");
  if (Mul == NULL) {
    MessageBox(L"Khong tim thay ham Multi");
    return;
  }
  UpdateData(TRUE);
  num_3 = Mul(num_1, num_2);
  UpdateData(FALSE);
  FreeLibrary(hmodule);
}
