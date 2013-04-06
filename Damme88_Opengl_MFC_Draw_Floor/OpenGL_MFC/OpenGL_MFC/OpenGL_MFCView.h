
// OpenGL_MFCView.h : interface of the COpenGL_MFCView class
//

#pragma once
#include "Struct.h"
class COpenGL_MFCView : public CView
{
protected: // create from serialization only
	COpenGL_MFCView();
	DECLARE_DYNCREATE(COpenGL_MFCView)

// Attributes
public:
	COpenGL_MFCDoc* GetDocument() const;

// Operation
private:
  HGLRC m_hRC; //Rendering Context
  CDC* m_pDC; //Device Context

public:
  int OnCreate(LPCREATESTRUCT lpCreateStruct);
  BOOL InitializeOpenGL();
  BOOL SetupPixelFormat();
  void OnSize(UINT nType, int cx, int cy);
  void RenderScene();
  BOOL OnEraseBkgnd(CDC* pDC);
  CString GetMoudlePath();
  char * CStringToChar(CString str);
  void OnDestroy();

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

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
  afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
  afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
  afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
  afx_msg void OnMouseMove(UINT nFlags, CPoint point);
  afx_msg BOOL OnMouseWheel(UINT nFlags, short zDetal, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()

public:
  bool Init();
  void DrawReflection();
  void DrawFloor();
  void SetupProjection(int width, int height);

private:
  CPoint mouse_down_point_;
  GLfloat x_position_;
  GLfloat y_position_;
  GLfloat value_zoom_;
  GLfloat m_angle_x_;
  GLfloat m_angle_y_;
	int m_windowWidth;
	int m_windowHeight;

  bool m_useList;
  GLuint m_list;
  GLuint m_brickTexture;

  vector_t  *m_positions;
  vector_t  *m_texCoords;
};

#ifndef _DEBUG  // debug version in OpenGL_MFCView.cpp
inline COpenGL_MFCDoc* COpenGL_MFCView::GetDocument() const
   { return reinterpret_cast<COpenGL_MFCDoc*>(m_pDocument); }
#endif

