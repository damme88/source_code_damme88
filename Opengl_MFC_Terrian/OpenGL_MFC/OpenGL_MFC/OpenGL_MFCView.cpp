
// OpenGL_MFCView.cpp : implementation of the COpenGL_MFCView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "OpenGL_MFC.h"
#endif

#include "OpenGL_MFCDoc.h"
#include "OpenGL_MFCView.h"
#include "HandleBitmap.h"
#include <math.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// COpenGL_MFCView

IMPLEMENT_DYNCREATE(COpenGL_MFCView, CView)

BEGIN_MESSAGE_MAP(COpenGL_MFCView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &COpenGL_MFCView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
  ON_WM_RBUTTONDOWN()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
  ON_WM_KEYDOWN()
  ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
  ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

// COpenGL_MFCView construction/destruction

COpenGL_MFCView::COpenGL_MFCView():
  x_position_(0.0f),
  y_position_(0.0f),
  angle_x_(30.0f),
  angle_y_(-30.0f),
  angle_z_(0.0f),
  angle_x_ob_(30.0f),
  angle_y_ob_(-30.0f),
  angle_z_ob_(0.0f),
  m_OrthoRangeLeft(-1.5f),
	m_OrthoRangeRight(1.5f),
	m_OrthoRangeBottom(-1.5f),
	m_OrthoRangeTop(1.5f),
	m_OrthoRangeNear(-50.0f),
	m_OrthoRangeFar(50.0f),
  m_scaling(0.05f)
{

}

COpenGL_MFCView::~COpenGL_MFCView()
{
}

BOOL COpenGL_MFCView::PreCreateWindow(CREATESTRUCT& cs)
{
  //An OpenGL Window must be created with the following flags
  cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	return CView::PreCreateWindow(cs);
}

int COpenGL_MFCView::OnCreate(LPCREATESTRUCT lpCreateStruct) {
  if (CView::OnCreate(lpCreateStruct) == -1)
    return -1;
  // call InitializeOpengl
  InitializeOpenGL();
  return 0;
}

BOOL COpenGL_MFCView::InitializeOpenGL() {
 //Get a DC for Client Area;
  m_pDC = new CClientDC(this);
  if (m_pDC == NULL) {
    MessageBox(L"Error Obtaining DC");
    return FALSE;
  }
  if (!SetupPixelFormat())
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
  ::glClearColor(0.0f,0.0f,0.0f,0.0f);

  //Specify the back of the buffer as clear depth
  ::glClearDepth(1.0f);

  //Enable Depth Testing
  ::glEnable(GL_DEPTH_TEST);
  image_data_ = LoadBitmapFile("terrain2.bmp", &bitmap_info_header_);
  InitTerrain();
  listId_ = MakeObject();
}

BOOL COpenGL_MFCView::SetupPixelFormat() {
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

void COpenGL_MFCView::OnSize(UINT nType, int cx, int cy) {
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
  //::gluPerspective(45.0f, aspect_ratio, .01f, 200.0f);
   glOrtho(m_OrthoRangeLeft * aspect_ratio,
            m_OrthoRangeRight * aspect_ratio,
		        m_OrthoRangeBottom, m_OrthoRangeTop,
		        m_OrthoRangeNear, m_OrthoRangeFar);

  // switch back to the modelview matrix and clear it
  ::glMatrixMode(GL_MODELVIEW);
  ::glLoadIdentity();
}


BOOL COpenGL_MFCView::OnEraseBkgnd(CDC* pDC) {
    // TODO: Add your message handler code here and/or call default
    //comment out the original call
    //return CView::OnEraseBkgnd(pDC);
    //Tell Windows not to erase the background
    return TRUE;
}


// COpenGL_MFCView drawing

void COpenGL_MFCView::OnDraw(CDC* /*pDC*/)
{
	COpenGL_MFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
  // Clear out the color & depth buffers
  ::glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	// TODO: add draw code for native data here
  RenderScene();
	// Tell OpenGL to flush its pipeline
  ::glFinish();
	// Now Swap the buffers
  ::SwapBuffers( m_pDC->GetSafeHdc() );
	// TODO: add draw code for native data here
	// TODO: add draw code for native data here
}


void COpenGL_MFCView::OnDestroy() {
  CView::OnDestroy();
  // TODO: Add your message handler code here
	//Make the RC non-current
  if(::wglMakeCurrent (0,0) == FALSE) 
    MessageBox(_T("Could not make RC non-current"));
	//Delete the rendering context
  if(::wglDeleteContext (m_hRC)==FALSE) 
    MessageBox(_T("Could not delete RC"));
  //Delete the DC
  if(m_pDC)
    delete m_pDC;
  //Set it to NULL
  m_pDC = NULL;
}

// COpenGL_MFCView printing
void COpenGL_MFCView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}
#ifdef USE_FUNCTION_PRINT
BOOL COpenGL_MFCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void COpenGL_MFCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void COpenGL_MFCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

#endif //USE_FUNCTION_PRINT

void COpenGL_MFCView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// COpenGL_MFCView diagnostics

#ifdef _DEBUG
void COpenGL_MFCView::AssertValid() const
{
	CView::AssertValid();
}

void COpenGL_MFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COpenGL_MFCDoc* COpenGL_MFCView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COpenGL_MFCDoc)));
	return (COpenGL_MFCDoc*)m_pDocument;
}
#endif //_DEBUG

