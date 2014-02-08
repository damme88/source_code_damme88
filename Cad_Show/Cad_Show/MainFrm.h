
// MainFrm.h : interface of the CMainFrame class
//

#pragma once
#include "DialogBar.h"
#include "InforBar.h"
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
	void OnViewFullscreen();
	void ShowAndDockToolbar();
	void HandleEscape();
	void ShowToolbar();
	void UpdateShowToolbar(CCmdUI* cmd);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
  CSplitterWnd m_wndSplitter;
  CSplitterWnd info_splitter_;
protected:  // control bar embedded members
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
  CMFCToolBar       view_toolbar_;
	CMFCStatusBar     m_wndStatusBar;
	CMFCToolBarImages m_UserImages;
  CCad_ShowView *cad_show_view_;
  DialogBar *dialog_view_;
  InfoBar *info_view_;
	bool is_full_screen_;

  // Generated message map functions
  virtual BOOL OnCreateClient(LPCREATESTRUCT lp, CCreateContext* pContext);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	DECLARE_MESSAGE_MAP()
};


