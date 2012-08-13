#pragma once


// CWorkspaceBar

class CWorkspaceBar : public CDockablePane
{
	DECLARE_DYNAMIC(CWorkspaceBar)

public:
	CWorkspaceBar();
	virtual ~CWorkspaceBar();

protected:
  CMFCTabCtrl   m_wndTabs;
	CTreeCtrl     m_wndTree1;
	CTreeCtrl     m_wndTree2;

protected:
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg void OnSize (UINT nType, int x, int y);

	DECLARE_MESSAGE_MAP()
};


