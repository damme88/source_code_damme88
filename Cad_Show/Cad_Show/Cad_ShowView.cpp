
// Cad_ShowView.cpp : implementation of the CCad_ShowView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Cad_Show.h"
#endif

#include "Cad_ShowDoc.h"
#include "Cad_ShowView.h"
#include "Cad_Point.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern Triangle GLPoint ;
// CCad_ShowView

IMPLEMENT_DYNCREATE(CCad_ShowView, CView)

BEGIN_MESSAGE_MAP(CCad_ShowView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CCad_ShowView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
  ON_WM_CREATE()
	ON_WM_SIZE()
  ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	ON_WM_RBUTTONUP()
  ON_WM_MOUSEWHEEL()
  ON_WM_MOUSEMOVE()
  ON_WM_MBUTTONDOWN()
  ON_WM_MBUTTONUP()
  ON_WM_KEYDOWN()
  ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
  ON_COMMAND_RANGE(ID_VIEW_HANDLE_START, ID_VIEW_ZOOM_OUT, OnHandleViewButton)
  ON_COMMAND_RANGE(ID_VIEW_HANDLE_MOVE_START, ID_VIEW_MOVE_RIGHT, OnHandleMoveButton)
  ON_COMMAND_RANGE(ID_VIEW_HANDLE_ROTATE_START, ID_ROTATE_RIGHT, OnHandleRotateButton)
  ON_COMMAND(ID_SHOW_BIG_COORDINATE, EnableShowBigCoordinate)
  ON_UPDATE_COMMAND_UI(ID_SHOW_BIG_COORDINATE, SetCheckBigCoordinate)
  ON_COMMAND(ID_RESET_CAD, OnHandleResetCad)
  ON_COMMAND(ID_EDIT_DELETE, DeleteCad)

END_MESSAGE_MAP()

// CCad_ShowView construction/destruction

CCad_ShowView::CCad_ShowView() :
  angle_x_(-60.0),
  angle_y_(0.0),
  angle_z_(-135.0),
  m_scaling(1.0),
  angle_x_cad_(-60.0),
  angle_y_cad_(0.0),
  angle_z_cad_(-135.0),
  x_position_(0.0),
  y_position_(0.0),
  m_nFontOffset(0),
  rotate_left_(FALSE),
  rotate_righit_(FALSE),
  middle_down_(FALSE),
  mode_cad_(0),
  red_color_(0.0f),
  green_color_(0.0f),
  blue_color_(0.0f),
  speed_rotate_(0.0f),
  is_check_rotate_(0.0),
  is_rot_x_(false),
  is_rot_y_(false),
  is_rot_z_(false),
  enable_big_coordinate_(false),
  is_check_coordiante_button_(false)
{
  m_OrthoRangeLeft = -1.5f;
	m_OrthoRangeRight = 1.5f;
	m_OrthoRangeBottom = -1.5f;
	m_OrthoRangeTop = 1.5f;
	m_OrthoRangeNear = -50.0f;
	m_OrthoRangeFar = 50.0f;
}

CCad_ShowView::~CCad_ShowView()
{
}

BOOL CCad_ShowView::PreCreateWindow(CREATESTRUCT& cs)
{
  //An OpenGL Window must be created with the following flags
  cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	return CView::PreCreateWindow(cs);
}

int CCad_ShowView::OnCreate(LPCREATESTRUCT lpCreateStruct) {
  if (CView::OnCreate(lpCreateStruct) == -1)
    return -1;
  // call InitializeOpengl
  InitializeOpenGL();
  BuildAxisesList();
  return 0;
}

BOOL CCad_ShowView::InitializeOpenGL() {
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
  ::glClearColor(0.0, 0.0f, 0.0f, 0.0f);

  //Specify the back of the buffer as clear depth
  ::glClearDepth(1.0f);

  //Enable Depth Testing
  ::glEnable(GL_DEPTH_TEST);
}


BOOL CCad_ShowView::SetupPixelFormat() {
	static PIXELFORMATDESCRIPTOR pfd = 
    {
		sizeof(PIXELFORMATDESCRIPTOR),    // size of this pfd
		1,                                // version number
		PFD_DRAW_TO_WINDOW |              // support window
		PFD_SUPPORT_OPENGL |              // support OpenGL
		PFD_DOUBLEBUFFER,                 // double buffered
		PFD_TYPE_RGBA,                    // RGBA type
		32,                               // 32-bit color depth
		8, 16, 8, 8, 8, 0,                 // color bits ignored
		0,                                // no alpha buffer
		0,                                // shift bit ignored
		64,                                // no accumulation buffer
		16, 16, 16, 0,                       // accumulation bits ignored
		32,                               // 32-bit z-buffer
		8,
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

void CCad_ShowView::OnSize(UINT nType, int cx, int cy) {
  CView::OnSize(nType, cx, cy);
	GLdouble aspect_ratio; 
	if ( 0 >= cx || 0 >= cy ) 
    return;

  //::gluOrtho2D(-10.0f, 10.0f, -10.0f, 10.0f); 
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

  glOrtho(m_OrthoRangeLeft * aspect_ratio, m_OrthoRangeRight * aspect_ratio,
		m_OrthoRangeBottom, m_OrthoRangeTop,
		m_OrthoRangeNear, m_OrthoRangeFar);

  // switch back to the modelview matrix and clear it
  ::glMatrixMode(GL_MODELVIEW);
  ::glLoadIdentity();
  //gluLookAt (0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}


BOOL CCad_ShowView::OnEraseBkgnd(CDC* pDC) {
    // TODO: Add your message handler code here and/or call default
    //comment out the original call
    //return CView::OnEraseBkgnd(pDC);
    //Tell Windows not to erase the background
    return TRUE;
}


// CCad_ShowView drawing

void CCad_ShowView::OnDraw(CDC* /*pDC*/)
{
	CCad_ShowDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
  // Clear out the color & depth buffers
  ::glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	 glClearColor(red_color_, green_color_, blue_color_, 1.0f);
	
	// TODO: add draw code for native data here
  RenderScene();
	// Tell OpenGL to flush its pipeline
  ::glFinish();
	// Now Swap the buffers
  ::SwapBuffers( m_pDC->GetSafeHdc() );
	// TODO: add draw code for native data here
	// TODO: add draw code for native data here
}

// CCad_ShowView printing
void CCad_ShowView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CCad_ShowView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCad_ShowView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCad_ShowView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CCad_ShowView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CCad_ShowView diagnostics

#ifdef _DEBUG
void CCad_ShowView::AssertValid() const
{
	CView::AssertValid();
}

void CCad_ShowView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCad_ShowDoc* CCad_ShowView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCad_ShowDoc)));
	return (CCad_ShowDoc*)m_pDocument;
}
#endif //_DEBUG