// COpenGL_MFCView message handlers

/*************************************************** new implement************/

void COpenGL_MFCView::OnRButtonUp(UINT nFlags, CPoint point)
{
	//ClientToScreen(&point);
	//OnContextMenu(this, point);  // Create menu cut copy paste
  mouse_down_point_ = CPoint(0, 0);
  ReleaseCapture();
  //CView::OnLButtonUp(nFlags, point);
}

void COpenGL_MFCView::OnRButtonDown(UINT nFlags, CPoint point) {
   mouse_down_point_ = point;
  SetCapture();
  //CView::OnLButtonDown(nFlags, point);
}

void COpenGL_MFCView::OnLButtonDown(UINT nFlags, CPoint point) {
  //TODO
}

void COpenGL_MFCView::OnLButtonUp(UINT nFlags, CPoint point) {
  //TODO
}

void COpenGL_MFCView::OnMouseMove(UINT nFlags, CPoint point) {
  // TODO: Add your message handler code here and/or call default
  // Check if we have captured the mouse
  CView::OnMouseMove(nFlags, point);
  if (GetCapture() == this) {
    //Increment the object rotation angles
    angle_x_ += (point.y - mouse_down_point_.y)/3.6;
    angle_y_ += (point.x - mouse_down_point_.x)/3.6;
    angle_x_ob_ += (point.y - mouse_down_point_.y)/3.6;;
    angle_y_ob_ += (point.x - mouse_down_point_.x)/3.6;;
      //Redraw the view
    InvalidateRect(NULL, FALSE);
      //Set the mouse point
    mouse_down_point_ = point;
#if 0
  old_mouse_x_ = mouse_x_;
  old_mouse_y_ = mouse_y_;
  mouse_x_ = point.x;
  mouse_y_ = point.y;

  		if (mouse_y_ < 800)
				mouse_y_ = 800;
			if (mouse_y_ > 900)
				mouse_y_ = 900;

  if ((mouse_x_ - old_mouse_x_) > 0)
    angle_ += 0.3f;
  else
    angle_ -= 0.3f;
#else
  int a = 5;
#endif
    }

}

BOOL COpenGL_MFCView::OnMouseWheel(UINT nFlags, short zDetal, CPoint point) {
  BOOL ret = FALSE ;
  if (zDetal >=0) {
    m_scaling *= 1.05f;;
    ret = TRUE ;
  } else {
    m_scaling /= 1.05f;
    ret = TRUE ;
  }
  InvalidateRect(NULL,FALSE);
  //Set the mouse point
  mouse_down_point_ = point;
  CWnd::OnMouseWheel(nFlags, zDetal, point);
  return  ret;
}

void COpenGL_MFCView::RenderScene () {
   // clear hoan toan bo dem
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glPushMatrix();
  glTranslatef(-2.75, -1.25, 0.0f);
  glRotatef(angle_x_, 1.0f, 0.0f, 0.0f);
  glRotatef(angle_y_, 0.0f, 1.0f, 0.0f);
  glRotatef(angle_z_, 0.0f, 0.0f, 1.0f);
  DrawCoordinate();
  glPopMatrix();

  glPushMatrix();
  //gluLookAt(1.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  glTranslatef(x_position_ , y_position_ , 0.0f);
  glRotatef(angle_x_ob_, 1.0f, 0.0f, 0.0f);
  glRotatef(angle_y_ob_, 0.0f, 1.0f, 0.0f);
  glRotatef(angle_z_ob_, 0.0f, 0.0f, 1.0f);
  glScalef(m_scaling, m_scaling, m_scaling);
  //OnEnableLight();      // implement lighting 
  glCallList(listId_);  // sphere is create and is called at OnCreate
  //OnDisableLight();     // disable lighting
  glPopMatrix();        // come back first postion
}

