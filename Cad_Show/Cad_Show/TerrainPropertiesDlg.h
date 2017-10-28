#pragma once
#include "afxwin.h"


// TerrainPropertiesDlg dialog

class TerrainPropertiesDlg : public CDialogEx
{
	DECLARE_DYNAMIC(TerrainPropertiesDlg)

public:
	TerrainPropertiesDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~TerrainPropertiesDlg();

// Dialog Data
	enum { IDD = IDD_DLG_TERRAIN };

public:
  CString GetFileImg() {return file_img_;};
  float GetHeight()const {return height_;};
  void OnOK();
  CString GetPathTerrainFolder();
protected:
  afx_msg void OnBrowers();
  afx_msg void OnRadSampleClicked();
  afx_msg void OnRadCustomClicked();
  afx_msg void SelectItemCombox();
  BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  void LoadBitmapSample(unsigned int sam_type);

	DECLARE_MESSAGE_MAP()
  CEdit terrain_img_file_;
  CButton btn_browers;
  CEdit terrain_offset_height_;
  CStatic terrain_img_;
  CString file_img_;
  float height_;

  int rad_custom_file_;
  int rad_sample_file_;
  CComboBox combox_img_sample_;
  CBitmap cbitmap_;
};