void CCad_ShowView::OnMouseMove(UINT nFlags, CPoint point) 
{
  // TODO: Add your message handler code here and/or call default
  // Check if we have captured the mouse
  CView::OnMouseMove(nFlags, point);
  if (GetCapture() == this) {
    //Increment the object rotation angles
    angle_x_ += (point.y - mouse_down_point_.y)/3.6;
    angle_z_ += (point.x - mouse_down_point_.x)/3.6;
    angle_x_cad_ += (point.y - mouse_down_point_.y)/3.6;
    angle_z_cad_ += (point.x - mouse_down_point_.x)/3.6;
      //Redraw the view
    InvalidateRect(NULL, FALSE);
      //Set the mouse point
    mouse_down_point_ = point;
  }

  if (middle_down_) {
    x_position_ -= (float)(middle_down_pos_.x -point.x)/100; 
    y_position_ += (float)(middle_down_pos_.y -point.y)/100;
    middle_down_pos_.x = point.x;
    middle_down_pos_.y = point.y;
    SendMessage(WM_PAINT, 0, 0);
    return;
  }
}

BOOL CCad_ShowView::OnMouseWheel(UINT nFlags, short zDelta, CPoint point)
{
  BOOL ret = FALSE ;
  if (zDelta >=0) {
    m_scaling *= 1.05f;
    ret = TRUE ;
  }
  else {
    m_scaling /= 1.05f;
    ret = TRUE ;
  }
  InvalidateRect(NULL,FALSE);
  //Set the mouse point
  mouse_down_point_ = point;
  CWnd::OnMouseWheel(nFlags, zDelta, point);
  return ret;
}

void CCad_ShowView::OnRButtonDown(UINT nFlags, CPoint point) 
{
  // TODO: Add your message handler code here and/or call default
  mouse_down_point_ = point;
  SetCapture();
  CView::OnLButtonDown(nFlags, point);
 
}

