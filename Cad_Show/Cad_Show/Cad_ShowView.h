﻿
// Cad_ShowView.h : interface of the CCad_ShowView class
//

#pragma once
#include "DialogBar.h"
class CCad_ShowView : public CView
{
protected: // create from serialization only
	CCad_ShowView();
	DECLARE_DYNCREATE(CCad_ShowView)

// Attributes
public:
	CCad_ShowDoc* GetDocument() const;

// Operations
private:
  HGLRC m_hRC; //Rendering Context
  CDC* m_pDC; //Device Context
// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

public:
  int OnCreate(LPCREATESTRUCT lpCreateStruct);
  BOOL InitializeOpenGL();
  BOOL SetupPixelFormat();
  void OnSize(UINT nType, int cx, int cy);
  void RenderScene();
  BOOL OnEraseBkgnd(CDC* pDC);
  void OnDestroy();

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CCad_ShowView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
  afx_msg void OnKeyDown(UINT nchar , UINT nRepCnt, UINT nFlas);
	DECLARE_MESSAGE_MAP()

private:
  //variable for rotatef and zoom for cad object
  GLfloat angle_x_;
	GLfloat angle_y_;
  GLfloat angle_x_cad_;
  GLfloat angle_y_cad_;
  GLfloat angle_z_cad_;
  GLfloat value_zoom_;
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
  // varialbe for speed rotate
  float speed_rotate_;
  bool is_check_rotate_;

  // variable status checbox rotate on DialogBar
  bool is_rot_x_;
  bool is_rot_y_;
  bool is_rot_z_;

  bool enable_big_coordinate_;
  bool is_check_coordiante_button_;
public:
  void IsRotX(bool val_x) {is_rot_x_ = val_x; InvalidateRect(NULL, FALSE);}
  void IsRotY(bool val_y) {is_rot_y_ = val_y; InvalidateRect(NULL, FALSE);}
  void IsRotZ(bool val_z) {is_rot_z_ = val_z; InvalidateRect(NULL, FALSE);}
  
public:
  enum ModelCad {SOLID_MODE_CAD, WIRE_FRAME_MODE_CAD, POINT_MODE_CAD};
public: 
  void OnMouseMove(UINT nFlags, CPoint point);
  BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
  void OnRButtonDown(UINT nFlags, CPoint point);
  void BuildAxisesList();  // draw sub coordinate
  void OnDrawCoordinateBig();  // draw big coordinate
  void EnableShowBigCoordinate(); 
  void SetCheckBigCoordinate(CCmdUI * cmd);
  void PrintAxisLabel(const char* str);
  void SetUpLight();
  void DisableSetupLigting();
  // functions for drawing
  void DrawCad();
  void PrepareAxisLabel();
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
public:
  void OnHandleViewButton(UINT nID); 
  void OnHandleMoveButton(UINT nID);
  void OnHandleRotateButton(UINT nID);
  void OnHandleResetCad();
};

#ifndef _DEBUG  // debug version in Cad_ShowView.cpp
inline CCad_ShowDoc* CCad_ShowView::GetDocument() const
   { return reinterpret_cast<CCad_ShowDoc*>(m_pDocument); }
#endif

