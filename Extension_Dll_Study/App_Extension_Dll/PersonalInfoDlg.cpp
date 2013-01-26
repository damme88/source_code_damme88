// PersonalInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "App_Extension_Dll.h"
#include "PersonalInfoDlg.h"
#include "afxdialogex.h"
#include "..\Extension_Dll_Study\Personal_Info.h"

// PersonalInfoDlg dialog

IMPLEMENT_DYNAMIC(PersonalInfoDlg, CDialogEx)

PersonalInfoDlg::PersonalInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(PersonalInfoDlg::IDD, pParent)
  , edit_name_(_T(""))
  , edit_old_(_T(""))
  , edit_gender_(_T(""))
  , edit_adress_(_T(""))
  , edit_major_(_T(""))
  , edit_role_(_T(""))
{

}

PersonalInfoDlg::~PersonalInfoDlg()
{
}

void PersonalInfoDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialogEx::DoDataExchange(pDX);
  DDX_Text(pDX, IDC_EDIT_NAME, edit_name_);
  DDX_Text(pDX, IDC_EDIT_OLD, edit_old_);
  DDX_Text(pDX, IDC_EDIT_GENDER, edit_gender_);
  DDX_Text(pDX, IDC_EDIT_ADRESS, edit_adress_);
  DDX_Text(pDX, IDC_EDIT_MAJOR, edit_major_);
  DDX_Text(pDX, IDC_EDIT_ROLE, edit_role_);
}


BEGIN_MESSAGE_MAP(PersonalInfoDlg, CDialogEx)
  ON_BN_CLICKED(IDC_BTN_CHECK_GENDER, OnCheckGender)
END_MESSAGE_MAP()



void PersonalInfoDlg::OnCheckGender() {
  UpdateData(TRUE);
  CString name = edit_name_;
  CString str_old = edit_old_;
  CString str_gender = edit_gender_;
  CString adress = edit_adress_;
  CString major = edit_major_;
  CString role = edit_role_;
  int old = _tstoi(str_old);
  int gender = _tstoi(str_gender);

  PersonalInfo personal_info(name, old, gender, adress, major, role);
  personal_info.CheckGender(personal_info);
}
// PersonalInfoDlg message handlers