void CCad_ShowView::OnRButtonUp(UINT nFlags, CPoint point)  {
  // TODO: Add your message handler code here and/or call default
  mouse_down_point_ = CPoint(0, 0);
  ReleaseCapture();
  CView::OnLButtonUp(nFlags, point);
}

void CCad_ShowView::OnMButtonDown(UINT nFlags, CPoint point) {
  CView::OnMButtonDown(nFlags, point);
  SendMessage(WM_PAINT, 0, 0);

  middle_down_= TRUE;
  middle_down_pos_= point;
	cursor_ = middle_down_cursor_;
}

void CCad_ShowView::OnMButtonUp(UINT nFlags, CPoint point) {
  CView::OnMButtonUp(nFlags, point);
  middle_down_ = FALSE;
}

void CCad_ShowView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
        // TODO: Add your message handler code here and/or call default
        switch (nChar)
        {
            case VK_UP:        y_position_ = y_position_ + 0.05f;
                                          break;
            case VK_DOWN:      y_position_ = y_position_ - 0.05f;
                                          break;
            case VK_LEFT:      x_position_ = x_position_ - 0.05f;
                                          break;
            case VK_RIGHT:     x_position_ = x_position_ + 0.05f;
                                          break;
        } 
        InvalidateRect(NULL,FALSE);
        CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CCad_ShowView::RenderScene () {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  glLoadIdentity();
  glPushMatrix();

  // clear AntiAliasing
  glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glTranslatef(-2.25, -1.25, 0.0f);
  glRotatef(angle_x_, 1.0f, 0.0f, 0.0f); 
	glRotatef(angle_y_, 0.0f, 1.0f, 0.0f); 
  glRotatef(angle_z_, 0.0f, 0.0f, 1.0f);
  //PrepareAxisLabel();  // don't use draw Label Axis
  glCallList(m_nAxisesList);
  glPopMatrix();
 
  glPushMatrix();
  glRotatef(angle_x_, 1.0f, 0.0f, 0.0f); 
	glRotatef(angle_y_, 0.0f, 1.0f, 0.0f); 
  glRotatef(angle_z_, 0.0f, 0.0f, 1.0f);

    // clear AntiAliasing
  glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  OnDrawCoordinateBig();
  glPopMatrix();

  glLoadIdentity();
  glTranslatef(x_position_, y_position_, 0.0f);
  glRotatef(angle_x_cad_, 1.0f, 0.0f, 0.0f);
	glRotatef(angle_y_cad_, 0.0f, 1.0f, 0.0f);
  glRotatef(angle_z_cad_, 0.0f, 0.0f, 1.0f);

  glScalef(m_scaling, m_scaling, m_scaling);

  SetUpLight();
  DrawCad();
  DisableSetupLigting();
}

void CCad_ShowView::DrawCad() {
   if(theApp.GetStateDrawStl() == TRUE)
	 {
		 glColor3f(1.0f, 0.0f, 1.0f);
     if (mode_cad_ == POINT_MODE_CAD) {
       glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
       glPointSize(4.0f);
     } else if (mode_cad_ == WIRE_FRAME_MODE_CAD){
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glLineWidth(2.0f);
     }
     else {
       glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
     }
     int a = theApp.GetNumberOfPoint();
     for (unsigned long i = 0; i < theApp.GetNumberOfPoint(); i = i+3) {
     glBegin(GL_POLYGON);
     glNormal3f(theApp.GetNormalVector()[i/3][0], theApp.GetNormalVector()[i/3][1], theApp.GetNormalVector()[i/3][2]); 
		 glVertex3f(theApp.GetTrianglePoint()->Vertex[i][0], theApp.GetTrianglePoint()->Vertex[i][1], theApp.GetTrianglePoint()->Vertex[i][2]);
		 glVertex3f(theApp.GetTrianglePoint()->Vertex[i+1][0], theApp.GetTrianglePoint()->Vertex[i+1][1], theApp.GetTrianglePoint()->Vertex[i+1][2]);
		 glVertex3f(theApp.GetTrianglePoint()->Vertex[i+2][0], theApp.GetTrianglePoint()->Vertex[i+2][1], theApp.GetTrianglePoint()->Vertex[i+2][2]);
		 glEnd();
		 }
	 }
}

void CCad_ShowView::DeleteCad() {
  theApp.SetStatusDrawCad(FALSE);
  theApp.FreePoint();
  InvalidateRect(NULL, FALSE);
}

