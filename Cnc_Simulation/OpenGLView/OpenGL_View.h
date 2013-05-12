#pragma once
#include <gl\glut.h>
#include <windows.h>
// OpenGL_View view

class AFX_EXT_CLASS OpenGL_View : public CView
{
	DECLARE_DYNCREATE(OpenGL_View)

protected:
	OpenGL_View();           // protected constructor used by dynamic creation
	virtual ~OpenGL_View();

public:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
  HGLRC   m_hRC;
  CDC* m_pDC; //Device Context
public:
  BOOL SetWindowPixelFormat();
  BOOL InitializeOpenGL();
  BOOL OnEraseBkgnd(CDC* pDC);
  void RenderScene();
protected:
  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
	DECLARE_MESSAGE_MAP()
  afx_msg int OnCreate(LPCREATESTRUCT lpcs);
  afx_msg void OnDestroy();
  afx_msg void OnSize(UINT nType, int cx, int cy);
};


