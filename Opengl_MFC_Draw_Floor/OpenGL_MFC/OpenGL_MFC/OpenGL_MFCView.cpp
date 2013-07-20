
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
#include "CTargaImage.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const float BOX_SIZE = 5.0f;    // size of box
const float SPHERE_SIZE = 0.3f; // size of sphere
const float PI = 3.14159f;
const int SPHERE_RESOLUTION = 6;

const float LIGHT_POSITION[] = {-12, 10, 10, 1.0};
const float NEG_LIGHT_POSITION[] = {-12, -20, 10, 1.0};

// returns a number ranging from -1.0 to 1.0 and this value is pseudorandom
#define FRAND()   (((float)rand()-(float)rand())/RAND_MAX)
#define RAND_COLOR() ((float)rand()/RAND_MAX)


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

COpenGL_MFCView::COpenGL_MFCView() :
  x_position_(0.0f),
  y_position_(0.0f),
  value_zoom_(0.0f),
  m_angle_x_(0.0f),
  m_angle_y_(0.0f),
  m_useList(false)
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
  Init();
}

bool COpenGL_MFCView::Init() {
  glVertexPointer(3, GL_FLOAT, 0, m_positions);
  glNormalPointer(GL_FLOAT, 0, m_texCoords);
  glTexCoordPointer(3, GL_FLOAT, 0, m_texCoords);

  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

  CTargaImage image;
  image.Release();
  CString full_name = GetMoudlePath() + L"\\brick.tga";
  fstream file;
  file.open(full_name, ios::in);
  if (!file) {
    ::MessageBox(NULL, L"Can't find file to load texture", L"Error Read File", MB_OK | MB_ICONERROR);
    return false;
  }
  char * file_name = CStringToChar(full_name);
  image.Load(file_name);
  glGenTextures(1, &m_brickTexture);
  glBindTexture(GL_TEXTURE_2D, m_brickTexture);
  gluBuild2DMipmaps(GL_TEXTURE_2D, 3, image.GetWidth(), image.GetHeight(), GL_RGB, GL_UNSIGNED_BYTE, image.GetImage());

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_DEPTH_TEST);

  return true;
}

