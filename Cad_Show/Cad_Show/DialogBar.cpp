// DialogBar.cpp : implementation file
//

#include "stdafx.h"
#include "Cad_Show.h"
#include "DialogBar.h"
#include "MainFrm.h"
#include "Cad_ShowView.h"
#include "SampleOpengl.h"
#include "DlgMaterialLight.h"
// DialogBar

IMPLEMENT_DYNCREATE(DialogBar, CFormView)

DialogBar::DialogBar()
	: CFormView(DialogBar::IDD)
{
  is_check_rotate_ = false;
  is_rot_x_ = false;
  is_rot_y_ = false;
  is_rot_z_ = false;
}

DialogBar::~DialogBar()
{
		pAmbien_ = NULL;
		pSpecular_ = NULL;
		pDiff_ = NULL;
}

void DialogBar::DoDataExchange(CDataExchange* pDX)
{
  CFormView::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_RADIO_SOLID_CAD, solid_radio_button_);
	DDX_Control(pDX, IDC_RADIO_WIRE_FRAME_CAD, wire_radio_button_);
	DDX_Control(pDX, IDC_RADIO_POINT_CAD, point_radio_button_);
  DDX_Control(pDX, IDC_BACKGROUND_COLOR, background_color_);
  DDX_Control(pDX, IDC_ROTATE, checkbox_rotate_);
  DDX_Control(pDX, IDC_SPEED_ROTATE, speed_rotate_);
  DDX_Control(pDX, IDC_ROTATE_X, cb_rot_x_);
  DDX_Control(pDX, IDC_ROTATE_Y, cb_rot_y_);
  DDX_Control(pDX, IDC_ROTATE_Z, cb_rot_z_);
}

BEGIN_MESSAGE_MAP(DialogBar, CFormView)
  ON_BN_CLICKED(IDC_RADIO_WIRE_FRAME_CAD, &DialogBar::OnBnClickedRadioWireFrameCad)
  ON_BN_CLICKED(IDC_RADIO_SOLID_CAD, &DialogBar::OnBnClickedRadioSolidCad)
  ON_BN_CLICKED(IDC_RADIO_POINT_CAD, &DialogBar::OnBnClickedRadioLineCad)
  ON_BN_CLICKED(IDC_ROTATE, &DialogBar::OnBnClickeCheckboxRotation)
  ON_WM_PAINT()
  ON_WM_LBUTTONUP()
  ON_WM_SIZE()
	ON_WM_HSCROLL()
  ON_BN_CLICKED(IDC_ROTATE_X, &DialogBar::OnBnClickedRotateX)
  ON_BN_CLICKED(IDC_ROTATE_Y, &DialogBar::OnBnClickedRotateY)
  ON_BN_CLICKED(IDC_ROTATE_Z, &DialogBar::OnBnClickedRotateZ)
	ON_BN_CLICKED(IDC_BTN_SAMPLE_OPENGL, &DialogBar::OnBnClickedSample)
	ON_BN_CLICKED(IDC_BTN_MAT_LIGHT, &DialogBar::ShowMaterialLight)
END_MESSAGE_MAP()


// DialogBar diagnostics

#ifdef _DEBUG
void DialogBar::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void DialogBar::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// DialogBar message handlers
void DialogBar::OnInitialUpdate() {
  CFormView::OnInitialUpdate();
  cb_rot_x_.SetCheck(0);
  cb_rot_y_.SetCheck(0);
  cb_rot_z_.SetCheck(0);
  GetCadShowView()->IsRotX(is_rot_x_);
  GetCadShowView()->IsRotY(is_rot_y_);
  GetCadShowView()->IsRotZ(is_rot_z_);
  solid_radio_button_.SetCheck(BST_CHECKED);
	wire_radio_button_.SetCheck(BST_UNCHECKED);
	point_radio_button_.SetCheck(BST_UNCHECKED);

  // set check box is not checked at first time
  checkbox_rotate_.SetCheck(is_check_rotate_ ? 1 : 0);
  speed_rotate_.EnableWindow(is_check_rotate_);
  cb_rot_x_.EnableWindow(is_check_rotate_);
  cb_rot_y_.EnableWindow(is_check_rotate_);
  cb_rot_z_.EnableWindow(is_check_rotate_);
  is_rot_x_ = is_rot_y_ = is_rot_z_ = is_check_rotate_;
  EnableScrollBarCtrl(SB_BOTH, FALSE);
}

void DialogBar::OnSize(UINT nType, int cx, int cy) {
  EnableScrollBarCtrl(SB_BOTH, FALSE);
}


void DialogBar::OnPaint() {
  CPaintDC dc(this);
  CCad_ShowApp *pApp = (CCad_ShowApp*)AfxGetApp();

  CRect rect;
  background_color_.GetWindowRect(&rect);
  ScreenToClient(&rect);
  CBrush BrushBack(pApp->option_color_glback);
  dc.FillRect(&rect, &BrushBack);

}

void DialogBar::OnLButtonUp(UINT nFlags, CPoint point) {
  float red_color = 0.0f;
  float green_color = 0.0f;
  float blue_color = 0.0f;
  CRect rect;
  CCad_ShowApp *pApp = (CCad_ShowApp*)AfxGetApp();
  // option custom color for background
  background_color_.GetWindowRect(&rect);
  ScreenToClient(&rect);
  if (rect.PtInRect(point)) {
    CColorDialog dlg(pApp->option_color_glback);
    if (dlg.DoModal() == IDOK) {
      pApp->option_color_glback = dlg.GetColor();
      CCad_ShowView *pView = (CCad_ShowView*)GetCadShowView();
      red_color = GetRValue(pApp->option_color_glback)/255.0F;
      green_color = GetGValue(pApp->option_color_glback)/255.0f;
      blue_color = GetBValue(pApp->option_color_glback)/255.0f;
      pView->SetColorForBackGround(red_color, green_color, blue_color);
      this->InvalidateRect(&rect,FALSE);
			pView->InvalidateRect(NULL,FALSE); 
    }
  }
  CFormView::OnLButtonUp(nFlags, point);
}


