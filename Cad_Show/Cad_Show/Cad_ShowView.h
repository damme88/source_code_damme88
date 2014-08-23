﻿
// Cad_ShowView.h : interface of the CCad_ShowView class
//

#pragma once
#include "DialogBar.h"
//#include "InforBar.h"

const double VALUE_AXIS = 10000.0;

class CCad_ShowView : public CView
{
public: // create from serialization only
	CCad_ShowView();
	DECLARE_DYNCREATE(CCad_ShowView)

// Attributes
	CCad_ShowDoc* GetDocument() const;

// Overrides
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

  int OnCreate(LPCREATESTRUCT lpCreateStruct);
  BOOL InitializeOpenGL();
  BOOL SetupPixelFormat();
  void OnSize(UINT nType, int cx, int cy);
  void RenderScene();
  BOOL OnEraseBkgnd(CDC* pDC);
  void OnDestroy();

// Implementation
	virtual ~CCad_ShowView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

  enum ModelCad {SOLID_MODE_CAD, WIRE_FRAME_MODE_CAD, POINT_MODE_CAD};
	enum SampleStyle {
		kTearpot = 0,
		kCube = 1,
		kSphere = 2,
		kTorus = 3,
		kCone = 4,
		kTetrahedron = 5,
		kIcosahedron = 6,
		kDodecahedron = 7,
		kOctahedron = 8,
	};
  void IsRotX(bool val_x) {is_rot_x_ = val_x; InvalidateRect(NULL, FALSE);}
  void IsRotY(bool val_y) {is_rot_y_ = val_y; InvalidateRect(NULL, FALSE);}
  void IsRotZ(bool val_z) {is_rot_z_ = val_z; InvalidateRect(NULL, FALSE);}

  void OnMouseMove(UINT nFlags, CPoint point);
  BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
  void OnRButtonDown(UINT nFlags, CPoint point);
  void BuildAxisesList();  // draw sub coordinate
  void RenderSmallCoordinate();
  void OnDrawCoordinateBig();  // draw big coordinate
  void EnableShowBigCoordinate(); 
  void SetCheckBigCoordinate(CCmdUI * cmd);
  void SetUpLight();
  void DisableSetupLigting();
  // functions for drawing
  void DrawCad();
  void OnMButtonDown(UINT nFlags, CPoint point);
  void OnMButtonUp(UINT nFlags, CPoint point);
  void SetModeCad(unsigned int mode_cad) {mode_cad_ = mode_cad;}
  void SetColorForBackGround(float red_value, float green_value, float blue_value);
  void DeleteCad();
  void SetSpeedRotate(float speed_value) {speed_rotate_ = speed_value;}
  void OnAnimation();
  void OnTimer(UINT_PTR nIDEvent);
  void SetRotateForCad();
  void SetStateCheckboxRotate(bool state) {is_check_rotate_ = state; InvalidateRect(NULL, FALSE);}

  void OnHandleViewButton(UINT nID); 
  void OnHandleMoveButton(UINT nID);
  void OnHandleRotateButton(UINT nID);
  void OnHandleResetCad();
  void DrawStringAt(double x, double y, double z, char* s);
  void CreateOpenGLFont();
  void UpdateInfoToOutput();
  void SetFormViewHandle(DialogBar * form_view) {form_view_ = form_view;}

  void SetEyeXCam(double eye_x) {eye_x_ = eye_x; InvalidateRect(NULL, FALSE);}
  void SetEyeYCam(double eye_y) {eye_y_ = eye_y; InvalidateRect(NULL, FALSE);}
  void SetEyeZCam(double eye_z) {eye_z_ = eye_z; InvalidateRect(NULL, FALSE);}

  void SetCenXCam(double cen_x) {cen_x_ = cen_x; InvalidateRect(NULL, FALSE);}
  void SetCenYCam(double cen_y) {cen_y_ = cen_y; InvalidateRect(NULL, FALSE);}
  void SetCenZCam(double cen_z) {cen_z_ = cen_z; InvalidateRect(NULL, FALSE);}

