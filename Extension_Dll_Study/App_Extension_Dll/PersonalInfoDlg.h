#pragma once


// PersonalInfoDlg dialog

class PersonalInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(PersonalInfoDlg)

public:
	PersonalInfoDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~PersonalInfoDlg();

// Dialog Data
	enum { IDD = IDD_PERSONAL_INFOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
  CString edit_name_;
  CString edit_old_;
  CString edit_gender_;
  CString edit_adress_;
  CString edit_major_;
  CString edit_role_;
public:
  void OnCheckGender();
};
