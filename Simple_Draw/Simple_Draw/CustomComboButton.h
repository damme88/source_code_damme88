#pragma once
#include "CustomCombo.h"

// CustomComboButton

class CustomComboButton : public CMFCToolBarComboBoxButton
{
  DECLARE_DYNCREATE(CustomComboButton)

public:
	CustomComboButton();
  CustomComboButton(UINT uiID, int iImage, DWORD dwStyle = CBS_DROPDOWNLIST, int iWidth = 0);
	virtual ~CustomComboButton();

protected:
	//DECLARE_MESSAGE_MAP()
public:
  virtual CComboBox* CreateCombo(CWnd* pWndParent, const CRect& rect) ;
};