void COpenGL_MFCView::SetupProjection(int width, int height)
{
	if (height == 0)					// don't want a divide by zero
	{
		height = 1;
	}
	glViewport(0, 0, width, height);		// reset the viewport to new dimensions
	glMatrixMode(GL_PROJECTION);			  // set projection matrix current matrix
	glLoadIdentity();						       // reset projection matrix

	// calculate aspect ratio of window
	gluPerspective(75.0f,(GLfloat)width/(GLfloat)height,1.0f,1000.0f);

	glMatrixMode(GL_MODELVIEW);				// set modelview matrix
	glLoadIdentity();						      // reset modelview matrix

	m_windowWidth = width;
	m_windowHeight = height;
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
  ::gluPerspective(45.0f, aspect_ratio, .01f, 200.0f);
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


void COpenGL_MFCView::OnRButtonUp(UINT nFlags , CPoint point)
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

void COpenGL_MFCView::OnLButtonUp(UINT nFlags, CPoint point) {
  
}


void COpenGL_MFCView::OnLButtonDown(UINT nFlags, CPoint point) {
  
}

void COpenGL_MFCView::OnMouseMove(UINT nFlags, CPoint point) {
  // TODO: Add your message handler code here and/or call default
  // Check if we have captured the mouse
  CView::OnMouseMove(nFlags, point);
  if (GetCapture() == this) {
    //Increment the object rotation angles
    m_angle_x_ += (point.y - mouse_down_point_.y)/3.6;
    m_angle_y_ += (point.x - mouse_down_point_.x)/3.6;
      //Redraw the view
    InvalidateRect(NULL, FALSE);
      //Set the mouse point
    mouse_down_point_ = point;
  }
}

BOOL COpenGL_MFCView::OnMouseWheel(UINT nFlags, short zDetal, CPoint point) {
  BOOL ret = FALSE ;
  if (zDetal >=0) {
    value_zoom_ = value_zoom_ + 0.5f;
    ret = TRUE ;
  }
  else {
    value_zoom_ = value_zoom_ - 0.5f;
    ret = TRUE ;
  }
  InvalidateRect(NULL,FALSE);
  //Set the mouse point
  mouse_down_point_ = point;
  CWnd::OnMouseWheel(nFlags, zDetal, point);
  return  ret;
}
// COpenGL_MFCView message handlers
void COpenGL_MFCView::RenderScene () {
  // clear hoan toan bo dem
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  // lay ve ma tran thuc
  glLoadIdentity();

  // gluLookAt la vi tri camera de nhin vao doi tuong
  // param 1 : truc x  - neu tang x len thi ta cam giac ta dang nhin thang thi se nghieng sang ben phai
  // param 2 : truc y - neu tang y len thi ta ca giac ta dang nhin thang thi nho nguoi cao len va nhin thang xuong
  // param 3 : truc z - neu tang z len thi ta dang nhin thang ta se lui nguoi phai sau lai va nhin thang tiep
  // Tham so 4, 5, 6 la toa do cua diem nhin. tuc la mat ta nhin vao diem nao cua vat the
  // neu 4 thang thi mat dang nhin thang se liec sang ben phai
  // neu 5 tang thi mat liec sang trai
  // neu 6 tang thi mat liec xuong duoi
  // ds 7, 8 ,9 la huong nhin cua camera. (giong nhu khi chup anh ta ko chup ngang ma chup doc)
  // neu 7 tang thi ta nghieng dau cua minh sang ben phai (chu y mat van giu nguyen, vi tri giu nguyen)
  // neu 8 tang thi ta cuoi dau dan xuong duoi (giong kieu chup anh tu tren xuong duoi)
  // neu 9 tang thi nghieng dau len tren (luc nay cam giac la tu nhin tu duoi nhin len cua doi tuong) (giong nhu kieu chup anh tuoi duoi len)
  gluLookAt(0.0, 10.0f, 25.0f, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  glTranslatef(x_position_, y_position_, value_zoom_ - 10.0f);
  glRotatef(m_angle_x_, 1.0f, 0.0f, 0.0f);
  glRotatef(m_angle_y_, 0.0f, 1.0f, 0.0f);

  OnDrawCoordinate();

  if (m_useList) {
    // use the existing list if there is one
    if (m_list) {
      glCallList(m_list);
      return;
    }
    else {
      m_list = glGenLists(1);
      glNewList(m_list, GL_COMPILE_AND_EXECUTE);
    }
  }

  glLightfv(GL_LIGHT0, GL_POSITION, LIGHT_POSITION);
  DrawFloor();
  DrawReflection();
  if (m_useList)
    glEndList();
}


// this function will implement to draw Floor
void COpenGL_MFCView::DrawFloor()
{
  glNormal3f(0.0, 1.0, 0.0);
  glDepthMask(GL_FALSE);
  glEnable(GL_TEXTURE_2D);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
  glBegin(GL_QUADS);
  glTexCoord2i(0, 0);
  glVertex3f(-BOX_SIZE * 4, -BOX_SIZE, BOX_SIZE * 4);
  glTexCoord2i(5, 0);
  glVertex3f(BOX_SIZE * 4, -BOX_SIZE, BOX_SIZE * 4);
  glTexCoord2i(5, 5);
  glVertex3f(BOX_SIZE * 4, -BOX_SIZE, -BOX_SIZE * 4);
  glTexCoord2i(0, 5);
  glVertex3f(-BOX_SIZE * 4, -BOX_SIZE, -BOX_SIZE * 4);
  glEnd();
  glDisable(GL_TEXTURE_2D);
  glDepthMask(GL_TRUE);
}


void COpenGL_MFCView::DrawReflection()
{
  glLightfv(GL_LIGHT0, GL_POSITION, NEG_LIGHT_POSITION);
  glDepthMask(GL_FALSE);
  glEnable(GL_STENCIL_TEST);
  glStencilFunc(GL_ALWAYS, 1, 0xFFFFFFFF);
  glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);

  glDepthMask(GL_TRUE);
  glStencilFunc(GL_EQUAL, 1, 0xFFFFFFFF);
  glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
  glDisable(GL_STENCIL_TEST);
  glLightfv(GL_LIGHT0, GL_POSITION, LIGHT_POSITION);
}

void COpenGL_MFCView::OnDrawCoordinate() {
  glPointSize(5.0);
  glColor3f(1.0f, 1.0f, 0.0f);
  glBegin(GL_POINTS);
  glVertex3f(0.0f, 0.0f, 0.0f);
  glEnd();

	glLineWidth(4.0f);
  // truc OX +
  glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(10000.0f, 0.0f, 0.0f);
	glEnd();

  // truc OX -
	glBegin(GL_LINES);
	glVertex3f(-10000.0f, 0.0f, 0.0f);
  glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();


  // truc OY +
  glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 10000.0f, 0.0f);
	glEnd();
      // truc OY -
	glBegin(GL_LINES);
	glVertex3f(0.0f, -10000.0f, 0.0f);
  glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();

  // truc OZ +
  glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 10000.0f);
	glEnd();
    // truc OZ -
	glBegin(GL_LINES);
  glVertex3f(0.0f, 0.0f, -10000.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
}

CString COpenGL_MFCView::GetMoudlePath() {
  CString full_name = L"";
  ::GetModuleFileName(NULL, full_name.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
  full_name = full_name.Left(full_name.ReverseFind('\\'));
  return full_name;
}

char * COpenGL_MFCView::CStringToChar(CString str_path) {
  char * str = new char[MAX_PATH];
  long size = str_path.GetLength();
  memset(str, 0, size);
  wcstombs(str, str_path, size+1);
  return str;
}
