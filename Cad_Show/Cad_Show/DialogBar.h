#pragma once
#include "afxwin.h"
#include "afxcmn.h"



// DialogBar form view
class CCad_ShowDoc;
class CCad_ShowView;
class DialogBar : public CFormView
{
	DECLARE_DYNCREATE(DialogBar)

protected:
	DialogBar();           // protected constructor used by dynamic creation
	virtual ~DialogBar();

public:
	enum { IDD = IDD_DIALOGBAR };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
// add new variable and function 
private:
  CButton solid_radio_button_;
  CButton checkbox_rotate_;
  bool is_check_rotate_;
  CSliderCtrl speed_rotate_;
  CStatic background_color_;

  // variable for checkbox rotate
  bool is_rot_x_;
  bool is_rot_y_;
  bool is_rot_z_;

private:
  CButton cb_rot_x_;
  CButton cb_rot_y_;
  CButton cb_rot_z_;
public:
  CDialogBar *GetDocument();
  CCad_ShowView *GetCadShowView();
  virtual void OnInitialUpdate();
  void SetStatusSpeedBar();
protected:
  afx_msg void OnSize(UINT nType, int cx, int cy);
  afx_msg void OnPaint();
  afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
  afx_msg void OnBnClickedRadioLineCad();
  afx_msg void OnBnClickedRadioWireFrameCad();
  afx_msg void OnBnClickedRadioSolidCad();
  afx_msg void OnBnClickeCheckboxRotation();
  afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
public:
  afx_msg void OnBnClickedRotateX();
  afx_msg void OnBnClickedRotateY();
  afx_msg void OnBnClickedRotateZ();

};