// draw label "X" "Y" "Z"
void CCad_ShowView::PrepareAxisLabel()
{
	GLubyte m_RasterFont[][13] = 
	{
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, 
		{0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18}, 
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x36, 0x36, 0x36}, 
		{0x00, 0x00, 0x00, 0x66, 0x66, 0xff, 0x66, 0x66, 0xff, 0x66, 0x66, 0x00, 0x00}, 
		{0x00, 0x00, 0x18, 0x7e, 0xff, 0x1b, 0x1f, 0x7e, 0xf8, 0xd8, 0xff, 0x7e, 0x18}, 
		{0x00, 0x00, 0x0e, 0x1b, 0xdb, 0x6e, 0x30, 0x18, 0x0c, 0x76, 0xdb, 0xd8, 0x70}, 
		{0x00, 0x00, 0x7f, 0xc6, 0xcf, 0xd8, 0x70, 0x70, 0xd8, 0xcc, 0xcc, 0x6c, 0x38}, 
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x1c, 0x0c, 0x0e}, 
		{0x00, 0x00, 0x0c, 0x18, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x18, 0x0c}, 
		{0x00, 0x00, 0x30, 0x18, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x18, 0x30}, 
		{0x00, 0x00, 0x00, 0x00, 0x99, 0x5a, 0x3c, 0xff, 0x3c, 0x5a, 0x99, 0x00, 0x00}, 
		{0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0xff, 0xff, 0x18, 0x18, 0x18, 0x00, 0x00}, 
		{0x00, 0x00, 0x30, 0x18, 0x1c, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, 
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00}, 
		{0x00, 0x00, 0x00, 0x38, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, 
		{0x00, 0x60, 0x60, 0x30, 0x30, 0x18, 0x18, 0x0c, 0x0c, 0x06, 0x06, 0x03, 0x03}, 
		{0x00, 0x00, 0x3c, 0x66, 0xc3, 0xe3, 0xf3, 0xdb, 0xcf, 0xc7, 0xc3, 0x66, 0x3c}, 
		{0x00, 0x00, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x78, 0x38, 0x18}, 
		{0x00, 0x00, 0xff, 0xc0, 0xc0, 0x60, 0x30, 0x18, 0x0c, 0x06, 0x03, 0xe7, 0x7e}, 
		{0x00, 0x00, 0x7e, 0xe7, 0x03, 0x03, 0x07, 0x7e, 0x07, 0x03, 0x03, 0xe7, 0x7e}, 
		{0x00, 0x00, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0xff, 0xcc, 0x6c, 0x3c, 0x1c, 0x0c}, 
		{0x00, 0x00, 0x7e, 0xe7, 0x03, 0x03, 0x07, 0xfe, 0xc0, 0xc0, 0xc0, 0xc0, 0xff}, 
		{0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xc7, 0xfe, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e}, 
		{0x00, 0x00, 0x30, 0x30, 0x30, 0x30, 0x18, 0x0c, 0x06, 0x03, 0x03, 0x03, 0xff}, 
		{0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xe7, 0x7e, 0xe7, 0xc3, 0xc3, 0xe7, 0x7e}, 
		{0x00, 0x00, 0x7e, 0xe7, 0x03, 0x03, 0x03, 0x7f, 0xe7, 0xc3, 0xc3, 0xe7, 0x7e}, 
		{0x00, 0x00, 0x00, 0x38, 0x38, 0x00, 0x00, 0x38, 0x38, 0x00, 0x00, 0x00, 0x00}, 
		{0x00, 0x00, 0x30, 0x18, 0x1c, 0x1c, 0x00, 0x00, 0x1c, 0x1c, 0x00, 0x00, 0x00}, 
		{0x00, 0x00, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc0, 0x60, 0x30, 0x18, 0x0c, 0x06}, 
		{0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00}, 
		{0x00, 0x00, 0x60, 0x30, 0x18, 0x0c, 0x06, 0x03, 0x06, 0x0c, 0x18, 0x30, 0x60}, 
		{0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x18, 0x0c, 0x06, 0x03, 0xc3, 0xc3, 0x7e}, 
		{0x00, 0x00, 0x3f, 0x60, 0xcf, 0xdb, 0xd3, 0xdd, 0xc3, 0x7e, 0x00, 0x00, 0x00}, 
		{0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3, 0xc3, 0x66, 0x3c, 0x18}, 
		{0x00, 0x00, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe}, 
		{0x00, 0x00, 0x7e, 0xe7, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e}, 
		{0x00, 0x00, 0xfc, 0xce, 0xc7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc7, 0xce, 0xfc}, 
		{0x00, 0x00, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xfc, 0xc0, 0xc0, 0xc0, 0xc0, 0xff}, 
		{0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xfc, 0xc0, 0xc0, 0xc0, 0xff}, 
		{0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xcf, 0xc0, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e}, 
		{0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3}, 
		{0x00, 0x00, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x7e}, 
		{0x00, 0x00, 0x7c, 0xee, 0xc6, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06}, 
		{0x00, 0x00, 0xc3, 0xc6, 0xcc, 0xd8, 0xf0, 0xe0, 0xf0, 0xd8, 0xcc, 0xc6, 0xc3}, 
		{0x00, 0x00, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0}, 
		{0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xdb, 0xff, 0xff, 0xe7, 0xc3}, 
		{0x00, 0x00, 0xc7, 0xc7, 0xcf, 0xcf, 0xdf, 0xdb, 0xfb, 0xf3, 0xf3, 0xe3, 0xe3}, 
		{0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xe7, 0x7e}, 
		{0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe}, 
		{0x00, 0x00, 0x3f, 0x6e, 0xdf, 0xdb, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x66, 0x3c}, 
		{0x00, 0x00, 0xc3, 0xc6, 0xcc, 0xd8, 0xf0, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe}, 
		{0x00, 0x00, 0x7e, 0xe7, 0x03, 0x03, 0x07, 0x7e, 0xe0, 0xc0, 0xc0, 0xe7, 0x7e}, 
		{0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xff}, 
		{0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3}, 
		{0x00, 0x00, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3}, 
		{0x00, 0x00, 0xc3, 0xe7, 0xff, 0xff, 0xdb, 0xdb, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3}, 
		{0x00, 0x00, 0xc3, 0x66, 0x66, 0x3c, 0x3c, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3}, 
		{0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3}, 
		{0x00, 0x00, 0xff, 0xc0, 0xc0, 0x60, 0x30, 0x7e, 0x0c, 0x06, 0x03, 0x03, 0xff}, 
		{0x00, 0x00, 0x3c, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x3c}, 
		{0x00, 0x03, 0x03, 0x06, 0x06, 0x0c, 0x0c, 0x18, 0x18, 0x30, 0x30, 0x60, 0x60}, 
		{0x00, 0x00, 0x3c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x3c}, 
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc3, 0x66, 0x3c, 0x18}, 
		{0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, 
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x38, 0x30, 0x70}, 
		{0x00, 0x00, 0x7f, 0xc3, 0xc3, 0x7f, 0x03, 0xc3, 0x7e, 0x00, 0x00, 0x00, 0x00}, 
		{0x00, 0x00, 0xfe, 0xc3, 0xc3, 0xc3, 0xc3, 0xfe, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0}, 
		{0x00, 0x00, 0x7e, 0xc3, 0xc0, 0xc0, 0xc0, 0xc3, 0x7e, 0x00, 0x00, 0x00, 0x00}, 
		{0x00, 0x00, 0x7f, 0xc3, 0xc3, 0xc3, 0xc3, 0x7f, 0x03, 0x03, 0x03, 0x03, 0x03}, 
		{0x00, 0x00, 0x7f, 0xc0, 0xc0, 0xfe, 0xc3, 0xc3, 0x7e, 0x00, 0x00, 0x00, 0x00}, 
		{0x00, 0x00, 0x30, 0x30, 0x30, 0x30, 0x30, 0xfc, 0x30, 0x30, 0x30, 0x33, 0x1e}, 
		{0x7e, 0xc3, 0x03, 0x03, 0x7f, 0xc3, 0xc3, 0xc3, 0x7e, 0x00, 0x00, 0x00, 0x00}, 
		{0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xfe, 0xc0, 0xc0, 0xc0, 0xc0}, 
		{0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x18, 0x00}, 
		{0x38, 0x6c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x00, 0x00, 0x0c, 0x00}, 
		{0x00, 0x00, 0xc6, 0xcc, 0xf8, 0xf0, 0xd8, 0xcc, 0xc6, 0xc0, 0xc0, 0xc0, 0xc0}, 
		{0x00, 0x00, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x78}, 
		{0x00, 0x00, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xfe, 0x00, 0x00, 0x00, 0x00}, 
		{0x00, 0x00, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xfc, 0x00, 0x00, 0x00, 0x00}, 
		{0x00, 0x00, 0x7c, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x7c, 0x00, 0x00, 0x00, 0x00}, 
		{0xc0, 0xc0, 0xc0, 0xfe, 0xc3, 0xc3, 0xc3, 0xc3, 0xfe, 0x00, 0x00, 0x00, 0x00}, 
		{0x03, 0x03, 0x03, 0x7f, 0xc3, 0xc3, 0xc3, 0xc3, 0x7f, 0x00, 0x00, 0x00, 0x00}, 
		{0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xe0, 0xfe, 0x00, 0x00, 0x00, 0x00}, 
		{0x00, 0x00, 0xfe, 0x03, 0x03, 0x7e, 0xc0, 0xc0, 0x7f, 0x00, 0x00, 0x00, 0x00}, 
		{0x00, 0x00, 0x1c, 0x36, 0x30, 0x30, 0x30, 0x30, 0xfc, 0x30, 0x30, 0x30, 0x00}, 
		{0x00, 0x00, 0x7e, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x00, 0x00, 0x00, 0x00}, 
		{0x00, 0x00, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3, 0xc3, 0x00, 0x00, 0x00, 0x00}, 
		{0x00, 0x00, 0xc3, 0xe7, 0xff, 0xdb, 0xc3, 0xc3, 0xc3, 0x00, 0x00, 0x00, 0x00}, 
		{0x00, 0x00, 0xc3, 0x66, 0x3c, 0x18, 0x3c, 0x66, 0xc3, 0x00, 0x00, 0x00, 0x00}, 
		{0xc0, 0x60, 0x60, 0x30, 0x18, 0x3c, 0x66, 0x66, 0xc3, 0x00, 0x00, 0x00, 0x00}, 
		{0x00, 0x00, 0xff, 0x60, 0x30, 0x18, 0x0c, 0x06, 0xff, 0x00, 0x00, 0x00, 0x00}, 
		{0x00, 0x00, 0x0f, 0x18, 0x18, 0x18, 0x38, 0xf0, 0x38, 0x18, 0x18, 0x18, 0x0f}, 
		{0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18}, 
		{0x00, 0x00, 0xf0, 0x18, 0x18, 0x18, 0x1c, 0x0f, 0x1c, 0x18, 0x18, 0x18, 0xf0}, 
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x8f, 0xf1, 0x60, 0x00, 0x00, 0x00} 
	};
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  m_nFontOffset = glGenLists(128);
  for (GLuint i = 32; i < 127; i++) {
		glNewList(i + m_nFontOffset, GL_COMPILE);
		glBitmap(8, 13, 0.0f, 0.0f, 0.0f, 0.0f, m_RasterFont[i-32]);
		glEndList();
  }
}