CCad_ShowView *DialogBar::GetCadShowView() {
  CCad_ShowApp *pApp= (CCad_ShowApp*)AfxGetApp();
  CMainFrame *pMainFrame = (CMainFrame*)pApp->m_pMainWnd;
  CCad_ShowView *pView = reinterpret_cast<CCad_ShowView*>(pMainFrame->m_wndSplitter.GetPane(0, 1));
  return pView;
}

void DialogBar::OnBnClickedRadioWireFrameCad() {
  CCad_ShowView *pCadView = reinterpret_cast<CCad_ShowView*>(this->GetCadShowView());
  pCadView->SetModeCad(CCad_ShowView::WIRE_FRAME_MODE_CAD);
  pCadView->InvalidateRect(NULL, FALSE);
}


void DialogBar::OnBnClickedRadioSolidCad() {
  CCad_ShowView *pCadView = reinterpret_cast<CCad_ShowView*>(this->GetCadShowView());
  pCadView->SetModeCad(CCad_ShowView::SOLID_MODE_CAD);
  pCadView->InvalidateRect(NULL, FALSE);
}

void DialogBar::OnBnClickedRadioLineCad() {
  CCad_ShowView *pCadView = reinterpret_cast<CCad_ShowView*>(this->GetCadShowView());
  pCadView->SetModeCad(CCad_ShowView::POINT_MODE_CAD);
  pCadView->InvalidateRect(NULL, FALSE);
}

void DialogBar::OnBnClickeCheckboxRotation() {
  CCad_ShowView *pView = reinterpret_cast<CCad_ShowView*>(GetCadShowView());
  is_check_rotate_ = !is_check_rotate_;
  if (is_check_rotate_) {
    cb_rot_x_.EnableWindow(true);
    cb_rot_y_.EnableWindow(true);
    cb_rot_z_.EnableWindow(true);
    cb_rot_x_.SetCheck(0);
    cb_rot_y_.SetCheck(0);
    cb_rot_z_.SetCheck(1);
    is_rot_x_ = false;
    is_rot_y_ = false;
    is_rot_z_ = true;
    GetCadShowView()->IsRotX(is_rot_x_);
    GetCadShowView()->IsRotY(is_rot_y_);
    GetCadShowView()->IsRotZ(is_rot_z_);
    speed_rotate_.EnableWindow(true);
    pView->SetStateCheckboxRotate(TRUE);
    SetStatusSpeedBar();
    pView->SetTimer(1, 10, NULL); // use when rotate by OnTimer
  } else {
    cb_rot_x_.SetCheck(0);
    cb_rot_y_.SetCheck(0);
    cb_rot_z_.SetCheck(0);
    cb_rot_x_.EnableWindow(false);
    cb_rot_y_.EnableWindow(false);
    cb_rot_z_.EnableWindow(false);
    pView->SetStateCheckboxRotate(FALSE);
    speed_rotate_.EnableWindow(false);
    pView->KillTimer(1);
  }
}

void DialogBar::SetStatusSpeedBar() {
  speed_rotate_.SetRange(1, 10, TRUE);
  speed_rotate_.SetPos(1);
  InvalidateRect(NULL, FALSE);
}

void DialogBar::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
  int pos = speed_rotate_.GetPos();
  CCad_ShowView *pView = reinterpret_cast<CCad_ShowView*>(GetCadShowView());
  float speed_value = pos/10.0;
  pView->SetSpeedRotate(speed_value);
  pView->InvalidateRect(NULL, FALSE);
}

void DialogBar::OnBnClickedRotateX()
{
  is_rot_x_ = cb_rot_x_.GetCheck() ? true : false;
  GetCadShowView()->IsRotX(is_rot_x_);
}


void DialogBar::OnBnClickedRotateY()
{
  is_rot_y_ = cb_rot_y_.GetCheck() ? true : false;
  GetCadShowView()->IsRotY(is_rot_y_);
}


void DialogBar::OnBnClickedRotateZ()
{
  is_rot_z_ = cb_rot_z_.GetCheck() ? true : false;
  GetCadShowView()->IsRotZ(is_rot_z_);
}

void DialogBar::OnBnClickedSample() {
  SampleOpengl dlg;
	if(IDOK == dlg.DoModal()) {
		GetCadShowView()->set_is_draw_sample(true);
		unsigned int style = dlg.GetCurrentSample();
		GetCadShowView()->set_current_sample(style);
	}
}

void DialogBar::ShowMaterialLight() {

	pAmbien_ = GetCadShowView()->GetAmbien();
	pSpecular_ = GetCadShowView()->GetSpecular();
	pDiff_ = GetCadShowView()->GetDiff();
	shininess_ = GetCadShowView()->GetShininess();

  DlgMaterialLight dlg(pAmbien_, pSpecular_, pDiff_, shininess_);
	if (dlg.DoModal() == IDOK) {
		pAmbien_ = dlg.GetAmbien();
		pSpecular_ = dlg.GetSpecular();
		pDiff_ = dlg.GetDiffuse();
		shininess_ = dlg.GetShininess();
	  GetCadShowView()->SetAmbien(pAmbien_);
		GetCadShowView()->SetSpecular(pSpecular_);
		GetCadShowView()->SetDiff(pDiff_);
		GetCadShowView()->SetShininess(shininess_);
	}
}