
// MainFrm.h : interface of the CMainFrame class
//
#pragma once

class CMainFrame : public CFrameWndEx
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
  BOOL show_viewbar_;
  BOOL show_drawbar_;
  BOOL show_officebar_;

public:
  void OnHanleShowBar(UINT nid);
  void OnComBo();
  void OnComBoTextStyle();
  void OnComboTextSize();
  void OnHandleItem();

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, 
                         DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW |
                         FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, 
                         CCreateContext* pContext = NULL);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
  CMFCStatusBar     m_wndStatusBar;
	CMFCMenuBar       m_wndMenuBar;
  CDialogBar	      m_wndToolbox;           //use for dialog bar
	CMFCToolBar       m_wndToolBar;
  CMFCToolBar       m_wndToolBar_Direct;
  CMFCToolBar       m_wndToolBar_Office;
  CMFCToolBar       m_wndToolBar_Draw;



// Generated message map functions
protected:
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewCustomize();
  afx_msg LRESULT OnToolbarCreateNew(WPARAM wp,LPARAM lp);
  afx_msg LRESULT OnToolbarReset(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};