void CCad_ShowView::SetUpLight() {

  glEnable(GL_DEPTH_TEST); // khởi động chế độ chiều sâu
  //glDepthFunc(GL_LESS);   // thiết lập loại chiều sâu là less

	// prepare light source
	GLfloat ambient[]  = {0.7f, 0.7f, 0.7f, 1.0f};
	GLfloat diffuse[]  = {0.8f, 0.8f, 0.8f, 1.0f};
	GLfloat specular[] = {0.5f, 0.5f, 0.5f, 1.0f};
	GLfloat position[] = {10000.0f, 10000.0f, 50000.0f, 1.0f};
	GLfloat global_ambient[] = { 0.8f, 0.8f, 0.8f, 1 };

	float MatAmbientBack[]  = {0.1f, 0.2f, 0.0f, 1.0f};
	glMaterialfv(GL_BACK, GL_AMBIENT, MatAmbientBack);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE); 

 	glEnable(GL_LIGHTING);
 	glEnable(GL_LIGHT0);
  glEnable(GL_NORMALIZE); //this is good command for light

	glShadeModel(GL_SMOOTH);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 	

  /********clear AntiAliasing - Back Face*******************/
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_CULL_FACE);
  /************clear AntiAliasing*Back Face ****************/
}


void CCad_ShowView::DisableSetupLigting() {
  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
  glDisable(GL_POINT_SMOOTH);
  glDisable(GL_LINE_SMOOTH);
	glDisable(GL_BLEND);
  glDisable(GL_CULL_FACE);
  glDisable(GL_LIGHTING);
}

