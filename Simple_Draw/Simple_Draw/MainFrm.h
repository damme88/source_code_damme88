
// MainFrm.h : interface of the CMainFrame class
#pragma once
#include "WorkspaceBar.h"

class CMainFrame : public CFrameWndEx
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
  short red_color_;
  short green_color_;
  short blue_color_;

public:
  void OnComBo();

  void OnComBoTextStyle();
  void OnComboTextSize();
  void OnHandleTextSixe();
  void OnHanleItemCombo();
  void OnHanleShowBar(UINT nid);
  void OnUpdateHandleShowBar(CCmdUI* pcmd);
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
	CMFCToolBar       m_wndToolBar;
  CMFCToolBar       m_wndToolBar_Direct;
  CMFCToolBar       m_wndToolBar_Office;
  CMFCToolBar       m_wndToolBar_Draw;
  CWorkspaceBar	    m_wndWorkSpace;
public:
  CMFCToolBarComboBoxButton *check_one_;


// Generated message map functions
protected:
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewCustomize();
  afx_msg LRESULT OnToolbarCreateNew(WPARAM wp,LPARAM lp);
  afx_msg LRESULT OnToolbarReset(WPARAM wParam, LPARAM lParam);
  afx_msg void OnViewWorkspace();
	afx_msg void OnUpdateViewWorkspace(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()
};


