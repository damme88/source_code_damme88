
// Tet_DllDlg.h : header file
//

#pragma once


// CTet_DllDlg dialog
class CTet_DllDlg : public CDialog
{
// Construction
public:
	CTet_DllDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TET_DLL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
  afx_msg void OnBnClickedCancel();
  float num_1;
  float num_2;
  float num_3;
  afx_msg void OnBnClickedMul();
};
