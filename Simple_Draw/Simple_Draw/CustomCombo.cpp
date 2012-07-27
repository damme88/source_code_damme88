// CustomCombo.cpp : implementation file
//

#include "stdafx.h"
#include "Simple_Draw.h"
#include "CustomCombo.h"


// CustomCombo

IMPLEMENT_DYNAMIC(CustomCombo, CComboBox)

CustomCombo::CustomCombo()
{

}

CustomCombo::~CustomCombo()
{
}


BEGIN_MESSAGE_MAP(CustomCombo, CComboBox)
END_MESSAGE_MAP()



// CustomCombo message handlers

INT_PTR CustomCombo::AddItemCombo(LPCTSTR lpszitem, UINT iconID) {
  HICON hicon = AfxGetApp()->LoadIcon(MAKEINTRESOURCE(iconID));
  AddString(lpszitem);
  //SetIcon(hicon, TRUE);
  return 1;

}