void COpenGL_MFCView::DrawCoordinate() {
  // Draw coordinate
  glColor3f(1.0f, 0.0f, 0.0f);
  glLineWidth(2.0f);
  glBegin(GL_LINES);
  glVertex3f(LENGTH_AXIS, 0.0f, 0.0f);
  glVertex3f(-1*LENGTH_AXIS, 0.0f, 0.0f);
  glEnd();

  glColor3f(0.0f, 1.0f, 0.0f);
  glLineWidth(2.0f);
  glBegin(GL_LINES);
  glVertex3f(0.0f, LENGTH_AXIS, 0.0f);
  glVertex3f(0.0f, -1*LENGTH_AXIS, 0.0f);
  glEnd();

  glColor3f(0.0f, 0.0f, 1.0f);
  glLineWidth(2.0f);
  glBegin(GL_LINES);
  glVertex3f(0.0f, 0.0, LENGTH_AXIS);
  glVertex3f(0.0f, 0.0f, -1*LENGTH_AXIS);
  glEnd();
}

void COpenGL_MFCView::OnEnableLight() {
  GLfloat light_ambient[] = {5.0f, 5.0f, 5.0f, 0.0f};
  glLightfv(GL_LIGHT0, GL_POSITION, light_ambient);

#ifdef DONT_USE_LIGHT_diff_SPEC
  GLfloat light_diff[] = {.9f, .9f, .9f, 1.0f};
  GLfloat lightK_specular[] = {1, 1, 1, 1};
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diff);
  glLightfv(GL_LIGHT0, GL_SPECULAR, lightK_specular);
#endif //DONT_USE_LIGHT_diff_SPEC

  //glShadeModel(GL_SMOOTH);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0); 
  glEnable(GL_CULL_FACE);
  glEnable(GL_NORMALIZE);
  glEnable(GL_DEPTH_TEST);

  // set material for sphere
  //GLfloat mat_ambient [] = {1.0, 1.0, 1.0, 1.0};
  //glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mat_ambient);

#ifdef DONT_USE_DIF_SPEC_SHI
  GLfloat mat_diffuse [] = {1.0, 1.0, 1.0, 1.0};
  GLfloat mat_specular [] = {1.0, 1.0, 1.0, 1.0};
  GLfloat mat_shininess [] = {50.0};
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
#endif //DONT_USE_DIF_SPEC_SHI
}

void COpenGL_MFCView::OnDisableLight() {
  glDisable(GL_LIGHTING);
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);
}

int COpenGL_MFCView::MakeObject() {
  GLuint id = glGenLists(1);  // make list to use CallList
  glNewList(id, GL_COMPILE);
  // Function draw object is called at here
  //glutSolidCone(1.0, 5.0, 16, 100);
  DrawTerrain();
  glEndList();
  return id;
}


void COpenGL_MFCView::InitTerrain() {
  for (int z = 0; z < MAP_LIMIT_Z; ++z) {
    for (int x = 0; x < MAP_LIMIT_X; ++x) {
      data_terrain_[x][z][0] = (float)x * MAP_SCALE;
      data_terrain_[x][z][1] = (float)image_data_[(z * MAP_LIMIT_Z + x) * 3];
      data_terrain_[x][z][2] = (float)z * MAP_SCALE;
    }
  }
}

void COpenGL_MFCView::DrawTerrain() {
  for (int z = 0; z < MAP_LIMIT_Z - 1; ++z) {
    glBegin(GL_TRIANGLE_STRIP);
    for (int x = 0; x < MAP_LIMIT_X -1; ++x) {
      glColor3f(data_terrain_[x][z][1]/255.0f, data_terrain_[x][z][1]/255.0f, data_terrain_[x][z][1]/255.0f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(data_terrain_[x][z][0], data_terrain_[x][z][1], data_terrain_[x][z][2]);

			// draw vertex 1
			glTexCoord2f(1.0f, 0.0f);
			glColor3f(data_terrain_[x+1][z][1]/255.0f, data_terrain_[x+1][z][1]/255.0f, data_terrain_[x+1][z][1]/255.0f);
			glVertex3f(data_terrain_[x+1][z][0], data_terrain_[x+1][z][1], data_terrain_[x+1][z][2]);

			// draw vertex 2
			glTexCoord2f(0.0f, 1.0f);
			glColor3f(data_terrain_[x][z+1][1]/255.0f, data_terrain_[x][z+1][1]/255.0f, data_terrain_[x][z+1][1]/255.0f);
			glVertex3f(data_terrain_[x][z+1][0], data_terrain_[x][z+1][1], data_terrain_[x][z+1][2]);

			// draw vertex 3
			glColor3f(data_terrain_[x+1][z+1][1]/255.0f, data_terrain_[x+1][z+1][1]/255.0f, data_terrain_[x+1][z+1][1]/255.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(data_terrain_[x+1][z+1][0], data_terrain_[x+1][z+1][1], data_terrain_[x+1][z+1][2]);
    }
    glEnd();
  }
  glFlush();
	//SwapBuffers(g_HDC);			// bring backbuffer to foreground
}