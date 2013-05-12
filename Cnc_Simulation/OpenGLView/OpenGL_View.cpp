// OpenGL_View.cpp : implementation file
//

#include "stdafx.h"
#include "OpenGL_View.h"


// OpenGL_View

IMPLEMENT_DYNCREATE(OpenGL_View, CView)

OpenGL_View::OpenGL_View()
{

}

OpenGL_View::~OpenGL_View()
{
}

BEGIN_MESSAGE_MAP(OpenGL_View, CView)
  ON_WM_CREATE()
  ON_WM_SIZE()
  ON_WM_DESTROY()
  ON_WM_ERASEBKGND()
END_MESSAGE_MAP()



int OpenGL_View::OnCreate(LPCREATESTRUCT lpcs) {
  if (CView::OnCreate(lpcs) == -1)
    return -1;

  InitializeOpenGL();
  return 0;
}

BOOL OpenGL_View::PreCreateWindow(CREATESTRUCT& cs) {
	// TODO: Add your specialized code here and/or call the base class
	// all OpenGL windows must have this window-style
	
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	return CView::PreCreateWindow(cs);
}


BOOL OpenGL_View::InitializeOpenGL() {
 //Get a DC for Client Area;
  m_pDC = new CClientDC(this);
  if (m_pDC == NULL) {
    MessageBox(L"Error Obtaining DC");
    return FALSE;
  }
  if (!SetWindowPixelFormat())
    return FALSE;
  // Create Rendering Context
  m_hRC = ::wglCreateContext(m_pDC->GetSafeHdc());
  if (m_hRC == 0 ){
    MessageBox(L"Error Creating RC");
    return FALSE;
  }
  //Make the RC Current
  if(::wglMakeCurrent (m_pDC->GetSafeHdc (), m_hRC)==FALSE) {
    MessageBox(L"Error making RC Current");
    return FALSE;
  }
  //Specify Black as the clear color
  ::glClearColor(0.0, 0.0f, 0.0f, 0.0f);

  //Specify the back of the buffer as clear depth
  ::glClearDepth(1.0f);

  //Enable Depth Testing
  ::glEnable(GL_DEPTH_TEST);
}



BOOL OpenGL_View::SetWindowPixelFormat() {
	static PIXELFORMATDESCRIPTOR pfd = 
    {
		sizeof(PIXELFORMATDESCRIPTOR),    // size of this pfd
		1,                                // version number
		PFD_DRAW_TO_WINDOW |              // support window
		PFD_SUPPORT_OPENGL |              // support OpenGL
		PFD_DOUBLEBUFFER,                 // double buffered
		PFD_TYPE_RGBA,                    // RGBA type
		24,                               // 24-bit color depth
		0, 0, 0, 0, 0, 0,                 // color bits ignored
		0,                                // no alpha buffer
		0,                                // shift bit ignored
		0,                                // no accumulation buffer
		0, 0, 0, 0,                       // accumulation bits ignored
		16,                               // 16-bit z-buffer
		0,                                // no stencil buffer
		0,                                // no auxiliary buffer
		PFD_MAIN_PLANE,                   // main layer
		0,                                // reserved
		0, 0, 0                           // layer masks ignored
    };
	int m_nPixelFormat = ::ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd);
  if (m_nPixelFormat == 0) {
        return FALSE;
  }
	if (::SetPixelFormat(m_pDC->GetSafeHdc(), m_nPixelFormat, &pfd) == FALSE) {
    return FALSE;
  }
  return TRUE;
}


BOOL OpenGL_View::OnEraseBkgnd(CDC* pDC) {
  return TRUE;
}

void OpenGL_View::OnDestroy() {
  CView::OnDestroy();
}

void OpenGL_View::OnSize(UINT nType, int cx, int cy) {
  CView::OnSize(nType, cx, cy);
	GLdouble aspect_ratio; 
	if ( 0 >= cx || 0 >= cy ) 
    return;

  ::gluOrtho2D(-10.0f, 10.0f, -10.0f, 10.0f); 
  // select the full client area
  ::glViewport(0, 0, cx, cy);
  // compute the aspect ratio
  // this will keep all dimension scales equal
  aspect_ratio = (GLdouble)cx/(GLdouble)cy;
  // select the projection matrix and clear it
  ::glMatrixMode(GL_PROJECTION);
  ::glLoadIdentity();
  // select the viewing volume
  ::gluPerspective(45.0f, aspect_ratio, .01f, 200.0f);
  // switch back to the modelview matrix and clear it
  ::glMatrixMode(GL_MODELVIEW);
  ::glLoadIdentity();
  //gluLookAt (0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

// OpenGL_View drawing

void OpenGL_View::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
  ::glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  RenderScene();
	// Tell OpenGL to flush its pipeline
  ::glFinish();
	// Now Swap the buffers
  ::SwapBuffers( m_pDC->GetSafeHdc() );
}


// OpenGL_View diagnostics

#ifdef _DEBUG
void OpenGL_View::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void OpenGL_View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// OpenGL_View message handlers

void OpenGL_View::RenderScene() {
  
}