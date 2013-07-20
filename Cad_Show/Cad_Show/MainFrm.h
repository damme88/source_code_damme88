
// MainFrm.h : interface of the CMainFrame class
//

#pragma once
#include "DialogBar.h"
#include "Cad_ShowView.h"
class CMainFrame : public CFrameWndEx
{
	
public: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
  CSplitterWnd m_wndSplitter;
protected:  // control bar embedded members
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
  CMFCToolBar       view_toolbar_;
	CMFCStatusBar     m_wndStatusBar;
	CMFCToolBarImages m_UserImages;
  CCad_ShowView *cad_show_view_;
  DialogBar *dialog_view_;

  // Generated message map functions
  virtual BOOL OnCreateClient(LPCREATESTRUCT lp, CCreateContext* pContext);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	DECLARE_MESSAGE_MAP()
};


