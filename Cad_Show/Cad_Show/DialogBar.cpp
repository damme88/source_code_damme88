// DialogBar.cpp : implementation file
//

#include "stdafx.h"
#include "Cad_Show.h"
#include "DialogBar.h"
#include "MainFrm.h"
#include "Cad_ShowView.h"

// DialogBar

IMPLEMENT_DYNCREATE(DialogBar, CFormView)

DialogBar::DialogBar()
	: CFormView(DialogBar::IDD)
{
  is_check_rotate_ = false;
}

DialogBar::~DialogBar()
{
}

void DialogBar::DoDataExchange(CDataExchange* pDX)
{
  CFormView::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_RADIO_SOLID_CAD, solid_radio_button_);
  DDX_Control(pDX, IDC_BACKGROUND_COLOR, background_color_);
  DDX_Control(pDX, IDC_ROTATE, checkbox_rotate_);
  DDX_Control(pDX, IDC_SPEED_ROTATE, speed_rotate_);
}

BEGIN_MESSAGE_MAP(DialogBar, CFormView)
  ON_BN_CLICKED(IDC_RADIO_WIRE_FRAME_CAD, &DialogBar::OnBnClickedRadioWireFrameCad)
  ON_BN_CLICKED(IDC_RADIO_SOLID_CAD, &DialogBar::OnBnClickedRadioSolidCad)
  ON_BN_CLICKED(IDC_RADIO_LINE_CAD, &DialogBar::OnBnClickedRadioLineCad)
  ON_BN_CLICKED(IDC_ROTATE, &DialogBar::OnBnClickeCheckboxRotation)
  ON_WM_PAINT()
  ON_WM_LBUTTONUP()
	ON_WM_HSCROLL()
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

  solid_radio_button_.SetCheck(BST_CHECKED);
  // set checkbox is not checked at first time
  checkbox_rotate_.SetCheck(is_check_rotate_ ? 1 : 0);
  speed_rotate_.EnableWindow(is_check_rotate_);
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


CView *DialogBar::GetCadShowView() {
  CCad_ShowApp *pApp= (CCad_ShowApp*)AfxGetApp();
  CMainFrame *pMainFrame = (CMainFrame*)pApp->m_pMainWnd;
  CView *pView = (CView*)pMainFrame->m_wndSplitter.GetPane(0, 1);
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
    speed_rotate_.EnableWindow(is_check_rotate_);
    SetStatusSpeedBar();
    pView->SetTimer(1, 10, NULL);
  } else {
    speed_rotate_.EnableWindow(is_check_rotate_);
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