  void SetUpXCam(double up_x) {up_x_ = up_x; InvalidateRect(NULL, FALSE);}
  void SetUpYCam(double up_y) {up_y_ = up_y; InvalidateRect(NULL, FALSE);}
  void SetUpZCam(double up_z) {up_z_ = up_z; InvalidateRect(NULL, FALSE);}

  void SetViewFrustum();
  void CalculateRotatefAngle(CPoint point);
	void ViewFullscreen();
	void DrawSampleOpengl();
	void set_is_draw_sample(bool is_draw_sample) {is_draw_sample_ = is_draw_sample; InvalidateRect(NULL, FALSE);}
	void set_current_sample(unsigned int st) {sample_style_ = st; InvalidateRect(NULL, FALSE);}
// Generated message map functions
	GLfloat* GetAmbien() const {return pAmbien_;}
	GLfloat* GetSpecular() const {return pSpecular_;}
	GLfloat* GetDiff()const {return pDiff_;}
	GLfloat GetShininess() const {return shininess_;}
	void SetAmbien(GLfloat* pAmbien) {pAmbien_ = pAmbien; InvalidateRect(NULL, FALSE);}
	void SetSpecular(GLfloat* pSpecular) {pSpecular_ = pSpecular; InvalidateRect(NULL, FALSE);}
	void SetDiff(GLfloat* pDiff) {pDiff_ = pDiff; InvalidateRect(NULL, FALSE);}
	void SetShininess(GLfloat shininess) {shininess_ = shininess; InvalidateRect(NULL, FALSE);}
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
  afx_msg void OnKeyDown(UINT nchar , UINT nRepCnt, UINT nFlas);
	DECLARE_MESSAGE_MAP()

private:
	bool is_draw_sample_;
	unsigned sample_style_;
  HGLRC m_hRC; //Rendering Context
  CDC* m_pDC; //Device Context
  GLuint m_editCLTip;
  GLuint m_textTip;

  GLfloat rendering_rate_;
  int cx_; // size of window
  int cy_; 
  //variable for rotate and zoom for cad object
  GLfloat angle_x_;
	GLfloat angle_y_;
  GLfloat angle_z_;

  GLfloat angle_x_big_cdn_;
  GLfloat angle_y_big_cdn_;
  GLfloat angle_z_big_cdn_;

  GLfloat angle_x_cad_;
  GLfloat angle_y_cad_;
  GLfloat angle_z_cad_;
  GLfloat m_scaling;
  CPoint mouse_down_point_;

  GLfloat x_position_ ;
	GLfloat y_position_ ;
  int     m_nFontOffset;
  GLuint  m_nAxisesList;

  //Variable for MButtonDown
  BOOL middle_down_;
  CPoint middle_down_pos_;
  HCURSOR cursor_;
  HCURSOR middle_down_cursor_;

  // Variable for rotate button
  BOOL rotate_left_;
  BOOL rotate_righit_;
  unsigned int mode_cad_;
  // Variable for setting background color
  float red_color_;
  float green_color_;
  float blue_color_;
  // variable for speed rotate
  float speed_rotate_;
  bool is_check_rotate_;

  // variable status checkbox rotate on DialogBar
  bool is_rot_x_;
  bool is_rot_y_;
  bool is_rot_z_;

  bool enable_big_coordinate_;
  bool is_check_coordiante_button_;

  DialogBar *form_view_;

  double eye_x_;
  double eye_y_;
  double eye_z_;
  double lx_;
  double ly_;
  double lz_;
  double cen_x_;
  double cen_y_;
  double cen_z_;

  double up_x_;
  double up_y_;
  double up_z_;

  GLdouble theta_;  // angle x
  GLdouble phi_;    // angle y

	GLdouble xPos_;
	GLdouble yPos_;
	GLdouble zPos_;

	GLfloat *pAmbien_;
	GLfloat *pSpecular_;
	GLfloat *pDiff_;
	GLfloat  shininess_;
};

#ifndef _DEBUG  // debug version in Cad_ShowView.cpp
inline CCad_ShowDoc* CCad_ShowView::GetDocument() const
   { return reinterpret_cast<CCad_ShowDoc*>(m_pDocument); }
#endif

