#pragma once


// CControlContextDlg dialog

class CControlContextDlg : public CDialog
{
	DECLARE_DYNAMIC(CControlContextDlg)

public:
	CControlContextDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CControlContextDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  void OnContextMenu(CWnd *pWnd, CPoint pos);
	DECLARE_MESSAGE_MAP()
public:
  afx_msg void OnBnClickedSubmitBtn();
};