void CCad_ShowView::OnDrawCoordinateBig() {
  if (enable_big_coordinate_ == true) {
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-1.0*VALUE_AXIS, 0.0f, 0.0f);
    glVertex3f(VALUE_AXIS, 0.0f, 0.0f);

    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, VALUE_AXIS, 0.0f);
    glVertex3f(0.0f, -1.0*VALUE_AXIS, 0.0f);

    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, VALUE_AXIS);
    glVertex3f(0.0f, 0.0f, -1*VALUE_AXIS);
    glEnd();
  }
}

void CCad_ShowView::EnableShowBigCoordinate() {
  if (is_check_coordiante_button_ == false) {
    enable_big_coordinate_ = true;
    is_check_coordiante_button_ = true;
  } else {
    enable_big_coordinate_ = false;
    is_check_coordiante_button_ = false;
  }
  InvalidateRect(NULL, FALSE);
}

void CCad_ShowView::SetCheckBigCoordinate(CCmdUI* cmd) {
  if (is_check_coordiante_button_ == false) {
    cmd->SetCheck(false);
  } else {
    cmd->SetCheck(true);
  }
  InvalidateRect(NULL, FALSE);
}

// hàm thực hiện vẽ ra trục tọa độ oxyz 
void CCad_ShowView::BuildAxisesList()
{
  m_nAxisesList = glGenLists(1);        // gen list
	glNewList(m_nAxisesList, GL_COMPILE);

	glLineWidth(2.0f);          // make OX axis
	glBegin(GL_LINES);
	glColor3ub(255, 0, 0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.3, 0.0, 0.0);

	glColor3ub(0, 255, 0);      // make OY axis
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.3, 0.0);
			
	glColor3ub(0, 0, 255);     // make OZ axis
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.3);
	glEnd();
	

	glColor3ub(255, 255, 255);
	glRasterPos3f(0.4, 0.0, 0.0);
  PrintAxisLabel("X");          // print X label
	glRasterPos3f(0.0, 0.4, 0.0);
  PrintAxisLabel("Y");	        // print Y label
	glRasterPos3f(0.0, 0.0, 0.4);
  PrintAxisLabel("Z");          // print Z lable

  // make X Arrow 
	glPushMatrix();
	glColor3ub(255, 0, 0);
	glTranslatef(0.3, 0.0, 0.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glutSolidCone(0.02, 0.08, 10, 10);
	glPopMatrix();

  // Make Y Arrow
	glPushMatrix();
	glColor3ub(0, 255, 0);
	glTranslatef(0.0, 0.3, 0.0);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glutSolidCone(0.02, 0.08, 10, 10);
	glPopMatrix();

	//Make Z Arrow
	glPushMatrix();
	glColor3ub(0, 0, 255);
	glTranslatef(0.0, 0.0, 0.3);
	glutSolidCone(0.02, 0.08, 10, 10);
	glPopMatrix();
 glEndList();
}

