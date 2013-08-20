// InforBar.cpp : implementation file
//

#include "stdafx.h"
#include "Cad_Show.h"
#include "InforBar.h"
#include "MainFrm.h"
#include "Cad_Show.h"

// InforBar

IMPLEMENT_DYNCREATE(InfoBar, CFormView)

InfoBar::InfoBar()
	: CFormView(InfoBar::IDD)
  , axis_x_angle_(_T(""))
  , axis_y_angle_(_T(""))
  , axis_z_angle_(_T(""))
{

}

InfoBar::~InfoBar()
{
}

void InfoBar::DoDataExchange(CDataExchange* pDX)
{
  CFormView::DoDataExchange(pDX);
  DDX_Text(pDX, IDC_EDIT_EYE_X, eye_x_);
  DDX_Text(pDX, IDC_EDIT_EYE_Y, eye_x_);
  DDX_Text(pDX, IDC_EDIT_EYE_Z, eye_z_);

  DDX_Text(pDX, IDC_EDIT_CENTER_X, cen_x_);
  DDX_Text(pDX, IDC_EDIT_CENTER_Y, cen_x_);
  DDX_Text(pDX, IDC_EDIT_CENTER_Z, cen_z_);

  DDX_Text(pDX, IDC_EDIT_UP_X, up_x_);
  DDX_Text(pDX, IDC_EDIT_UP_Y, up_x_);
  DDX_Text(pDX, IDC_EDIT_UP_Z, up_z_);

  DDX_Text(pDX, IDC_EDT_ANGLE_X, axis_x_angle_);
  DDX_Text(pDX, IDC_EDT_ANGLE_Y, axis_y_angle_);
  DDX_Text(pDX, IDC_EDT_ANGLE_Z, axis_z_angle_);
}

BEGIN_MESSAGE_MAP(InfoBar, CFormView)
  ON_WM_SIZE()
  ON_EN_CHANGE(IDC_EDIT_EYE_X, InfoBar::OnEditEyeX)
END_MESSAGE_MAP()


// InforBar diagnostics

#ifdef _DEBUG
void InfoBar::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void InfoBar::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// InforBar message handlers


void InfoBar::OnInitialUpdate() {
  CFormView::OnInitialUpdate();
  EnableScrollBarCtrl(SB_BOTH, FALSE);
}

void InfoBar::OnSize(UINT type, int cx, int cy) {
  EnableScrollBarCtrl(SB_BOTH, FALSE);
  CFormView::OnSize(type, cx, cy);
}

void InfoBar::OnUpdateAngleAxis(GLfloat ax, GLfloat ay, GLfloat az) {
  CString str_ax = _T("");
  CString str_ay = _T("");
  CString str_az = _T("");
  str_ax.Format(_T("%f"), ax);
  str_ay.Format(_T("%f"), ay);
  str_az.Format(_T("%f"), az);

  axis_x_angle_ = str_ax;
  axis_y_angle_ = str_ay;
  axis_z_angle_ = str_az;
  UpdateData(FALSE);
}

void InfoBar::OnUpdateValueCam( GLfloat eye_x, GLfloat eye_y, GLfloat eye_z,
  GLfloat cen_x, GLfloat cen_y, GLfloat cen_z,
  GLfloat up_x, GLfloat up_y, GLfloat up_z) {
  
  eye_x_.Format(_T("%f"), eye_x);
  eye_y_.Format(_T("%f"), eye_y);
  eye_z_.Format(_T("%f"), eye_z);

  cen_x_.Format(_T("%f"), cen_x);
  cen_y_.Format(_T("%f"), cen_y);
  cen_z_.Format(_T("%f"), cen_z);

  up_x_.Format(_T("%f"), up_x);
  up_y_.Format(_T("%f"), up_y);
  up_z_.Format(_T("%f"), up_z);
  UpdateData(FALSE);
}


CCad_ShowView* InfoBar::GetCadShowView() {
  CCad_ShowApp *pApp= (CCad_ShowApp*)AfxGetApp();
  CMainFrame *pMainFrame = (CMainFrame*)pApp->m_pMainWnd;
  CCad_ShowView *pView = reinterpret_cast<CCad_ShowView*>(pMainFrame->info_splitter_.GetPane(0, 0));
  return pView;
}

void InfoBar::OnEditEyeX() {
  //UpdateData(TRUE);
  CString str = eye_x_;
  float value = _ttof(str);
  GetCadShowView()->SetEyeXCam(value);
}

void InfoBar::OnEditEyeY() {
  //UpdateData(TRUE);
  CString str = eye_y_;
  float value = _ttof(str);
  GetCadShowView()->SetEyeYCam(value);
}

void InfoBar::OnEditEyeZ() {
  //UpdateData(TRUE);
  CString str = eye_z_;
  float value = _ttof(str);
  GetCadShowView()->SetEyeZCam(value);
}

void InfoBar::OnEditCenX() {
  //UpdateData(TRUE);
  CString str = cen_x_;
  float value = _ttof(str);
  GetCadShowView()->SetCenXCam(value);
}

void InfoBar::OnEditCenY() {
  //UpdateData(TRUE);
  CString str = cen_y_;
  float value = _ttof(str);
  GetCadShowView()->SetCenYCam(value);
}

void InfoBar::OnEditCenZ() {
 // UpdateData(TRUE);
  CString str = cen_z_;
  float value = _ttof(str);
  GetCadShowView()->SetCenZCam(value);
}

void InfoBar::OnEditUpX() {
 // UpdateData(TRUE);
  CString str = up_x_;
  float value = _ttof(str);
  GetCadShowView()->SetUpXCam(value);
}

void InfoBar::OnEditUpY() {
  //UpdateData(TRUE);
  CString str = up_y_;
  float value = _ttof(str);
  GetCadShowView()->SetUpYCam(value);
}
void InfoBar::OnEditUpZ() {
  //UpdateData(TRUE);
  CString str = up_z_;
  float value = _ttof(str);
  GetCadShowView()->SetUpZCam(value);
}


