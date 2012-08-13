// ControlContextDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Simple_Draw.h"
#include "ControlContextDlg.h"


// CControlContextDlg dialog

IMPLEMENT_DYNAMIC(CControlContextDlg, CDialog)

CControlContextDlg::CControlContextDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CControlContextDlg::IDD, pParent)
{

}

CControlContextDlg::~CControlContextDlg()
{
}

void CControlContextDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CControlContextDlg, CDialog)
ON_WM_CONTEXTMENU()
ON_BN_CLICKED(IDC_SUBMIT_BTN, &CControlContextDlg::OnBnClickedSubmitBtn)
END_MESSAGE_MAP()

void CControlContextDlg::OnContextMenu(CWnd *pWnd, CPoint pos) {
  // thuc hien load menu voi bien thuoc class Menu
  CMenu menu_pop_submit;
  menu_pop_submit.LoadMenu(IDR_MENU_CONTEX);

  CButton *pbutton;
  // lay handle kieu CWnd cua button ve luu vao 1 con tro kieu CButton sau khi 
  // da dc ep kieu voi tu khoa reinterpret_cast
  pbutton = reinterpret_cast<CButton*>(GetDlgItem(IDC_SUBMIT_BTN));
  CRect rect_submit_button;
  pbutton->GetWindowRect(&rect_submit_button);
  // item dau tien se duoc focus khi menu duoc active
  CMenu *p_pop_menu = menu_pop_submit.GetSubMenu(0);
  ASSERT(*p_pop_menu);
  // neu thuc hien an chuot phai thi menu item nay se duoc hien ra tai vi tri
  // toa do chuot phai duoc kich
  if (rect_submit_button.PtInRect(pos));
    p_pop_menu->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, pos.x, pos.y, this);
}
// CControlContextDlg message handlers

void CControlContextDlg::OnBnClickedSubmitBtn()
{
  AfxMessageBox(L"You clicked the Submit button but ain't nothin' to do right now!!!");
}