void CCad_ShowView::PrintAxisLabel(const char* str)
{
  glPushAttrib(GL_LIST_BIT);
  glListBase(m_nFontOffset);
	glCallLists(static_cast<GLsizei>(strlen(str)), GL_UNSIGNED_BYTE, (GLubyte*)str);
  glPopAttrib();
}

void CCad_ShowView::SetColorForBackGround(float red_value, float green_value, float blue_value) {
  red_color_ = red_value;
  green_color_ = green_value;
  blue_color_ = blue_value;
  InvalidateRect(NULL, FALSE);
}


void CCad_ShowView::OnDestroy() {
  theApp.FreePoint();
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

// if don't use OnTime so can this use to replace
void CCad_ShowView::OnAnimation() {
  //return;
  if (is_check_rotate_ == TRUE) {
    angle_x_cad_ += speed_rotate_  + 0.5f;
    angle_z_cad_ += speed_rotate_  + 0.5f;
    if (angle_x_cad_ >= 360.0f) {
      angle_x_cad_ = 0.0f;
    } 
    if (angle_x_cad_ >= 360.0f) {
      angle_z_cad_ = 0.0f;
    }
  }
}

void CCad_ShowView::OnTimer(UINT_PTR nIDEvent) {
  //return ; // do not use Ontimer to make rotation for cad
  switch (nIDEvent) {
  case 0:
    break;
  case 1: {   // use when SetTime(1,...) is called
    SetRotateForCad();
   }
    break;
  default: break;
  }
  //CView::OnTimer(nIDEvent);
  InvalidateRect(NULL, FALSE);
}

void CCad_ShowView::SetRotateForCad() {
  if (theApp.GetTrianglePoint() != NULL ) {
    if (is_rot_x_ == true) {
      angle_x_cad_ += speed_rotate_ + 0.5f;
    }
    if (is_rot_y_ == true) {
      angle_y_cad_ += speed_rotate_ + 0.5f;
    }
    if (is_rot_z_ == true) {
      angle_z_cad_ += speed_rotate_ + 0.5f;
    }
    if (angle_x_cad_ >= 360.0f) {
      angle_x_cad_ = 0.0f;
    }
    if (angle_y_cad_ >= 360.0f) {
      angle_y_cad_ = 0.0f;
    }
    if (angle_z_cad_ >= 360.0f) {
      angle_z_cad_ = 0.0f;
    }
  }
}

void CCad_ShowView::OnHandleViewButton(UINT nID) {
  if (nID == ID_VIEW_TOP) {
    angle_x_ = 0.0f;
    angle_y_ = 0.0f;
    angle_z_ = 0.0f;
    angle_x_cad_ = 0.0f;
    angle_y_cad_ = 0.0f;
    angle_z_cad_ = 0.0f;
  }

  if (nID == ID_VIEW_BOTTOM) {
    angle_x_ = -180.0f;
    angle_y_ = 0.0f;
    angle_z_ = 0.0f;
    angle_x_cad_ = -180.0f;
    angle_y_cad_ = 0.0f;
    angle_z_cad_ = 0.0f;
  }

  if (nID == ID_VIEW_BACK) {
    angle_x_ = -90.0f;
    angle_y_ = 0.0f;
    angle_z_ = 90.0f;
    angle_x_cad_ = -90.0f;
    angle_y_cad_ = 0.0f;
    angle_z_cad_ = 90.0f;
  }

  if (nID == ID_VIEW_FRONT) {
    angle_x_ = -90.0f;
    angle_y_ = 0.0f;
    angle_z_ = -90.0f;
    angle_x_cad_ = -90.0f;
    angle_y_cad_ = 0.0f;
    angle_z_cad_ = -90.0f;
  }

  if (nID == ID_VIEW_RIGHT) {
    angle_x_ = -90.0f;
    angle_y_ = 0.0f;
    angle_z_ = -180.0f;
    angle_x_cad_ = -90.0f;
    angle_y_cad_ = 0.0f;
    angle_z_cad_ = -180.0f;
  }

  if (nID == ID_VIEW_LEFT) {
    angle_x_ = -90.0f;
    angle_y_ = 0.0f;
    angle_z_ = 0.0f;
    angle_x_cad_ = -90.0f;
    angle_y_cad_ = 0.0f;
    angle_z_cad_ = 0.0f;
  }

  if (nID == ID_VIEW_ISO) {
    angle_x_ = -60.0f;
    angle_y_ = 0.0f;
    angle_z_ = -135.0f;

    angle_x_cad_ = -60.0f;
    angle_y_cad_ = 0.0f;
    angle_z_cad_ = -135.0f;
  }

  if (nID == ID_VIEW_ZOOM_IN) {
    m_scaling *= 1.05f;  // scale is diff zoom 
  }
  if (nID == ID_VIEW_ZOOM_OUT) {
    m_scaling /= 1.05f;
  }
  InvalidateRect(NULL, FALSE);
}

void CCad_ShowView::OnHandleMoveButton(UINT nID) {
  if (theApp.GetTrianglePoint()) {
    if (nID == ID_VIEW_MOVE_DOWN) {
      y_position_ -= 0.05f;
    }
    if (nID ==ID_VIEW_MOVE_UP) {
      y_position_ += 0.05f;
    }
    if (nID == ID_VIEW_MOVE_LEFT) {
      x_position_ -= 0.05f;
    }
    if (nID == ID_VIEW_MOVE_RIGHT) {
      x_position_ += 0.05f;
    }
  }
  InvalidateRect(NULL, FALSE);
}

void CCad_ShowView::OnHandleRotateButton(UINT nID) {
  
}

void CCad_ShowView::OnHandleResetCad() {
  angle_x_ = -60.0f;
  angle_y_ = 0.0f;
  angle_z_ = -135.0f;

  angle_x_cad_ = -60.0f;
  angle_y_cad_ = 0.0f;
  angle_z_cad_ = -135.0f;

  x_position_ = 0.0f;
  y_position_ = 0.0f;
  InvalidateRect(NULL, FALSE);
}

// CCad_ShowView message handlers
