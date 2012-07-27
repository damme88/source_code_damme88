// CustomComboButton.cpp : implementation file
//

#include "stdafx.h"
#include "Simple_Draw.h"
#include "CustomComboButton.h"
#include "CustomCombo.h"

// CustomComboButton

IMPLEMENT_DYNCREATE(CustomComboButton, CMFCToolBarComboBoxButton)

CustomComboButton::CustomComboButton()
{

}

CustomComboButton::CustomComboButton(UINT uiId, int iImage, DWORD dwStyle, int iWidth)
  : CMFCToolBarComboBoxButton(uiId, iImage, dwStyle, iWidth) {
}

CustomComboButton::~CustomComboButton()
{
}


//BEGIN_MESSAGE_MAP(CustomComboButton, CMFCToolBarComboBoxButton)
//END_MESSAGE_MAP()

CComboBox *CustomComboButton::CreateCombo(CWnd* pWndParent, const CRect& rect) {
  CustomCombo *cuscom = new CustomCombo();
  if(cuscom->Create(m_dwStyle, rect, pWndParent , 
                       m_nID)) {
    return cuscom;
  }

  delete cuscom;
  return NULL;
}

// CustomComboButton message handlers


