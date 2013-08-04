
// OpenGL_MFCView.h : interface of the COpenGL_MFCView class
//

#pragma once
#include "Resource.h"

#define BITMAP_ID 0x4D42
#define LENGTH_AXIS 100000
#define MAP_LIMIT_X 32
#define MAP_LIMIT_Z 32
#define MAP_SCALE 15.0f
#define PI 3.14


class COpenGL_MFCView : public CView
{
public: // create from serialization only
	COpenGL_MFCView();
	DECLARE_DYNCREATE(COpenGL_MFCView)

// Attributes
public:
	COpenGL_MFCDoc* GetDocument() const;

// Operation
public:
  int OnCreate(LPCREATESTRUCT lpCreateStruct);
  BOOL InitializeOpenGL();
  BOOL SetupPixelFormat();
  void OnSize(UINT nType, int cx, int cy);
  void RenderScene();
  BOOL OnEraseBkgnd(CDC* pDC);
  void OnDestroy();
  void DrawCoordinate();
  void OnEnableLight();
  void OnDisableLight();
  int MakeObject();
  void DrawTerrain();
  void InitTerrain();
// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~COpenGL_MFCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
  afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
  afx_msg void OnMouseMove(UINT nFlags, CPoint point);
  afx_msg BOOL OnMouseWheel(UINT nFlags, short zDetal, CPoint point);
  afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
  afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
  
  //virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	//virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	//virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	DECLARE_MESSAGE_MAP()
private:
  HGLRC m_hRC; //Rendering Context
  CDC* m_pDC; //Device Context
  CPoint mouse_down_point_;
  GLfloat x_position_;
  GLfloat y_position_;

  GLfloat angle_x_;
  GLfloat angle_y_;
  GLfloat angle_z_;

  GLfloat angle_x_ob_;
	GLfloat angle_y_ob_;
  GLfloat angle_z_ob_;
  GLuint listId_;

  GLfloat m_OrthoRangeLeft;
	GLfloat m_OrthoRangeRight;
	GLfloat m_OrthoRangeTop;
	GLfloat m_OrthoRangeBottom;
	GLfloat m_OrthoRangeNear;
	GLfloat m_OrthoRangeFar;

  GLfloat m_scaling;

  // array with three direct which store data to render terrain
  GLfloat data_terrain_[MAP_LIMIT_X][MAP_LIMIT_Z][3];
  unsigned char* image_data_;
  BITMAPINFOHEADER	bitmap_info_header_;
};

#ifndef _DEBUG  // debug version in OpenGL_MFCView.cpp
inline COpenGL_MFCDoc* COpenGL_MFCView::GetDocument() const
   { return reinterpret_cast<COpenGL_MFCDoc*>(m_pDocument); }
#endif

