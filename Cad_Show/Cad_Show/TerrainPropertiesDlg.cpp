// TerrainPropertiesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Cad_Show.h"
#include "TerrainPropertiesDlg.h"
#include "afxdialogex.h"
#include "FileWork.h"
#include "Base.h"


// TerrainPropertiesDlg dialog

IMPLEMENT_DYNAMIC(TerrainPropertiesDlg, CDialogEx)

TerrainPropertiesDlg::TerrainPropertiesDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(TerrainPropertiesDlg::IDD, pParent)
  , rad_custom_file_(0)
  , rad_sample_file_(0)
{
  file_img_ = _T("");
  height_ = 20;
}

TerrainPropertiesDlg::~TerrainPropertiesDlg()
{
}

void TerrainPropertiesDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialogEx::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_EDIT_FILE_NAME, terrain_img_file_);
  DDX_Control(pDX, IDC_BTN_BROWERS, btn_browers);
  DDX_Control(pDX, IDC_EDIT_OFFSET_HEIGHT, terrain_offset_height_);
  DDX_Control(pDX, IDC_IMG_TERRAIN, terrain_img_);
  DDX_Check(pDX, IDC_RAD_CUSTOM, rad_custom_file_);
  DDX_Check(pDX, IDC_RAD_SAMPLE, rad_sample_file_);
  DDX_Control(pDX, IDC_CB_TERRAIN_IMG, combox_img_sample_);
  DDX_Control(pDX, IDC_IMG_TERRAIN, terrain_img_);
}


BEGIN_MESSAGE_MAP(TerrainPropertiesDlg, CDialogEx)
  ON_BN_CLICKED(IDC_BTN_BROWERS, &TerrainPropertiesDlg::OnBrowers)
  ON_BN_CLICKED(IDC_RAD_SAMPLE, &TerrainPropertiesDlg::OnRadSampleClicked)
  ON_BN_CLICKED(IDC_RAD_CUSTOM, &TerrainPropertiesDlg::OnRadCustomClicked)
  	ON_CBN_SELENDOK(IDC_CB_TERRAIN_IMG, SelectItemCombox)
END_MESSAGE_MAP()


BOOL TerrainPropertiesDlg::OnInitDialog()
{
  CDialogEx::OnInitDialog();
  height_ = 20;
  CString strHeight;
  strHeight.Format(_T("%f"), height_);
  terrain_offset_height_.SetWindowText(strHeight);


  rad_custom_file_ = 0;
  rad_sample_file_ = 1;
  btn_browers.EnableWindow(FALSE);
  terrain_img_file_.EnableWindow(FALSE);

  if (rad_sample_file_ == 1)
  {
    CString terrain_folder_path = GetPathTerrainFolder() + _T("*.bmp");
    std::string terrain_path = CStringA(terrain_folder_path);
    std::vector<std::string> list_files = FileWrk::FileWork::ListFileInFolder(terrain_path);
    if (list_files.empty())
    {
      MessageBox(_T("TerrainImage is not exist"));
    }
    else
    {
      for (int i = 0; i < list_files.size(); i++)
      {
        CA2T str_sam(list_files.at(i).c_str());
        combox_img_sample_.AddString(str_sam);
      }
      combox_img_sample_.SetCurSel(2);

       file_img_ = GetPathTerrainFolder();
       file_img_ += list_files.at(2).c_str();
       LoadBitmapSample(2);
    }
  }


  UpdateData(FALSE);
  return TRUE;
}

void TerrainPropertiesDlg::LoadBitmapSample(unsigned int sam_type) {
  switch (sam_type) {
  case 0 :
    {
      cbitmap_.Detach();
      cbitmap_.LoadBitmap(IDB_BM_TER_1);
      terrain_img_.SetBitmap((HBITMAP)cbitmap_);
      break;
    }
  case 1: 
    {
      cbitmap_.Detach();
      cbitmap_.LoadBitmap(IDB_BM_TER_2);
      terrain_img_.SetBitmap((HBITMAP)cbitmap_);
      break;

    }
  case 2:
    {
      cbitmap_.Detach();
      cbitmap_.LoadBitmap(IDB_BM_TER_3);
      terrain_img_.SetBitmap((HBITMAP)cbitmap_);
      break;

    }
  }
}


void TerrainPropertiesDlg::OnOK()
{
  CDialogEx::OnOK();

  if (rad_custom_file_)
  {
      terrain_img_file_.GetWindowText(file_img_);
  }
  CString str_value;
  terrain_offset_height_.GetWindowText(str_value);
  height_ = _ttof(str_value);

}
// TerrainPropertiesDlg message handlers

void TerrainPropertiesDlg::OnBrowers()
{
  CFileDialog dlg(TRUE, L"", L"",
                  OFN_HIDEREADONLY | OFN_FILEMUSTEXIST,
                  _T("Bitmap File (*.bmp)|*.bmp||"));
  CString file_name_stl = L"";
  // Get file name 
  if (IDOK == dlg.DoModal()) 
  {
    file_img_ = dlg.GetPathName();
    terrain_img_file_.SetWindowText(file_img_);
  }
}

void TerrainPropertiesDlg::OnRadSampleClicked()
{
  rad_sample_file_ = 1;
  rad_custom_file_ = 0;
  btn_browers.EnableWindow(FALSE);
  terrain_img_.EnableWindow(FALSE);
  combox_img_sample_.EnableWindow(TRUE);
  UpdateData(FALSE);
}

void TerrainPropertiesDlg::OnRadCustomClicked()
{
  rad_sample_file_ = 0;
  rad_custom_file_ = 1;
  btn_browers.EnableWindow(TRUE);
  terrain_img_.EnableWindow(TRUE);
  combox_img_sample_.EnableWindow(FALSE);
  UpdateData(FALSE);
}

CString TerrainPropertiesDlg::GetPathTerrainFolder()
{
  CString terrain_folder_path = Base::GetPathModule();
  terrain_folder_path += _T("\\TerrainImage\\");
  return terrain_folder_path;
}

void TerrainPropertiesDlg::SelectItemCombox()
{
  int current_index = combox_img_sample_.GetCurSel();
  LoadBitmapSample(current_index);
  CString file_name;
  combox_img_sample_.GetLBText(current_index, file_name);

  file_img_ = GetPathTerrainFolder();
  file_img_ += file_name;
}