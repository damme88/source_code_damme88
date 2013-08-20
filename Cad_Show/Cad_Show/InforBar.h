#pragma once



// InforBar form view

#include "stdafx.h"

class CCad_ShowView;
class CCad_ShowDoc;

class InfoBar : public CFormView
{
	DECLARE_DYNCREATE(InfoBar)

protected:
	InfoBar();           // protected constructor used by dynamic creation
	virtual ~InfoBar();

public:
	enum { IDD = IDD_INFORBAR };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

  void OnUpdateAngleAxis(GLfloat ax, GLfloat ay, GLfloat az);
  void OnUpdateValueCam(GLfloat eye_x, GLfloat eye_y, GLfloat eye_z,
                        GLfloat cen_x, GLfloat cen_y, GLfloat cen_z,
                        GLfloat up_x, GLfloat up_y, GLfloat up_z);
  CCad_ShowView* GetCadShowView();
protected:
  virtual void OnInitialUpdate();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  virtual void OnSize(UINT type, int cx, int cy);

  afx_msg void OnEditEyeX();
  afx_msg void OnEditEyeY();
  afx_msg void OnEditEyeZ();

  afx_msg void OnEditCenX();
  afx_msg void OnEditCenY();
  afx_msg void OnEditCenZ();

  afx_msg void OnEditUpX();
  afx_msg void OnEditUpY();
  afx_msg void OnEditUpZ();
	DECLARE_MESSAGE_MAP()
protected:

  CString eye_x_;
  CString eye_y_;
  CString eye_z_;

  CString cen_x_;
  CString cen_y_;
  CString cen_z_;
  
  CString up_x_;
  CString up_y_;
  CString up_z_;
  CString axis_x_angle_;
  CString axis_y_angle_;
  CString axis_z_angle_;
};


